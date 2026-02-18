import { FastifyRequest, FastifyReply } from "fastify";
import { prisma } from "../lib/prisma";
import {
	ProfileRequest,
	ProfileSuccessResponse,
	ProfileRoute,
} from "../types/profile";
import { getUserIdFromRequest } from "../lib/auth";

/**
 * LaravelのUserControllerに相当
 */
export const getHello = async (
	request: FastifyRequest,
	reply: FastifyReply,
) => {
	return {
		message: "Hello from Controller!",
		timestamp: new Date().toISOString(),
	};
};

export const getUsers = async (
	request: FastifyRequest,
	reply: FastifyReply,
) => {
	const users = await prisma.user.findMany();
	return users;
};

/**
 * GET /profile
 */
export const getProfile = async (
	request: FastifyRequest<ProfileRoute>,
	reply: FastifyReply<ProfileRoute>,
) => {
	const userId = await getUserIdFromRequest(request);
	if (!userId) return reply.code(404).send({ message: "User not found" });
	const user = await prisma.user.findUnique({
		where: { id: Number(userId) },
	});
	if (!user) return reply.code(404).send({ message: "User not found" });

	// userbadgesから取得
	const userBadgesWithDetails = await prisma.userBadge.findMany({
		where: {
			user_id: Number(userId),
		},
		include: {
			badge: true,
		},
	});

	// 取得した結果からバッジの実体だけを取り出す場合
	// const badges = userBadgesWithDetails.map((ub) => ub.badge);

	const data: ProfileSuccessResponse = {
		name: user.name,
		total_score: user.total_score ?? 0,
		first_place_count: user.first_place_count ?? 0,
		play_count: user.play_count ?? 0,
		// badges: badges.badges ?? 0,
	};
	return data;
};
