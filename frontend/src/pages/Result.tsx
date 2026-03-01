import { useEffect, useState, useRef } from "react";
import { useNavigate, useParams } from "react-router-dom";
import { gameApi } from "../api/gameApi";
import { GameRole } from "../types/user";
import { type GameDetails, type GameRoomMember } from "../types/game";
import { roomApi } from "../api/roomApi";
import { authApi } from "../api/authApi";
import { createWebSocket } from "../api/wsClient";
import { WebSocketMessageType } from "../types/room";

const Result = () => {
	const { id } = useParams();
	const navigate = useNavigate();

	const [players, setPlayers] = useState<{ name: string; score: number }[]>(
		[],
	);
	const [currentUserId, setCurrentUserId] = useState<number | null>(null);
	const [newRoomId, setNewRoomId] = useState<number | null>(null);
	const [rematchToken, setRematchToken] = useState<string | null>(null);

	const socketRef = useRef<WebSocket | null>(null);

	useEffect(() => {
		const fetchUser = async () => {
			try {
				const user = await authApi.me();
				setCurrentUserId(user.id);
			} catch (error) {
				console.error("Failed to get user:", error);
				navigate("/login");
			}
		};

		fetchUser();
	}, [navigate]);

	useEffect(() => {
		if (!id || !currentUserId) return;

		const ws = createWebSocket();
		socketRef.current = ws;

		ws.onopen = () => {
			ws.send(
				JSON.stringify({
					type: WebSocketMessageType.JOIN,
					userId: currentUserId,
					roomId: id,
				}),
			);
		};

		ws.onmessage = event => {
			const data = JSON.parse(event.data);
			console.log("📥 Result received:", data);
			if (data.type === WebSocketMessageType.REMATCH_CREATED) {
				setNewRoomId(data.newRoomId);
				setRematchToken(data.token);
			}
		};

		return () => {
			ws.close();
			socketRef.current = null;
		};
	}, [id, currentUserId]);

	useEffect(() => {
		const fetchResult = async () => {
			if (!id) return;

			try {
				// APIからデータ取得
				const roomData: GameDetails = await gameApi.getGameRoomDetails(
					Number(id),
				);

				// PLAYERだけ絞り込み
				const playerData = roomData.members
					.filter(m => m.role === GameRole.PLAYER)
					.map((m: GameRoomMember) => ({
						name: m.user.name,
						score: m.score,
					}))
					// スコア降順ソート
					.sort((a, b) => b.score - a.score);

				// setPlayersに保存
				setPlayers(playerData);
			} catch (error) {
				console.error("Failed to fetch result:", error);
			}
		};

		fetchResult();
	}, [id]);

	return (
		<div className="min-h-screen bg-base-200">
			{/* ヘッダー */}
			<div className="navbar bg-base-100 shadow-lg">
				<div className="flex-1">
					<span className="text-xl font-bold">🎨 お絵かきの森</span>
				</div>
			</div>

			<div className="flex flex-col items-center mt-10">
				<h1 className="text-3xl font-bold mb-6">🏆 結果発表</h1>

				<div className="w-full max-w-md space-y-3">
					{players.map((player, index) => (
						<div
							key={player.name}
							className="flex items-center justify-between bg-base-100 p-4 rounded-lg shadow"
						>
							<div className="flex items-center gap-3">
								<span className="text-2xl font-bold">
									{index + 1}位
								</span>
								<span className="text-lg">{player.name}</span>
							</div>
							<span className="text-lg font-bold">
								{player.score}pt
							</span>
						</div>
					))}
				</div>

				<div className="flex gap-4 mt-8">
					<button
						className="btn btn-primary"
						onClick={async () => {
							await roomApi.leaveResult(Number(id));
							navigate("/");
						}}
					>
						ホームに戻る
					</button>
					<button
						className="btn btn-secondary"
						onClick={async () => {
							if (!currentUserId) return;
							if (newRoomId && rematchToken) {
								await roomApi.joinRoomByToken(rematchToken);
								await roomApi.leaveResult(Number(id));
								navigate(`/waiting/${newRoomId}`);
							} else {
								const newRoom =
									await roomApi.createRoom(currentUserId);
								socketRef.current?.send(
									JSON.stringify({
										type: WebSocketMessageType.REMATCH_CREATED,
										newRoomId: newRoom.id,
										token: newRoom.invitation_token,
									}),
								);
								await roomApi.leaveResult(Number(id));
								navigate(`/waiting/${newRoom.id}`);
							}
						}}
					>
						{newRoomId ? "再戦ルームに参加" : "再戦"}
					</button>
				</div>
			</div>
		</div>
	);
};

export default Result;
