import { FastifyRequest, FastifyReply } from 'fastify';
import { prisma } from '../lib/prisma';

export const createRoom = async (request: FastifyReply, reply: FastifyReply) => {
	const room = await prisma.room.create({
		data: {
			
		}
	})
}