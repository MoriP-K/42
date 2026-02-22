import { prisma } from "../lib/prisma";

/*
 * ユーザのステータスを変更する
 */
export const updateReadyStatus = async (
	roomId: number,
	userId: number,
	isReady: boolean,
) => {
	return prisma.roomMember.update({
		where: {
			room_id_user_id: {
				room_id: roomId,
				user_id: userId,
			},
		},
		data: {
			is_ready: isReady,
		},
	});
};
