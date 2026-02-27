import { FastifyRequest, FastifyReply } from "fastify";
import { OAuth2Client } from "google-auth-library";
import { randomUUID } from "crypto";
import {
	GoogleAuthQuerystring,
	GoogleCallbackQuerystring,
	GoogleUserInfo,
	OAuthState,
} from "../../types/googleAuth";
import { handleGoogleRegister } from "./googleRegisterController";

const GOOGLE_CLIENT_ID = process.env.GOOGLE_CLIENT_ID ?? "";
const GOOGLE_CLIENT_SECRET = process.env.GOOGLE_CLIENT_SECRET ?? "";
const GOOGLE_REDIRECT_URI = process.env.GOOGLE_REDIRECT_URI ?? "";
const FRONTEND_URL = process.env.FRONTEND_URL ?? "http://localhost:5173";

const oauth2Client = new OAuth2Client(
	GOOGLE_CLIENT_ID,
	GOOGLE_CLIENT_SECRET,
	GOOGLE_REDIRECT_URI,
);

export const googleAuth = async (
	request: FastifyRequest<{ Querystring: GoogleAuthQuerystring }>,
	reply: FastifyReply,
) => {
	const { mode } = request.query;
	if (mode !== "login" && mode !== "register") {
		return reply.code(400).send({
			message:
				"modeパラメータは login または register である必要があります",
		});
	}

	const nonce = randomUUID();
	const oauthState: OAuthState = { nonce, mode };
	const stateStr = JSON.stringify(oauthState);

	reply.setCookie("oauth_state", stateStr, {
		path: "/",
		httpOnly: true,
		sameSite: "lax",
		secure: process.env.NODE_ENV === "production",
		maxAge: 60 * 10, // 10分
	});

	const authUrl = oauth2Client.generateAuthUrl({
		access_type: "online",
		scope: ["openid", "email", "profile"],
		state: stateStr,
	});

	return reply.redirect(authUrl);
};

const parseModeFromCookieState = (
	cookieStateRaw: string | undefined,
): "login" | "register" | null => {
	if (!cookieStateRaw) return null;
	try {
		const parsed = JSON.parse(cookieStateRaw) as OAuthState;
		if (parsed.mode === "login" || parsed.mode === "register") {
			return parsed.mode;
		}
		return null;
	} catch {
		return null;
	}
};

const exchangeCodeForUserInfo = async (
	code: string,
): Promise<GoogleUserInfo> => {
	// code をアクセストークンに交換
	const { tokens } = await oauth2Client.getToken(code);
	oauth2Client.setCredentials(tokens);

	// アクセストークンでユーザー情報を取得
	const userInfoRes = await oauth2Client.request<GoogleUserInfo>({
		url: "https://www.googleapis.com/oauth2/v3/userinfo",
	});
	return userInfoRes.data;
};

export const googleCallback = async (
	request: FastifyRequest<{ Querystring: GoogleCallbackQuerystring }>,
	reply: FastifyReply,
) => {
	const { code, error, state } = request.query;

	// CookieのstateからmodeをパースしてerrorBaseを決定
	const cookieStateRaw = request.cookies?.oauth_state;
	const mode = parseModeFromCookieState(cookieStateRaw);
	if (mode === null) {
		reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });
		return reply.redirect(FRONTEND_URL + "/login?error=invalid_request");
	}
	const errorBase = `${FRONTEND_URL}/${mode}`;

	// Googleからエラーが返された場合（ユーザーが認証を拒否した場合など）
	if (error) {
		reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });
		return reply.redirect(errorBase + "?error=invalid_request");
	}

	// state検証（CSRF対策）
	if (!state || !cookieStateRaw || state !== cookieStateRaw) {
		reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });
		return reply.redirect(errorBase + "?error=invalid_request");
	}

	// 使用済みstateを削除（再利用防止）
	reply.setCookie("oauth_state", "", { maxAge: 0, path: "/" });

	if (!code) {
		return reply.redirect(errorBase + "?error=invalid_request");
	}

	try {
		const userInfo = await exchangeCodeForUserInfo(code);
		if (!userInfo.email || !userInfo.email_verified) {
			return reply.redirect(errorBase + "?error=server_error");
		}
		// modeごとに処理
		if (mode === "login") {
			//TODO: ログイン処理
		} else if (mode === "register") {
			return await handleGoogleRegister(reply, userInfo);
		} else {
			return reply.redirect(
				FRONTEND_URL + "/login?error=invalid_request",
			);
		}
	} catch (err) {
		console.error("[googleCallback] 予期しないエラー:", err);
		return reply.redirect(errorBase + "?error=server_error");
	}
};
