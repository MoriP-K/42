import { apiClient } from './apiClient';
import { GameMode, Role } from '../types/room';

export const roomApi = {
	// GET /api/rooms
	createRoom: async (hostId: number) => {
		return apiClient('/rooms', {
			method: 'POST',
			body: JSON.stringify({ hostId }),
		});
	},

	updateRoomMemberRole: async (roomId: number, id: number, role: typeof Role[keyof typeof Role]) => {
		return apiClient(`/rooms/${roomId}/members/${id}`, {
			method: 'PATCH',
			body: JSON.stringify({ role }),
		})
	},

	updateGameMode: async (roomId: number, mode: typeof GameMode[keyof typeof GameMode]) => {
		return apiClient(`/rooms/${roomId}/game-mode`, {
			method: 'PATCH',
			body: JSON.stringify({ mode }),
		});
	}
}