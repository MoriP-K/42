import { useState, useEffect, useRef } from 'react';

const Canvas = () => {
	const canvasRef = useRef<HTMLCanvasElement>(null);
	const [isDrawing, setIsDrawing] = useState(false);
	const [isEraser, setIsEraser] = useState(false);
	const [color, setColor] = useState("#000000");

	useEffect(() => {
		const canvas = canvasRef.current;
		if (!canvas)
			return ;

		const ctx = canvas.getContext("2d");
		if (!ctx)
			return ;

		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
	}, []);

	const startDrawing = (e: React.MouseEvent<HTMLCanvasElement>) => {
		const canvas = canvasRef.current;
		if (!canvas)
			return ;

		const rect = canvas.getBoundingClientRect();
		const scaleX = canvas.width / rect.width;
		const scaleY = canvas.height / rect.height;
		const x = (e.clientX - rect.left) * scaleX;
		const y = (e.clientY - rect.top) * scaleY;

		const ctx = canvas.getContext("2d");
		if (!ctx)
			return ;

		ctx.beginPath();
		ctx.moveTo(x, y);
		setIsDrawing(true);
	};

	const draw = (e: React.MouseEvent<HTMLCanvasElement>) => {
		if (!isDrawing)
			return ;

		const canvas = canvasRef.current;
		if (!canvas)
			return ;

		const rect = canvas.getBoundingClientRect();
		const scaleX = canvas.width / rect.width;
		const scaleY = canvas.height / rect.height;
		const x = (e.clientX - rect.left) * scaleX;
		const y = (e.clientY - rect.top) * scaleY;

		const ctx = canvas.getContext("2d");
		if (!ctx)
			return ;

		ctx.strokeStyle = isEraser ? "white" : color;
		ctx.lineWidth = isEraser ? 15 : 3;
		ctx.lineCap = "round";
		ctx.lineTo(x, y);
		ctx.stroke();
	};

	const stopDrawing = () => {
		setIsDrawing(false);
	};

	const clearCanvas = () => {
		const canvas = canvasRef.current;
		if (!canvas)
			return ;

		const ctx = canvas.getContext("2d");
		if (!ctx)
			return ;

		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
	};

	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-0">
				<div className="flex items-center justify-between mb-2">
					<h2 className="card-title font-mono text-base font-semibold mb-1">お題: ???</h2>
					<button
							className="btn btn-sm btn-primary ml-auto"
							>
						スキップ
					</button>
				</div>

				<canvas
					ref={canvasRef}
					width={1258}
					height={668}
					onMouseDown={startDrawing}
					onMouseMove={draw}
					onMouseUp={stopDrawing}
					onMouseLeave={stopDrawing}
					className="border border-base-300 rounded-lg bg-white cursor-crosshair w-full"
				/>

				<div className="flex items-center gap-2 mb-2">
					{["#000000", "#ef4444", "#3b82f6", "#22c55e", "#eab308", "#a855f7"].map(c => (
						<button
							key={c}
							onClick={() => {
								setColor(c);
								setIsEraser(false);
							}}
							className={`btn btn-sm btn-circle
								${ color === c ? "btn-active" : "btn-ghost"}
							`}
							style={{backgroundColor: c}}
						/>
					))}
					<button
						onClick={() => setIsEraser(!isEraser)}
						className={`btn btn-outline btn-accent btn-sm ${isEraser ? "btn-active" : "btn-ghost"}`}
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
