import { BrowserRouter, Routes, Route, Outlet } from 'react-router-dom'
import './App.css'
import Home from './pages/Home'
import WaitingGame from './pages/WaitingGame'
import Prepare from './pages/Prepare'
import Game from './pages/Game'
import TermsOfService from './pages/TermsOfService'
import AccountRegister from './pages/AccountRegister'
import PaaswordResetSendMail from './pages/PaaswordResetSendMail'
import PaaswordReset from './pages/PasswordReset'
import PrivacyPolicy from './pages/PrivacyPolicy'
import RedirectLogin from './pages/RedirectLogin'
import Login from './pages/Login'
import { RequireAuth } from './features/auth/RequireAuth'

function App() {
	return (
		<BrowserRouter>
			<Routes>
				{/* ログイン画面は未ログインでも表示可能 */}
				<Route path="/login" element={<Login />} />
				<Route path="/login/redirect" element={<RedirectLogin />} />

				{/* それ以外はすべてログイン必須 */}
				<Route
					path="/"
					element={
						<RequireAuth>
							<Outlet />
						</RequireAuth>
					}
				>
					<Route index element={<Home />} />
					<Route path="waiting-game/:id" element={<WaitingGame />} />
					<Route path="prepare" element={<Prepare />} />
					<Route path="game" element={<Game />} />
					<Route path="terms" element={<TermsOfService />} />
					<Route path="register" element={<AccountRegister />} />
					<Route path="password-reset/send-mail" element={<PaaswordResetSendMail />} />
					<Route path="password-reset" element={<PaaswordReset />} />
					<Route path="privacy-policy" element={<PrivacyPolicy />} />
				</Route>
			</Routes>
		</BrowserRouter>
	)
}

export default App
