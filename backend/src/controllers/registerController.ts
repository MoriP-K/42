import { FastifyRequest, FastifyReply } from 'fastify';
import {
	RegisterRequest,
	RegisterSuccessResponse,
	RegisterErrorResponse,
	RegisterRoute
} from '../types/register';
import { prisma } from '../lib/prisma';

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
 * ユーザー登録エンドポイント
 */
export const registerUser = async (
	request: FastifyRequest<RegisterRoute>,
	reply: FastifyReply<RegisterRoute>
) => {

	const valitationResult = validateRegisterRequest(request.body);
	if (!valitationResult.success) {
		return (reply.code(400).send(valitationResult.error));
	}

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

	//TODO:userDBにINSERT


	// ダミーレスポンス: 成功時 (201)
	const successResponse: RegisterSuccessResponse = {
		userId: 1
	};

	//TODO:ここからログイン処理
	// 1. セッションIDを生成
	// 2. セッションIDとuserIDを紐づけて保存
	// 3. クッキーに設定し、レスポンスを返す

	return (reply.code(201).send(successResponse));
};
