/**
 * Me API の型定義
 */

/**
 * GET /api/me 成功レスポンス型 (200)
 */
export interface MeSuccessResponse {
	id: number;
	name: string;
}

/**
 * GET /api/me 未ログインレスポンス型 (401)
 */
export interface MeUnauthorizedResponse {
	message: string;
}

/**
 * GET /api/me ルートの型定義
 */
export type MeRoute = {
	Reply: MeSuccessResponse | MeUnauthorizedResponse;
};

