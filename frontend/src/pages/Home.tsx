import Footer from "../components/footer/Footer"
import { useEffect, useState } from 'react'
import { userApi } from '../api/userApi'
import { roomApi } from '../api/roomApi'
import { useNavigate } from 'react-router-dom'

function Home() {
	const navigate = useNavigate();
	const [message, setMessage] = useState('Loading...')
	const [user] = useState({id: 1})

	useEffect(() => {
		userApi.getHello()
			.then(data => setMessage(data.message))
			.catch(err => setMessage('Error' + err.message))
	}, [])

	const handleCreateRoom = async () => {
		try {
			const room = await roomApi.createRoom(user.id);
			if (!room)
				throw new Error('Room cannot be created');
			navigate(`/waiting-game/${room.id}`, { state: { hostId: user.id, roomId: room.id } });
		} catch (error) {
			console.error('Error:', error);
		}
	}

	return (
		<div className="min-h-screen bg-base-200">
			<div className="navbar bg-base-100 shadow-lg">
				<div className="flex-1">
					<a className="btn btn-ghost text-xl">🎨 おえかきの森</a>
				</div>
			</div>

			<div className="hero min-h-[80vh]">
				<div className="hero-content text-center">
					<div className="max-w-md">
						<h1 className="text-5xl font-bold">おえかきの森へようこそ！</h1>
						<p className="py-6">友達と一緒にお絵かきで遊ぼう</p>
						<p className="mb-4">APIからのメッセージ: <span className="text-primary font-semibold">{message}</span></p>
						<button onClick={handleCreateRoom} className="btn btn-primary btn-lg">
							ルームを作成する
						</button>
					</div>
				</div>
			</div>
			<Footer></Footer>
		</div>
	)
}

export default Home
