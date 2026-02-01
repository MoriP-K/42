import { FastifyRequest, FastifyReply } from "fastify";
import { prisma } from "../lib/prisma";
import {
	ProfileRequest,
	ProfileSuccessResponse,
	ProfileRoute,
} from "../types/profile";

/**
 * LaravelのUserControllerに相当
 */
export const getHello = async (
	request: FastifyRequest,
	reply: FastifyReply
) => {
	return {
		message: "Hello from Controller!",
		timestamp: new Date().toISOString(),
	};
};

export const getUsers = async (
	request: FastifyRequest,
	reply: FastifyReply
) => {
	const users = await prisma.user.findMany();
	return users;
};

/**
 * GET /profile
 */
export const getProfile = async (
	request: FastifyRequest<ProfileRoute>,
	reply: FastifyReply<ProfileRoute>
) => {
	const userId = Number(request.query.userId);
	const user = await prisma.user.findUnique({
		where: { id: Number((request.query as { userId: number }).userId) },
	});
	if (!user) return reply.code(404).send({ message: "User not found" });

	// userbadgesから取得
	const user_badges = await prisma.userBadge.findMany({
		where: {
			user_id: Number((request.query as { userId: number }).userId),
		},
	});
	let badges: Array<string> = new Array(0);
	for (let i: number = 0; i < user_badges.length; i++) {
		console.log(user_badges[i]);
		badges.push(
			await prisma.badge.findUnique({
				where: { id: Number(user_badges[i].badge_id) },
			})
		);
	}

	const data: ProfileSuccessResponse = {
		name: user.name,
		total_score: user.total_score ?? 0,
		first_place_count: user.first_place_count ?? 0,
		play_count: user.play_count ?? 0,
		// badges: badges.badges ?? 0,
	};
	return data;
};
