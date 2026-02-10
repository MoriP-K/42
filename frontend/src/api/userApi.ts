import { apiClient } from "./apiClient";

/**
 * ユーザー関連のAPI定義
 */
export const userApi = {
	// GET /api/hello
	getHello: async () => {
		return apiClient("/hello");
	},

	// GET /api/users
	getUsers: async () => {
		return apiClient("/users");
	},

	// GET /api/profile
	getProfile: async () => {
		return apiClient("/profile", { credentials: "include" });
	},
};
