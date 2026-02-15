import { useState, useEffect, useRef } from "react";

export interface DrawData {
	x: number;
	y: number;
	color: string;
	lineWidth: number;
	isStart?: boolean;
}

interface CanvasProps {
	socket: WebSocket | null;
	drawData: DrawData | null;
	clearTrigger: number;
}

const Canvas = ({ socket, drawData, clearTrigger }: CanvasProps) => {
	const canvasRef = useRef<HTMLCanvasElement>(null);
	const [isDrawing, setIsDrawing] = useState(false);
	const [isEraser, setIsEraser] = useState(false);
	const [color, setColor] = useState("#000000");

	useEffect(() => {
		const canvas = canvasRef.current;
		if (!canvas) return;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
	}, []);

	useEffect(() => {
		if (!drawData) return;

		const canvas = canvasRef.current;
		if (!canvas) return;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		if (drawData.isStart) {
			ctx.beginPath();
			ctx.moveTo(drawData.x, drawData.y);
		} else {
			ctx.strokeStyle = drawData.color;
			ctx.lineWidth = drawData.lineWidth;
			ctx.lineCap = "round";
			ctx.lineTo(drawData.x, drawData.y);
			ctx.stroke();
		}
	}, [drawData]);

	useEffect(() => {
		if (clearTrigger === 0) return;

		const canvas = canvasRef.current;
		if (!canvas) return;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
	}, [clearTrigger]);

	const startDrawing = (e: React.MouseEvent<HTMLCanvasElement>) => {
		const canvas = canvasRef.current;
		if (!canvas) return;

		const rect = canvas.getBoundingClientRect();
		const scaleX = canvas.width / rect.width;
		const scaleY = canvas.height / rect.height;
		const x = (e.clientX - rect.left) * scaleX;
		const y = (e.clientY - rect.top) * scaleY;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		ctx.beginPath();
		ctx.moveTo(x, y);
		setIsDrawing(true);

		if (socket && socket.readyState === WebSocket.OPEN) {
			const strokeColor = isEraser ? "white" : color;
			const lineWidth = isEraser ? 15 : 3;

			socket.send(
				JSON.stringify({
					type: "draw",
					x: x,
					y: y,
					color: strokeColor,
					lineWidth: lineWidth,
					isStart: true,
				}),
			);
		}
	};

	const draw = (e: React.MouseEvent<HTMLCanvasElement>) => {
		if (!isDrawing) return;

		const canvas = canvasRef.current;
		if (!canvas) return;

		const rect = canvas.getBoundingClientRect();
		const scaleX = canvas.width / rect.width;
		const scaleY = canvas.height / rect.height;
		const x = (e.clientX - rect.left) * scaleX;
		const y = (e.clientY - rect.top) * scaleY;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		const strokeColor = isEraser ? "white" : color;
		const lineWidth = isEraser ? 15 : 3;

		ctx.strokeStyle = strokeColor;
		ctx.lineWidth = lineWidth;
		ctx.lineCap = "round";
		ctx.lineTo(x, y);
		ctx.stroke();

		if (socket && socket.readyState === WebSocket.OPEN) {
			socket.send(
				JSON.stringify({
					type: "draw",
					x: x,
					y: y,
					color: strokeColor,
					lineWidth: lineWidth,
				}),
			);
		}
	};

	const stopDrawing = () => {
		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext("2d");
			if (ctx) {
				ctx.closePath();
			}
		}

		setIsDrawing(false);

		if (socket && socket.readyState === WebSocket.OPEN) {
			socket.send(
				JSON.stringify({
					type: "drawEnd",
				}),
			);
		}
	};

	const clearCanvas = () => {
		const canvas = canvasRef.current;
		if (!canvas) return;

		const ctx = canvas.getContext("2d");
		if (!ctx) return;

		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, canvas.width, canvas.height);

		if (socket && socket.readyState === WebSocket.OPEN) {
			socket.send(
				JSON.stringify({
					type: "clear",
				}),
			);
		}
	};

	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-0">
				<div className="flex items-center justify-between mb-1">
					<h2 className="card-title font-mono text-base font-semibold mb-1">
						お題: ???
					</h2>
					<button className="btn btn-sm btn-primary ml-auto">
						スキップ
					</button>
				</div>

				<canvas
					ref={canvasRef}
					width={1280}
					height={720}
					onMouseDown={startDrawing}
					onMouseMove={draw}
					onMouseUp={stopDrawing}
					onMouseLeave={stopDrawing}
					className="border border-base-300 rounded-lg bg-white cursor-crosshair w-full"
					aria-label="描画キャンバス"
				/>

				<div className="flex items-center gap-2">
					{[
						{ hex: "#000000", label: "黒" },
						{ hex: "#ef4444", label: "赤" },
						{ hex: "#3b82f6", label: "青" },
						{ hex: "#22c55e", label: "緑" },
						{ hex: "#eab308", label: "黄" },
						{ hex: "#a855f7", label: "紫" },
					].map(({ hex, label }) => (
						<button
							key={hex}
							onClick={() => {
								setColor(hex);
								setIsEraser(false);
							}}
							className={`btn btn-sm btn-circle border-2 border-transparent
								${color === hex ? "ring-2 ring-offset-2 ring-primary border-primary" : "opacity-70"}
							`}
							style={{ backgroundColor: hex }}
							aria-label={label}
						/>
					))}
					<button
						onClick={() => setIsEraser(!isEraser)}
						className={`btn btn-sm
							${isEraser ? "btn-outline btn-accent btn-active" : "btn-ghost"}
						`}
					>
						消しゴム
					</button>
					<button
						onClick={clearCanvas}
						className="btn btn-sm btn-primary ml-auto"
					>
						クリア
					</button>
				</div>
			</div>
		</div>
	);
};

export default Canvas;
