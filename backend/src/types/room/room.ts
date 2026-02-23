import { z } from "zod";
import { WebSocket } from "ws";
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
 * GET /api/rooms/:roomId パラメータ型
 */
export const GetRoomParamsSchema = z.object({
	roomId: z.coerce.number(),
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

export interface CreateRoundRoute {
	Params: GetRoomParams;
}

/**
 * PATCH /api/rooms/join ボディ型
 */
export const JoinByTokenBodySchema = z.object({
	token: z.coerce.string(),
});

export type JoinByTokenBody = z.infer<typeof JoinByTokenBodySchema>;

export interface JoinByTokenRoute {
	Body: JoinByTokenBody;
}

/**
 * WebSocket用 ルームクライアント型
 */
export interface RoomClient {
	socket: WebSocket;
	userId: number;
	roomId: string;
	role: string;
}

/**
 * ラウンドタイマー用の定数
 */
export const ROUND_DURATION = 60;

/**
 * WebSocketメッセージタイプ
 */
export const WebSocketMessageType = {
	JOIN: "join",
	LEFT: "userLeft",
	CHAT: "chat",
	DRAW: "draw",
	DRAW_END: "drawEnd",
	CLEAR: "clear",
	NAVIGATE_TO_PREPARE: "navigateToPrepare",
	PREPARE_STARTED: "prepareStarted",
	ROUND_START: "roundStart",
	ROUND_STARTED: "roundStarted",
	ROUND_END: "roundEnd",
	TIMER: "timer",
	UPDATE_READY: "updateReady",
	MEMBER_JOINED: "memberJoined",
	GAME_MODE_UPDATED: "gameModeUpdated",
	CORRECT_ANSWER: "correctAnswer",
	NEXT_WORD: "nextWord",
	ERROR: "error",
};
