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
