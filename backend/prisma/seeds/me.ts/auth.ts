import { randomUUID } from 'node:crypto';
import { PrismaClient } from "../../src/generated/prisma/client";
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

	//有効期限が過ぎているセッション（expires_at が過去）
	const expiredSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: alice.id,
			expires_at: new Date(now.getTime() - 60 * 60 * 1000),
			revoked_at: null,
		},
	});

	//無効化されているセッション（revoked_at が非NULL）
	const revokedSession = await prisma.session.create({
		data: {
			id: randomUUID(),
			user_id: alice.id,
			expires_at: new Date(now.getTime() + 24 * 60 * 60 * 1000), // 1日後
			revoked_at: now,
		},
	});

	console.log('seed_user:', { id: alice.id, name: alice.name });
	console.log('valid_session_id:', validSession.id);
	console.log('expired_session_id:', expiredSession.id);
	console.log('revoked_session_id:', revokedSession.id);

	console.log('\n以下のテストコマンドを実行してください:');
	console.log(`# 有効なセッション\ncurl -i -H "Cookie: session_id=${validSession.id}" http://localhost:3000/api/me\n`);
	console.log(`# 無効なセッション(有効期限が過ぎている)\ncurl -i -H "Cookie: session_id=${expiredSession.id}" http://localhost:3000/api/me\n`);
	console.log(`# 無効なセッション(無効化されている)\ncurl -i -H "Cookie: session_id=${revokedSession.id}" http://localhost:3000/api/me\n`);
	console.log(`# 無効なセッション(session_idが空)\ncurl -i -H "Cookie: session_id=" http://localhost:3000/api/me\n`);

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
