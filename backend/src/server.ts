import Fastify from 'fastify';
import cors from '@fastify/cors';
import cookie from '@fastify/cookie';
import websocket from '@fastify/websocket';
import { userRoutes } from './routes/userRoutes';
import { authRoutes } from './routes/authRoutes';
import { roomRoutes } from './routes/roomRoutes';
import { handleConnection } from './ws/connectionHandler';

const fastify = Fastify({
	logger: true
});

// CORS設定 (Reactアプリからのリクエストを許可)
fastify.register(cors, {
	origin: true, // 開発環境なので全て許可 (本番では制限を推奨)
	methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
	credentials: true, // Cookieを送受信するため
});

// WebSocket機能を有効化する
fastify.register(websocket);

// Cookie機能を有効化する
fastify.register(cookie);

fastify.get('/', async (request, reply) => {
	return { hello: 'world' }
});

// ルートの登録
fastify.register(userRoutes, { prefix: '/api' });
fastify.register(authRoutes, { prefix: '/api' });
fastify.register(roomRoutes, { prefix: '/api' });

// WebSocketのルートを定義
fastify.register(async (fastify) => {
	fastify.get('/ws', { websocket: true }, (socket, request) => {
		handleConnection(socket);
	});
});

const start = async () => {
	try {
		await fastify.listen({ port: 3000, host: '0.0.0.0' })
	} catch (err) {
		fastify.log.error(err)
		process.exit(1)
	}
};

start();
