import { z } from "zod";
import { GameModeEnum, RoomIdParamsSchema } from "./common";

/**
 * POST /api/rooms リクエスト型
 */
export const CreateRoomSchema = z.object({
	hostId: z.number(),
});

export type CreateRoomBody = z.infer<typeof CreateRoomSchema>;

export interface CreateRoomRoute {
	Body: CreateRoomBody;
}

/**
 * GET /api/rooms/:id パラメータ型
 */
export const GetRoomParamsSchema = z.object({
	id: z.coerce.number(),
});

export type GetRoomParams = z.infer<typeof GetRoomParamsSchema>;

export interface GetRoomRoute {
	Params: GetRoomParams;
}

/**
 * PATCH /api/rooms/:roomId/game-mode パラメータ型
 */
export const UpdateGameModeParamsSchema = RoomIdParamsSchema;

/**
 * PATCH /api/rooms/:roomId/game-mode ボディ型
 */
export const UpdateGameModeBodySchema = z.object({
	mode: GameModeEnum,
});

export type UpdateGameModeParams = z.infer<typeof UpdateGameModeParamsSchema>;
export type UpdateGameModeBody = z.infer<typeof UpdateGameModeBodySchema>;

export interface UpdateGameModeRoute {
	Params: UpdateGameModeParams;
	Body: UpdateGameModeBody;
}