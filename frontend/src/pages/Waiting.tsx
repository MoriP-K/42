import { useState, useEffect, useCallback, useRef } from "react";
import {
	Link,
	useNavigate,
	useParams,
	useSearchParams,
} from "react-router-dom";
import { useAuth } from "../features/auth/useAuth";
import { roomApi } from "../api/roomApi";
import { GameRole, type User } from "../types/user";
import { GameMode, type RoomDetails, type RoomMember } from "../types/room";
import Toast from "../components/Toast";
import { createWebSocket } from "../api/wsClient";
import Footer from "../components/footer/Footer";

const Waiting = () => {
	const { user } = useAuth();
	const navigate = useNavigate();
	const [users, setUsers] = useState<User[]>([]);
	const [gameMode, setGameMode] = useState(GameMode.DEFAULT);
	const [showToast, setShowToast] = useState(false);
	const { id: roomId } = useParams();
	const [isHost, setIsHost] = useState(false);
	const [invitationToken, setInvitationToken] = useState<string | null>(null);
	const [searchParams] = useSearchParams();
	const token = searchParams.get("token");
	const currentUserId = user?.id;

	const getRoomDetails = useCallback(async () => {
		try {
			const res = (await roomApi.getRoomDetails(
				Number(roomId),
			)) as RoomDetails;
			setIsHost(res.host_id === user?.id);
			setGameMode(res.game_mode);
			const mappedUsers = res.members.map((member: RoomMember) => ({
				id: member.user.id,
				name: member.user.name,
				role: member.role,
				avatar: member.user.avatar,
				isReady: member.user.isReady,
			}));
			setUsers(mappedUsers);
			setInvitationToken(res.invitation_token ?? null);
		} catch (error) {
			console.log(error);
		}
	}, [roomId, user]);

	const getRoomDetailsRef = useRef(getRoomDetails);
	useEffect(() => {
		getRoomDetailsRef.current = getRoomDetails;
	}, [getRoomDetails]);

	// 参加者一覧を取得する
	useEffect(() => {
		// eslint-disable-next-line react-hooks/set-state-in-effect
		getRoomDetails();
	}, [user?.id, roomId, getRoomDetails]);

	useEffect(() => {
		if (!roomId || !user?.id) return;
		const ws = createWebSocket();
		ws.onopen = () => {
			ws.send(
				JSON.stringify({
					type: "join",
					userId: String(user?.id),
					roomId: String(roomId),
				}),
			);
		};
		ws.onmessage = event => {
			const data = JSON.parse(event.data);
			if (data.type === "memberJoined") {
				getRoomDetailsRef.current();
			}
			if (data.type === "memberRoleUpdated") {
				getRoomDetailsRef.current();
			}
			if (data.type === "gameModeUpdated") {
				setGameMode(data.mode);
			}
		};
		return () => {
			ws.close();
		};
	}, [roomId, user?.id]);

	// URL招待で参加したメンバーをルームに追加する
	useEffect(() => {
		if (!token || !user?.id || !roomId) return;
		roomApi
			.joinByToken(token)
			.then(() => {
				getRoomDetails();
			})
			.catch(console.error);
	}, [token, user?.id, roomId, getRoomDetails]);

	const toggleRole = async (id: number) => {
		// toggleするたびにAPIを叩く、そのプレイヤーのroleを変更する
		const targetUser = users.find(user => user.id === id);
		if (!targetUser) return;
		const newRole =
			targetUser.role === GameRole.PLAYER
				? GameRole.SPECTATOR
				: GameRole.PLAYER;
		const oldRole = targetUser.role;
		try {
			await roomApi.updateRoomMemberRole(Number(roomId), id, newRole);
			setUsers(prevUser =>
				prevUser.map(user =>
					user.id === id ? { ...user, role: newRole } : user,
				),
			);
		} catch (error) {
			setUsers(prevUser =>
				prevUser.map(user =>
					user.id === id ? { ...user, role: oldRole } : user,
				),
			);
			console.log(error);
		}
	};

	// ゲームモード変更 API叩く（hostのみ変更可能）
	const updateGameMode = async (mode: string) => {
		try {
			const res = await roomApi.updateGameMode(Number(roomId), mode);
			if (res && res.game_mode === mode) {
				setGameMode(res.game_mode);
			}
		} catch (error) {
			console.log(error);
		}
	};

	const copyToClipboard = () => {
		const url = invitationToken
			? `${window.location.origin}/waiting/${roomId}?token=${invitationToken}`
			: window.location.href;
		navigator.clipboard.writeText(url);
		setShowToast(true);
		setTimeout(() => setShowToast(false), 1500);
	};

	return (
		<div className="min-h-screen bg-gradient-to-br from-indigo-900 via-purple-900 to-black text-white flex flex-col font-sans overflow-hidden">
			{/* トースト通知 */}
			{showToast && (
				<Toast type="success" message="招待URLをコピーしました！" />
			)}

			{/* Navbar */}
			<div className="navbar bg-white/10 backdrop-blur-md border-b border-white/10 shadow-lg z-20">
				<div className="flex-1">
					<Link to="/" className="btn btn-ghost text-xl text-white">
						🎨 おえかきの森
					</Link>
				</div>
			</div>

			{/* Background Decorations */}
			<div className="absolute top-10 left-10 w-64 h-64 bg-primary/20 rounded-full blur-3xl animate-pulse"></div>
			<div className="absolute bottom-10 right-10 w-96 h-96 bg-secondary/20 rounded-full blur-3xl animate-pulse delay-700"></div>

			{/* Main Content */}
			<div className="flex-1 relative z-10 flex flex-col items-center p-6 overflow-y-auto">
				<div className="w-full max-w-2xl flex flex-col gap-6 items-center">
					{/* Header */}
					<div className="text-center space-y-2">
						<h1 className="text-3xl md:text-5xl font-black bg-clip-text text-transparent bg-gradient-to-r from-cyan-400 to-purple-400">
							WAITING ROOM
						</h1>
						<p className="text-gray-400 tracking-[0.2em] font-light text-sm">
							参加者を待っています
						</p>
					</div>

					{/* 参加者一覧セクション */}
					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.01] transition-transform">
						<div className="card-body p-6">
							<h2 className="text-sm font-bold text-cyan-400 uppercase tracking-widest mb-4">
								参加者一覧
							</h2>
							<div className="flex flex-col gap-3">
								{users.map(member => (
									<div
										key={member.id}
										className="flex items-center justify-between bg-white/5 p-4 rounded-xl border border-white/10 hover:bg-white/10 transition-colors"
									>
										<div className="flex items-center gap-3">
											<div className="avatar placeholder flex items-center justify-center">
												<div className="bg-gradient-to-tr from-cyan-500 to-blue-500 text-neutral-content rounded-full w-12 h-12 flex items-center justify-center ring ring-cyan-400/50 ring-offset-2 ring-offset-transparent">
													<span className="text-xl">
														{member.avatar ?? "👤"}
													</span>
												</div>
											</div>
											<span
												className={`font-bold ${member.id === currentUserId ? "text-cyan-400" : "text-white"}`}
											>
												{member.name}
												{member.id ===
													currentUserId && (
													<span className="text-gray-400 text-xs font-normal ml-2">
														(あなた)
													</span>
												)}
											</span>
										</div>
										<div className="bg-black/30 p-0.5 rounded-lg flex gap-0.5">
											<button
												type="button"
												onClick={() => {
													if (
														member.role !==
															GameRole.SPECTATOR &&
														(isHost ||
															member.id ===
																currentUserId)
													) {
														toggleRole(member.id);
													}
												}}
												disabled={
													!isHost &&
													member.id !== currentUserId
												}
												className={`flex-1 min-w-0 py-1.5 ps-2 pe-5 text-xs font-bold rounded-md transition-all duration-300 disabled:cursor-not-allowed disabled:opacity-50 whitespace-nowrap text-center ${
													member.role ===
													GameRole.SPECTATOR
														? "bg-gradient-to-r from-purple-500 to-violet-500 text-white shadow-md"
														: "text-gray-500 hover:bg-white/10 hover:text-gray-300 disabled:hover:bg-transparent disabled:hover:text-gray-500"
												}`}
											>
												SPECTATOR
											</button>
											<button
												type="button"
												onClick={() => {
													if (
														member.role !==
															GameRole.PLAYER &&
														(isHost ||
															member.id ===
																currentUserId)
													) {
														toggleRole(member.id);
													}
												}}
												disabled={
													!isHost &&
													member.id !== currentUserId
												}
												className={`flex-1 min-w-0 py-1.5 px-4 text-xs font-bold rounded-md transition-all duration-300 disabled:cursor-not-allowed disabled:opacity-50 whitespace-nowrap text-center ${
													member.role ===
													GameRole.PLAYER
														? "bg-gradient-to-r from-cyan-500 to-blue-500 text-white shadow-md"
														: "text-gray-500 hover:bg-white/10 hover:text-gray-300 disabled:hover:bg-transparent disabled:hover:text-gray-500"
												}`}
											>
												PLAYER
											</button>
										</div>
									</div>
								))}
							</div>
						</div>
					</div>

					{/* 招待URLセクション */}
					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.01] transition-transform">
						<div className="card-body p-6">
							<button
								onClick={copyToClipboard}
								className="w-full py-4 px-6 rounded-xl font-bold text-sm uppercase tracking-wider cursor-pointer select-none transition-all duration-200 hover:scale-[1.02] hover:brightness-110 active:scale-[0.98] focus:outline-none focus:ring-2 focus:ring-cyan-400/50 bg-gradient-to-r from-emerald-500 to-teal-600 border border-emerald-400/50 text-white shadow-[0_0_20px_rgba(16,185,129,0.3)] hover:shadow-[0_0_25px_rgba(16,185,129,0.5)] flex items-center justify-center gap-2"
							>
								<svg
									xmlns="http://www.w3.org/2000/svg"
									className="h-5 w-5"
									fill="none"
									viewBox="0 0 24 24"
									stroke="currentColor"
								>
									<path
										strokeLinecap="round"
										strokeLinejoin="round"
										strokeWidth={2}
										d="M8 5H6a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2v-1M8 5a2 2 0 002 2h2a2 2 0 002-2M8 5a2 2 0 012-2h2a2 2 0 012 2m0 0h2a2 2 0 012 2v3m2 4H10m0 0l3-3m-3 3l3 3"
									/>
								</svg>
								招待URLをコピー
							</button>
						</div>
					</div>

					{/* ゲームモードセクション */}
					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.01] transition-transform">
						<div className="card-body p-6">
							<h3 className="text-sm font-bold text-gray-400 uppercase tracking-widest mb-4">
								ゲームモード
							</h3>
							<div className="bg-black/30 p-1 rounded-xl flex gap-1">
								<button
									onClick={() =>
										updateGameMode(GameMode.DEFAULT)
									}
									disabled={!isHost}
									className={`flex-1 py-3 rounded-lg transition-all duration-300 ${
										gameMode === GameMode.DEFAULT
											? "bg-gradient-to-r from-cyan-500 to-blue-500 text-white font-bold shadow-md scale-[1.02]"
											: "text-gray-500 hover:bg-white/10 hover:text-gray-300 disabled:hover:bg-transparent disabled:hover:text-gray-500"
									}`}
								>
									デフォルト
								</button>
								<button
									onClick={() =>
										updateGameMode(GameMode.ONE_STROKE)
									}
									disabled={!isHost}
									className={`flex-1 py-3 rounded-lg transition-all duration-300 ${
										gameMode === GameMode.ONE_STROKE
											? "bg-gradient-to-r from-orange-400 to-rose-500 text-white font-bold shadow-md scale-[1.02]"
											: "text-gray-500 hover:bg-white/10 hover:text-gray-300 disabled:hover:bg-transparent disabled:hover:text-gray-500"
									}`}
								>
									一筆書き
								</button>
							</div>
						</div>
					</div>

					{/* ゲーム開始ボタン */}
					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden">
						<div className="card-body p-6">
							<button
								onClick={() => navigate(`/prepare/${roomId}`)}
								disabled={!isHost}
								className="w-full py-4 px-6 rounded-xl font-bold text-lg uppercase tracking-wider cursor-pointer select-none transition-all duration-200 hover:scale-[1.02] hover:brightness-110 active:scale-[0.98] focus:outline-none focus:ring-2 focus:ring-cyan-400/50 disabled:opacity-50 disabled:cursor-not-allowed disabled:hover:scale-100 disabled:hover:brightness-100 bg-gradient-to-r from-cyan-500 to-purple-500 border border-cyan-400/50 text-white shadow-[0_0_20px_rgba(34,211,238,0.3)] hover:shadow-[0_0_25px_rgba(34,211,238,0.5)]"
							>
								準備完了！
							</button>
						</div>
					</div>
				</div>
			</div>

			<Footer />
		</div>
	);
};

export default Waiting;
