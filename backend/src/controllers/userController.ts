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
	reply: FastifyReply<ProfileRoute>
) => {
	const sessionId = request.cookies["session_id"];
	const session = await prisma.session.findUnique({
		where: { id: sessionId },
		include: { user: true },
	});
	console.log(session);
	if (!session || !session.user) {
		return reply.code(401).send({ message: "Invalid Session" });
	}

	const userId = Number(session.user.id);
	console.log("userId " + userId);

	const user = await prisma.user.findUnique({
		where: { id: userId },
	});
	if (!user) return reply.code(404).send({ message: "User not found" });

	// userbadgesから取得
	const userBadgesWithDetails = await prisma.userBadge.findMany({
		where: {
			user_id: userId,
		},
		include: {
			badge: true, // リレーション名を指定して実体を取得
		},
	});
	console.log("userBadgesWithDetails  ");
	console.log(userBadgesWithDetails);

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
