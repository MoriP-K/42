import { BrowserRouter, Routes, Route } from 'react-router-dom'
import './App.css'
import Home from './pages/Home'
import WaitingGame from './pages/WaitingGame'
import TermsOfService from './pages/TermsOfService'
import Login from './pages/Login'
import AccountRegister from './pages/AccountRegister'
import PaaswordResetSendMail from './pages/PaaswordResetSendMail'
import PaaswordReset from './pages/PasswordReset'
import PrivacyPolicy from './pages/PrivacyPolicy'
import RedirectLogin from './pages/RedirectLogin'

function App() {
	return (
		<BrowserRouter>
			<Routes>
				<Route path="/" element={<Home />} />
				<Route path="/waiting-game" element={<WaitingGame />} />
				<Route path="/terms" element={<TermsOfService />} />
				<Route path="/login" element={<Login />} />
				<Route path="/register" element={<AccountRegister />} />
				<Route path="/passwordReset/sendMail" element={<PaaswordResetSendMail />} />
				<Route path="/passwordReset" element={<PaaswordReset />} />
				<Route path="/login/redirect" element={<RedirectLogin />} />
				<Route path="/privacyPolicy" element={<PrivacyPolicy />} />
			</Routes>
		</BrowserRouter>
	)
}

export default App
