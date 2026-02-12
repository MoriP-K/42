import { z } from 'zod';

export const UserRoleEnum = z.enum(['PLAYER', 'SPECTATOR']);
export const GameModeEnum = z.enum(['DEFAULT', 'ONE_STROKE']);

export const RoomMemberParamsSchema = z.object({
	roomId: z.coerce.number(),
	userId: z.coerce.number(),
});

export const RoomIdParamsSchema = z.object({
	roomId: z.coerce.number(),
});

export const UserIdParamsSchema = z.object({
	userId: z.coerce.number(),
});

export type RoomMemberParams = z.infer<typeof RoomMemberParamsSchema>;
