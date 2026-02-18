const GOOGLE_CLIENT_ID = import.meta.env.VITE_GOOGLE_CLIENT_ID as string;
const GOOGLE_REDIRECT_URI = import.meta.env.VITE_GOOGLE_REDIRECT_URI as string;

export function GoogleAccountRegister() {
	const handleGoogleAuth = () => {
		const params = new URLSearchParams({
			client_id: GOOGLE_CLIENT_ID,
			redirect_uri: GOOGLE_REDIRECT_URI,
			response_type: "code",
			scope: "openid email profile",
			access_type: "offline",
			prompt: "consent",
		});

		const authUrl = `https://accounts.google.com/o/oauth2/v2/auth?${params}`;
		window.location.href = authUrl;
	};

	return (
		<button
			type="button"
			className="btn btn-outline w-full"
			onClick={handleGoogleAuth}
		>
			<span className="inline-flex items-center gap-2">
				<span className="i" aria-hidden="true">
					G
				</span>
				Googleアカウントで登録
			</span>
		</button>
	);
}
