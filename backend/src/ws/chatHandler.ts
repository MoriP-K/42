import { broadcastToRoom } from "./roomManager";
import { RoomClient } from "../types/room";

export const handleChatMessage = (client: RoomClient, data: any) => {
	console.log(
		`💬 Chat from ${client.userId} in room ${client.roomId}: ${data.text}`,
	);

	broadcastToRoom(client.roomId, {
		type: "chat",
		id: data.id,
		sender: data.sender,
		text: data.text,
		timestamp: data.timestamp,
	});
};
