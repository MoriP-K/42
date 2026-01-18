import { useState, useEffect } from "react";

interface User {
	id: number;
	name: string;
	role: string;
}

const WaitingGame = () => {
	const [users, setUsers] = useState<User[]>([]);
	const [gameMode, setGameMode] = useState('default');

	useEffect(() => {
		setUsers([
			{id: 1, name: 'P1', role: 'player'},
			{id: 2, name: 'P2', role: 'player'},
			{id: 3, name: 'P3', role: 'player'},
			{id: 4, name: 'P4', role: 'spectator'},
		]);
	}, []);

	return (
		<>
			<div className="min-h-screen bg-base-200 p-8 flex flex-col items-center gap-6 font-sans">
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
							{users.map((user) => (
								<div key={user.id} className="flex items-center justify-between border p-3 rounded-md bg-white">
									<span>{user.name}</span>
									<div className="flex gap-4 w-32 justify-end">
										{/* チェックボックス風の表示（daisyUIのjoinを使用） */}
										<div className="join border">
											<button className={`join-item px-4 py-1 ${user.role === 'player' ? 'bg-gray-400' : 'bg-base-100'}`}>
												{user.role === 'player' && '✓'}
											</button>
											<button className={`join-item px-4 py-1 ${user.role === 'spectator' ? 'bg-gray-400' : 'bg-base-100'}`}>
												{user.role === 'spectator' && '✓'}
											</button>
										</div>
									</div>
								</div>
							))}
						</div>
					</div>
				</div>

				{/* 招待URLセクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<h3 className="text-md mb-2">招待URL</h3>
					<input
						type="text"
						readOnly
						// value={inviteUrl}
						className="input input-bordered w-full mb-3 text-center"
					/>
					{/* <button onClick={copyToClipboard} className="btn btn-outline w-full bg-white">
						URLをコピー
					</button> */}
				</div>

				{/* ゲームモードセクション */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<h3 className="text-md mb-4">ゲームモード</h3>
					<div className="flex gap-0 border rounded-md overflow-hidden">
						<button
							onClick={() => setGameMode('default')}
							className={`flex-1 py-3 transition-colors ${gameMode === 'default' ? 'bg-gray-300 font-bold' : 'bg-white'}`}
						>
							デフォルト
						</button>
						<button
							onClick={() => setGameMode('one-stroke')}
							className={`flex-1 py-3 transition-colors border-l ${gameMode === 'one-stroke' ? 'bg-gray-300 font-bold' : 'bg-white'}`}
						>
							1ストローク
						</button>
					</div>
				</div>

				{/* ゲーム開始ボタン */}
				<div className="card w-full max-w-2xl bg-base-100 shadow-xl border border-base-300 p-6 text-center">
					<h3 className="text-md mb-4">ゲーム開始ボタン</h3>
					<button className="btn btn-outline w-full bg-white text-lg">
						→プレイヤー準備画面へ
					</button>
				</div>
			</div>
		</>
	)
};

export default WaitingGame;
