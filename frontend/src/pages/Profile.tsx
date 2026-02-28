import { useEffect, useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import { userApi } from "../api/userApi";
import { useAuth } from "../features/auth/useAuth";
import Footer from "../components/footer/Footer";
import { type profileData } from "../types/profile";
import { BadgeImage } from "../components/profile/badges";

const Profile = () => {
	const navigate = useNavigate();
	const { logout } = useAuth();

	const handleLogout = async () => {
		await logout();
		navigate("/login");
	};

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
				<div className="flex flex-wrap gap-4 mt-2">
					{profileData.badges && profileData.badges.length > 0 ? (
						profileData.badges.map((badgeName, index) => (
							<BadgeImage key={index} name={badgeName} />
						))
					) : (
						<p className="text-gray-400">
							まだバッジを持っていません
						</p>
					)}
				</div>
			</div>

			<div>
				<p className="font-bold">リーダーボード</p>
				<p> 自分の順位： {profileData.user_rank + 1}位</p>
				<div className="flex flex-wrap gap-4 mt-2">
					{profileData.top_ranker ? (
						Object.entries(profileData.top_ranker).map(
							([name, score]) => (
								<div
									key={name}
									className="flex justify-between w-48"
								>
									<span>{name}</span>
									<span>{score}点</span>
								</div>
							),
						)
					) : (
						<p className="text-gray-400">
							まだランキングはありません
						</p>
					)}
				</div>
			</div>
			<Footer></Footer>
		</div>
	);
};

export default Profile;
