import { FastifyRequest, FastifyReply } from "fastify";
import { prisma } from "../lib/prisma";
import {
	CreateRoomRoute,
	CreateRoundRoute,
	GetRoomRoute,
	UpdateGameModeBodySchema,
	UpdateGameModeParamsSchema,
	UpdateGameModeRoute,
	JoinByTokenBodySchema,
	JoinByTokenRoute,
} from "../types/room/room";

/*
 * GET /api/rooms/:roomId/game Game用ルーム詳細取得
 */
export const getGameRoomDetails = async (
	request: FastifyRequest<GetRoomRoute>,
	reply: FastifyReply,
) => {
	const room = await prisma.room.findUnique({
		where: {
			id: Number(request.params.roomId),
		},
		select: {
			members: {
				select: {
					user_id: true,
					role: true,
					score: true,
					is_ready: true,
					user: {
						select: {
							name: true,
						},
					},
				},
				orderBy: {
					joined_at: "asc",
				},
			},
			rounds: {
				select: {
					started_at: true,
					ended_time: true,
					drawer_id: true,
				},
			},
		},
	});
	return reply.code(200).send(room);
};
