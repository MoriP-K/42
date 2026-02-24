import { apiClient } from "./apiClient";
// import { type GameDetails } from "../types/game";

export const gameApi = {
	getGameRoomDetails: async (roomId: number) => {
		return apiClient(`/rooms/${roomId}/game`, {
			method: "GET",
		});
	},
};
