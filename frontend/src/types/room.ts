import { GameRole, type User } from "./user";

export const GameMode = {
	DEFAULT: "DEFAULT",
	ONE_STROKE: "ONE_STROKE",
};

export interface RoomMember {
	room_id: number;
	user_id: number;
	is_ready: boolean;
	role: (typeof GameRole)[keyof typeof GameRole];
	user: User;
}

export interface Round {
	id: number;
	room_id: number;
	drawer_id: number;
	word: string | null;
	winner_id: number | null;
	started_at: string | null;
	ended_time: string | null;
}

export interface RoomDetails {
	id: number;
	game_mode: (typeof GameMode)[keyof typeof GameMode];
	host_id: number;
	invitation_token?: string;
	members: RoomMember[];
	rounds: Round[];
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

export interface Player {
	id: number;
	name: string;
	score: number;
	isDrawing: boolean;
}
