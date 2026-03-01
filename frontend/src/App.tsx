import { BrowserRouter, Routes, Route, Outlet } from "react-router-dom";
import "./App.css";
import Home from "./pages/Home";
import Waiting from "./pages/Waiting";
import Prepare from "./pages/Prepare";
import Game from "./pages/Game";
import TermsOfService from "./pages/TermsOfService";
import AccountRegister from "./pages/AccountRegister";
import PasswordResetSendMail from "./pages/PasswordResetSendMail";
import PasswordReset from "./pages/PasswordReset";
import PrivacyPolicy from "./pages/PrivacyPolicy";
import RedirectLogin from "./pages/RedirectLogin";
import Login from "./pages/Login";
import Profile from "./pages/Profile";
import SetupProfile from "./pages/SetupProfile";
import RequireAuth from "./features/auth/RequireAuth";
import RequireGuest from "./features/auth/RequireGuest";

const App = () => {
	return (
		<BrowserRouter>
			<Routes>
				{/* 未ログインの場合に表示するページ */}
				<Route
					path="/login"
					element={
						<RequireGuest>
							<Login />
						</RequireGuest>
					}
				/>
				<Route
					path="/login/redirect"
					element={
						<RequireGuest>
							<RedirectLogin />
						</RequireGuest>
					}
				/>
				<Route
					path="/register"
					element={
						<RequireGuest>
							<AccountRegister />
						</RequireGuest>
					}
				/>
				<Route
					path="/password-reset/send-mail"
					element={
						<RequireGuest>
							<PasswordResetSendMail />
						</RequireGuest>
					}
				/>
				<Route
					path="/password-reset"
					element={
						<RequireGuest>
							<PasswordReset />
						</RequireGuest>
					}
				/>

				{/* ↓未ログイン状態でアクセスした場合、ログイン画面にリダイレクトされるページ */}
				<Route
					path="/"
					element={
						<RequireAuth>
							<Outlet />
						</RequireAuth>
					}
				>
					<Route index element={<Home />} />
					<Route path="waiting/:id" element={<Waiting />} />
					<Route path="prepare/:id" element={<Prepare />} />
					<Route path="game/:id" element={<Game />} />
					<Route path="profile" element={<Profile />} />
					<Route path="setup-profile" element={<SetupProfile />} />
				</Route>

				<Route path="/terms" element={<TermsOfService />} />
				<Route path="/privacy-policy" element={<PrivacyPolicy />} />
			</Routes>
		</BrowserRouter>
	);
};

export default App;
