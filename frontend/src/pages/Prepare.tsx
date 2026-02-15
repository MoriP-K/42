import { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";

interface Player {
	id: number;
	name: string;
	isReady: boolean;
	avatar: string;
}

const Prepare = () => {
	const navigate = useNavigate();
	// Mock data
	const players: Player[] = [
		{ id: 1, name: "Tanaka", isReady: true, avatar: "🐙" },
		{ id: 2, name: "Sato", isReady: true, avatar: "🐼" },
		{ id: 3, name: "Suzuki", isReady: false, avatar: "🦊" },
		{ id: 4, name: "You", isReady: true, avatar: "🐱" },
	];
	const count: number = 3;

	const currentWriter = players[0];
	type Role = "回答者" | "描き手";
	const [role] = useState<Role>("回答者");
	const [countdown, setCountdown] = useState(3);

	useEffect(() => {
		if (countdown < 0) {
			const redirectTimer = setTimeout(() => {
				navigate("/game");
			}, 1500);
			return () => clearTimeout(redirectTimer);
		}

		const timer = setInterval(() => {
			setCountdown(prev => prev - 1);
		}, 1000);
		return () => clearInterval(timer);
	}, [countdown, navigate]);

	return (
		<div className="min-h-screen bg-gradient-to-br from-indigo-900 via-purple-900 to-black text-white p-6 flex flex-col items-center justify-center font-sans overflow-hidden">
			{/* Background Decorations */}
			<div className="absolute top-10 left-10 w-64 h-64 bg-primary/20 rounded-full blur-3xl animate-pulse"></div>
			<div className="absolute bottom-10 right-10 w-96 h-96 bg-secondary/20 rounded-full blur-3xl animate-pulse delay-700"></div>

			<div className="z-10 w-full max-w-4xl flex flex-col gap-8 items-center">
				{/* Header Section */}
				<div className="text-center space-y-2 animate-bounce-in">
					<h1 className="text-4xl md:text-6xl font-black bg-clip-text text-transparent bg-gradient-to-r from-cyan-400 to-purple-400">
						GAME STARTING...
					</h1>
					<p className="text-gray-400 tracking-[0.3em] font-light">まもなく開始します</p>
				</div>

				{/* Main Content Grid */}
				<div className="grid grid-cols-1 md:grid-cols-2 gap-8 w-full">
					{/* Left Column: Roles & Writer */}
					<div className="flex flex-col gap-6">
						{/* Current Writer Card */}
						<div className="card bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.02] transition-transform">
							<div className="card-body p-6">
								<h2 className="text-sm font-bold text-cyan-400 uppercase tracking-widest mb-4">今回の書き手</h2>
								<div className="flex items-center gap-6">
									<div className="avatar placeholder">
										<div className="bg-gradient-to-tr from-cyan-500 to-blue-500 text-neutral-content rounded-full w-20 ring ring-cyan-400 ring-offset-base-100 ring-offset-2">
											<span className="text-4xl">{currentWriter.avatar}</span>
										</div>
									</div>
									<div>
										<p className="text-3xl font-bold">{currentWriter.name}</p>
										<div className="badge badge-outline badge-primary mt-1 px-3 py-1 font-mono uppercase">Artist</div>
									</div>
								</div>
							</div>
						</div>

						{/* Your Role Card */}
						<div className="card bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden hover:scale-[1.02] transition-transform">
							<div className="card-body p-6">
								<h2 className="text-sm font-bold text-purple-400 uppercase tracking-widest mb-4">あなたの役割</h2>
								<div className="flex items-center justify-between">
									<span className="text-4xl font-black italic">{role}</span>
									<div className={`w-12 h-12 rounded-xl flex items-center justify-center ${role === "描き手" ? "bg-orange-500" : "bg-emerald-500 shadow-[0_0_20px_rgba(16,185,129,0.5)] animate-pulse"}`}>
										{role === "描き手" ? "🎨" : "💡"}
									</div>
								</div>
							</div>
						</div>
					</div>

					{/* Right Column: Player Readiness */}
					<div className="card bg-black/30 backdrop-blur-sm border border-white/10 shadow-2xl">
						<div className="card-body p-6">
							<h2 className="text-sm font-bold text-gray-400 uppercase tracking-widest mb-6">プレイヤーの準備状況</h2>
							<div className="space-y-4">
								{players.map((player) => (
									<div key={player.id} className="flex items-center justify-between bg-white/5 p-3 rounded-xl border border-white/5 hover:bg-white/10 transition-colors">
										<div className="flex items-center gap-3">
											<span className="text-2xl">{player.avatar}</span>
											<span className={`font-semibold ${player.name === "You" ? "text-yellow-400" : "text-white"}`}>
												{player.name}
											</span>
										</div>
										{player.isReady ? (
											<span className="flex items-center gap-1 text-emerald-400 text-sm font-bold">
												<svg xmlns="http://www.w3.org/2000/svg" className="h-4 w-4" viewBox="0 0 20 20" fill="currentColor">
													<path fillRule="evenodd" d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z" clipRule="evenodd" />
												</svg>
												READY
											</span>
										) : (
											<span className="flex items-center gap-2 text-rose-400 text-sm font-bold">
												<span className="loading loading-spinner loading-xs"></span>
												WAITING
											</span>
										)}
									</div>
								))}
							</div>
						</div>
					</div>
				</div>

				{/* Countdown Overlay Section */}
				<div className="mt-8 relative flex flex-col items-center">
					<div className="absolute inset-0 bg-white/20 rounded-full blur-3xl opacity-20 scale-150 animate-ping"></div>
					<div className="relative text-center">
						{countdown >= 0 ?
							<>
								<span className="countdown font-mono text-9xl md:text-[12rem] leading-none text-white drop-shadow-[0_0_30px_rgba(255,255,255,0.5)]">
									<span style={{ "--value": countdown } as React.CSSProperties}></span>
								</span>
								<div className="mt-4 flex gap-2 justify-center">
									{[...Array(count)].map((_, i) => (
										<div
											key={i}
											className={`w-3 h-3 rounded-full transition-all duration-500 ${count - i <= countdown ? "bg-cyan-400 scale-125" : "bg-white/10"}`}
										></div>
									))}
								</div>
							</> : (
								<div className="flex flex-col items-center animate-game-start">
									<span className="text-6xl md:text-8xl font-black text-white drop-shadow-[0_0_50px_rgba(255,255,255,0.8)] tracking-widest italic">
										GAME START!
									</span>
									<div className="mt-4 h-1 w-64 bg-gradient-to-r from-transparent via-cyan-400 to-transparent animate-expand-width"></div>
								</div>
							)
						}
					</div>
				</div>
			</div>

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
				@keyframes game-start {
					0% { transform: scale(0.5); opacity: 0; filter: blur(10px); }
					50% { transform: scale(1.1); opacity: 1; filter: blur(0px); }
					100% { transform: scale(1); opacity: 1; }
				}
				.animate-game-start {
					animation: game-start 0.5s cubic-bezier(0.34, 1.56, 0.64, 1) forwards;
				}
				@keyframes expand-width {
					0% { width: 0; opacity: 0; }
					100% { width: 16rem; opacity: 1; }
				}
				.animate-expand-width {
					animation: expand-width 0.8s ease-out forwards;
				}
                `}
			</style>
		</div>
	);
};

export default Prepare;