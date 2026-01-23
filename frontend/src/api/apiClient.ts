const BASE_URL = 'http://localhost:3000/api';

/**
 * 共通のAPIクライアント
 * fetchをラップして共通の処理（エラーハンドリング等）を行う
 */
export class ApiError extends Error {
	status: number
	data: unknown

	constructor(status: number, data: unknown, message?: string) {
		super(message ?? 'API Request Failed')
		this.name = 'ApiError'
		this.status = status
		this.data = data
	}
}

export const apiClient = async (endpoint: string, options: RequestInit = {}) => {
	const url = `${BASE_URL}${endpoint}`;

	// 必要に応じてヘッダーを追加
	const headers = {
		'Content-Type': 'application/json',
		...options.headers,
	};

	const response = await fetch(url, { ...options, headers });

	if (!response.ok) {
		// ここで共通のエラーハンドリングが可能（LaravelのAxios Interceptor相当）
		const errorBody = await response.json().catch(() => ({}));
		const message =
			(typeof errorBody === 'object' && errorBody !== null && 'message' in errorBody)
				? String((errorBody as { message?: unknown }).message ?? 'API Request Failed')
				: 'API Request Failed'
		throw new ApiError(response.status, errorBody, message);
	}

	return response.json();
};
