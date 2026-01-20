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
export const getProfile = async (request: ProfileRequest, reply: ProfileSuccessResponse) => {

	// データをテーブルから持ってくる
	// const user = await prisma.user.findUnique({where: {id: request.userId, name: request.name}});
	const user = await prisma.user.findUnique({where: {id: 1}},);
	console.dir(user, {depth: null});

	// ダミーデータ
	const successResponse: ProfileSuccessResponse = {
		name: "test",
		total_score: 1,
		first_place_count: 2,
		play_count: 3
	};
	return (successResponse);
};
