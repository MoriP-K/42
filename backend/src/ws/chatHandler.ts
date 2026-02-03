import { WebSocket } from 'ws';

// 接続中のクライアント
// const clients = new Set<WebSocket>();

interface RoomClient {
	socket: WebSocket,
	userId: string,
	roomId: string,
};

// 引数のメッセージを接続中の全クライアントに配信するbroadcast関数
// const broadcast = (message: any) => {
// 	const payload = JSON.stringify(message);

// 	// 全クライアントに送信
// 	clients.forEach((client) => {
// 		if (client.readyState === WebSocket.OPEN) {
// 			client.send(payload);
// 		}
// 	});
// };

export const handleChatMessage = (client: RoomClient, data: any) => {
	console.log(`💬 Chat from ${client.userId} in room ${client.roomId}: ${data.text}`);

	client.socket.send(JSON.stringify({
		type: 'chat',
		id: data.id,
		sender: data.sender,
		text: data.text,
		timestamp: data.timestamp,
	}));
};
