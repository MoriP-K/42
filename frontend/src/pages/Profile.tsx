import Footer from "../components/Footer"
import { useEffect, useState } from "react";
import { apiClient } from '../api/apiClient';

const Profile = () => {

	// 1ユーザのデータがそのまま帰ってくる
	const [profileData, setProfileData] = useState<any>(null);
	const [isLoading, setIsLoading] = useState(true);

	useEffect(() => {
		const fetchProfile = async () => {
			try {
				const currentUserId = 1;
				const data = await apiClient(`/profile?userId=${currentUserId}`);
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
			<h1 className="text-5xl font-bold">プロフィール</h1>
				<p>ユーザ名 {profileData.name}</p>
					<p className="font-bold">実績</p>
						<p>トータルスコア: {profileData.total_score}</p>
						<p>1位回数: {profileData.first_place_count}</p>
						<p>プレイ回数: {profileData.play_count}</p>

			<div>
				<p className="font-bold">バッジ</p>
			</div>
			<Footer></Footer>
		</div>
	)
}

export default Profile
