export interface profileData {
	name: string;
	total_score: number;
	first_place_count: number;
	play_count: number;
	badges: string[];
	user_rank: number;
	top_ranker: { [key: string]: number };
}
