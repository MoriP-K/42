import { z } from "zod";
import {
	AuthSuccessResponse,
	AuthServerErrorResponse,
	AuthErrorResponse,
} from "./common";

/**
 * Register API の型定義
 */

/**
 * POST /api/register リクエスト型
 */
export const RegisterRequest = z.object({
	name: z
		.string()
		.min(1)
		.regex(
			/^[a-z0-9_]+$/,
			"ユーザー名には半角英数字と「_」のみ使用できます",
		),
	email: z.email("メールアドレスの形式が正しくありません").min(1),
	password: z
		.string()
		.min(8, "パスワードは8文字以上で入力してください")
		.regex(
			/^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)[A-Za-z0-9]{8,}$/,
			"パスワードには英大文字・英小文字・数字をそれぞれ1文字以上含めてください",
		),
});
export type RegisterRequest = z.infer<typeof RegisterRequest>;

/**
 * POST /api/register ルートの型定義
 */
export type RegisterRoute = {
	Body: RegisterRequest;
	Reply: AuthSuccessResponse | AuthServerErrorResponse | AuthErrorResponse;
};
