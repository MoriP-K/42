const Footer = () => {
	return (
		<div className="py-4 text-center">
			<p className="flex flex-wrap justify-center gap-4 text-sm">
				<a
					href="/terms"
					className="text-cyan-400 hover:text-cyan-300 transition-colors"
				>
					利用規約
				</a>
				<a
					href="/privacy-policy"
					className="text-cyan-400 hover:text-cyan-300 transition-colors"
				>
					プライバシーポリシー
				</a>
			</p>
		</div>
	);
};

export default Footer;
