import { useRef, useEffect } from "react";

export interface Message {
	id: string;
	sender: string;
	text: string;
	timestamp: Date;
}

interface ChatMessagesProps {
	messages: Message[];
	currentUserName: string;
}

const ChatMessages = ({ messages, currentUserName }: ChatMessagesProps) => {
	const scrollContainerRef = useRef<HTMLDivElement>(null);

	useEffect(() => {
		const container = scrollContainerRef.current;
		if (container) {
			container.scrollTop = container.scrollHeight;
		}
	}, [messages.length]);

	return (
		<div
			ref={scrollContainerRef}
			className="space-y-2 h-64 overflow-y-auto p-2 bg-base-200 rounded-lg"
		>
			{messages.length === 0 ? (
				<p className="text-center text-base-content/50">
					メッセージはまだありません
				</p>
			) : (
				messages.map(message => {
					const isOwnMessage = message.sender === currentUserName;
					return (
						<div key={message.id} className="chat chat-start">
							<div className="chat-header">
								<span className="font-semibold">
									{message.sender}
								</span>
							</div>
							<div
								className={`chat-bubble text-sm ${isOwnMessage ? "chat-bubble-primary" : "chat-bubble-secondary"}`}
							>
								{message.text}
							</div>
						</div>
					);
				})
			)}
			<div />
		</div>
	);
};

export default ChatMessages;
