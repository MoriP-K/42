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

	const user = await prisma.user.findUnique({where: {id: Number(request.query.userId)}},);
	// console.dir(user, {depth: null});
	return (user);
};

// userIDを指定してデータを取得
// curl -X GET "http://localhost:3000/api/profile?userId=1" \
//   -H "Content-Type: application/json"