import { z } from 'zod';

/**
 * PATCH /api/rooms/:roomId/members/:userId パラメータ型
 */
export const UpdateRoomMemberParamsSchema = z.object({
	roomId: z.coerce.number(),
	userId: z.coerce.number(),
});

/**
 * PATCH /api/rooms/:roomId/members/:userId ボディ型
 */
export const UpdateRoomMemberRoleBodySchema = z.object({
	role: z.enum(['PLAYER', 'SPECTATOR']),
});

/**
 * TypeScriptの型をZodから抽出
 */
export type UpdateRoomMemberParams = z.infer<typeof UpdateRoomMemberParamsSchema>;
export type UpdateRoomMemberRoleBody = z.infer<typeof UpdateRoomMemberRoleBodySchema>;

/**
 * Route型
 */
export interface UpdateRoomMemberRoleRoute {
	Params: UpdateRoomMemberParams;
	Body: UpdateRoomMemberRoleBody;
}