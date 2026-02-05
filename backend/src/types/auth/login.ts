import {
	AuthSuccessResponse,
	AuthServerErrorResponse
} from './common'

/**
 * Login API の型定義
 */

/**
 * POST /api/login リクエスト型
 */
export interface LoginRequest {
	email: string;
	password: string;
}

/**
 * POST /api/login エラーレスポンス型 (401)
 */
export interface LoginErrorResponse {
	message: string;
}

/**
 * POST /api/login ルートの型定義
 */
export type LoginRoute = {
	Body: LoginRequest;
	Reply: AuthSuccessResponse | AuthServerErrorResponse | LoginErrorResponse;
};
