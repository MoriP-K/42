import { useState, useEffect } from 'react';
import Timer from "../components/Timer";
import Canvas from "../components/Canvas";
import ScoreBoard from "../components/ScoreBoard";
import ChatMessages from "../components/ChatMessages";
import ChatInput from "../components/ChatInput";

const Game = () => {
	// プレイヤーデータ
	const [players, setPlayers] = useState([
	{ id: 1, name: 'Ken', score: 5, isDrawing: true },
	{ id: 2, name: 'Alice', score: 3, isDrawing: false },
	{ id: 3, name: 'Bob', score: 6, isDrawing: false },
	]);

	// タイマー処理
	const	totalTime = 60; // 制限時間用の変数
	const	[timeLeft, setTimeLeft] = useState(totalTime); // useStateを使って, setTimeLeftでtimeLeftを更新する

	// タイマー処理: timeLeftが更新される度にUseEffectの中の処理を実行する
	useEffect(() => {
		if (timeLeft <= 0) // UseEffectの停止条件: timeLeftが0以下になったら
			return ;

		const timer = setInterval(() => { // 1000msごとにsetInterval()の中の処理を実行する
			setTimeLeft(prev => prev - 1); // 処理: 前のtimeLeftの値から1引く
		}, 1000);

		return () => clearInterval(timer); // UseEffectが停止したら: clearInterval()でtimerを解放
	}, [timeLeft]); // timeLeftが更新される度に上の処理を再実行, その度にコンポーネントは再描画される

	// あとでWebSocketに置き換える
	// UseEffect(() => {
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
				<div className="grid grid-cols-1 xl:grid-cols-[763px_373px] gap-4">

					{/* 左カラム: 残り時間, キャンバス */}
					<div className="space-y-4">
						<Timer timeLeft={timeLeft} />
						<Canvas />
					</div>

					{/* 右カラム: スコアボード, チャットボード */}
					<div className="space-y-4">
						<ScoreBoard players={players} />

						<div className="card bg-base-100 shadow-xl">
							<div className="card-body">
								<h2 className="card-title">チャット</h2>
								<ChatMessages />
								<ChatInput />
							</div>
						</div>
					</div>

				</div>
			</div>

		</div>
	);
}

export default Game;

// import { useRef, useState, useEffect } from 'react'

// function Game() {
// 	const canvasRef = useRef<HTMLCanvasElement>(null)
// 	const [isDrawing, setIsDrawing] = useState(false)
// 	const [color, setColor] = useState('#ef4444')

// 	useEffect(() => {
// 		const canvas = canvasRef.current
// 		if (!canvas) return

// 		const ctx = canvas.getContext('2d')
// 		if (!ctx) return

// 		// Canvas初期化
// 		ctx.fillStyle = 'white'
// 		ctx.fillRect(0, 0, canvas.width, canvas.height)
// 	}, [])

// 	const startDrawing = (e: React.MouseEvent<HTMLCanvasElement>) => {
// 		setIsDrawing(true)
// 		const canvas = canvasRef.current
// 		if (!canvas) return

// 		const rect = canvas.getBoundingClientRect()
// 		const scaleX = canvas.width / rect.width
// 		const scaleY = canvas.height / rect.height
// 		const x = (e.clientX - rect.left) * scaleX
// 		const y = (e.clientY - rect.top) * scaleY

// 		const ctx = canvas.getContext('2d')
// 		if (!ctx) return

// 		ctx.beginPath()
// 		ctx.moveTo(x, y)
//   	}

// 	const draw = (e: React.MouseEvent<HTMLCanvasElement>) => {
// 		if (!isDrawing) return

// 		const canvas = canvasRef.current
// 		if (!canvas) return

// 		const rect = canvas.getBoundingClientRect()
// 		const scaleX = canvas.width / rect.width
// 		const scaleY = canvas.height / rect.height
// 		const x = (e.clientX - rect.left) * scaleX
// 		const y = (e.clientY - rect.top) * scaleY

// 		const ctx = canvas.getContext('2d')
// 		if (!ctx) return

// 		ctx.strokeStyle = color
// 		ctx.lineWidth = 3
// 		ctx.lineCap = 'round'
// 		ctx.lineTo(x, y)
// 		ctx.stroke()
// 	}

// 	const stopDrawing = () => {
// 		setIsDrawing(false)
// 	}

// 	const clearCanvas = () => {
// 		const canvas = canvasRef.current
// 		if (!canvas) return

