import { FastifyRequest, FastifyReply } from 'fastify';
import { prisma } from '../lib/prisma';
import { randomUUID } from 'node:crypto';
import { CreateRoomRequest } from '../types/room';

export const createRoom = async (
	request: FastifyRequest<{Body: CreateRoomRequest}>,
	reply: FastifyReply
) => {
	const room = await prisma.room.create({
		data: {
			host_id: request.body.hostId,
			invitation_token: randomUUID(),
		}
	})
	return reply.code(201).send(room);
}