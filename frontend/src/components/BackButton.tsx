import { Link, useNavigate } from "react-router-dom";

const BackButton = () => {
	const navigate = useNavigate();

	const handleBack = () => {
		navigate(-1);
	};

	return (
		<div className="flex justify-center gap-4 py-4">
			<button
				type="button"
				onClick={handleBack}
				className="px-6 py-2 rounded-lg text-sm font-bold text-cyan-400 border border-cyan-400/50 hover:bg-cyan-400/10 transition-colors"
			>
				戻る
			</button>
			<Link
				to="/"
				className="px-6 py-2 rounded-lg text-sm font-bold text-cyan-400 border border-cyan-400/50 hover:bg-cyan-400/10 transition-colors"
			>
				ホームへ
			</Link>
		</div>
	);
};

export default BackButton;
