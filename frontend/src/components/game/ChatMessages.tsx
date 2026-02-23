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
	const messageEndRef = useRef<HTMLDivElement>(null);

	useEffect(() => {
		messageEndRef.current?.scrollIntoView({ behavior: "smooth" });
	}, [messages.length]);

	return (
		<div className="space-y-2 h-64 overflow-y-auto p-2 bg-base-200 rounded-lg">
			{messages.length === 0 ? (
				<p className="text-center text-base-content/50">
					メッセージはまだありません
				</p>
			) : (
				messages.map(message => {
					const isOwnMessage = message.sender === currentUserName;
					return (
						<div
							key={message.id}
							className={`chat ${isOwnMessage ? "chat-start" : "chat-end"}`}
						>
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
			<div ref={messageEndRef} />
		</div>
	);
};

export default ChatMessages;
