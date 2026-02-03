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