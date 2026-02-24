import { prisma } from "../lib/prisma";
import {
	broadcastToRoom,
	findClientByUserId,
	getRoundState,
	setRoundState,
} from "./roomManager";
import { RoomClient, WebSocketMessageType } from "../types/room/room";
import { selectRandomWord } from "./wordSelector";

export const handleChatMessage = async (client: RoomClient, data: any) => {
	console.log(
		`💬 Chat from ${client.userId} in room ${client.roomId}: ${data.text}`,
	);

	if (client.role === "SPECTATOR") {
		client.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.ERROR,
				message: "Spectators cannot send chat messages",
			}),
		);
		return;
	}

	const currentRound = getRoundState(client.roomId);

	if (!currentRound || !currentRound.word) return;

	if (client.userId === currentRound.drawerId) {
		broadcastToRoom(client.roomId, {
			type: WebSocketMessageType.CHAT,
			id: data.id,
			sender: data.sender,
			text: data.text,
			timestamp: data.timestamp,
		});
		return;
	}

	const isCorrect =
		data.text.trim().toLowerCase() ===
		currentRound.word.trim().toLowerCase();

	if (isCorrect) {
		// WebSocketで正解配信 + チャット送信
		broadcastToRoom(client.roomId, {
			type: WebSocketMessageType.CHAT,
			id: data.id,
			sender: data.sender,
			text: data.text,
			timestamp: data.timestamp,
		});

		// 正解通知
		broadcastToRoom(client.roomId, {
			type: WebSocketMessageType.CORRECT_ANSWER,
			userId: client.userId,
			sender: data.sender,
		});

		// DB更新
		const newWord = selectRandomWord();
		await prisma.round.update({
			where: { id: currentRound.roundId },
			data: { word: newWord },
		});
		setRoundState(
			client.roomId,
			currentRound.roundId,
			newWord,
			currentRound.drawerId,
		);

		// Drawerにお題を送る
		const drawerClient = findClientByUserId(
			client.roomId,
			currentRound.drawerId,
		);

		drawerClient?.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.NEXT_WORD,
				word: newWord,
			}),
		);
	} else {
		broadcastToRoom(client.roomId, {
			type: WebSocketMessageType.CHAT,
			id: data.id,
			sender: data.sender,
			text: data.text,
			timestamp: data.timestamp,
		});
	}
	return;
};
