import { WebSocket } from 'ws';

import { handleChatMessage } from './chatHandler'

interface RoomClient {
	socket: WebSocket,
	userId: string,
	roomId: string,
};

export const handleConnection = (socket: WebSocket) => {
	let currentClient: RoomClient | null = null;

	console.log("✅ Client connected");

	socket.on('message', (rawMessage) => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log("📥 Received: ", data);

			if (data.type === 'join') {
				currentClient = {
					socket,
					userId: data.userId,
					roomId: data.roomId,
				};

				socket.send(JSON.stringify({
					type: 'joined',
					roomId: data.roomId,
					userId: data.userId,
				}));

				return ;
			}

			if (!currentClient) {
				console.error("❌ Not joined to any room");
				socket.send(JSON.stringify({
					type: 'error',
					message: "Join a room first",
				}));

				return ;
			}

			if (data.type === 'chat') {
				handleChatMessage(currentClient, data);
			}
		} catch (error) {
			console.error("❌ Invalid message: ", error);
		}
	});

	socket.on('close', () => {
		if (currentClient) {
			;
		}
		console.log("🔌 Client disconnected");
	});
}
