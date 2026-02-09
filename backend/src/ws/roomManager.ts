import { WebSocket } from 'ws';
import { RoomClient } from '../types/room/room';

// キー：roomId (string)
// 値: Set<RoomClient>
const rooms = new Map<string, Set<RoomClient>>()

export const joinRoom = (client: RoomClient) => {
	// ルームが存在しなければ作成
	if (!rooms.has(client.roomId)) {
		rooms.set(client.roomId, new Set());
	}

	const room = rooms.get(client.roomId);
	if (room) {
		room.add(client);
		console.log(`✅ User ${client.userId} joined room ${client.roomId}`);
		console.log(`📈 Room ${client.roomId} now has ${rooms.size} members`);
	}

};

export const leaveRoom = (client: RoomClient) => {
	const room = rooms.get(client.roomId);
	if (!room)
		return ;

	room.delete(client);
	console.log(`👋 User ${client.userId} left room ${client.roomId}`);

	// ルームが空になったらルームを削除
	if (room.size === 0) {
		rooms.delete(client.roomId);
		console.log(`🗑️ Room ${client.roomId} delete (empty)`);
	} else {
		console.log(`📉 Room ${client.roomId} now has ${room.size} members`);
	}
};

export const broadcastToRoom = (roomId: string, message: any) => {
	const room = rooms.get(roomId);
	if (!room) {
		console.log(`⚠️ Room ${roomId} not found`);
		return ;
	}

	const payload = JSON.stringify(message);
	let sentCount = 0;

	room.forEach(client => {
		if (client.socket.readyState == WebSocket.OPEN) {
			client.socket.send(payload);
			sentCount++;
		}
	});

	console.log(`📤 Broadcasted to ${sentCount}/${room.size} clients in room ${roomId}`);
};
