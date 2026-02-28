import { useEffect, useState, type ReactNode } from "react";
import { Navigate } from "react-router-dom";
import Footer from "../../components/footer/Footer";
import { useAuth } from "./useAuth";

const RequireGuest = ({ children }: { children: ReactNode }) => {
	const { isAuthenticated, refreshAuth } = useAuth();

	const [isChecking, setIsChecking] = useState(false);
	const [isInitialized, setIsInitialized] = useState(false);

	useEffect(() => {
		// すでに認証済み、または初期化済み、または確認中なら何もしない
		if (isAuthenticated || isChecking || isInitialized) return;

		const run = async () => {
			setIsChecking(true);
			// refreshAuth()内部でGET /api/meを叩き、isAuthenticatedに結果をset
			await refreshAuth().catch(() => false);
			setIsChecking(false);
			setIsInitialized(true);
		};

		void run();
	}, [isAuthenticated, isChecking, isInitialized, refreshAuth]);

	// ログイン済みの場合はホーム画面にリダイレクト
	const redirectEnabled =
		import.meta.env.VITE_AUTH_REDIRECT_ENABLED !== "false";

	// リダイレクトが有効かつログイン済みの場合はホーム画面にリダイレクト
	if (redirectEnabled && isAuthenticated) return <Navigate to="/" replace />;

	// /api/me確認中ならローディング表示
	if (!isInitialized || isChecking) {
		return (
			<>
				<div className="text-center mb-4">
					<span className="text-2xl font-bold">認証中</span>
				</div>
				<Footer />
			</>
		);
	}

	//未ログインの場合はページを表示する
	return <>{children}</>;
};

export default RequireGuest;
