/**
 * Profile API の型定義
 */

/**
 * GET /api/profile リクエスト型
 */
export interface ProfileRequest {
	userId: number;
}

/**
 * GET /api/profile
 */
export interface ProfileSuccessResponse {
	name: String;
	total_score: number;
	first_place_count: number;
	play_count: number;
	badges: String[];
	user_rank: number;
	top_ranker: Record<string, number>[];
}

/**
 * GET /api/profile エラーレスポンス型 (404)
 */
export interface ProfileErrorResponse {
	message: string;
}

/**
 * GET /api/profile
 */
export type ProfileRoute = {
	Querystring: ProfileRequest;
	Reply: ProfileSuccessResponse | ProfileErrorResponse;
};
