import {
	AuthSuccessResponse,
	AuthServerErrorResponse
} from './common'

/**
 * Me API の型定義
 */

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
	Reply: AuthSuccessResponse | AuthServerErrorResponse | MeUnauthorizedResponse;
};
