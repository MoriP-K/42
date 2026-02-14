export const GameRole = {
	PLAYER: "PLAYER",
	SPECTATOR: "SPECTATOR",
};

export const PlayerRole = {
	DRAWER: "DRAWER",
	GUESSER: "GUESSER",
};

export interface AuthUser {
	id: number;
	name: string;
}

export interface User {
	id: number;
	name: string;
	role: (typeof GameRole)[keyof typeof GameRole];
}
