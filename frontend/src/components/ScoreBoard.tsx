interface Player {
	id: number,
	name: string,
	score: number,
	isDrawing: boolean,
};

interface ScoreBoardProps {
	players: Player[]
};

const ScoreBoard = ({ players }: ScoreBoardProps) => {
	const sortedPlayers = [...players].sort((a, b) => b.score - a.score);

	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-0">
				<h2 className="card-title font-mono text-2xl font-semibold">スコア</h2>
				
				<div className="space-y-2">
					{sortedPlayers.map(player => (
						<div
							key={player.id}
							className="flex items-baseline justify-between p-3 bg-base-200 rounded-lg"
						>
							<div className="flex items-baseline gap-2">
								{player.isDrawing && (
									<span className="text-xl">🖌</span>
								)}
								<span className="font-mono text-xl font-semibold">{player.name}</span>
							</div>
							<span className="font-mono text-xl font-bold">{player.score}点</span>
						</div>
					))}
				</div>

			</div>
		</div>
	);
};

export default ScoreBoard;
