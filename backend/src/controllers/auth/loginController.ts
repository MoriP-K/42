import { FastifyRequest, FastifyReply } from 'fastify';
import { AuthSuccessResponse } from '../../types/auth/common';
import { prisma } from '../../lib/prisma';
import { randomUUID } from 'crypto';

const SESSION_TTL_MS = 24 * 60 * 60 * 1000 //1日

export const login = async (reply: FastifyReply, userId: number) => {
	// セッションIDとuserIDを紐づけて保存
	const now = new Date();
	const newSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: userId,
			expires_at: new Date(now.getTime() + SESSION_TTL_MS),
		},
		include: {
			user: {
				select: {
					name: true,
				},
			},
		},
	});

	//TODO: データーベース接続エラー時の処理書く

	// Cookie に session_id をセット
	reply.setCookie('session_id', newSession.id, {
		path: '/',
		httpOnly: true,
		sameSite: 'lax',
		secure: process.env.NODE_ENV === 'production',
		expires: newSession.expires_at,
	});

	const successResponse: AuthSuccessResponse = {
		name: newSession.user.name,
	};
	return (successResponse)
}
