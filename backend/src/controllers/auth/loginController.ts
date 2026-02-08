import { FastifyRequest, FastifyReply } from 'fastify';
import {
	AuthSuccessResponse,
} from '../../types/auth/common';
import {
	LoginRequest,
	LoginRoute,
} from '../../types/auth/login';
import { prisma } from '../../lib/prisma';
import { randomUUID } from 'crypto';
import bcrypt from 'bcrypt';

const SESSION_TTL_MS = 24 * 60 * 60 * 1000 //1日

export const createSessionAndSetCookie = async (reply: FastifyReply, userId: number) => {
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

export const login = async (
	request: FastifyRequest<LoginRoute>,
	reply: FastifyReply<LoginRoute>
) => {
	const parsed = LoginRequest.safeParse(request.body);
	if (!parsed.success) {
		return reply.code(400).send({
			message: 'メールアドレスまたはパスワードが正しくありません'
		});
	}
	const { email, password } = parsed.data;

	try {
		const user = await prisma.user.findUnique({
			where: { email },
			select: {
				id: true,
				password: true,
			},
		});

		if (!user) {
			return reply.code(400).send({
				message: 'メールアドレスまたはパスワードが正しくありません'
			});
		}

		const ok = await bcrypt.compare(password, user.password);
		if (!ok) {
			return reply.code(400).send({
				message: 'メールアドレスまたはパスワードが正しくありません'
			});
		}

		const successResponse = await createSessionAndSetCookie(reply, user.id);
		return reply.code(201).send(successResponse);
	} catch (err) {
		request.log?.error?.(err);
		return reply.code(500).send({
			message: '予期しないエラーが発生しました。時間をおいて再度お試しください'
		});
	}
}
