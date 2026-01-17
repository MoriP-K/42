import { PrismaClient } from '../generated/prisma/client';

/**
 * LaravelのDB接続やModelの起点にあたるシングルトンインスタンス
 * どこからでも import { prisma } from '../lib/prisma' で利用可能にします
 */
const globalForPrisma = global as unknown as { prisma: PrismaClient };

export const prisma =
    globalForPrisma.prisma ||
    new PrismaClient({
        log: ['query'], // 開発中に発行されたSQLをログ出力（LaravelのDBログ相当）
    });

if (process.env.NODE_ENV !== 'production')
	globalForPrisma.prisma = prisma;
