/**
 * userbadge API の型定義
 */

/**
 * GET /api/userbadge リクエスト型
 */
export interface UserBadgeRequest {
	userId: number;
}

interface badge_data {
	id: number;
	name: string;
}

export interface UserBadgeSuccessResponse {
	getbadges: badge_data[];
}

/**
 * GET /api/userbadge エラーレスポンス型 (404)
 */
export interface UserBadgeErrorResponse {
	message: string;
}

/**
 * GET /api/userbadge
 */
export type UserBadgeRoute = {
	Querystring: UserBadgeRequest;
	Reply: UserBadgeSuccessResponse | UserBadgeErrorResponse;
};
