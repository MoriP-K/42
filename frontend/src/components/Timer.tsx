import { useState, useEffect } from 'react';

const Timer = () => {
	let		totalTime = 60; // 制限時間用の変数
	const	[timeLeft, setTimeLeft] = useState<number>(totalTime); // useStateを使って, setTimeLeftでtimeLeftを更新する

	// タイマー処理: timeLeftが更新される度にUseEffectの中の処理を実行する
	useEffect(() => {
		if (timeLeft <= 0) // UseEffectの停止条件: timeLeftが0以下になったら
			return ;

		const timer = setInterval(() => { // 1000msごとにsetInterval()の中の処理を実行する
			setTimeLeft(prev => prev - 1); // 処理: 前のtimeLeftの値から1引く
		}, 1000);

		return () => clearInterval(timer); // UseEffectが停止したら: clearInterval()でtimerを解放
	}, [timeLeft]); // timeLeftが更新される度に上の処理を再実行, その度にコンポーネントは再描画される

	let percentage = (timeLeft / totalTime) * 100; // 残り時間の割合を示すための変数

	// 表示
	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-4">

					<div className="flex mb-2">
						<span className="font-mono text-2xl font-semibold">残り時間</span>
					</div>
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
