import { broadcastToRoom } from "./roomManager";
import { RoomClient, WebSocketMessageType } from "../types/room/room";
import { WebSocket } from "ws";

export const handleChatMessage = (client: RoomClient, data: any) => {
	console.log(
		`💬 Chat from ${client.userId} in room ${client.roomId}: ${data.text}`,
	);

	if (client.role === "SPECTATOR") {
		client.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.ERROR,
				message: "Spectators cannot send chat messages",
			}),
		);
		return;
	}

	broadcastToRoom(client.roomId, {
		type: "chat",
		id: data.id,
		sender: data.sender,
		text: data.text,
		timestamp: data.timestamp,
	});
};
