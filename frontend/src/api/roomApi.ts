import { apiClient } from './apiClient'

export const roomApi = {
	// GET /api/rooms
	createRoom: async (hostId: number) => {
		return apiClient('/room', {
			method: 'POST',
			body: JSON.stringify({ hostId }),
		});
	}
}