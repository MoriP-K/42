import { Navigate } from 'react-router-dom'
import Footer from '../components/Footer'
import { useAuth } from '../features/auth/useAuth'

function RedirectLogin() {
	const { isAuthenticated } = useAuth()

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