// 		const ctx = canvas.getContext('2d')
// 		if (!ctx) return

// 		ctx.fillStyle = 'white'
// 		ctx.fillRect(0, 0, canvas.width, canvas.height)
// 	}

// 	return (
// 		<div className="min-h-screen bg-base-200">
// 			<div className="navbar bg-base-100 shadow-lg">
// 				<div className="flex-1">
// 					<span className="text-xl font-bold">🎨 おえかきの森</span>
// 				</div>
// 				<div className="flex-none">
// 					<span className="text-lg font-semibold">残り時間: 60秒</span>
// 				</div>
// 			</div>

// 			<div className="container mx-auto p-4">
// 				<div className="grid grid-cols-1 lg:grid-cols-4 gap-4">
// 					<div className="lg:col-span-3">
// 						<div className="card bg-base-100 shadow-xl">
// 							<div className="card-body">
// 								<h2 className="card-title">お題: ???</h2>

// 								<canvas
// 									ref={canvasRef}
// 									width={800}
// 									height={600}
// 									className="border-2 border-base-300 rounded-lg cursor-crosshair"
// 									onMouseDown={startDrawing}
// 									onMouseMove={draw}
// 									onMouseUp={stopDrawing}
// 									onMouseLeave={stopDrawing}
// 								/>

// 								{/* カラーパレット */}
// 								<div className="flex gap-2 mt-4">
// 									<button
// 									className="btn btn-circle btn-error"
// 									onClick={() => setColor('#ef4444')}
// 									/>
// 									<button
// 									className="btn btn-circle btn-primary"
// 									onClick={() => setColor('#3b82f6')}
// 									/>
// 									<button
// 									className="btn btn-circle btn-success"
// 									onClick={() => setColor('#22c55e')}
// 									/>
// 									<button
// 									className="btn btn-circle btn-warning"
// 									onClick={() => setColor('#eab308')}
// 									/>
// 									<button
// 									className="btn btn-circle"
// 									style={{ backgroundColor: '#000' }}
// 									onClick={() => setColor('#000000')}
// 									/>

// 									<div className="divider divider-horizontal" />
// 										<button
// 										className="btn btn-error btn-outline"
// 										onClick={clearCanvas}
// 										>
// 										クリア
// 										</button>
// 								</div>
// 							</div>
// 						</div>
// 					</div>

// 					{/* サイドバー（前と同じ） */}
// 					<div className="space-y-4">
// 						<div className="card bg-base-100 shadow-xl">
// 							<div className="card-body">
// 							<h2 className="card-title">プレイヤー</h2>

// 							<div className="flex items-center gap-3 p-3 bg-base-200 rounded-lg">
// 								<div className="avatar placeholder">
// 								<div className="bg-primary text-primary-content rounded-full w-12">
// 									<span>K</span>
// 								</div>
// 								</div>
// 								<div className="flex-1">
// 								<p className="font-bold">Ken</p>
// 								<p className="text-sm opacity-70">250pt</p>
// 								</div>
// 								<div className="badge badge-success">描画中</div>
// 							</div>

// 							<div className="flex items-center gap-3 p-3 bg-base-200 rounded-lg">
// 								<div className="avatar placeholder">
// 								<div className="bg-secondary text-secondary-content rounded-full w-12">
// 									<span>A</span>
// 								</div>
// 								</div>
// 								<div className="flex-1">
// 								<p className="font-bold">Alice</p>
// 								<p className="text-sm opacity-70">180pt</p>
// 								</div>
// 							</div>
// 							</div>
// 						</div>

// 						<div className="card bg-base-100 shadow-xl">
// 							<div className="card-body">
// 							<h2 className="card-title">チャット</h2>

// 							<div className="space-y-2 h-64 overflow-y-auto">
// 								<div className="chat chat-start">
// 								<div className="chat-bubble">犬？</div>
// 								</div>
// 								<div className="chat chat-end">
// 								<div className="chat-bubble chat-primary">猫！</div>
// 								</div>
// 							</div>

// 							<div className="join w-full">
// 								<input
// 								className="input input-bordered join-item flex-1"
// 								placeholder="答えを入力..."
// 								/>
// 								<button className="btn btn-primary join-item">送信</button>
// 							</div>
// 							</div>
// 						</div>
// 					</div>
// 				</div>
// 			</div>
// 		</div>
// 	)
// }

// export default Game
