import { WebSocket } from "ws";
import { RoomClient } from "../types/room/room";
import { stopTimer } from "./timerManager";

// キー：roomId (string)
// 値: Set<RoomClient>
const rooms = new Map<string, Set<RoomClient>>();
const roomRoundState = new Map<
	string,
	{ roundId: number; word: string; drawerId: number }
>();

export const joinRoom = (client: RoomClient) => {
	// ルームが存在しなければ作成
	if (!rooms.has(client.roomId)) {
		rooms.set(client.roomId, new Set());
	}

	const room = rooms.get(client.roomId);
	if (room) {
		room.add(client);
		console.log(`✅ User ${client.userId} joined room ${client.roomId}`);
		console.log(`📈 Room ${client.roomId} now has ${room.size} members`);
	}
};

export const leaveRoom = (client: RoomClient) => {
	const room = rooms.get(client.roomId);
	if (!room) return;

	room.delete(client);
	console.log(`👋 User ${client.userId} left room ${client.roomId}`);

	// ルームが空になったらルームを削除
	if (room.size === 0) {
		rooms.delete(client.roomId);
		stopTimer(client.roomId);
		console.log(`🗑️ Room ${client.roomId} delete (empty)`);
	} else {
		console.log(`📉 Room ${client.roomId} now has ${room.size} members`);
	}
};

export const broadcastToRoom = (
	roomId: string,
	message: any,
	excludeSocket?: WebSocket,
) => {
	const room = rooms.get(roomId);
	if (!room) {
		console.log(`⚠️ Room ${roomId} not found`);
		return;
	}

	const payload = JSON.stringify(message);
	let sentCount = 0;

	room.forEach(client => {
		if (excludeSocket && client.socket === excludeSocket) return;

		if (client.socket.readyState === WebSocket.OPEN) {
			client.socket.send(payload);
			sentCount++;
		}
	});
};

export const findClientByUserId = (
	roomId: string,
	userId: number,
): RoomClient | undefined => {
	const room = rooms.get(roomId);
	if (!room) return undefined;

	for (const client of room) {
		if (client.userId === userId) return client;
	}
	return undefined;
};

export const setRoundState = (
	roomId: string,
	roundId: number,
	word: string,
	drawerId: number,
) => {
	roomRoundState.set(roomId, { roundId, word, drawerId });
};

export const getRoundState = (roomId: string) => {
	return roomRoundState.get(roomId) ?? null;
};
