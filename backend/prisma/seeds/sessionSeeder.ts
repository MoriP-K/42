import { PrismaClient } from '../../src/generated/prisma/client';
import { randomUUID } from 'node:crypto';

export async function seedSessions(prisma: PrismaClient) {
	console.log('🔐 Seeding sessions for auth testing...');

	// alice ユーザーを取得（既に seed.ts で作成されている前提）
	const alice = await prisma.user.findUnique({ where: { name: 'alice' } });

	if (!alice) {
		throw new Error('User "alice" not found. Please ensure alice is created in the main seeder.');
	}

	const now = new Date();

	// 有効なセッション（revoked_at が NULL かつ expires_at が未来）
	const validSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: alice.id,
			expires_at: new Date(now.getTime() + 24 * 60 * 60 * 1000), // 1日後
			revoked_at: null,
		},
	});

	// 有効期限が過ぎているセッション（expires_at が過去）
	const expiredSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: alice.id,
			expires_at: new Date(now.getTime() - 60 * 60 * 1000), // 1時間前
			revoked_at: null,
		},
	});

	// 無効化されているセッション（revoked_at が非NULL）
	const revokedSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: alice.id,
			expires_at: new Date(now.getTime() + 24 * 60 * 60 * 1000), // 1日後
			revoked_at: now,
		},
	});

	console.log('✅ Sessions seeded');
	console.log('   Valid session ID:', validSession.id);
	console.log('   Expired session ID:', expiredSession.id);
	console.log('   Revoked session ID:', revokedSession.id);

	console.log('\n📋 Test commands:');
	console.log(`# 有効なセッション\ncurl -i -H "Cookie: session_id=${validSession.id}" http://localhost:3000/api/me\n`);
	console.log(`# 無効なセッション(有効期限が過ぎている)\ncurl -i -H "Cookie: session_id=${expiredSession.id}" http://localhost:3000/api/me\n`);
	console.log(`# 無効なセッション(無効化されている)\ncurl -i -H "Cookie: session_id=${revokedSession.id}" http://localhost:3000/api/me\n`);

	return { validSession, expiredSession, revokedSession };
}
