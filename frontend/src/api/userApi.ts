import { apiClient } from './apiClient';

/**
 * ユーザー関連のAPI定義
 */
export const userApi = {
	// GET /api/hello
	getHello: async () => {
		return apiClient('/hello');
	},

	// GET /api/users
	getUsers: async () => {
		return apiClient('/users');
	},

	// POST /api/register
	register: async (data: { name: string; email: string; password: string }) => {
		return apiClient('/register', {
			method: 'POST',
			body: JSON.stringify(data),
		});
	},

	// GET /api/me
	getMe: async (): Promise<{ id: number; name: string }> => {
		return apiClient('/me', {
			credentials: 'include'
		});
	},

	// POST /api/users (例)
	// createUser: async (data: any) => {
	//     return apiClient('/users', {
	//         method: 'POST',
	//         body: JSON.stringify(data),
	//     });
	// },
};
