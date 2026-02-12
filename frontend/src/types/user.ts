export const Role = {
	PLAYER: 'PLAYER',
	SPECTATOR: 'SPECTATOR',
};

export interface AuthUser {
	id: number;
	name: string;
}

export interface User {
	id: number;
	name: string;
	role: (typeof Role)[keyof typeof Role];
}
