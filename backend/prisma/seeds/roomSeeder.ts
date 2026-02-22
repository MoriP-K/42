import { PrismaClient } from "../../src/generated/prisma/client";
import { randomUUID } from "node:crypto";

export async function seedRooms(prisma: PrismaClient) {
	console.log("🏠 Seeding rooms...");

	// ユーザーを取得（既に seed.ts で作成されている前提）
	const funa = await prisma.user.findUnique({ where: { name: "funa" } });
	const ken = await prisma.user.findUnique({ where: { name: "ken" } });
	const mori = await prisma.user.findUnique({ where: { name: "mori" } });
	const nusu = await prisma.user.findUnique({ where: { name: "nusu" } });

	if (!mori || !ken || !funa || !nusu) {
		throw new Error("Users not found. Please run user seeder first.");
	}

	// Room 1: funa がホスト、DEFAULT モード
	const room1 = await prisma.room.upsert({
		where: { id: 1 },
		update: {},
		create: {
			id: 1,
			host_id: funa.id,
			game_mode: "DEFAULT",
			status: "WAITING",
			invitation_token: randomUUID(),
			members: {
				create: [
					{
						user_id: funa.id,
						role: "SPECTATOR",
						is_ready: false,
					},
					{
						user_id: ken.id,
						role: "PLAYER",
						is_ready: false,
					},
					{
						user_id: nusu.id,
						role: "PLAYER",
						is_ready: false,
					},
					{
						user_id: mori.id,
						role: "PLAYER",
						is_ready: false,
					},
				],
			},
		},
	});

	// Room 2: ken がホスト、ONE_STROKE モード
	const room2 = await prisma.room.upsert({
		where: { id: 2 },
		update: {},
		create: {
			id: 2,
			host_id: ken.id,
			game_mode: "ONE_STROKE",
			status: "WAITING",
			invitation_token: randomUUID(),
			members: {
				create: [
					{
						user_id: ken.id,
						role: "PLAYER",
						is_ready: true,
					},
					{
						user_id: mori.id,
						role: "PLAYER",
						is_ready: false,
					},
				],
			},
		},
	});

	// Round 1: nusuがDrawer
	await prisma.round.upsert({
		where: { id: 1 },
		update: {},
		create: {
			id: 1,
			room_id: room1.id,
			drawer_id: nusu.id,
			started_at: new Date(),
			ended_time: null,
		},
	});

	console.log("✅ Rooms seeded:", { room1, room2 });
	console.log("✅ Round seeded");

	return { room1, room2 };
}
