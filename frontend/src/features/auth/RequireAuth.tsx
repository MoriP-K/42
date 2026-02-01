import { useEffect, useState, type ReactNode } from 'react'
import { Navigate, useLocation } from 'react-router-dom'
import Footer from '../../components/footer/Footer'
import { useAuth } from './useAuth'

export function RequireAuth({ children }: { children: ReactNode }) {
	const { isAuthenticated, refreshAuth } = useAuth()
	const location = useLocation()

	const [checkingMe, setCheckingMe] = useState(false)
	const [deny, setDeny] = useState(false)
	const redirectEnabled = import.meta.env.VITE_AUTH_REDIRECT_ENABLED !== 'false'

	useEffect(() => {
		const run = async () => {
			if (isAuthenticated) {
				setDeny(false)
				return
			}
			// StrictMode の effect 二重実行で「キャンセル→checkedOnceで再実行されない」問題を避けるため、
			// ref での一回きり制御は使わず state でガードする
			if (checkingMe || deny)
				return

			setCheckingMe(true)

			const ok = await refreshAuth().catch(() => false)
			setCheckingMe(false)
			if (!ok)
				setDeny(true)
		}

		void run()
	}, [checkingMe, deny, isAuthenticated, refreshAuth])

	if (!redirectEnabled || isAuthenticated)
		return <>{children}</>

	// /api/me 再確認中は最低限のレイアウトを表示
	if (checkingMe) {
		return (
			<div>
				<Footer />
			</div>
		)
	}

	if (deny) {
		return <Navigate to="/login" replace state={{ from: location }} />
	}

	// effect が走るまでの1フレーム
	return (
		<div>
			<Footer />
		</div>
	)
}

