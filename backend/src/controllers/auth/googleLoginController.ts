import { FastifyReply } from "fastify";
import { GoogleUserInfo } from "../../types/googleAuth";
import { createSessionAndSetCookie } from "../../lib/login";
import { findUserByGoogleSub } from "../../lib/googleOAuth";
import { prisma } from "../../lib/prisma";

const FRONTEND_URL = process.env.FRONTEND_URL ?? "http://localhost:5173";

export const handleGoogleLogin = async (
	reply: FastifyReply,
	userInfo: GoogleUserInfo,
) => {
	const existingGoogleUser = await findUserByGoogleSub(userInfo.sub);
	if (!existingGoogleUser) {
		// Googleアカウント未登録 → メールアドレスの重複確認
		const emailUser = await prisma.user.findUnique({
			where: { email: userInfo.email },
			select: { id: true },
		});
		if (emailUser) {
			return reply.redirect(FRONTEND_URL + "/login?error=email_conflict");
		}
		return reply.redirect(FRONTEND_URL + "/login?error=account_not_found");
	}
	// 既存Googleユーザー → セッション作成してトップへ
	await createSessionAndSetCookie(reply, existingGoogleUser.id);
	return reply.redirect(FRONTEND_URL + "/");
};
