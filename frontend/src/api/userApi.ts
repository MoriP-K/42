import { apiClient } from "./apiClient";

/**
 * ユーザー関連のAPI定義
 */
export const userApi = {
	// GET /api/users
	getUsers: async () => {
		return apiClient("/users");
	},

	// GET /api/users
	getProfile: async () => {
		return apiClient("/profile");
	},
};
