import { useEffect, useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import { userApi } from "../api/userApi";
import { useAuth } from "../features/auth/useAuth";
import Footer from "../components/footer/Footer";
import test1 from "../images/badges/food_kakuni_manju.png";
import test2 from "../images/badges/food_ika_ikidukuri_naruko.png";
import test3 from "../images/badges/food_kanazawa_curry.png";
import test4 from "../images/badges/food_nasu_yakinasu.png";

const Profile = () => {
	const navigate = useNavigate();
	const { logout } = useAuth();

	const handleLogout = async () => {
		await logout();
		navigate("/login");
	};

	interface profileData {
		name: string;
		total_score: number;
		first_place_count: number;
		play_count: number;
		// badges: string[];
	}

	// 1ユーザのデータがそのまま帰ってくる
	const [profileData, setProfileData] = useState<profileData | null>(null);
	const [isLoading, setIsLoading] = useState(true);

	useEffect(() => {
		const fetchProfile = async () => {
			try {
				const data = await userApi.getProfile();
				setProfileData(data);
			} catch (error) {
				console.error("データの取得に失敗しました", error);
			} finally {
				setIsLoading(false);
			}
		};

		fetchProfile();
	}, []);

	// バッジは直近で取得したもの３つを表示する
	// 画像のマッピング（Record型を使用）
	const imageMap: Record<string, string> = {
		first: test1,
		second: test2,
		third: test3,
		fource: test4,
	};

	const MyComponent = ({ rank }: { rank: string }) => {
		return (
			<img
				src={imageMap[rank]} // 型の「Rank」ではなく、小文字の変数「rank」を使う
				alt={`${rank} test`}
				width={100}
			/>
		);
	};

	if (isLoading) {
		return <div className="p-10">読み込み中...</div>;
	}
	if (!profileData) {
		return <div className="p-10">データを表示できません</div>;
	}

	return (
		<div>
			<div className="flex justify-between items-center mb-6">
				<h1 className="text-5xl font-bold">プロフィール</h1>
				<div className="flex gap-2">
					<Link to="/" className="btn btn-primary btn-sm">
						ホーム
					</Link>
					<button
						onClick={handleLogout}
						className="btn btn-error btn-sm"
					>
						ログアウト
					</button>
				</div>
			</div>
			<p>ユーザ名 {profileData.name}</p>
			<p className="font-bold">実績</p>
			<p>トータルスコア: {profileData.total_score}</p>
			<p>1位回数: {profileData.first_place_count}</p>
			<p>プレイ回数: {profileData.play_count}</p>

			<div>
				<p className="font-bold">バッジ</p>
				{/* <p>バッジ: {profileData.badges}</p> */}
				<MyComponent rank="first" />
				<MyComponent rank="second" />
				<MyComponent rank="third" />
			</div>
			<Footer></Footer>
		</div>
	);
};

export default Profile;
