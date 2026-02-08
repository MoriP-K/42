export const GameMode = {
	DEFAULT: 'DEFAULT',
	ONE_STROKE: 'ONE_STROKE',
}

export const Role = {
	PLAYER: 'PLAYER',
	SPECTATOR: 'SPECTATOR',
}

export interface User {
	id: number;
	name: string;
	role: typeof Role[keyof typeof Role];
}

export interface RoomMember {
	room_id: number;
	user_id: number;
	is_ready: boolean;
	role: typeof Role[keyof typeof Role];
	user: User;
}

export interface RoomDetails {
	id: number;
	host_id: number;
	game_mode: typeof GameMode[keyof typeof GameMode];
	members: RoomMember[];
}