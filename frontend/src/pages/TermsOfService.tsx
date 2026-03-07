import { Link } from "react-router-dom";
import TermsOfServiceContent from "../components/footer/TermsOfServiceContent";
import Footer from "../components/footer/Footer";
import BackButton from "../components/BackButton";

function TermsOfService() {
	return (
		<div className="min-h-screen bg-gradient-to-br from-indigo-900 via-purple-900 to-black text-white flex flex-col overflow-hidden">
			{/* Navbar */}
			<div className="navbar bg-white/10 backdrop-blur-md border-b border-white/10 shadow-lg z-20">
				<div className="flex-1">
					<Link to="/" className="btn btn-ghost text-xl text-white">
						🎨 お絵描きアイランド
					</Link>
				</div>
			</div>

			{/* Background Decorations */}
			<div className="absolute top-10 left-10 w-64 h-64 bg-primary/20 rounded-full blur-3xl animate-pulse"></div>
			<div className="absolute bottom-10 right-10 w-96 h-96 bg-secondary/20 rounded-full blur-3xl animate-pulse delay-700"></div>

			{/* Main Content */}
			<div className="flex-1 relative z-10 flex flex-col items-center p-6 overflow-y-auto">
				<div className="w-full max-w-3xl flex flex-col gap-6 items-center">
					<h1 className="text-4xl md:text-5xl font-black bg-clip-text text-transparent bg-gradient-to-r from-cyan-400 to-purple-400">
						利用規約
					</h1>

					<div className="card w-full bg-white/10 backdrop-blur-md border border-white/20 shadow-2xl overflow-hidden">
						<div className="card-body p-6 md:p-8">
							<TermsOfServiceContent />
						</div>
					</div>

					<BackButton />
				</div>
			</div>

			<Footer />
		</div>
	);
}

export default TermsOfService;
