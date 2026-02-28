import kakuni from "../../images/badges/food_kakuni_manju.png";
import ika from "../../images/badges/food_ika_ikidukuri_naruko.png";
import curry from "../../images/badges/food_kanazawa_curry.png";

export const imageMap: Record<string, string> = {
	firstWin: kakuni,
	happyPlayer: ika,
	richScore: curry,
};

export const BadgeImage = ({ name }: { name: string }) => {
	if (!imageMap[name]) return null;
	else {
		return <img src={imageMap[name]} width={100} />;
	}
};
