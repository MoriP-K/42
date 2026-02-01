import { apiClient } from './apiClient'

export const roomApi = {
	// GET /api/rooms
	createRoom: async (hostId: number) => {
		return apiClient('/rooms', {
			method: 'POST',
			body: JSON.stringify({ hostId }),
		});
	},

	updateGameMode: async (roomId: number, mode: string) => {
		return apiClient(`/rooms/${roomId}/game-mode`, {
			method: 'PATCH',
			body: JSON.stringify({ mode }),
		});
	}
}