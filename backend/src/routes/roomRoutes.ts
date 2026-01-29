import { FastifyInstance } from 'fastify';
import { createRoom } from '../controllers/roomController';

export async function roomRoutes(fastify: FastifyInstance) {
	fastify.post('/room', createRoom);
}