export interface GameRoomMember {
	user_id: number;
	role: string;
	is_ready: boolean;
	user: { name: string };
}

export interface GameRoomRound {
	started_at: string | null;
	ended_time: string | null;
	drawer_id: number;
}

export interface GameDetails {
	members: GameRoomMember[];
	rounds: GameRoomRound[];
}
