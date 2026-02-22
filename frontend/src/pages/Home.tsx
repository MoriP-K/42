import { Link, useNavigate } from "react-router-dom";
import { useAuth } from "../features/auth/useAuth";
import { roomApi } from "../api/roomApi";
import Footer from "../components/footer/Footer";

function Home() {
	const navigate = useNavigate();
	const { isAuthenticated, user } = useAuth();

	const handleCreateRoom = async () => {
		if (!isAuthenticated || !user) return;
		try {
			const room = await roomApi.createRoom(user.id);
			if (!room) throw new Error("Room cannot be created");
			navigate(`/waiting/${room.id}`);
		} catch (error) {
			console.error("Error:", error);
		}
	};

	return (
		<div className="min-h-screen bg-gradient-to-br from-indigo-900 via-purple-900 to-black text-white flex flex-col font-sans overflow-hidden">
			{/* Navbar */}
			<div className="navbar bg-white/10 backdrop-blur-md border-b border-white/10 shadow-lg z-20">
				<div className="flex-1">
					<a className="btn btn-ghost text-xl text-white">
						🎨 おえかきの森
					</a>
				</div>
			</div>

			{/* Background Decorations */}
			<div className="absolute top-10 left-10 w-64 h-64 bg-primary/20 rounded-full blur-3xl animate-pulse"></div>
			<div className="absolute bottom-10 right-10 w-96 h-96 bg-secondary/20 rounded-full blur-3xl animate-pulse delay-700"></div>

			{/* Main Content */}
			<div className="flex-1 relative z-10 flex flex-col items-center justify-center p-6">
				<div className="w-full max-w-2xl flex flex-col gap-8 items-center">
					{/* Header Section */}
					<div className="text-center space-y-2 animate-bounce-in">
						<h1 className="text-4xl md:text-6xl font-black bg-clip-text text-transparent bg-gradient-to-r from-cyan-400 to-purple-400">
							おえかきの森
						</h1>
						<p className="text-gray-400 tracking-[0.3em] font-light">
							友達と一緒にお絵かきで遊ぼう
						</p>
					</div>

					{/* User Info Card */}
					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.02] transition-transform">
						<div className="card-body p-6 w-full flex flex-col items-center text-center">
							<h2 className="text-sm font-bold text-cyan-400 uppercase tracking-widest mb-4">
								ログイン中のユーザー
							</h2>
							<div className="flex items-center justify-center gap-6 w-full">
								<div className="avatar placeholder">
									<div className="flex items-center justify-center bg-gradient-to-tr from-cyan-500 to-blue-500 text-neutral-content rounded-full w-20 ring ring-cyan-400 ring-offset-base-100 ring-offset-2">
										<span className="text-4xl">👤</span>
									</div>
								</div>
								<div className="text-center">
									<p className="text-3xl font-bold">
										{user?.name ?? "ゲスト"}
									</p>
									{user?.id != null && (
										<p className="text-gray-400 text-sm mt-1 font-mono">
											ID: {user.id}
										</p>
									)}
								</div>
							</div>
							<Link
								to="/profile"
								className="mt-4 px-6 py-2 rounded-lg text-sm font-bold text-cyan-400 border border-cyan-400/50 hover:bg-cyan-400/10 transition-colors"
							>
								プロフィール
							</Link>
						</div>
					</div>

					{/* CTA Button */}
					<button
						onClick={handleCreateRoom}
						className="min-w-[16rem] px-8 py-4 rounded-xl font-bold text-lg uppercase tracking-wider cursor-pointer select-none transition-all duration-200 hover:scale-[1.02] hover:brightness-110 active:scale-[0.98] focus:outline-none focus:ring-2 focus:ring-cyan-400/50 focus:ring-offset-2 focus:ring-offset-transparent bg-gradient-to-r from-cyan-500 to-purple-500 border border-cyan-400/50 text-white shadow-[0_0_20px_rgba(34,211,238,0.3)] hover:shadow-[0_0_25px_rgba(34,211,238,0.5)]"
					>
						ルームを作成する
					</button>
				</div>
			</div>

			<Footer />

			<style>
				{`
				@keyframes bounce-in {
					0% { transform: translateY(-50px); opacity: 0; }
					60% { transform: translateY(10px); }
					100% { transform: translateY(0); opacity: 1; }
				}
				.animate-bounce-in {
					animation: bounce-in 1s cubic-bezier(0.175, 0.885, 0.32, 1.275);
				}
				`}
			</style>
		</div>
	);
}

export default Home;
