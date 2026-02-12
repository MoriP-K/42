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
	UpdateGameModeRoute,
} from "../types/room/room";
import { UpdateRoomMemberRoleRoute } from "../types/room/roomMember";
import { RoomMemberRoute } from "../types/room/common";

/*
 * POST /api/rooms ルーム作成
 */
export const createRoom = async (
	request: FastifyRequest<CreateRoomRoute>,
	reply: FastifyReply,
) => {
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
		},
	});
	return reply.code(200).send(room);
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
	try {
		const roomId = Number(request.params.roomId);
		const room = await prisma.room.update({
			where: {
				id: roomId,
			},
			data: {
				game_mode: request.body.mode,
			},
		});
		return reply.code(200).send(room);
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
	} catch (error) {}
};
