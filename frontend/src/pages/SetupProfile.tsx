import Footer from "../components/footer/Footer";

const SetupProfile = () => {
	return (
		<div className="min-h-screen bg-gradient-to-br from-indigo-900 via-purple-900 to-black text-white flex flex-col font-sans overflow-hidden">
			{/* Background Decorations */}
			<div className="absolute top-10 left-10 w-64 h-64 bg-primary/20 rounded-full blur-3xl animate-pulse"></div>
			<div className="absolute bottom-10 right-10 w-96 h-96 bg-secondary/20 rounded-full blur-3xl animate-pulse delay-700"></div>

			<div className="text-center mb-4">
				<span className="text-2xl font-bold">名前入力画面</span>
			</div>
			<Footer />
		</div>
	);
};

export default SetupProfile;
