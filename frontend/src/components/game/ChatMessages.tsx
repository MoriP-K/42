export interface Message {
	id: string;
	sender: string;
	text: string;
	timestamp: Date;
}

interface ChatMessagesProps {
	messages: Message[];
}

const ChatMessages = ({ messages }: ChatMessagesProps) => {
	return (
		<div className="space-y-2 h-64 overflow-y-auto p-2 bg-base-200 rounded-lg">
			{messages.length === 0 ? (
				<p className="text-center text-base-content/50">
					メッセージはまだありません
				</p>
			) : (
				messages.map(message => (
					<div key={message.id} className="chat chat-end">
						<div className="chat-header">
							<span className="font-semibold">
								{message.sender}
							</span>
						</div>
						<div className="chat-bubble chat-bubble-primary text-sm">
							{message.text}
						</div>
					</div>
				))
			)}
		</div>
	);
};

export default ChatMessages;
