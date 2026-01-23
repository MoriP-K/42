interface TimerProps {
	timeLeft: number,
};

const Timer = ({ timeLeft }: TimerProps) => {
	const	totalTime = 15;
	let		percentage = (timeLeft / totalTime) * 100;

	// 表示
	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-0">
				<h2 className="card-title font-mono text-base font-semibold mb-1">残り時間</h2>

					<div className="flex items-center gap-1">
						<span className="countdown font-mono text-2xl font-semibold">
							<span
								style={{ "--value": timeLeft, "--digits": 2 } as React.CSSProperties}
							></span>
						</span>
						<span className="font-mono text-2xl font-semibold mr-2">秒</span>
						<div className="w-full bg-base-300 rounded-full h-3 overflow-hidden">
							<div
								className={`h-full transition-all duration-1000 ease-linear ${
									timeLeft <= 10 ? "bg-warning" : "bg-primary"
								}`}
								style={{width: `${percentage}%`}}
							></div>
						</div>
					</div>

			</div>
		</div>
	);
};

export default Timer;
