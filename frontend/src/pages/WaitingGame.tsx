import { useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import { roomApi } from '../api/roomApi'

interface User {
	id: number;
	name: string;
	role: 'player' | 'spectator';
}

const WaitingGame = () => {
	const location = useLocation();
	const [me] = useState<User>({ id: 1, name: 'MORI', role: 'player' }); // ログイン後自分のデータを取得する
	const navigate = useNavigate();

	const [users, setUsers] = useState<User[]>([
		{ id: me.id, name: me.name, role: me.role },
		{ id: 2, name: 'KEN', role: 'player' },
		{ id: 3, name: 'FUNA', role: 'player' },
		{ id: 4, name: 'NUSU', role: 'player' },
	]);

	const [gameMode, setGameMode] = useState('default');
	const [showToast, setShowToast] = useState(false);
	const isHost = location.state?.hostId === me.id;
	const roomId = location.state?.roomId;

	const toggleRole = (id: number) => {
		// toggleするたびにAPIを叩く、そのプレイヤーのroleを変更する
		
		setUsers(prevUser =>
			prevUser.map(user =>
				user.id === id
					? { ...user, role: user.role === 'player' ? 'spectator' : 'player' }
					: user
			)
		);
	};

	// ゲームモード変更 API叩く hostのみ変更可能
	const updateGameMode = async (mode: string) => {
		try {
			const res = await roomApi.updateGameMode(roomId, mode);
			if (res.status === 200) {
				setGameMode(mode);
			}
		} catch (error) {
			console.log(error);
		}
	}

	const copyToClipboard = () => {
		navigator.clipboard.writeText(window.location.href || '');
		setShowToast(true);
		setTimeout(() => setShowToast(false), 1500);
	};

	return (
		<>
			<div className="min-h-screen bg-base-200 p-8 flex flex-col items-center gap-6 font-sans">
				{/* トースト通知 */}
				{showToast && (
					<div className="toast toast-top toast-center">
						<div className="alert alert-success shadow-lg border-none bg-emerald-500 text-white">
							<svg xmlns="http://www.w3.org/2000/svg" className="h-6 w-6 shrink-0 stroke-current" fill="none" viewBox="0 0 24 24">
								<path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
							</svg>
							<span className="font-bold">招待URLをコピーしました！</span>
						</div>
					</div>
				)}
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
											onChange={() => toggleRole(user.id)}
											disabled={!isHost && user.id !== me.id}
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
							onClick={() => updateGameMode('default')}
							disabled={!isHost}
							className={`flex-1 py-3 rounded-lg transition-all duration-300 ${gameMode === 'default'
								? 'bg-white text-indigo-700 font-bold shadow-md scale-[1.02]'
								: 'text-gray-500 hover:bg-base-300'
								}`}
						>
							デフォルト
						</button>
						<button
							onClick={() => updateGameMode('one-stroke')}
							disabled={!isHost}
							className={`flex-1 py-3 rounded-lg transition-all duration-300 ${gameMode === 'one-stroke'
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
