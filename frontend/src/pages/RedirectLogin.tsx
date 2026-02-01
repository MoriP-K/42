import { Navigate } from 'react-router-dom'
import Footer from "../components/footer/Footer"
import { useAuth } from '../features/auth/useAuth'

function RedirectLogin() {
	const { isAuthenticated } = useAuth()

	// すでに認証済みだったら、ホーム画面に自動遷移する
	if (isAuthenticated) {
		return <Navigate to="/" replace />
	}

	return (
		<div>
			<Footer />
		</div>
	)
}

export default RedirectLogin
