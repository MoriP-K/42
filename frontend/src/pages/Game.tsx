import { useState, useEffect } from "react";
import { createWebSocket } from "../api/wsClient";

import Timer from "../components/game/Timer";
import Canvas, { type DrawData } from "../components/game/Canvas";
import ScoreBoard from "../components/game/ScoreBoard";
import ChatMessages, { type Message } from "../components/game/ChatMessages";
import ChatInput from "../components/game/ChatInput";
import { WebSocketMessageType, ROUND_DURATION } from "../types/room";

const Game = () => {
	const [socket, setSocket] = useState<WebSocket | null>(null);
	const [messages, setMessages] = useState<Message[]>([]); // メッセージデータ
	const [drawData, setDrawData] = useState<DrawData | null>(null); // 描画データ
	const [clearTrigger, setClearTrigger] = useState(0); // キャンバスクリア処理
	const [timeLeft, setTimeLeft] = useState(ROUND_DURATION); // useStateを使って, setTimeLeftでtimeLeftを更新する

	// プレイヤーデータ
	const [players] = useState([
		{ id: 1, name: "Ken", score: 0, isDrawing: true },
		{ id: 2, name: "Alice", score: 0, isDrawing: false },
		{ id: 3, name: "Bob", score: 0, isDrawing: false },
	]);

	useEffect(() => {
		const ws = createWebSocket();

		ws.onopen = () => {
			console.log("✅ WebSocket connected");

			// TODO: ログイン機能実装後、実際のuserIdを使用
			// TODO: URLパラメータからroomIdを取得
			const tempUserId =
				"user-" + Math.random().toString(36).substring(2, 9);
			const tempRoomId = "room-test-2";

			ws.send(
				JSON.stringify({
					type: WebSocketMessageType.JOIN,
					userId: tempUserId, // TODO: GET /api/me から取得
					roomId: tempRoomId, // TODO: useParams() から取得
				}),
			);
		};

		ws.onmessage = event => {
			try {
				const data = JSON.parse(event.data);

				if (data.type === WebSocketMessageType.CHAT) {
					const newMessage: Message = {
						id: data.id,
						sender: data.sender,
						text: data.text,
						timestamp: new Date(data.timestamp),
					};
					setMessages(prev => [...prev, newMessage]);
				} else if (data.type === WebSocketMessageType.DRAW) {
					setDrawData({
						x: data.x,
						y: data.y,
						color: data.color,
						lineWidth: data.lineWidth,
						isStart: data.isStart,
					});
				} else if (data.type === WebSocketMessageType.DRAW_END) {
					setDrawData(null);
				} else if (data.type === WebSocketMessageType.CLEAR) {
					setClearTrigger(prev => prev + 1);
				} else if (data.type === WebSocketMessageType.TIMER) {
					setTimeLeft(data.timeLeft);
				} else if (data.type === WebSocketMessageType.ROUND_START) {
					console.log("Round started!");
					/**
					 * TODO: フロント側のゲーム開始時の処理（お題表示など）
					 */
				} else if (data.type === WebSocketMessageType.ROUND_END) {
					console.log("Round Ended!");
					/**
					 * TODO: ラウンド終了時の処理（Prepare画面に戻るかResult画面に遷移するかなど）
					 */
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

		// eslint-disable-next-line react-hooks/set-state-in-effect
		setSocket(ws);

		return () => {
			ws.close();
			setSocket(null);
		};
	}, []);

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
						<Timer totalTime={ROUND_DURATION} timeLeft={timeLeft} />
						<Canvas
							socket={socket}
							drawData={drawData}
							clearTrigger={clearTrigger}
						/>
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
