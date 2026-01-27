/**
 * WebSocket URLを生成
 */
export const getWebSocketUrl = () => {
	const base = import.meta.env.VITE_API_URL || 'http://localhost:3000';
	// http → ws, https → wss に変換
	const wsBase = base.replace(/^http/, 'ws');

	return (`${wsBase}/ws`);
};

/**
 * WebSocket接続を作成
 */
export const createWebSocket = (): WebSocket => {
	const url = getWebSocketUrl();

	return (new WebSocket(url));
};
