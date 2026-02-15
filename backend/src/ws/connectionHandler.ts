import { WebSocket } from "ws";
import { RoomClient } from "../types/room";
import { joinRoom, leaveRoom, broadcastToRoom } from "./roomManager";
import { handleChatMessage } from "./chatHandler";
import {
	CANVAS_WIDTH,
	CANVAS_HEIGHT,
	PEN_LINE_WIDTH,
	ERASER_LINE_WIDTH,
} from "../types/canvas";

export const handleConnection = (socket: WebSocket) => {
	let currentClient: RoomClient | null = null;

	console.log("✅ Client connected");

	socket.on("message", rawMessage => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log("📥 Received: ", data);

			if (data.type === "join") {
				if (
					!data.userId ||
					typeof data.userId !== "string" ||
					data.userId.trim() === ""
				) {
					console.log("❌ Invalid userId:", data.userId);
					socket.send(
						JSON.stringify({
							type: "error",
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
							type: "error",
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

				socket.send(
					JSON.stringify({
						type: "joined",
						roomId: data.roomId,
						userId: data.userId,
					}),
				);

				broadcastToRoom(data.roomId, {
					type: "userJoined",
					userId: data.userId,
				});

				return;
			}

			if (!currentClient) {
				console.error("❌ Not joined to any room");
				socket.send(
					JSON.stringify({
						type: "error",
						message: "Join a room first",
					}),
				);

				return;
			}

			if (data.type === "chat") {
				handleChatMessage(currentClient, data);
			} else if (data.type === "draw") {
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
						type: "draw",
						x: x,
						y: y,
						color: data.color,
						lineWidth: lineWidth,
						isStart: data.isStart,
					},
					socket,
				);
			} else if (data.type === "drawEnd") {
				console.log(`DrawEnd from ${currentClient.userId}`);

				broadcastToRoom(
					currentClient.roomId,
					{
						type: "drawEnd",
					},
					socket,
				);
			} else if (data.type === "clear") {
				console.log(`Clear from ${currentClient.userId}`);

				broadcastToRoom(
					currentClient.roomId,
					{
						type: "clear",
					},
					socket,
				);
			}
		} catch (error) {
			console.error("❌ Invalid message: ", error);
		}
	});

	socket.on("close", () => {
		if (currentClient) {
			broadcastToRoom(currentClient.roomId, {
				type: "userLeft",
				userId: currentClient.userId,
			});

			leaveRoom(currentClient);
		}
		console.log("🔌 Client disconnected");
	});
};
