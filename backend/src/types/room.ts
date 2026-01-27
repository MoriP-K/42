/**
 * Room API の型定義
 */
import { z } from "zod";

/**
 * POST /api/rooms リクエスト型
 */
export const CreateRoomRequest = z.object({
	hostId: z.number(),
});

export type CreateRoomRequest = z.infer<typeof CreateRoomRequest>;