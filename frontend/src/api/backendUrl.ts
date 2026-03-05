/**
 * バックエンドのベースURLを取得
 * - VITE_API_URL が設定されているとき（ngrok等）: その値を使用
 * - localhost:5173 のとき: http://localhost:3000（バックエンドに直接アクセス）
 * - それ以外: 同一オリジン（window.location.origin）
 */
export const getBackendBaseUrl = (): string => {
	const env = (import.meta.env.VITE_API_URL ?? "").trim();
	if (env) return env.replace(/\/$/, "");

	// localhost:5173 のときはバックエンドに直接アクセス（Cookie が正しく送信される）
	if (
		window.location.hostname === "localhost" &&
		window.location.port === "5173"
	) {
		return "http://localhost:3000";
	}

	return window.location.origin;
};
