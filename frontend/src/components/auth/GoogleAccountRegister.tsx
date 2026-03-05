import { getBackendBaseUrl } from "../../api/backendUrl";

export function GoogleAccountRegister() {
	const handleGoogleAuth = () => {
		window.location.href = `${getBackendBaseUrl()}/v1/auth/google/auth?mode=register`;
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
