import { apiClient } from "./apiClient";
import { GameRole } from "../types/user";
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
		userId: number,
		role: (typeof GameRole)[keyof typeof GameRole],
	) => {
		return apiClient(`/rooms/${roomId}/members/${userId}`, {
			method: "PATCH",
			body: JSON.stringify({ role }),
		});
	},

	updateGameMode: async (roomId: number, mode: (typeof GameMode)[keyof typeof GameMode]) => {
		return apiClient(`/rooms/${roomId}/game-mode`, {
			method: "PATCH",
			body: JSON.stringify({ mode }),
		});
	},

	updateRoomMemberReady: async (roomId: number, userId: number, isReady: boolean) => {
		return apiClient(`/rooms/${roomId}/members/${userId}/ready`, {
			method: "PATCH",
			body: JSON.stringify({ isReady }),
		});
	},
};
