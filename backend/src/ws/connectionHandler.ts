import { WebSocket } from 'ws';
import { RoomClient } from '../types/room/room';
import { joinRoom, leaveRoom, broadcastToRoom } from './roomManager';
import { handleChatMessage } from './chatHandler';

export const handleConnection = (socket: WebSocket) => {
	let currentClient: RoomClient | null = null;

	console.log("✅ Client connected");

	socket.on('message', (rawMessage) => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log("📥 Received: ", data);

			if (!data.userId || typeof data.userId !== 'string' || data.userId.trim() === '') {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Invalid userId'
				}));
				return ;
			}

			if (!data.roomId || typeof data.roomId !== 'string' || data.roomId.trim() === '') {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Invalid roomId'
				}));
				return ;
			}

			if (data.type === 'join') {
				if (currentClient) {
					leaveRoom(currentClient);
				}

				currentClient = {
					socket,
					userId: data.userId,
					roomId: data.roomId,
				};

				joinRoom(currentClient);

				socket.send(JSON.stringify({
					type: 'joined',
					roomId: data.roomId,
					userId: data.userId,
				}));

				broadcastToRoom(data.roomId, {
					type: 'userJoined',
					userId: data.userId,
				});

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
			broadcastToRoom(currentClient.roomId, {
				type: 'userLeft',
				userId: currentClient.userId,
			});

			leaveRoom(currentClient);
		}
		console.log("🔌 Client disconnected");
	});
}
