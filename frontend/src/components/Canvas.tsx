import { useState, useEffect, useRef } from 'react';

const Canvas = () => {
	const canvasRef = useRef<HTMLCanvasElement>(null);
	const [isDrawing, setIsDrawing] = useState(false);
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

		ctx.strokeStyle = color;
		ctx.lineWidth = 3;
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
				<h2 className="card-title font-mono text-base font-semibold mb-1">お題: ???</h2>

				<canvas
					ref={canvasRef}
					width={699}
					height={384}
					onMouseDown={startDrawing}
					onMouseMove={draw}
					onMouseUp={stopDrawing}
					onMouseLeave={stopDrawing}
					className="border border-base-300 rounded-lg bg-white cursor-crosshair w-full"
				/>

				<div className="flex gap-2 mb-2">
					{["#000000", "#ef4444", "#3b82f6", "#22c55e", "#eab308", "#a855f7"].map(c => (
						<button
							key={c}
							onClick={() => setColor(c)}
							className={`btn-sm btn-circle border-2 ${
								color === c ? "border-base-content" : "border-base-300"
							}`}
							style={{backgroundColor: c}}
						/>
					))}
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
