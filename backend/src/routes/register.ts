import { FastifyInstance } from 'fastify';
import { registerSchema } from '../schemas/register';
import {
	RegisterRequest,
	RegisterSuccessResponse,
	RegisterErrorResponse
} from '../types/register';

/**
 * POST /api/register
 * ユーザー登録エンドポイント
 */
export async function registerRoutes(fastify: FastifyInstance) {
	fastify.post<{
		Body: RegisterRequest;
		Reply: RegisterSuccessResponse | RegisterErrorResponse;
	}>('/api/register', { schema: registerSchema }, async (request, reply) => {

		console.log("username: ", request.body);
		// ダミーレスポンス: 成功時 (201)
		// TODO: 実際の実装では、ここでバリデーションとDB操作を行う
		const successResponse: RegisterSuccessResponse = {
			userId: 1
		};
		reply.code(201).send(successResponse);

		// ダミーレスポンス: エラー時 (400) の例
		// コメントアウトしていますが、エラー時は以下のように返します：
		// 例)
		// const errorResponse: RegisterErrorResponse = {
		// 	field: 'email',
		// 	message: 'このメールアドレスは既に登録されています'
		// };
		// reply.code(400).send(errorResponse);
	});
}
