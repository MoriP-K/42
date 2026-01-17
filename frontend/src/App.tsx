import { BrowserRouter, Routes, Route } from 'react-router-dom'
import './App.css'
import Home from './pages/Home'
import Game from './pages/Game'
import TermsOfService from './pages/TermsOfService'

function App() {
	return (
		<BrowserRouter>
			<Routes>
				<Route path="/" element={<Home />} />
				<Route path="/game" element={<Game />} />
				<Route path="/terms" element={<TermsOfService />} />
			</Routes>
		</BrowserRouter>
	)
}

export default App
