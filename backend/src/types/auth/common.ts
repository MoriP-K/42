/**
 * auth系API共通レスポンス型
 */


/**
 * ユーザー名を返す成功レスポンス型 POST→201 その他→200
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
