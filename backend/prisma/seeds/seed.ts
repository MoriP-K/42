import { PrismaClient } from "../../src/generated/prisma/client";
import * as bcrypt from "bcrypt";
import { seedRooms } from "./roomSeeder";
import { seedSessions } from "./sessionSeeder";
import { seedBadegs } from "./badgesSeeder";

const prisma = new PrismaClient();

async function main() {
	console.log("🌱 Starting database seeding...\n");

	// 1. Seed Users
	console.log("👤 Seeding users...");
	const saltRounds = 10;
	const hashedPassword = await bcrypt.hash("Password123", saltRounds);

	const funa = await prisma.user.upsert({
		where: { name: "funa" },
		update: {},
		create: {
			name: "funa",
			email: "funa@example.com",
			password: hashedPassword,
			is_profile_complete: true,
		},
	});

	const ken = await prisma.user.upsert({
		where: { name: "ken" },
		update: {},
		create: {
			name: "ken",
			email: "ken@example.com",
			password: hashedPassword,
			is_profile_complete: true,
		},
	});

	const nusu = await prisma.user.upsert({
		where: { name: "nusu" },
		update: {},
		create: {
			name: "nusu",
			email: "nusu@example.com",
			password: hashedPassword,
			is_profile_complete: true,
		},
	});

	const mori = await prisma.user.upsert({
		where: { name: "mori" },
		update: {},
		create: {
			name: "mori",
			email: "mori@example.com",
			password: hashedPassword,
			is_profile_complete: true,
		},
	});

	const alice = await prisma.user.upsert({
		where: { name: "alice" },
		update: {},
		create: {
			name: "alice",
			email: "alice@example.com",
			password: hashedPassword,
			is_profile_complete: true,
		},
	});

	console.log("✅ Users seeded:", { mori, ken, nusu, funa, alice });

	// 2. Seed Badges
	console.log("\n🏅 Seeding badges...");
	const firstWin = await prisma.badge.upsert({
		where: { id: 1 },
		update: {},
		create: {
			name: "First Win",
			description: "Won your first game!",
		},
	});

	const happyPlayer = await prisma.badge.upsert({
		where: { id: 2 },
		update: {
			name: "happy player",
			description: "you played 5 times",
		},
		create: {
			name: "happy player",
			description: "you played 5 times",
		},
	});

	const richScore = await prisma.badge.upsert({
		where: { id: 3 },
		update: {},
		create: {
			name: "rich score",
			description: "you get 100 score",
		},
	});

	console.log("✅ Badges seeded:", { firstWin, happyPlayer, richScore });

	// 3. Seed UserBadges
	console.log("\n🎖️  Seeding user badges...");
	await prisma.userBadge.upsert({
		where: {
			user_id_badge_id: {
				user_id: mori.id,
				badge_id: firstWin.id,
			},
		},
		update: {},
		create: {
			user_id: mori.id,
			badge_id: firstWin.id,
		},
	});

	console.log("✅ User badges seeded");

	// 4. Seed Rooms (with members)
	console.log("");
	await seedRooms(prisma);

	// 5. Seed Sessions (for auth testing)
	console.log("");
	await seedSessions(prisma);

	// 6. badges data & user score update (for profile)
	console.log("");
	await seedBadegs(prisma);

	console.log("\n🎉 All seeding completed successfully!");
}

main()
	.then(async () => {
		await prisma.$disconnect();
	})
	.catch(async e => {
		console.error(e);
		await prisma.$disconnect();
		process.exit(1);
	});
