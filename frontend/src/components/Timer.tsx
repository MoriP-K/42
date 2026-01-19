import { useState, useEffect } from 'react';

const Timer = () => {
	const [timeLeft, setTimeLeft] = useState<number>(60);

	// タイマー処理
	useEffect(() => {
		if (timeLeft <= 0) // 停止条件
			return ;

		const timer = setInterval(() => {
			setTimeLeft(prev => prev - 1); // 1秒ごとに減らす
		}, 1000);

		return () => clearInterval(timer); // クリーンアップ
	}, [timeLeft]); // timeLeft変更で再実行

	// 表示
	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body">
				<div className="flex items-center justify-between">
					<span className="text-lg font-semibold">残り時間</span>
					<span className="countdown font-mono text-6xl">
						<span
							style={{
								"--value": timeLeft,
								display: "inline-block"
								 } as React.CSSProperties}
						></span>
					</span>
				</div>
			</div>
		</div>
	);
};

export default Timer;
