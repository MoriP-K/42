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

	const user: ProfileSuccessResponse = await prisma.user.findUnique({where: {id: Number(request.query.userId)}},);
	if (!user)
		return reply.code(404).send({ message: 'User not found' });
	return (user);
};