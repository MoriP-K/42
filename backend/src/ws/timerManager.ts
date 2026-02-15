import { broadcastToRoom } from "./roomManager";

interface RoomTimer {
	roomId: string;
	timeLeft: number;
	interval: NodeJS.Timeout | null;
}

// ルームごとのタイマーを管理
const timers = new Map<string, RoomTimer>();

export const startTimer = (roomId: string, duration: number = 60) => {
	// 既存のタイマーがあれば停止
	if (timers.has(roomId)) {
		stopTimer(roomId);
	}

	const timer: RoomTimer = {
		roomId,
		timeLeft: duration,
		interval: null,
	};

	timer.interval = setInterval(() => {
		timer.timeLeft -= 1;

		broadcastToRoom(roomId, {
			type: "timer",
			timeLeft: timer.timeLeft,
		});

		console.log(`Timer ${roomId}: ${timer.timeLeft}s`);

		if (timer.timeLeft <= 0) {
			stopTimer(roomId);

			broadcastToRoom(roomId, {
				type: "roundEnd",
			});
		}
	}, 1000);

	timers.set(roomId, timer);
	console.log(`Timer started for room ${roomId}: ${duration}s`);
};

export const stopTimer = (roomId: string) => {
	const timer = timers.get(roomId);
	if (!timer) return;

	if (timer.interval) {
		clearInterval(timer.interval);
	}

	timers.delete(roomId);
	console.log(`Timer stopped for room ${roomId}`);
};
