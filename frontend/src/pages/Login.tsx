import { Navigate } from 'react-router-dom'
import { useAuth } from '../features/auth/useAuth'
import Footer from "../components/footer/Footer"

const Login = () => {
	const { isAuthenticated } = useAuth()

	// すでにログイン認証済みだったら、ホーム画面に自動遷移する
	if (isAuthenticated) {
		return <Navigate to="/" replace />
	}

	return (
		<>
			{/* ヘッダー */}
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">ログイン画面</span>
			</div>

			{/* フッター */}
			<Footer />
		</>
	)
}

export default Login
