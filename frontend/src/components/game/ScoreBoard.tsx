interface Player {
	id: number,
	name: string,
	score: number,
	isDrawing: boolean,
};

interface ScoreBoardProps {
	players: Player[],
};

const ScoreBoard = ({ players }: ScoreBoardProps) => {
	const sortedPlayers = [...players].sort((a, b) => b.score - a.score);

	return (
		<div className="card bg-base-100 shadow-xl">
			<div className="card-body p-0">
				<h2 className="card-title font-mono text-base font-semibold mb-1">スコア</h2>
				
				<div className="space-y-2">
					{sortedPlayers.map(player => (
						<div
							key={player.id}
							className="flex items-baseline justify-between px-3 py-3 bg-base-200 rounded-lg"
						>
							<div className="flex items-baseline gap-2">
								<div className="indicator">
									{player.isDrawing && (
										<span className="indicator-item badge badge-ghost badge-xs">🖌</span>
									)}
									<span className="font-mono text-base font-semibold pr-2">{player.name}</span>
								</div>
							</div>
							<span className="font-mono text-base font-bold">{player.score}点</span>
						</div>
					))}
				</div>

			</div>
		</div>
	);
};

export default ScoreBoard;
