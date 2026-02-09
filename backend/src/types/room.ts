/**
 * Room API の型定義
 */
import { z } from "zod";
import { WebSocket } from "ws";

/**
 * POST /api/rooms リクエスト型
 */
export const CreateRoomRequest = z.object({
	hostId: z.number(),
});

export type CreateRoomRequest = z.infer<typeof CreateRoomRequest>;

/**
 * WebSocket用 ルームクライアント型
 */
export interface RoomClient {
	socket: WebSocket,
	userId: string,
	roomId: string,
};
