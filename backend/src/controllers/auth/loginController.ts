import { FastifyRequest, FastifyReply } from 'fastify';
import { AuthSuccessResponse } from '../../types/auth/common';
import { prisma } from '../../lib/prisma';
import { randomUUID } from 'crypto';


export const login = async (reply: FastifyReply, userId: number) => {
	// セッションIDとuserIDを紐づけて保存
	const now = new Date();
	const newSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: userId,
			expires_at: new Date(now.getTime() + 24 * 60 * 60 * 1000),
		},
		include: {
			user: {
				select: {
					name: true,
				},
			},
		},
	});

	// Cookie に session_id をセット（credentials: 'include' で送受信される）
	reply.setCookie('session_id', newSession.id, {
		path: '/',
		httpOnly: true,
		sameSite: 'lax',
		secure: false,
		expires: newSession.expires_at,
	})

	const successResponse: AuthSuccessResponse = {
		name: newSession.user.name,
	}
	return (successResponse)
}
