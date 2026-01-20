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

	// GET /api/users
    getProfile: async () => {
        return apiClient('/profile');
    },

    // POST /api/users (例)
    // createUser: async (data: any) => {
    //     return apiClient('/users', {
    //         method: 'POST',
    //         body: JSON.stringify(data),
    //     });
    // },
};
