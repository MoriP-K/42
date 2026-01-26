import { useState, useEffect } from 'react';

import Timer from "../components/game/Timer";
import Canvas from "../components/game/Canvas";
import ScoreBoard from "../components/game/ScoreBoard";
import ChatMessages from "../components/game/ChatMessages";
import ChatInput from "../components/game/ChatInput";

const Game = () => {
	// プレイヤーデータ
	const [players] = useState([
		{ id: 1, name: 'Ken', score: 0, isDrawing: true },
		{ id: 2, name: 'Alice', score: 0, isDrawing: false },
		{ id: 3, name: 'Bob', score: 0, isDrawing: false },
	]);

	// メッセージデータ
	const [messages, setMessages] = useState([
		{ id: crypto.randomUUID(), sender: 'Alice', text: 'バナナ', timestamp: new Date()},
		{ id: crypto.randomUUID(), sender: 'Bob', text: 'みかん', timestamp: new Date()},
	]);

	const handleSendMessage = (text: string) => {
		const newMessage = {
			id: crypto.randomUUID(),
			sender: 'Ken',
			text: text,
			timestamp: new Date(),
		};
		setMessages([...messages, newMessage]);
	};

	// タイマー処理
	const totalTime = 60; // 制限時間用の変数
	const [timeLeft, setTimeLeft] = useState(totalTime); // useStateを使って, setTimeLeftでtimeLeftを更新する

	// タイマー処理: timeLeftが更新される度にuseEffectの中の処理を実行する
	useEffect(() => {
		if (timeLeft <= 0) // useEffectの停止条件: timeLeftが0以下になったら
			return ;

		const timer = setInterval(() => { // 1000msごとにsetInterval()の中の処理を実行する
			setTimeLeft(prev => prev - 1); // 処理: 前のtimeLeftの値から1引く
		}, 1000);

		return () => clearInterval(timer); // useEffectが停止したら: clearInterval()でtimerを解放
	}, [timeLeft]); // timeLeftが更新される度に上の処理を再実行, その度にコンポーネントは再描画される

	// あとでWebSocketに置き換える
	// useEffect(() => {
	//     socket.on('gameState', (state) => {
	//         setTimeLeft(state.timeLeft);
	//     });
	//} []);

	return (
		<div className="min-h-screen bg-base-200">

			{/* ヘッダー */}
			<div className="navbar bg-base-100 shadow-lg">
				<div className="flex-1">
					<span className="text-xl font-bold">🎨 お絵かきの森</span>
				</div>
			</div>

			<div className="w-full max-w-[1280px] mx-auto px-8 py-8">
				<div className="grid grid-cols-1 xl:grid-cols-[2fr_1fr] gap-4">

					{/* 左カラム: 残り時間, キャンバス */}
					<div className="space-y-4">
						<Timer totalTime={totalTime} timeLeft={timeLeft} />
						<Canvas />
					</div>

					{/* 右カラム: スコアボード, コメント*/}
					<div className="space-y-4">
						<ScoreBoard players={players} />

						<div className="card bg-base-100 shadow-xl">
							<div className="card-body p-0">
								<h2 className="card-title font-mono text-base font-semibold mb-1">コメント</h2>
								<ChatMessages messages={messages} />
								<ChatInput onSendMessage={handleSendMessage}/>
							</div>
						</div>
					</div>

				</div>
			</div>

		</div>
	);
}

export default Game;
