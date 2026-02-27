import { FastifyReply } from "fastify";
import { randomUUID } from "crypto";
import { GoogleUserInfo } from "../../types/googleAuth";
import { createSessionAndSetCookie } from "../../lib/login";
import { findUserByGoogleSub } from "../../lib/googleOAuth";
import { prisma } from "../../lib/prisma";

const FRONTEND_URL = process.env.FRONTEND_URL ?? "http://localhost:5173";

const createGoogleUser = async (email: string, sub: string) => {
	return await prisma.$transaction(async tx => {
		const user = await tx.user.create({
			data: {
				name: randomUUID(),
				email,
				password: null,
				is_profile_complete: false,
			},
			select: {
				id: true,
				is_profile_complete: true,
			},
		});
		await tx.userAuthentication.create({
			data: {
				user_id: user.id,
				provider: "google",
				provider_user_id: sub,
			},
		});
		return user;
	});
};

export const handleGoogleRegister = async (
	reply: FastifyReply,
	userInfo: GoogleUserInfo,
) => {
	const existingGoogleUser = await findUserByGoogleSub(userInfo.sub);
	if (existingGoogleUser) {
		return reply.redirect(
			FRONTEND_URL + "/register?error=already_registered",
		);
	}
	// メールアドレスの重複確認
	const emailUser = await prisma.user.findUnique({
		where: { email: userInfo.email },
		select: { id: true },
	});
	if (emailUser) {
		return reply.redirect(
			FRONTEND_URL + "/register?error=already_registered",
		);
	}
	// 新規ユーザー作成 → セッション作成してプロフィール設定へ
	const newUser = await createGoogleUser(userInfo.email, userInfo.sub);
	await createSessionAndSetCookie(reply, newUser.id);
	return reply.redirect(FRONTEND_URL + "/setup-profile");
};
