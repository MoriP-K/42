/**
 * Register API の型定義
 */

/**
 * POST /api/register リクエスト型
 */
export interface RegisterRequest {
	username: string;
	email: string;
	password: string;
}

/**
 * POST /api/register 成功レスポンス型 (201)
 */
export interface RegisterSuccessResponse {
	userId: number;
}

/**
 * POST /api/register エラーレスポンス型 (400)
 */
export interface RegisterErrorResponse {
	field: "email" | "username" | "password";
	message: string;
}
