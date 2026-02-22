import { FastifyRequest, FastifyReply } from "fastify";
import { OAuth2Client } from "google-auth-library";

const GOOGLE_CLIENT_ID = process.env.GOOGLE_CLIENT_ID ?? "";
const GOOGLE_CLIENT_SECRET = process.env.GOOGLE_CLIENT_SECRET ?? "";
const GOOGLE_REDIRECT_URI =
	process.env.GOOGLE_REDIRECT_URI ??
	"http://localhost:3000/v1/auth/google/callback";

const oauth2Client = new OAuth2Client(
	GOOGLE_CLIENT_ID,
	GOOGLE_CLIENT_SECRET,
	GOOGLE_REDIRECT_URI,
);

type GoogleCallbackQuerystring = {
	code?: string;
	error?: string;
	state?: string;
};

type GoogleUserInfo = {
	sub: string;
	email: string;
	email_verified: boolean;
	name: string;
	picture: string;
	given_name: string;
	family_name: string;
};

export const googleCallback = async (
	request: FastifyRequest<{ Querystring: GoogleCallbackQuerystring }>,
	reply: FastifyReply,
) => {
	const { code, error, state } = request.query;

	if (error) {
		return reply
			.code(400)
			.send({ message: "Google認証がキャンセルされました" });
	}

	// CSRF対策: stateの検証
	const cookieState = request.cookies?.oauth_state;
	if (!state || !cookieState || state !== cookieState) {
		console.error("[googleCallback] state不一致 - CSRF攻撃の可能性", {
			queryState: state,
			cookieState: cookieState,
		});
		return reply.code(400).send({ message: "不正なリクエストです" });
	}
	// 使用済みのstateを削除（再利用防止）
	reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });
	console.log("[googleCallback] state検証 OK");

	if (!code) {
		return reply.code(400).send({ message: "認証コードが見つかりません" });
	}

	console.log("[googleCallback] ① code 受け取り成功");

	try {
		// ② code をアクセストークンに交換
		const { tokens } = await oauth2Client.getToken(code);
		oauth2Client.setCredentials(tokens);

		console.log("[googleCallback] ② アクセストークン取得成功:", {
			access_token: tokens.access_token,
			token_type: tokens.token_type,
			expiry_date: tokens.expiry_date,
		});

		// ③ アクセストークンでユーザー情報を取得
		const userInfoRes = await oauth2Client.request<GoogleUserInfo>({
			url: "https://www.googleapis.com/oauth2/v3/userinfo",
		});
		const userInfo = userInfoRes.data;

		console.log("[googleCallback] ③ ユーザー情報取得成功:", {
			sub: userInfo.sub,
			email: userInfo.email,
			email_verified: userInfo.email_verified,
			name: userInfo.name,
		});

		// TODO: DBへの保存・セッション作成はここに追加予定
		return reply.code(200).send({
			message: "Google認証成功（デバッグ用レスポンス）",
			email: userInfo.email,
			name: userInfo.name,
		});
	} catch (err) {
		console.error("[googleCallback] 予期しないエラー:", err);
		return reply
			.code(500)
			.send({ message: "予期しないエラーが発生しました" });
	}
};
