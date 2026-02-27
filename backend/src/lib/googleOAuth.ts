import { prisma } from "./prisma";

export const findUserByGoogleSub = async (sub: string) => {
	const userAuth = await prisma.userAuthentication.findUnique({
		where: {
			provider_provider_user_id: {
				provider: "google",
				provider_user_id: sub,
			},
		},
		include: {
			user: {
				select: {
					id: true,
					is_profile_complete: true,
				},
			},
		},
	});
	if (!userAuth) return null;
	return userAuth.user;
};
