import { BrowserRouter, Routes, Route } from 'react-router-dom'
import './App.css'
import Home from './pages/Home'
import WaitingGame from './pages/WaitingGame'

function App() {
	return (
		<BrowserRouter>
			<Routes>
				<Route path="/" element={<Home />} />
				<Route path="/waiting-game" element={<WaitingGame />} />
			</Routes>
		</BrowserRouter>
	)
}

export default App
