import { PrismaClient } from "../../src/generated/prisma/client";
import { randomUUID } from "node:crypto";

export async function seedBadegs(prisma: PrismaClient) {
	console.log("🔐 Seeding sessions for auth testing...");

	// alice ユーザーを取得（既に seed.ts で作成されている前提）
	const alice = await prisma.user.findUnique({ where: { name: "alice" } });

	// userBadgesとusersを更新
	await prisma.userBadge.upsert({
		where: {
			user_id_badge_id: {
				user_id: alice.id,
				badge_id: 1,
			},
		},
		update: {},
		create: {
			user_id: alice.id,
			badge_id: 1,
		},
	});

	await prisma.userBadge.upsert({
		where: {
			user_id_badge_id: {
				user_id: alice.id,
				badge_id: 2,
			},
		},
		update: {},
		create: {
			user_id: alice.id,
			badge_id: 2,
		},
	});

	await prisma.userBadge.upsert({
		where: {
			user_id_badge_id: {
				user_id: alice.id,
				badge_id: 3,
			},
		},
		update: {},
		create: {
			user_id: alice.id,
			badge_id: 3,
		},
	});




	const now = new Date();

	console.log("✅ badges seeded");

	return {  };
}
