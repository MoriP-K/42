import { apiClient } from './apiClient';

/**
 * ユーザー関連のAPI定義
 */
export const authApi = {
	// GET /api/me
	me: async (): Promise<{ id: number; name: string }> => {
		return apiClient('/me', { credentials: 'include' });
	},

	// POST /api/register
	register: async (data: { name: string; email: string; password: string }) => {
		return apiClient('/register', {
			method: 'POST',
			body: JSON.stringify(data),
			credentials: 'include'
		});
	},

	// POST /api/login
	login: async (data: { email: string; password: string }) => {
		return apiClient('/login', {
			method: 'POST',
			body: JSON.stringify(data),
			credentials: 'include'
		});
	},
};
