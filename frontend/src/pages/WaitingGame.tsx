import { useState, useEffect } from 'react';
import { useLocation, useNavigate, useParams } from 'react-router-dom';
import { useAuth } from '../features/auth/useAuth';
import { roomApi } from '../api/roomApi';
import { Role, type User } from '../types/user';
import { GameMode, type RoomDetails } from '../types/room';
import Toast from '../components/Toast';

const WaitingGame = () => {
	const { user } = useAuth(); // login中ユーザの情報
	const navigate = useNavigate();
	const [users, setUsers] = useState<User[]>([]);
	const [gameMode, setGameMode] = useState(GameMode.DEFAULT);
	const [showToast, setShowToast] = useState(false);
	const { id: roomId } = useParams();
	const location = useLocation();
	const [isHost, setIsHost] = useState(location.state?.hostId === user?.id);

	useEffect(() => {
		const getRoomDetails = async () => {
			try {
				const res = (await roomApi.getRoomDetails(Number(roomId))) as RoomDetails;
				setIsHost(res.host_id === user?.id);
				setGameMode(res.game_mode);
				const mappedUsers = res.members.map(member => ({
					id: member.user.id,
					name: member.user.name,
					role: member.role,
				}));
				setUsers(mappedUsers);
			} catch (error) {
				console.log(error);
			}
		};
		getRoomDetails();
	}, [user?.id, roomId]);

	const toggleRole = async (id: number) => {
		// toggleするたびにAPIを叩く、そのプレイヤーのroleを変更する
		const targetUser = users.find(user => user.id === id);
		if (!targetUser) return;
		const newRole = targetUser.role === Role.PLAYER ? Role.SPECTATOR : Role.PLAYER;
		const oldRole = targetUser.role;
		try {
			await roomApi.updateRoomMemberRole(Number(roomId), id, newRole);
			setUsers(prevUser =>
				prevUser.map(user => (user.id === id ? { ...user, role: newRole } : user))
			);
		} catch (error) {
			setUsers(prevUser =>
				prevUser.map(user => (user.id === id ? { ...user, role: oldRole } : user))
			);
			console.log(error);
		}
	};

	// ゲームモード変更 API叩く hostのみ変更可能
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
		navigator.clipboard.writeText(window.location.href || '');
		setShowToast(true);
		setTimeout(() => setShowToast(false), 1500);
	};

	return (
		<>
			<div className="min-h-screen bg-base-200 p-8 flex flex-col items-center gap-6 font-sans">
				{/* トースト通知 */}
				{showToast && <Toast type="success" message="招待URLをコピーしました！" />}
				<div>Waiting Game</div>

				{/* 参加者一覧セクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300">
					<div className="card-body p-6">
						<div className="flex justify-between items-center mb-4">
							<h2 className="card-title text-lg">参加者一覧</h2>
							<div className="flex gap-4 text-sm font-bold text-gray-500">
								<span>プレイヤー</span>
								<span>観戦者</span>
							</div>
						</div>
						<div className="flex flex-col gap-2">
							{users.map(user => (
								<div
									key={user.id}
									className="flex items-center justify-between border p-3 rounded-md bg-base-100"
								>
									<span className="font-bold">{user.name}</span>
									<div className="flex gap-4 w-32 justify-end">
										<input
											className="toggle border-indigo-600 bg-indigo-500 checked:border-orange-500 checked:bg-orange-400 checked:text-orange-800"
											type="checkbox"
											checked={user.role === Role.PLAYER}
											onChange={() => toggleRole(user.id)}
											disabled={!isHost && user.id !== user.id}
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
									? 'bg-white text-indigo-700 font-bold shadow-md scale-[1.02]'
									: 'text-gray-500 hover:bg-base-300'
							}`}
						>
							デフォルト
						</button>
						<button
							onClick={() => updateGameMode(GameMode.ONE_STROKE)}
							disabled={!isHost}
							className={`flex-1 py-3 rounded-lg transition-all duration-300 ${
								gameMode === GameMode.ONE_STROKE
									? 'bg-gradient-to-r from-orange-400 to-rose-500 text-white font-bold shadow-md scale-[1.02]'
									: 'text-gray-500 hover:bg-base-300'
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

export default WaitingGame;
