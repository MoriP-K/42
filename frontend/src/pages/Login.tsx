import { Navigate } from 'react-router-dom'
import Footer from '../components/Footer'
import { useAuth } from '../features/auth/useAuth'

function Login() {
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

export default Login
