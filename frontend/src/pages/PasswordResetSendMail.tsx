import Footer from '../components/footer/Footer';

const PasswordResetSendMail = () => {
	return (
		<>
			{/* ヘッダー */}
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">パスワード再設定用メール送信画面</span>
			</div>

			{/* フッター */}
			<Footer />
		</>
	);
};

export default PasswordResetSendMail;
