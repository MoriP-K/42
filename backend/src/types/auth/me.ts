import { z } from "zod";
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

/**
 * PATCH /api/me リクエスト型
 */
export const UpdateMeRequest = z.object({
	name: z
		.string()
		.min(1)
		.regex(
			/^[a-z0-9_]+$/,
			"ユーザー名には半角英数字と「_」のみ使用できます",
		),
});
export type UpdateMeRequest = z.infer<typeof UpdateMeRequest>;

/**
 * PATCH /api/me 成功レスポンス型 (200)
 */
export const UpdateMeSuccessResponse = z.object({
	id: z.number(),
	name: z.string(),
	is_profile_complete: z.literal(true),
});
export type UpdateMeSuccessResponse = z.infer<typeof UpdateMeSuccessResponse>;

/**
 * PATCH /api/me ルートの型定義
 */
export type UpdateMeRoute = {
	Body: UpdateMeRequest;
	Reply:
		| UpdateMeSuccessResponse
		| AuthErrorResponse
		| AuthServerErrorResponse;
};
