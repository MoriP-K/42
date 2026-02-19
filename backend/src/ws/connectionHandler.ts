import { WebSocket } from "ws";
import { prisma } from "../lib/prisma";
import {
	RoomClient,
	WebSocketMessageType,
	ROUND_DURATION,
} from "../types/room/room";
import {
	CANVAS_WIDTH,
	CANVAS_HEIGHT,
	PEN_LINE_WIDTH,
	ERASER_LINE_WIDTH,
} from "../types/canvas";
import { joinRoom, leaveRoom, broadcastToRoom } from "./roomManager";
import { handleChatMessage } from "./chatHandler";
import { wsUpdateReady } from "../controllers/roomController";
import { isTimerRunning, startTimer } from "./timerManager";

export const handleConnection = (socket: WebSocket) => {
	let currentClient: RoomClient | null = null;

	console.log("✅ Client connected");

	socket.on("message", async rawMessage => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log("📥 Received: ", data);

			if (data.type === WebSocketMessageType.JOIN) {
				if (!data.userId || typeof data.userId !== "number") {
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
			} else if (data.type === WebSocketMessageType.UPDATE_READY) {
				if (typeof data.isReady !== "boolean") return;
				try {
					await wsUpdateReady(
						Number(currentClient.roomId),
						Number(currentClient.userId),
						data.isReady,
					);
					broadcastToRoom(currentClient.roomId, {
						type: WebSocketMessageType.UPDATE_READY,
						userId: currentClient.userId,
						isReady: data.isReady,
					});
				} catch (error) {
					console.error("Error:", error);
					socket.send(
						JSON.stringify({
							type: WebSocketMessageType.ERROR,
							message: "Failed to update ready",
						}),
					);
				}
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

				if (isTimerRunning(currentClient.roomId)) {
					console.log(
						`⚠️ Timer already running in room ${currentClient.roomId}`,
					);
					return;
				}

				try {
					const room = await prisma.room.findUnique({
						where: { id: Number(currentClient.roomId) },
						include: { members: true },
					});

					if (!room) {
						console.log(
							`❌ Room ${currentClient.roomId} not found`,
						);
						return;
					}

					const allReady = room?.members.every(m => m.is_ready);
					if (!allReady) {
						console.log(
							`⚠️ Not all members ready in room ${currentClient.roomId}`,
						);
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
				} catch (error) {
					console.error(`❌ Failed to check room status:`, error);
				}
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
