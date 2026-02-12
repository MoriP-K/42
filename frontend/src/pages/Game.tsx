import { useState, useEffect } from "react";
import { createWebSocket } from "../api/wsClient";

import Timer from "../components/game/Timer";
import Canvas from "../components/game/Canvas";
import ScoreBoard from "../components/game/ScoreBoard";
import ChatMessages, { type Message } from "../components/game/ChatMessages";
import ChatInput from "../components/game/ChatInput";

const Game = () => {
	const [socket, setSocket] = useState<WebSocket | null>(null);

	// メッセージデータ
	const [messages, setMessages] = useState<Message[]>([]);

	useEffect(() => {
		const ws = createWebSocket();

		ws.onopen = () => {
			console.log('✅ WebSocket connected');

			// TODO: ログイン機能実装後、実際のuserIdを使用
			// TODO: URLパラメータからroomIdを取得
			const tempUserId = 'user-' + Math.random().toString(36).substring(2, 9);
			const tempRoomId = 'room-test-1';

			ws.send(JSON.stringify({
				type: 'join',
				userId: tempUserId, // TODO: GET /api/me から取得
				roomId: tempRoomId, // TODO: useParams() から取得
			}));
		};

		ws.onmessage = event => {
			try {
				const data = JSON.parse(event.data);
				console.log("✉️ Received: ", data);

				if (data.type == "chat") {
					const newMessage: Message = {
						id: data.id,
						sender: data.sender,
						text: data.text,
						timestamp: new Date(data.timestamp),
					};
					setMessages(prev => [...prev, newMessage]);
				}
			} catch (error) {
				console.error("❌ Failed to parse message:", error);
			}
		};

		ws.onerror = error => {
			console.error("❌ WebSocket error: ", error);
		};

		ws.onclose = () => {
			console.log("🔌 WebSocket disconnected");
		};

		setSocket(ws);

		return () => {
			ws.close();
		};
	}, []);

	// プレイヤーデータ
	const [players] = useState([
		{ id: 1, name: "Ken", score: 0, isDrawing: true },
		{ id: 2, name: "Alice", score: 0, isDrawing: false },
		{ id: 3, name: "Bob", score: 0, isDrawing: false },
	]);

	const handleSendMessage = (text: string) => {
		if (!socket || socket.readyState !== WebSocket.OPEN) {
			console.error("❌ WebSocket not connected");
			return;
		}

		const message = {
			type: "chat",
			id: crypto.randomUUID(),
			sender: "Ken",
			text: text,
			timestamp: new Date().toISOString(),
		};

		socket.send(JSON.stringify(message));
	};

	// タイマー処理
	const totalTime = 60; // 制限時間用の変数
	const [timeLeft, setTimeLeft] = useState(totalTime); // useStateを使って, setTimeLeftでtimeLeftを更新する

	// タイマー処理: timeLeftが更新される度にuseEffectの中の処理を実行する
	useEffect(() => {
		if (timeLeft <= 0)
			// useEffectの停止条件: timeLeftが0以下になったら
			return;

		const timer = setInterval(() => {
			// 1000msごとにsetInterval()の中の処理を実行する
			setTimeLeft(prev => prev - 1); // 処理: 前のtimeLeftの値から1引く
		}, 1000);

		return () => clearInterval(timer); // useEffectが停止したら: clearInterval()でtimerを解放
	}, [timeLeft]); // timeLeftが更新される度に上の処理を再実行, その度にコンポーネントは再描画される

	// あとでWebSocketに置き換える
	// useEffect(() => {
	//     socket.on('gameState', (state) => {
	//         setTimeLeft(state.timeLeft);
	//     });
	//} []);

	return (
		<div className="min-h-screen bg-base-200">
			{/* ヘッダー */}
			<div className="navbar bg-base-100 shadow-lg">
				<div className="flex-1">
					<span className="text-xl font-bold">🎨 お絵かきの森</span>
				</div>
			</div>

			<div className="w-full max-w-[1280px] mx-auto px-8 py-8">
				<div className="grid grid-cols-1 xl:grid-cols-[2fr_1fr] gap-4">
					{/* 左カラム: 残り時間, キャンバス */}
					<div className="space-y-4">
						<Timer totalTime={totalTime} timeLeft={timeLeft} />
						<Canvas />
					</div>

					{/* 右カラム: スコアボード, コメント*/}
					<div className="space-y-4">
						<ScoreBoard players={players} />

						<div className="card bg-base-100 shadow-xl">
							<div className="card-body p-0">
								<h2 className="card-title font-mono text-base font-semibold mb-1">
									コメント
								</h2>
								<ChatMessages messages={messages} />
								<ChatInput onSendMessage={handleSendMessage} />
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
};

export default Game;
