import { FastifyReply, FastifyRequest } from "fastify";
import { prisma } from "../../lib/prisma";
import { UpdateMeRequest, UpdateMeRoute } from "../../types/auth/me";

/**
 * PATCH /api/me
 *
 * セッション Cookie でユーザー取得（認証チェック）し、
 * name の重複チェック後に User.name と is_profile_complete を更新する。
 *
 * 成功: 200 { id, name, is_profile_complete: true }
 * 失敗(未ログイン): 401 { message }
 * 失敗(バリデーション・名前重複): 400 { message }
 * 失敗(サーバーエラー): 500 { message }
 */
export const updateMe = async (
	request: FastifyRequest<UpdateMeRoute>,
	reply: FastifyReply<UpdateMeRoute>,
) => {
	const cookieName = "session_id";
	const sessionId = request.cookies?.[cookieName];

	if (!sessionId) {
		return reply.code(401).send({ message: "Unauthorized" });
	}

	const parsed = UpdateMeRequest.safeParse(request.body);
	if (!parsed.success) {
		const firstIssue = parsed.error.issues[0];
		const message = firstIssue?.message ?? "入力に不備があります。";
		return reply.code(400).send({ message });
	}
	const { name } = parsed.data;

	try {
		const session = await prisma.session.findUnique({
			where: { id: sessionId },
			include: {
				user: {
					select: {
						id: true,
					},
				},
			},
		});

		//セッションの有効チェック
		const now = new Date();
		if (!session) {
			return reply.code(401).send({ message: "Unauthorized" });
		}
		if (session.revoked_at !== null) {
			return reply.code(401).send({ message: "Unauthorized" });
		}
		if (session.expires_at <= now) {
			return reply.code(401).send({ message: "Unauthorized" });
		}

		//nameの重複チェック
		const existingUserWithName = await prisma.user.findUnique({
			where: { name },
			select: { id: true },
		});
		if (
			existingUserWithName !== null &&
			existingUserWithName.id !== session.user.id
		) {
			return reply.code(400).send({
				message: "このユーザー名は既に使用されています",
			});
		}

		//DBインサート
		const updatedUser = await prisma.user.update({
			where: { id: session.user.id },
			data: {
				name,
				is_profile_complete: true,
			},
			select: {
				id: true,
				name: true,
			},
		});

		return reply.code(200).send({
			id: updatedUser.id,
			name: updatedUser.name,
			is_profile_complete: true,
		});
	} catch (err) {
		request.log?.error?.(err);
		return reply.code(500).send({
			message:
				"予期しないエラーが発生しました。時間をおいて再度お試しください",
		});
	}
};
