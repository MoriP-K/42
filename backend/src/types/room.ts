/**
 * Room API の型定義
 */
import { z } from "zod";

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