import { getBackendBaseUrl } from "../../api/backendUrl";

export function GoogleAccountLogin() {
	const handleGoogleAuth = () => {
		window.location.href = `${getBackendBaseUrl()}/v1/auth/google/auth?mode=login`;
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
				Googleアカウントでログイン
			</span>
		</button>
	);
}
