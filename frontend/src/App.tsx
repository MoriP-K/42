import { BrowserRouter, Routes, Route } from 'react-router-dom'
import './App.css'
import Home from './pages/Home'
import WaitingGame from './pages/WaitingGame'
import Prepare from './pages/Prepare'
import TermsOfService from './pages/TermsOfService'
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
				<Route path="/waiting-game/:id" element={<WaitingGame />} />
				<Route path="/prepare" element={<Prepare />} />
				<Route path="/terms" element={<TermsOfService />} />
				<Route path="/register" element={<AccountRegister />} />
				<Route path="/password-reset/send-mail" element={<PaaswordResetSendMail />} />
				<Route path="/password-reset" element={<PaaswordReset />} />
				<Route path="/login/redirect" element={<RedirectLogin />} />
				<Route path="/privacy-policy" element={<PrivacyPolicy />} />
			</Routes>
		</BrowserRouter>
	)
}

export default App
