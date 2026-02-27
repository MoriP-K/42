const BACKEND_URL = import.meta.env.VITE_API_URL || "http://localhost:3000";

export function GoogleAccountRegister() {
	const handleGoogleAuth = () => {
		window.location.href = `${BACKEND_URL}/v1/auth/google/auth?mode=register`;
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
