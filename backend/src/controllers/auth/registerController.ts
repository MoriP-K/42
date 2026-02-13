import { FastifyRequest, FastifyReply } from "fastify";
import { RegisterRequest, RegisterRoute } from "../../types/auth/register";
import { AuthErrorResponse } from "../../types/auth/common";
import { prisma } from "../../lib/prisma";
import bcrypt from "bcrypt";
import { createSessionAndSetCookie } from "./loginController";

type ValidateResult =
	| { success: true }
	| { success: false; error: AuthErrorResponse };

const checkEmailDuplicate = async (email: string): Promise<ValidateResult> => {
	const existingUser = await prisma.user.findUnique({
		where: { email: email },
	});

	if (existingUser) {
		return {
			success: false,
			error: {
				message: "このメールアドレスは既に登録されています",
			},
		};
	}
	return { success: true };
};

const checkNameDuplicate = async (name: string): Promise<ValidateResult> => {
	const existingName = await prisma.user.findUnique({
		where: { name: name },
	});

	if (existingName) {
		return {
			success: false,
			error: {
				message: "このユーザー名は既に使用されています",
			},
		};
	}
	return { success: true };
};

/**
 * POST /api/register
 *
 * 成功: 201 { name }
 * 失敗(パラメータ不備): 400 { message }
 * 失敗(サーバーエラー): 500 { message }
 *
 * パラメーターに不備がないか確認後、アカウントを新規作成。
 * 作成したアカウントでログイン処理をした状態でレスポンスを返す。
 */
export const registerUser = async (
	request: FastifyRequest<RegisterRoute>,
	reply: FastifyReply<RegisterRoute>,
) => {
	const parsed = RegisterRequest.safeParse(request.body);
	if (!parsed.success) {
		const issue = parsed.error.issues[0];
		const message = issue?.message ?? "test";

		return reply.code(400).send({
			message,
		});
	}

	try {
		// emailの重複チェック
		const emailDupResult = await checkEmailDuplicate(request.body.email);
		if (!emailDupResult.success) {
			return reply.code(400).send(emailDupResult.error);
		}

		//nameの重複チェック
		const nameDupResult = await checkNameDuplicate(request.body.name);
		if (!nameDupResult.success) {
			return reply.code(400).send(nameDupResult.error);
		}

		// userDBにINSERT
		const passwordHash = await bcrypt.hash(request.body.password, 10);
		const createdUser = await prisma.user.create({
			data: {
				name: request.body.name,
				email: request.body.email,
				password: passwordHash,
			},
		});

		// 登録成功後、そのままログイン（セッション作成＋Cookieセット）して返す
		try {
			const successResponse = await createSessionAndSetCookie(
				reply,
				createdUser.id,
			);
			return reply.code(201).send(successResponse);
		} catch (err) {
			request.log?.error?.(err);
			//TODO: アカウント登録はできたが、ログインに失敗した場合の処理書く。この場合、ログイン画面にリダイレクトする。
			return reply.code(500).send({
				message:
					"ユーザー登録は完了しましたが、自動ログイン中にエラーが発生しました。ログイン画面から再度ログインしてください。",
			});
		}
	} catch (err) {
		request.log?.error?.(err);
		return reply.code(500).send({
			message:
				"予期しないエラーが発生しました。時間をおいて再度お試しください",
		});
	}
};
