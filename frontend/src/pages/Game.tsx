import Timer from "../components/Timer"
import Canvas from "../components/Canvas"
import ScoreBoard from "../components/ScoreBoard"
import ChatMessages from "../components/ChatMessages"
import ChatInput from "../components/ChatInput"
import Footer from "../components/Footer"

const Game = () => {
	return (
		<div className="min-h-screen bg-base-200">

			{/* ヘッダー */}
			<div className="navbar bg-base-100 shadow-lg">

				<div className="flex-1">
					<span className="text-xl font-bold">🎨 お絵かきの森</span>
				</div>

			</div>

			<div className="container mx-auto p-4">
				<div className="grid grid-cols-1 lg:grid-cols-4 gap-4">

					{/* キャンバスエリア */}
					<div className="lg:col-span-3 spcae-y-4">
						<Timer />
						<Canvas />
					</div>

					<div className="space-y-4">
						<ScoreBoard />

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

			<Footer></Footer>
		</div>
	)
}

export default Game

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
