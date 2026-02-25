import { useEffect, useState } from "react";
import { userApi } from "../api/userApi";
import Footer from "../components/footer/Footer";
import kakuni from "../images/badges/food_kakuni_manju.png";
import ika from "../images/badges/food_ika_ikidukuri_naruko.png";
import curry from "../images/badges/food_kanazawa_curry.png";

const Profile = () => {
	interface profileData {
		name: string;
		total_score: number;
		first_place_count: number;
		play_count: number;
		badges: string[];
	}

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

	const imageMap: Record<string, string> = {
		firstWin: kakuni,
		happyPlayer: ika,
		richScore: curry,
	};

	const BadgeImage = ({ name }: { name: string }) => {
		if (!imageMap[name])
			return (null);
		else
		{
			return (
				<img
					src={imageMap[name]}
					width={100}
				/>
			);
		}
	};

	if (isLoading) {
		return <div className="p-10">読み込み中...</div>;
	}
	if (!profileData) {
		return <div className="p-10">データを表示できません</div>;
	}

	return (
		<div>
			<h1 className="text-5xl font-bold">プロフィール</h1>
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
						<p className="text-gray-400">まだバッジを持っていません</p>
					)}
				</div>
			</div>
			<Footer></Footer>
		</div>
	);
};

export default Profile;
