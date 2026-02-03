import { useEffect, useState, type ReactNode } from 'react'
import { Navigate, useLocation } from 'react-router-dom'
import Footer from '../../components/footer/Footer'
import { useAuth } from './useAuth'

export function RequireAuth({ children }: { children: ReactNode }) {
	const { isAuthenticated, refreshAuth } = useAuth()
	const location = useLocation()

	const [isChecking, setIsChecking] = useState(false)
	const [isInitialized, setIsInitialized] = useState(false)

	const redirectEnabled = import.meta.env.VITE_AUTH_REDIRECT_ENABLED !== 'false'

	useEffect(() => {
		// すでに認証済み、または初期化済み、または確認中なら何もしない
		if (isAuthenticated || isChecking || isInitialized)
			return
		const run = async () => {
			setIsChecking(true)
			//refreshAuth()内部でGET /api/meを叩き、isAuthenticatedに結果をset
			await refreshAuth().catch(() => false)
			setIsChecking(false)
			setIsInitialized(true)
		}

		void run()
	}, [isAuthenticated, isChecking, isInitialized, refreshAuth])

	//リダイレクトが無効、もしくは、ログイン認証済みであればchildrenページを表示
	if (!redirectEnabled || isAuthenticated)
		return <>{children}</>

	// /api/me確認中ならローディング表示
	if (!isInitialized || isChecking) {
		return (
			<>
				<div className="text-center mb-4">
					<span className="text-2xl font-bold">認証中</span>
				</div>
				<Footer />
			</>
		)
	}

	//未ログインの場合、ログイン画面に飛ばす
	return <Navigate to="/login" replace state={{ from: location }} />
}

