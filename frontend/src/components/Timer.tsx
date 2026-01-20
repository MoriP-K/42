import { useState, useEffect } from 'react';

const Timer = () => {
	const totalTime = 60;
	const [timeLeft, setTimeLeft] = useState<number>(totalTime);

	// タイマー処理
	useEffect(() => {
		if (timeLeft <= 0) // 停止条件
			return ;

		const timer = setInterval(() => {
			setTimeLeft(prev => prev - 1); // 1秒ごとに減らす
		}, 1000);

		return () => clearInterval(timer); // クリーンアップ
	}, [timeLeft]); // timeLeft変更で再実行

	const percentage = (timeLeft / totalTime) * 100;

	// 表示
	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-4">

					<div className="flex mb-2">
						<span className="text-2xl font-semibold">残り時間</span>
					</div>
					<div className="flex items-center gap-1 mb-2">
						<span className="countdown font-mono text-2xl">
							<span
								style={{ "--value": timeLeft } as React.CSSProperties}
							></span>
						</span>
						<span className="text-2xl font-semibold">秒</span>
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
