import { FastifyRequest, FastifyReply } from "fastify";
import { OAuth2Client } from "google-auth-library";
import {
	GoogleCallbackQuerystring,
	GoogleUserInfo,
} from "../../types/googleAuth";

const GOOGLE_CLIENT_ID = process.env.GOOGLE_CLIENT_ID ?? "";
const GOOGLE_CLIENT_SECRET = process.env.GOOGLE_CLIENT_SECRET ?? "";
const GOOGLE_REDIRECT_URI = process.env.GOOGLE_REDIRECT_URI ?? "";

const oauth2Client = new OAuth2Client(
	GOOGLE_CLIENT_ID,
	GOOGLE_CLIENT_SECRET,
	GOOGLE_REDIRECT_URI,
);

//TODO: return reply.redirect(FRONTEND_URL + "/login?error=invalid_request");のように、エラーコードをクエリパラメータとして渡して返す
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
		console.error("[googleCallback] state不一致", {
			queryState: state,
			cookieState: cookieState,
		});
		return reply.code(400).send({ message: "不正なリクエストです" });
	}
	// 使用済みのstateを削除（再利用防止）
	reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });

	if (!code) {
		return reply.code(400).send({ message: "認証コードが見つかりません" });
	}

	try {
		// code をアクセストークンに交換
		const { tokens } = await oauth2Client.getToken(code);
		oauth2Client.setCredentials(tokens);

		// アクセストークンでユーザー情報を取得
		const userInfoRes = await oauth2Client.request<GoogleUserInfo>({
			url: "https://www.googleapis.com/oauth2/v3/userinfo",
		});
		const userInfo = userInfoRes.data;

		// TODO: DBへの保存・セッション作成はここに追加予定。nameは適当な値にする。
		//TODO: name入力画面にリダイレクト。return reply.code(302).redirect("http://localhost:5173/");
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
