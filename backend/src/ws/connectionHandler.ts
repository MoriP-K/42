import { WebSocket } from "ws";
import {
	RoomClient,
	WebSocketMessageType,
	ROUND_DURATION,
} from "../types/room";
import {
	CANVAS_WIDTH,
	CANVAS_HEIGHT,
	PEN_LINE_WIDTH,
	ERASER_LINE_WIDTH,
} from "../types/canvas";
import { joinRoom, leaveRoom, broadcastToRoom } from "./roomManager";
import { handleChatMessage } from "./chatHandler";
import { startTimer } from "./timerManager";

export const handleConnection = (socket: WebSocket) => {
	let currentClient: RoomClient | null = null;

	console.log("✅ Client connected");

	socket.on("message", rawMessage => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log("📥 Received: ", data);

			if (data.type === WebSocketMessageType.JOIN) {
				if (
					!data.userId ||
					typeof data.userId !== "string" ||
					data.userId.trim() === ""
				) {
					console.log("❌ Invalid userId:", data.userId);
					socket.send(
						JSON.stringify({
							type: WebSocketMessageType.ERROR,
							message: "Invalid userId",
						}),
					);
					return;
				}

				if (
					!data.roomId ||
					typeof data.roomId !== "string" ||
					data.roomId.trim() === ""
				) {
					socket.send(
						JSON.stringify({
							type: WebSocketMessageType.ERROR,
							message: "Invalid roomId",
						}),
					);
					return;
				}

				if (currentClient) {
					leaveRoom(currentClient);
				}

				currentClient = {
					socket,
					userId: data.userId,
					roomId: data.roomId,
				};

				joinRoom(currentClient);

				/**
				 * タイマー開始（仮）
				 * TODO: else if (data.type === "roundStart")のstartTimerのみを残す
				 */
				startTimer(data.roomId, ROUND_DURATION);

				return;
			}

			if (!currentClient) {
				console.error("❌ Not joined to any room");
				socket.send(
					JSON.stringify({
						type: WebSocketMessageType.ERROR,
						message: "Join a room first",
					}),
				);

				return;
			} else if (data.type === WebSocketMessageType.CHAT) {
				handleChatMessage(currentClient, data);
			} else if (data.type === WebSocketMessageType.DRAW) {
				console.log(
					`Draw from ${currentClient.userId} in room ${currentClient.roomId}`,
				);

				if (
					typeof data.x !== "number" ||
					typeof data.y !== "number" ||
					typeof data.color !== "string" ||
					typeof data.lineWidth !== "number"
				) {
					console.log("❌ Invalid draw message");
					return;
				}

				const x = Math.max(0, Math.min(CANVAS_WIDTH, data.x));
				const y = Math.max(0, Math.min(CANVAS_HEIGHT, data.y));

				const lineWidth =
					data.lineWidth === ERASER_LINE_WIDTH
						? ERASER_LINE_WIDTH
						: PEN_LINE_WIDTH;

				broadcastToRoom(
					currentClient.roomId,
					{
						type: WebSocketMessageType.DRAW,
						x: x,
						y: y,
						color: data.color,
						lineWidth: lineWidth,
						isStart: data.isStart,
					},
					socket,
				);
			} else if (data.type === WebSocketMessageType.DRAW_END) {
				broadcastToRoom(
					currentClient.roomId,
					{
						type: WebSocketMessageType.DRAW_END,
					},
					socket,
				);
			} else if (data.type === WebSocketMessageType.CLEAR) {
				broadcastToRoom(
					currentClient.roomId,
					{
						type: WebSocketMessageType.CLEAR,
					},
					socket,
				);
			} else if (data.type === WebSocketMessageType.ROUND_START) {
				if (!currentClient) {
					console.log("❌ Not joined to any room");
					return;
				}

				console.log(
					`Game start from ${currentClient.userId} in room ${currentClient.roomId}`,
				);

				broadcastToRoom(
					currentClient.roomId,
					{
						type: WebSocketMessageType.ROUND_START,
					},
					socket,
				);

				startTimer(currentClient.roomId, ROUND_DURATION);
			}
		} catch (error) {
			console.error("❌ Invalid message: ", error);
		}
	});

	socket.on("close", () => {
		if (currentClient) {
			broadcastToRoom(currentClient.roomId, {
				type: WebSocketMessageType.LEFT,
				userId: currentClient.userId,
			});

			leaveRoom(currentClient);
		}
		console.log("🔌 Client disconnected");
	});
};
