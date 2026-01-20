/**
 * Profile API の型定義
 */

/**
 * GET /api/profile リクエスト型
 */
export interface ProfileRequest {
	userId: number;
	name: string;
}

/**
 * GET /api/register 成功レスポンス型 (201)
 */
export interface ProfileSuccessResponse {
	name: String;
	total_score: number;
	first_place_count: number;
	play_count: number;
	// badges            UserBadge[]
}

/**
 * GET /api/register ルートの型定義
 */
export type ProfileRoute = {
	Body: ProfileRequest;
	Reply: ProfileSuccessResponse;
};
