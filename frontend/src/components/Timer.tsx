interface TimerProps {
	timeLeft: number,
}

const Timer = ({ timeLeft }: TimerProps) => {
	const	totalTime = 60;
	let		percentage = (timeLeft / totalTime) * 100;

	// 表示
	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-4">
				<h2 className="card-title font-mono text-2xl font-semibold">残り時間</h2>

					<div className="flex items-center gap-1 mb-2">
						<span className="countdown font-mono text-2xl font-semibold">
							<span
								style={{ "--value": timeLeft } as React.CSSProperties}
							></span>
						</span>
						<span className="font-mono text-2xl font-semibold">秒</span>
					</div>
					<div className="w-full bg-base-300 rounded-full h-3 overflow-hidden">
						<div
							className={`h-full transition-all duration-1000 ease-linear ${
								timeLeft <= 10 ? 'bg-error' : 'bg-primary'
							}`}
							style={{width: `${percentage}%`}}
						></div>
					</div>

			</div>
		</div>
	);
};

export default Timer;
