import { FastifyRequest, FastifyReply } from 'fastify';
import {
	RegisterRequest,
	RegisterSuccessResponse,
	RegisterErrorResponse,
	RegisterRoute
} from '../types/register';

type ValidateResult = { success: true } | { success: false; error: RegisterErrorResponse };

const ValidateEmail = (email: string): ValidateResult => {
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

const ValidateName = (name: string): ValidateResult => {
	const nameRegex = /^[a-z0-9_]$/;

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

const ValidatePassword = (password: string): ValidateResult => {
	if (password.length < 8) {
		return ({
			success: false,
			error: {
				field: "password",
				message: "パスワードは8文字以上で入力してください"
			}
		});
	}

	const hasUpperCase = /[0-9]/.test(password);
	const hasLowerCase = /[a-z]/.test(password);
	const hasNumber = /[A-Z]/.test(password);
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

const ValidateRegisterRequest = (body: RegisterRequest): ValidateResult => {
	const emailResut = ValidateEmail(body.email);
	if (!emailResut.success)
		return (emailResut);

	const nameResut = ValidateName(body.name);
	if (!nameResut.success)
		return (nameResut);

	const passwordResut = ValidatePassword(body.password);
	if (!passwordResut.success)
		return (passwordResut);

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
	const valitationResult = ValidateRegisterRequest(request.body);
	if (!valitationResult.success) {
		return (reply.code(400).send(valitationResult.error));
	}

	// ダミーレスポンス: 成功時 (201)
	const successResponse: RegisterSuccessResponse = {
		userId: 1
	};
	return (reply.code(201).send(successResponse));
};
