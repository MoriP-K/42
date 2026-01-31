import { z } from 'zod';

// パラメータ用のスキーマ
export const UpdateMemberParamsSchema = z.object({
	id: z.coerce.number(),
	userId: z.coerce.number(),
});

// ボディ用のスキーマ
export const UpdateMemberBodySchema = z.object({
	role: z.enum(['player', 'spectator']),
});

// TypeScriptの型をZodから抽出
export type UpdateMemberParams = z.infer<typeof UpdateMemberParamsSchema>;
export type UpdateMemberBody = z.infer<typeof UpdateMemberBodySchema>;

export interface UpdateMemberRoute {
	Params: UpdateMemberParams;
	Body: UpdateMemberBody;
}