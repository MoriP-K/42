import { WebSocket } from 'ws';

// 接続中のクライアント
const clients = new Set<WebSocket>();

// 引数のメッセージを接続中の全クライアントに配信するbroadcast関数
const broadcast = (message: any) => {
	const payload = JSON.stringify(message);

	// 全クライアントに送信
	clients.forEach((client) => {
		if (client.readyState === WebSocket.OPEN) {
			client.send(payload);
		}
	});
};

export const handleChatConnection = (socket: WebSocket) => {
	// サーバー接続時にクライアントを追加
	clients.add(socket);
	console.log('✅ Client connected. Total: ', clients.size);

	socket.on('message', (rawMessage: any) => {
		try {
			const data = JSON.parse(rawMessage.toString());
			console.log('✉️ Received:', data);
			broadcast(data); // 受信したメッセージを全クライアントに配信
		} catch (error) {
			console.error('❌ Invalid message:', error);
		}
	});

	// クライアント切断時の処理
	socket.on('close', () => {
		clients.delete(socket); // クライアントを削除
		console.log('🔌 Client disconnected. Total:', clients.size);
	});
};
