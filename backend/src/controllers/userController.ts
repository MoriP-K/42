import { FastifyRequest, FastifyReply } from 'fastify';
import { prisma } from '../lib/prisma';

/**
 * LaravelのUserControllerに相当
 */
export const getHello = async (request: FastifyRequest, reply: FastifyReply) => {

    return {
        message: 'Hello from Controller!',
        timestamp: new Date().toISOString()
    };
};

export const getUsers = async (request: FastifyRequest, reply: FastifyReply) => {
	const users = await prisma.user.findMany();
    return users;
};


import {
	ProfileRequest,
	ProfileSuccessResponse,
	ProfileRoute
} from '../types/profile';

/**
 * GET /profile
 */
export const getProfile = async (request: FastifyRequest<ProfileRoute>, 
								reply: FastifyReply<ProfileRoute>) => {

	const userId = Number(request.query.userId);
	const user = await prisma.user.findUnique({where: {id: Number((request.query as { userId: number }).userId)}},);
	if (!user)
		return reply.code(404).send({ message: 'User not found' });
	
	const data: ProfileSuccessResponse = {
		name: user.name,
		total_score: user.total_score ?? 0,
		first_place_count: user.first_place_count ?? 0,
		play_count: user.play_count ?? 0,
	};
	return (data);
};