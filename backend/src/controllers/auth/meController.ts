import { FastifyReply, FastifyRequest } from 'fastify';
import { prisma } from '../../lib/prisma';
import { MeRoute } from '../../types/auth/me';

/**
 * GET /api/me
 *
 * 成功(ログイン済み): 200 { name }
 * 失敗(未ログイン): 401 { message }
 * 失敗(サーバーエラー): 500 { message }
 *
 * セッションIDは Cookie(session_id) から取得し、
 * Sessionテーブルの revoked_at/expires_at を検証して user を返す。
 */
export const me = async (request: FastifyRequest<MeRoute>, reply: FastifyReply<MeRoute>) => {
	const cookieName = 'session_id';
	const sessionId = request.cookies?.[cookieName];

	if (!sessionId) {
		return reply.code(401).send({ message: 'Unauthorized' });
	}

	try {
		const session = await prisma.session.findUnique({
			where: { id: sessionId },
			include: {
				user: {
					select: {
						id: true,
						name: true,
					},
				},
			},
		});

		const now = new Date();
		if (!session) {
			return reply.code(401).send({ message: 'Unauthorized' });
		}
		if (session.revoked_at !== null) {
			return reply.code(401).send({ message: 'Unauthorized' });
		}
		if (session.expires_at <= now) {
			return reply.code(401).send({ message: 'Unauthorized' });
		}

		return reply.code(200).send({
			id: session.user.id,
			name: session.user.name,
		});
	} catch (err) {
		request.log?.error?.(err);
		return reply.code(500).send({
			message: '予期しないエラーが発生しました。時間をおいて再度お試しください'
		});
	}
};
