import { PrismaClient } from '../../src/generated/prisma/client';
import * as bcrypt from 'bcrypt';

const prisma = new PrismaClient();

async function main() {
	const saltRounds = 10;
	const hashedPassword = await bcrypt.hash('Password123', saltRounds);

	// Seed Users
	const alice = await prisma.user.upsert({
		where: { name: 'alice' },
		update: {},
		create: {
			name: 'alice',
			email: 'alice@example.com',
			password: hashedPassword,
		},
	});

	const bob = await prisma.user.upsert({
		where: { name: 'bob' },
		update: {},
		create: {
			name: 'bob',
			email: 'bob@example.com',
			password: hashedPassword,
		},
	});

	// Seed Badges
	const firstWin = await prisma.badge.upsert({
		where: { id: 1 },
		update: {},
		create: {
			name: 'First Win',
			description: 'Won your first game!',
		},
	});

	const socialButterfly = await prisma.badge.upsert({
		where: { id: 2 },
		update: {},
		create: {
			name: 'Social Butterfly',
			description: 'Played with 5 different users.',
		},
	});

	// Seed UserBadges
	await prisma.userBadge.upsert({
		where: {
			user_id_badge_id: {
				user_id: alice.id,
				badge_id: firstWin.id,
			},
		},
		update: {},
		create: {
			user_id: alice.id,
			badge_id: firstWin.id,
		},
	});

	console.log({ alice, bob, firstWin, socialButterfly });
}

main()
	.then(async () => {
		await prisma.$disconnect();
	})
	.catch(async (e) => {
		console.error(e);
		await prisma.$disconnect();
		process.exit(1);
	});
