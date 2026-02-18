import { apiClient } from "./apiClient";
import { Role } from "../types/user";
import { GameMode } from "../types/room";

export const roomApi = {
	// POST /api/rooms
	createRoom: async (hostId: number) => {
		return apiClient("/rooms", {
			method: "POST",
			body: JSON.stringify({ hostId }),
		});
	},

	getRoomDetails: async (roomId: number) => {
		return apiClient(`/rooms/${roomId}`, {
			method: "GET",
		});
	},

	updateRoomMemberRole: async (
		roomId: number,
		id: number,
		role: (typeof Role)[keyof typeof Role],
	) => {
		return apiClient(`/rooms/${roomId}/members/${id}`, {
			method: "PATCH",
			body: JSON.stringify({ role }),
		});
	},

	updateGameMode: async (
		roomId: number,
		mode: (typeof GameMode)[keyof typeof GameMode],
	) => {
		return apiClient(`/rooms/${roomId}/game-mode`, {
			method: "PATCH",
			body: JSON.stringify({ mode }),
		});
	},
};
