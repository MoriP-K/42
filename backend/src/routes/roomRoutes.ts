import { FastifyInstance } from 'fastify';
import {
	createRoom,
	getRoomDetails,
	updateRoomMemberRole,
	updateGameMode,
} from '../controllers/roomController';
import { UpdateGameModeParamsSchema, UpdateGameModeBodySchema } from '../types/room/room';

export async function roomRoutes(fastify: FastifyInstance) {
	fastify.post('/rooms', createRoom);
	fastify.get('/rooms/:id', getRoomDetails);
	fastify.patch('/rooms/:roomId/members/:userId', updateRoomMemberRole);
	fastify.patch('/rooms/:roomId/game-mode', updateGameMode);
}
