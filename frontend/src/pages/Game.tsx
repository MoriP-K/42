import { useState, useEffect, useRef } from "react";
import { createWebSocket } from "../api/wsClient";
import { useNavigate, useParams } from "react-router-dom";

import { roomApi } from "../api/roomApi";
import { authApi } from "../api/authApi";
import {
	type RoomDetails,
	type RoomMember,
	type Player,
	WebSocketMessageType,
	ROUND_DURATION,
} from "../types/room";
import Timer from "../components/game/Timer";
import Canvas, { type DrawData } from "../components/game/Canvas";
import ScoreBoard from "../components/game/ScoreBoard";
import ChatMessages, { type Message } from "../components/game/ChatMessages";
import ChatInput from "../components/game/ChatInput";

const Game = () => {
	const { id } = useParams<{ id?: string }>(); // URLパラメータ取得
	const navigate = useNavigate();

	const [currentUserId, setCurrentUserId] = useState<number | null>(null);
	const currentUserIdRef = useRef<number | null>(null);
	const [currentUserName, setCurrentUserName] = useState<string | null>(null);
	const [players, setPlayers] = useState<Player[]>([]);
	const [isDrawer, setIsDrawer] = useState(false);
	const [isSpectator, setIsSpectator] = useState(false);
	const [currentWord, setCurrentWord] = useState<string | null>(null);

	const [socket, setSocket] = useState<WebSocket | null>(null);
	const [messages, setMessages] = useState<Message[]>([]); // メッセージデータ
	const [drawData, setDrawData] = useState<DrawData | null>(null); // 描画データ
	const [clearTrigger, setClearTrigger] = useState(0); // キャンバスクリア処理
	const [timeLeft, setTimeLeft] = useState(ROUND_DURATION); // setTimeLeftでtimeLeftを更新する

	useEffect(() => {
		const fetchUser = async () => {
			try {
				const user = await authApi.me();
				setCurrentUserId(user.id);
				currentUserIdRef.current = user.id;
				setCurrentUserName(user.name);
			} catch (error) {
				console.error("❌ Failed to get user:", error);
				navigate("/login");
			}
		};

		fetchUser();
	}, []);

	useEffect(() => {
		if (!currentUserId || !id) return;

		const ws = createWebSocket();

		ws.onopen = () => {
			console.log("✅ WebSocket connected");

			if (id) {
				ws.send(
					JSON.stringify({
						type: WebSocketMessageType.JOIN,
						userId: currentUserId,
						roomId: id,
					}),
				);

				checkAndStartRound(ws);
			}
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
				} else if (data.type === WebSocketMessageType.ROUND_STARTED) {
					console.log("ROUND_STARTED received:", {
						word: data.word,
						drawerId: data.drawerId,
						isDrawer: data.drawerId === currentUserId,
						currentUserId: currentUserIdRef.current,
					});
					updateRoundState(data.word, data.drawerId);
				} else if (data.type === WebSocketMessageType.ROUND_END) {
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
	}, [currentUserId, id]);

	const updateRoundState = (word: string, drawerId: number) => {
		setCurrentWord(word);
		setIsDrawer(drawerId === currentUserIdRef.current);
		setPlayers(prev =>
			prev.map(p => ({
				...p,
				isDrawing: p.id === drawerId,
			})),
		);
	};

	const checkAndStartRound = async (socket: WebSocket) => {
		if (!id) return;

		try {
			const roomData: RoomDetails = await roomApi.getRoomDetails(
				Number(id),
			);
			if (!roomData || !roomData.members) return;

			const playerData: Player[] = roomData.members
				.filter(m => m.role === "PLAYER")
				.map((m: RoomMember) => ({
					id: m.user_id,
					name: m.user.name,
					score: 0,
					isDrawing: false,
				}));

			setPlayers(playerData);

			const currentRound = roomData.rounds?.find(
				r => r.started_at !== null && r.ended_time === null,
			);

			if (currentRound && currentRound.word) {
				updateRoundState(currentRound.word, currentRound.drawer_id);
			}

			const currentMember = roomData.members.find(
				m => m.user_id === currentUserIdRef.current,
			);
			setIsSpectator(currentMember?.role === "SPECTATOR");

			const allReady = roomData.members.every(
				(m: RoomMember) => m.is_ready,
			);

			if (allReady && socket.readyState === WebSocket.OPEN) {
				socket.send(
					JSON.stringify({
						type: WebSocketMessageType.ROUND_START,
					}),
				);
			}
		} catch (error) {
			console.error("❌ Failed to check room status: ", error);
		}
	};

	const handleSendMessage = (text: string) => {
		if (!socket || socket.readyState !== WebSocket.OPEN) {
			console.error("❌ WebSocket not connected");
			return;
		}

		if (!currentUserName) {
			console.error("❌ User name not found");
			return;
		}

		const message = {
			type: WebSocketMessageType.CHAT,
			id: crypto.randomUUID(),
			sender: currentUserName,
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
							isDrawer={isDrawer}
							currentWord={currentWord}
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
								<ChatMessages
									messages={messages}
									currentUserName={currentUserName ?? ""}
								/>
								<ChatInput
									onSendMessage={handleSendMessage}
									disabled={isSpectator}
								/>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
};

export default Game;
