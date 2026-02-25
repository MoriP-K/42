import { PrismaClient } from "../../src/generated/prisma/client";
import * as bcrypt from "bcrypt";

export async function seedRunking(prisma: PrismaClient) {
	console.log("🔐 Seeding runking testing...");
	const saltRounds = 10;
	const hashedPassword = await bcrypt.hash("Password123", saltRounds);

	for (let i: number = 0; i < 21; i++)
	{
		const user1 = await prisma.user.upsert({
			where: { name: "user" + i },
			update: {},
			create: {
				name: "user"+i,
				email: "user" + i + "@example.com",
				password: hashedPassword,
				is_profile_complete: true,
				total_score: i,
			},
		});
	}

	console.log("✅ Users seeded:");
}
