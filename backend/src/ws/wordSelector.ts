import { words } from "../types/game/word";

export const selectRandomWord = () => {
	const randomIndex = Math.floor(Math.random() * words.length);
	return words[randomIndex];
};
