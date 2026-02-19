import fastify, {
	FastifyRequest,
	FastifyReply,
	FastifyRouterOptions,
} from "fastify";
import { prisma } from "../lib/prisma";
import { randomUUID } from "node:crypto";
import {
	CreateRoomRoute,
	GetRoomRoute,
	UpdateGameModeBodySchema,
	UpdateGameModeParamsSchema,
	UpdateGameModeRoute,
} from "../types/room/room";
import { UpdateRoomMemberRoleRoute } from "../types/room/roomMember";
import {
	RoomIdParamsSchema,
	RoomMemberBodySchema,
	RoomMemberParamsSchema,
	RoomMemberRoute,
} from "../types/room/common";

/*
 * POST /api/rooms ルーム作成
 */
export const createRoom = async (
	request: FastifyRequest<CreateRoomRoute>,
	reply: FastifyReply,
) => {
	try {
		const room = await prisma.room.create({
			data: {
				host_id: request.body.hostId,
				invitation_token: randomUUID(),
				members: {
					create: {
						user_id: request.body.hostId,
						role: "PLAYER",
					},
				},
			},
		});
		return reply.code(201).send(room);
	} catch (error) {
		console.log("Error:", error);
		return reply.code(403).send();
	}
};

/*
 * GET /api/rooms/:roomId ルーム詳細取得
 */
export const getRoomDetails = async (
	request: FastifyRequest<GetRoomRoute>,
	reply: FastifyReply,
) => {
	const room = await prisma.room.findUnique({
		where: {
			id: Number(request.params.roomId),
		},
		include: {
			members: {
				include: {
					user: true,
				},
			},
			rounds: true,
		},
	});
	return reply.code(200).send(room);
};

/*
 * GET /api/rooms/:roomId/members ルームメンバーの取得
 */
export const getRoomMembers = async (
	request: FastifyRequest<RoomMemberRoute>,
	reply: FastifyReply,
) => {
	const paramResult = RoomIdParamsSchema.safeParse(request.params);
	if (!paramResult.success) {
		return reply
			.code(400)
			.send({ message: "パラメータに不備があります。" });
	}

	const roomId = paramResult.data.roomId;
	try {
		const roomMembers = await prisma.roomMember.findMany({
			where: {
				room_id: roomId,
			},
			include: {
				user: true,
			},
		});
		return reply.code(200).send(roomMembers);
	} catch (error) {
		console.error("Error:", error);
		return reply.code(500).send({ error: "Failed to fetch roomMembers" });
	}
};

/*
 * PATCH /api/rooms/:id/members/:userId ルームメンバー更新
 */
export const updateRoomMemberRole = async (
	request: FastifyRequest<UpdateRoomMemberRoleRoute>,
	reply: FastifyReply,
) => {
	const { roomId, userId } = request.params;
	const { role } = request.body;
	try {
		const updatedMember = await prisma.roomMember.update({
			where: {
				room_id_user_id: {
					room_id: Number(roomId),
					user_id: Number(userId),
				},
			},
			data: {
				role: role,
			},
		});
		return reply.code(200).send(updatedMember);
	} catch (error) {
		console.log(error);
		return reply
			.code(500)
			.send({ error: "Failed to update room member role" });
	}
};

/*
 * PATCH /api/rooms/:roomId/game-mode ゲームモード変更
 */
export const updateGameMode = async (
	request: FastifyRequest<UpdateGameModeRoute>,
	reply: FastifyReply,
) => {
	const paramResult = UpdateGameModeParamsSchema.safeParse(request.params);
	const bodyResult = UpdateGameModeBodySchema.safeParse(request.body);

	if (!paramResult.success) {
		return reply
			.code(400)
			.send({ message: "パラメータに不備があります。" });
	}

	if (!bodyResult.success) {
		return reply
			.code(400)
			.send({ message: "リクエストボディに不備があります。" });
	}

	const roomId = paramResult.data.roomId;
	const mode = bodyResult.data.mode;

	try {
		const updatedMode = await prisma.room.update({
			where: {
				id: roomId,
			},
			data: {
				game_mode: mode,
			},
		});
		return reply.code(200).send(updatedMode);
	} catch (error) {
		console.log(error);
		return reply.code(500).send({ error: "Failed to update game mode" });
	}
};

/*
 * PATCH /api/rooms/:roomId/members/:userId/ready 各プレイヤーの準備ステータス
 */
export const updateRoomMemberReady = async (
	request: FastifyRequest<RoomMemberRoute>,
	reply: FastifyReply,
) => {
	try {
		const paramResult = RoomMemberParamsSchema.safeParse(request.params);
		const bodyResult = RoomMemberBodySchema.safeParse(request.body);

		if (!paramResult.success) {
			return reply
				.code(400)
				.send({ message: "パラメータに不備があります。" });
		}

		if (!bodyResult.success) {
			return reply
				.code(400)
				.send({ message: "リクエストボディに不備があります。" });
		}

		const { roomId, userId } = paramResult.data;
		const isReady = bodyResult.data.isReady;

		const userStatus = await prisma.roomMember.update({
			where: {
				room_id_user_id: {
					room_id: roomId,
					user_id: userId,
				},
			},
			data: {
				is_ready: isReady,
			},
		});

		return reply.code(200).send(userStatus);
	} catch (error) {
		console.log(error);
		return reply.code(500).send({ error: "Failed to update user status" });
	}
};

export const wsUpdateReady = async (
	roomId: number,
	userId: number,
	isReady: boolean,
) => {
	try {
		await prisma.roomMember.update({
			where: {
				room_id_user_id: {
					room_id: roomId,
					user_id: userId,
				},
			},
			data: {
				is_ready: isReady,
			},
		});
	} catch (error) {
		console.error(error);
	}
};
