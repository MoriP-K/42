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

export interface RoomDetails {
	id: number;
	host_id: number;
	game_mode: (typeof GameMode)[keyof typeof GameMode];
	members: RoomMember[];
}
