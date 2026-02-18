import { useState, useEffect, useCallback } from "react";
import { useNavigate, useParams, useSearchParams } from "react-router-dom";
import { useAuth } from "../features/auth/useAuth";
import { roomApi } from "../api/roomApi";
import { GameRole, type User } from "../types/user";
import { GameMode, type RoomDetails, type RoomMember } from "../types/room";
import Toast from "../components/Toast";
import { createWebSocket } from "../api/wsClient";

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
				getRoomDetails();
			}
			if (data.type === "memberRoleUpdated") {
				getRoomDetails();
			}
			if (data.type === "gameModeUpdated") {
				setGameMode(data.mode);
			}
		};
	}, [roomId, user, getRoomDetails]);

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
		<>
			<div className="min-h-screen bg-base-200 p-8 flex flex-col items-center gap-6 font-sans">
				{/* トースト通知 */}
				{showToast && (
					<Toast type="success" message="招待URLをコピーしました！" />
				)}
				<div>Waiting Game</div>

				{/* 参加者一覧セクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300">
					<div className="card-body p-6">
						<div className="flex justify-between items-center mb-4">
							<h2 className="card-title text-lg">参加者一覧</h2>
							<div className="flex gap-4 text-sm font-bold text-gray-500">
								<span>観戦者</span>
								<span>プレイヤー</span>
							</div>
						</div>
						<div className="flex flex-col gap-2">
							{users.map(member => (
								<div
									key={member.id}
									className="flex items-center justify-between border p-3 rounded-md bg-base-100"
								>
									<span className="font-bold">
										{member.name}
									</span>
									<div className="flex gap-4 w-32 justify-end">
										<input
											className="toggle border-indigo-600 bg-indigo-500 checked:border-orange-500 checked:bg-orange-400 checked:text-orange-800"
											type="checkbox"
											checked={
												member.role === GameRole.PLAYER
											}
											onChange={() =>
												toggleRole(member.id)
											}
											disabled={
												!isHost &&
												member.id !== currentUserId
											}
										/>
									</div>
								</div>
							))}
						</div>
					</div>
				</div>

				{/* 招待URLセクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<button
						onClick={copyToClipboard}
						className="btn w-full text-md border-none bg-gradient-to-r from-emerald-500 to-teal-600 hover:from-emerald-400 hover:to-teal-500 text-white shadow-md hover:shadow-lg hover:scale-[1.01] active:scale-[0.99] transition-all duration-200"
					>
						<svg
							xmlns="http://www.w3.org/2000/svg"
							className="h-5 w-5 mr-2"
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

				{/* ゲームモードセクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<h3 className="text-md font-bold text-gray-400 mb-4 uppercase tracking-wider">
						ゲームモード
					</h3>
					<div className="bg-base-200 p-1 rounded-xl flex gap-1 shadow-inner">
						<button
							onClick={() => updateGameMode(GameMode.DEFAULT)}
							disabled={!isHost}
							className={`flex-1 py-3 rounded-lg transition-all duration-300 ${
								gameMode === GameMode.DEFAULT
									? "bg-white text-indigo-700 font-bold shadow-md scale-[1.02]"
									: "text-gray-500 hover:bg-base-300"
							}`}
						>
							デフォルト
						</button>
						<button
							onClick={() => updateGameMode(GameMode.ONE_STROKE)}
							disabled={!isHost}
							className={`flex-1 py-3 rounded-lg transition-all duration-300 ${
								gameMode === GameMode.ONE_STROKE
									? "bg-gradient-to-r from-orange-400 to-rose-500 text-white font-bold shadow-md scale-[1.02]"
									: "text-gray-500 hover:bg-base-300"
							}`}
						>
							一筆書き
						</button>
					</div>
				</div>

				{/* ゲーム開始ボタン */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<button
						onClick={() => navigate(`/prepare/${roomId}`)}
						disabled={!isHost}
						className="btn w-full text-lg border-none bg-gradient-to-r from-indigo-600 to-purple-600 hover:from-indigo-500 hover:to-purple-500 text-white shadow-xl hover:shadow-2xl hover:scale-[1.02] active:scale-[0.98] transition-all duration-200"
					>
						準備完了！
					</button>
				</div>
			</div>
		</>
	);
};

export default Waiting;
