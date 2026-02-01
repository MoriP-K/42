import { apiClient } from './apiClient';

/**
 * ユーザー関連のAPI定義
 */
export const userApi = {
	// GET /api/hello
	getHello: async () => {
		return apiClient('/hello');
	},

	// GET /api/me
	me: async (): Promise<{ id: number; name: string }> => {
		return apiClient('/me', { credentials: 'include' });
	},

	// GET /api/users
	getUsers: async () => {
		return apiClient('/users');
	},

	// GET /api/users
    getProfile: async () => {
        return apiClient('/profile');
    },

	// POST /api/register
	register: async (data: { name: string; email: string; password: string }) => {
		return apiClient('/register', {
			method: 'POST',
			body: JSON.stringify(data),
		});
	},
};
