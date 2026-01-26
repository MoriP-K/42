import { apiClient } from './apiClient'

export const roomApi = {
	// GET /api/rooms
	createRoom: async () => {
		return apiClient('/rooms', {
			method: 'POST',
			body: JSON.stringify({}),
		});
	}
}