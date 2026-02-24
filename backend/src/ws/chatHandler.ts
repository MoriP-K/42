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

	if (typeof data.text !== "string") {
		client.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.ERROR,
				message: "Invalid message format",
			}),
		);
		return;
	}

	if (client.role === "SPECTATOR") {
		client.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.ERROR,
				message: "Spectators cannot send chat messages",
			}),
		);
		return;
	}

	try {
		const currentRound = getRoundState(client.roomId);

		if (!currentRound || !currentRound.word) {
			broadcastToRoom(client.roomId, {
				type: WebSocketMessageType.CHAT,
				id: data.id,
				sender: data.sender,
				text: data.text,
				timeStamp: data.timeStamp,
			});
			return;
		}

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

		console.log("🔍 Debug:", {
			text: data.text,
			word: currentRound.word,
			drawerId: currentRound.drawerId,
			userId: client.userId,
		});

		if (isCorrect) {
			// WebSocketで正解配信 + チャット送信
			broadcastToRoom(client.roomId, {
				type: WebSocketMessageType.CHAT,
				id: data.id,
				sender: data.sender,
				text: data.text,
				timestamp: data.timestamp,
			});

			// DB更新
			const newWord = selectRandomWord();
			const result = await prisma.round.updateMany({
				where: { id: currentRound.roundId, word: currentRound.word },
				data: { word: newWord },
			});
			if (result.count === 0) return;

			setRoundState(
				client.roomId,
				currentRound.roundId,
				newWord,
				currentRound.drawerId,
			);

			// 正解通知
			broadcastToRoom(client.roomId, {
				type: WebSocketMessageType.CORRECT_ANSWER,
				userId: client.userId,
				sender: data.sender,
			});

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
	} catch (error) {
		console.error("❌ Failed to handle chat message:", error);
		client.socket.send(
			JSON.stringify({
				type: WebSocketMessageType.ERROR,
				message: "Failed to process message",
			}),
		);
	}
};
