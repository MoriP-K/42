import { Link } from "react-router-dom";
import Footer from "../components/footer/Footer";
import PrivacyPolicyContent from "../components/footer/PrivacyPolicyContent";
import BackButton from "../components/BackButton";
import Logo from "../images/logo.svg";

function PrivacyPolicy() {
	return (
		<div
			className="min-h-screen flex flex-col font-sans"
			style={{ backgroundColor: "#87ceeb" }}
		>
			{/* Navbar */}
			<div className="h-25 flex items-center px-6">
				<div className="flex-1 flex justify-center">
					<Link to="/" className="flex items-center justify-center">
						<img
							src={Logo}
							alt="お絵描きアイランド"
							className="h-20 w-auto p-1"
						/>
					</Link>
				</div>
			</div>

			{/* Main Content */}
			<div className="flex-1 flex flex-col items-center p-6 overflow-y-auto">
				<div className="w-full max-w-3xl flex flex-col gap-6">
					<h1
						className="text-4xl font-black"
						style={{ color: "#6d4c41" }}
					>
						プライバシーポリシー
					</h1>

					<div
						className="w-full rounded-lg p-6 md:p-8"
						style={{ backgroundColor: "#fffde7", color: "#6d4c41" }}
					>
						<PrivacyPolicyContent />
					</div>
				</div>
			</div>
			<BackButton />
			<Footer />
		</div>
	);
}

export default PrivacyPolicy;
