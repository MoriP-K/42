import { z } from "zod";

/**
 * auth系API共通レスポンス型
 */

/**
 * ユーザー名を返す成功レスポンス型 POST→201 その他→200
 */
export const AuthSuccessResponseSchema = z.object({
	id: z.number(),
	name: z.string(),
});
export type AuthSuccessResponse = z.infer<typeof AuthSuccessResponseSchema>;

/**
 * エラーレスポンス型 (400/401)
 */
export const AuthErrorResponseSchema = z.object({
	message: z.string(),
});
export type AuthErrorResponse = z.infer<typeof AuthErrorResponseSchema>;

/**
 * サーバーエラーレスポンス型 (500)
 */
export const AuthServerErrorResponseSchema = z.object({
	message: z.string(),
});
export type AuthServerErrorResponse = z.infer<
	typeof AuthServerErrorResponseSchema
>;
