import { Role, type User } from "./user";

export const GameMode = {
	DEFAULT: "DEFAULT",
	ONE_STROKE: "ONE_STROKE",
};

export interface RoomMember {
	room_id: number;
	user_id: number;
	is_ready: boolean;
	role: (typeof Role)[keyof typeof Role];
	user: User;
}

export interface RoomDetails {
	id: number;
	host_id: number;
	game_mode: (typeof GameMode)[keyof typeof GameMode];
	members: RoomMember[];
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
	ROUND_START: "roundStart",
	ROUND_END: "roundEnd",
	TIMER: "timer",
	ERROR: "error",
};
