import { FastifyInstance } from 'fastify';
import { createRoom, getRoomDetails, updateRoomMember } from '../controllers/roomController';

export async function roomRoutes(fastify: FastifyInstance) {
	fastify.post('/rooms', createRoom);
	fastify.get('/rooms/:id', getRoomDetails);
	fastify.patch('/rooms/:id/members/:userId', updateRoomMember);
}