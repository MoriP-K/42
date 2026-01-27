import { WebSocket } from 'ws';

const clients = new Set<WebSocket>();

const broadcast = (message: any) => {
	const payload = JSON.stringify(message);

	clients.forEach((client) => {
		if (client.readyState === WebSocket.OPEN) {
			client.send(payload);
		}
	});
};

export const handleChatConnection = (socket: WebSocket) => {
	clients.add(socket);
	console.log('✅ Client connected. Total: ', clients.size);

	socket.on('message', (rawMessage: any) => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log('✉️ Received:', data);

			broadcast(data);
		} catch (error) {
			console.error('❌ Invalid message:', error);
		}
	});

	socket.on('close', () => {
		clients.delete(socket);
		console.log('🔌 Client disconnected. Total:', clients.size);
	});
};
