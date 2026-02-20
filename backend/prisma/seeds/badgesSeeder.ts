import { PrismaClient } from "../../src/generated/prisma/client";
import { randomUUID } from "node:crypto";

export async function seedBadegs(prisma: PrismaClient) {
	console.log("🔐 Seeding sessions for auth testing...");

	// users tableのbadges[]を全削除
	const delete_user_badges = await prisma.user.update({
										data: {badges: null },
										where: { name: "alice" } });

	// userBadgeのデータを削除
	const delete_useBadge = await prisma.userBadge.delete({ where: { user_id: 1 } });

	// badges tableからSocial Butterflyを削除
	const delete_socialButterfly = await prisma.badge.delete({ where: { name: "SocialButterfly" } });
	console.log("✅ delete old data:", { delete_user_badges, delete_useBadge, delete_socialButterfly });

	// badges tableに新規データを追加
	const add_badge_play_count = await prisma.badge.create({ data: { id: 2, name: "", description: ""}});
	const add_badge_total_score = await prisma.badge.create({ data: { id: 3, name: "", description: ""}});
	console.log("✅ add badge data:", { add_badge_play_count, add_badge_total_score });

	// userBadgesとusersを更新
		// funaはすべてのバッジを持つ
		// kenは一つのバッジを持つ


	const now = new Date();

	console.log("✅ Sessions seeded");

	return { validSession };
}
