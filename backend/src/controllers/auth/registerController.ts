import { FastifyRequest, FastifyReply } from 'fastify';
import {
	RegisterRequest,
	RegisterErrorResponse,
	RegisterRoute
} from '../../types/auth/register';
import { prisma } from '../../lib/prisma';
import bcrypt from 'bcrypt';
import { createSessionAndSetCookie } from './loginController'

type ValidateResult = { success: true } | { success: false; error: RegisterErrorResponse };

const validateEmail = (email: string): ValidateResult => {
	const emailRegex = /^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;

	if (!emailRegex.test(email)) {
		return ({
			success: false,
			error: {
				field: "email",
				message: 'メールアドレスの形式が正しくありません'
			}
		});
	}
	return ({ success: true });
};

const validateName = (name: string): ValidateResult => {
	const nameRegex = /^[a-z0-9_]+$/;

	if (!nameRegex.test(name)) {
		return ({
			success: false,
			error: {
				field: "name",
				message: "ユーザー名には半角英数字と「_」のみ使用できます"
			}
		});
	}
	return ({ success: true });
};

const validatePassword = (password: string): ValidateResult => {
	if (password.length < 8) {
		return ({
			success: false,
			error: {
				field: "password",
				message: "パスワードは8文字以上で入力してください"
			}
		});
	}

	const hasUpperCase = /[A-Z]/.test(password);
	const hasLowerCase = /[a-z]/.test(password);
	const hasNumber = /[0-9]/.test(password);
	if (!hasUpperCase || !hasLowerCase || !hasNumber) {
		return ({
			success: false,
			error: {
				field: "password",
				message: "パスワードには英大文字・英小文字・数字をそれぞれ1文字以上含めてください"
			}
		});
	}
	return ({ success: true });
};

const validateRegisterRequest = (body: RegisterRequest): ValidateResult => {
	const emailResult = validateEmail(body.email);
	if (!emailResult.success)
		return (emailResult);

	const nameResult = validateName(body.name);
	if (!nameResult.success)
		return (nameResult);

	const passwordResult = validatePassword(body.password);
	if (!passwordResult.success)
		return (passwordResult);

	return ({ success: true });
};

const checkEmailDuplicate = async (email: string): Promise<ValidateResult> => {
	const existingUser = await prisma.user.findUnique({
		where: { email: email }
	});

	if (existingUser) {
		return {
			success: false,
			error: {
				field: "email",
				message: "このメールアドレスは既に登録されています"
			}
		};
	}
	return { success: true };
};

const checkNameDuplicate = async (name: string): Promise<ValidateResult> => {
	const existingName = await prisma.user.findUnique({
		where: { name: name }
	});

	if (existingName) {
		return ({
			success: false,
			error: {
				field: "name",
				message: "このユーザー名は既に使用されています"
			}
		});
	}
	return ({ success: true });
};

/**
 * POST /api/register
 *
 * 成功: 201 { name }
 * 失敗(パラメータ不備): 400 { field, message }
 * 失敗(サーバーエラー): 500 { message }
 *
 * パラメーターに不備がないか確認後、アカウントを新規作成。
 * 作成したアカウントでログイン処理をした状態でレスポンスを返す。
 */
export const registerUser = async (
	request: FastifyRequest<RegisterRoute>,
	reply: FastifyReply<RegisterRoute>
) => {

	const validationResult = validateRegisterRequest(request.body);
	if (!validationResult.success) {
		return (reply.code(400).send(validationResult.error));
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
			return (reply.code(400).send(nameDupResult.error));
		}

		// userDBにINSERT
		const passwordHash = await bcrypt.hash(request.body.password, 10);
		const createdUser = await prisma.user.create({
			data: {
				name: request.body.name,
				email: request.body.email,
				password: passwordHash
			}
		});

		// 登録成功後、そのままログイン（セッション作成＋Cookieセット）して返す
		try {
			const successResponse = await createSessionAndSetCookie(reply, createdUser.id);
			return reply.code(201).send(successResponse);
		} catch (err) {
			request.log?.error?.(err);
			//TODO: アカウント登録はできたが、ログインに失敗した場合の処理書く。この場合、ログイン画面にリダイレクトする。
			return reply.code(500).send({
				message: 'ユーザー登録は完了しましたが、自動ログイン中にエラーが発生しました。ログイン画面から再度ログインしてください。'
			});
		}

	} catch (err) {
		request.log?.error?.(err);
		return (reply.code(500).send({
			message: '予期しないエラーが発生しました。時間をおいて再度お試しください'
		}));
	}
};
