import { FastifyReply, FastifyRequest } from 'fastify';
import { prisma } from '../../lib/prisma';
import { MeRoute } from '../../types/me';

const DEFAULT_SESSION_COOKIE_NAME = 'session_id';

function parseCookieHeader(cookieHeader: string | undefined): Record<string, string> {
	if (!cookieHeader) return {};

	const out: Record<string, string> = {};
	for (const part of cookieHeader.split(';')) {
		const [rawKey, ...rawValueParts] = part.trim().split('=');
		if (!rawKey) continue;
		const rawValue = rawValueParts.join('=');
		out[rawKey] = decodeURIComponent(rawValue ?? '');
	}
	return out;
}

function buildSetCookieHeader(params: {
	name: string;
	value: string;
	expiresAt: Date;
}): string {
	const cookieName = params.name;
	const cookieValue = encodeURIComponent(params.value);

	const pieces = [
		`${cookieName}=${cookieValue}`,
		'Path=/',
		'HttpOnly',
		'SameSite=Lax',
		`Expires=${params.expiresAt.toUTCString()}`,
	];

	// HTTPS環境のときだけ Secure を付ける
	if (process.env.NODE_ENV === 'production') {
		pieces.push('Secure');
	}

	return pieces.join('; ');
}

/**
 * GET /api/me
 *
 * 成功(ログイン済み): 200 { id, name }
 * 失敗(未ログイン): 401
 *
 * セッションIDは Cookie(session_id) から取得し、
 * Sessionテーブルの revoked_at/expires_at を検証して user を返す。
 */
export const me = async (request: FastifyRequest<MeRoute>, reply: FastifyReply<MeRoute>) => {
	const cookieName = process.env.SESSION_COOKIE_NAME ?? DEFAULT_SESSION_COOKIE_NAME;
	const cookies = parseCookieHeader(request.headers.cookie);
	const sessionId = cookies[cookieName];

	if (!sessionId) {
		return reply.code(401).send({ message: 'Unauthorized' });
	}

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

	// 期限の延長はしない（仕様に無い）。ただし要求通り Set-Cookie は再送する。
	reply.header(
		'Set-Cookie',
		buildSetCookieHeader({
			name: cookieName,
			value: session.id,
			expiresAt: session.expires_at,
		}),
	);

	return reply.code(200).send({
		id: session.user.id,
		name: session.user.name,
	});
};
