import { FastifyRequest, FastifyReply, FastifyRouterOptions } from 'fastify';
import { prisma } from '../lib/prisma';
import { randomUUID } from 'node:crypto';
import { CreateRoomRoute, GetRoomRoute } from '../types/room';
import { UpdateMemberRoute } from '../types/roomMember';

/*
 * POST /api/rooms ルーム作成
 */
export const createRoom = async (
	request: FastifyRequest<CreateRoomRoute>,
	reply: FastifyReply
) => {
	const room = await prisma.room.create({
		data: {
			host_id: request.body.hostId,
			invitation_token: randomUUID(),
		}
	})
	return reply.code(201).send(room);
}

/*
 * GET /api/rooms/:id ルーム詳細取得
 */
export const getRoomDetails = async (
	request: FastifyRequest<GetRoomRoute>,
	reply: FastifyReply
) => {
	const room = await prisma.room.findUnique({
		where: {
			id: request.params.id,
		}
	})
	return reply.code(200).send(room);
}

/*
 * PATCH /api/rooms/:id/members/:userId ルームメンバー更新
 */
export const updateRoomMember = async (
	request: FastifyRequest<UpdateMemberRoute>,
	reply: FastifyReply
) => {
	const { id: roomId, userId } = request.params;
	const room = await prisma.room.update({
		where: {
			id: roomId,
		},
		data: {
		}
	})
	return reply.code(200).send(room);
}

/*
* PATCH /api/rooms/${roomId}/game-mode ゲームモード変更
*/
export const upateGameMode = async (
	request: FastifyRequest<UpdateGameModeRoute>,
	reply: FastifyReply
) => {
	
}