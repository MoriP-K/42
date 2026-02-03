/**
 * auth系API共通レスポンス型
 */


/**
 * ユーザー名を返す成功レスポンス型 (201)
 */
export interface AuthSuccessResponse {
	name: string;
}

/**
 * エラーレスポンス型 (401)
 */
export interface AuthErrorResponse {
	message: string;
}

/**
 * サーバーエラーレスポンス型 (500)
 */
export interface AuthServerErrorResponse {
	message: string;
}
