import Footer from "../components/footer/Footer"
import PrivacyPolicyContent from "../components/footer/PrivacyPolicyContent"
import BackButton from "../components/BackButton"


function PrivacyPolicy() {
	return (
		<div>
			<div className="hero min-h-[80vh]">
			<div className="hero-content text-center">
			<div className="max-w-md">
				<h1 className="text-5xl font-bold">プライバシーポリシー</h1>
					<PrivacyPolicyContent>
					</PrivacyPolicyContent>
			</div>
		</div>
		</div>
			<BackButton></BackButton>
			<Footer></Footer>
		</div>
	)
}

export default PrivacyPolicy
