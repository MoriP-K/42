import {
	AuthSuccessResponse,
	AuthServerErrorResponse,
	AuthErrorResponse,
} from "./common";

/**
 * Me API の型定義
 */

/**
 * GET /api/me ルートの型定義
 */
export type MeRoute = {
	Reply: AuthSuccessResponse | AuthServerErrorResponse | AuthErrorResponse;
};
