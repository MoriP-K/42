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
	JoinByTokenBodySchema,
	JoinByTokenRoute,
} from "../types/room/room";
import { UpdateRoomMemberRoleRoute } from "../types/room/roomMember";
import {
	RoomIdParamsSchema,
	RoomMemberBodySchema,
	RoomMemberParamsSchema,
	RoomMemberRoute,
} from "../types/room/common";
import { updateReadyStatus } from "../services/roomService";
import { getUserIdFromRequest } from "../lib/auth";
import { UserRole } from "../generated/prisma/enums";
import { broadcastToRoom } from "../ws/roomManager";

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
				orderBy: {
					joined_at: "asc",
				},
			},
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
			orderBy: {
				joined_at: "asc",
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
	const requesterId = await getUserIdFromRequest(request);
	if (!requesterId) {
		return reply.code(401).send({ error: "Unauthorized" });
	}
	const paramResult = RoomMemberParamsSchema.safeParse(request.params);
	if (!paramResult.success) {
		return reply
			.code(400)
			.send({ message: "パラメータに不備があります。" });
	}
	const { roomId, userId } = paramResult.data;
	const { role } = request.body;
	const room = await prisma.room.findUnique({
		where: { id: roomId },
		select: { host_id: true },
	});
	if (!room) {
		return reply.code(404).send({ error: "Room not found" });
	}
	const targetUserId = userId;
	const isHost = room.host_id === requesterId;
	const isSelf = targetUserId === requesterId;
	if (!isHost && !isSelf) {
		const currentMember = await prisma.roomMember.findUnique({
			where: {
				room_id_user_id: {
					room_id: roomId,
					user_id: userId,
				},
			},
			include: { user: true },
		});
		return reply.code(200).send(currentMember);
	}
	try {
		const updatedMember = await prisma.roomMember.update({
			where: {
				room_id_user_id: {
					room_id: roomId,
					user_id: userId,
				},
			},
			data: { role: role },
		});
		broadcastToRoom(String(roomId), {
			type: "memberRoleUpdated",
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
		broadcastToRoom(String(roomId), {
			type: "gameModeUpdated",
			mode: mode,
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

		const userStatus = await updateReadyStatus(roomId, userId, isReady);

		return reply.code(200).send(userStatus);
	} catch (error) {
		console.log(error);
		return reply.code(500).send({ error: "Failed to update user status" });
	}
};

/*
 * POST /api/rooms/join 招待URLから参加したユーザをルームに追加する
 */
export const joinRoomByToken = async (
	request: FastifyRequest<JoinByTokenRoute>,
	reply: FastifyReply,
) => {
	const userId = await getUserIdFromRequest(request);
	if (!userId) return reply.code(401).send({ error: "Unauthorized" });

	const bodyResult = JoinByTokenBodySchema.safeParse(request.body);
	if (!bodyResult.success) {
		return reply.code(400).send({ message: "招待URLに不備があります。" });
	}
	const { token } = bodyResult.data;

	const room = await prisma.room.findUnique({
		where: { invitation_token: token },
	});
	if (!room) {
		return reply.code(404).send({ message: "招待が無効です。" });
	}
	const roomId = room.id;
	try {
		await prisma.roomMember.upsert({
			where: {
				room_id_user_id: {
					room_id: roomId,
					user_id: userId,
				},
			},
			create: {
				room_id: room.id,
				user_id: userId,
				role: UserRole.PLAYER,
			},
			update: {},
		});
		broadcastToRoom(String(roomId), { type: "memberJoined" });
		return reply.code(200).send({ roomId });
	} catch (error) {
		console.error("Error:", error);
		return reply.code(500).send("Failed to join room");
	}
};
