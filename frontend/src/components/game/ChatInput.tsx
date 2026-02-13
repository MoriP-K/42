import { useState } from "react";

interface ChatInputProps {
	onSendMessage: (text: string) => void;
}

const ChatInput = ({ onSendMessage }: ChatInputProps) => {
	const [input, setInput] = useState("");

	const handleSubmit = (e: React.FormEvent) => {
		e.preventDefault();

		if (input.trim() === "") return;

		onSendMessage(input);
		setInput("");
	};

	return (
		<form onSubmit={handleSubmit} className="join w-full">
			<input
				type="text"
				value={input}
				onChange={e => setInput(e.target.value)}
				className="input input-bordered join-item flex-1"
				placeholder="コメントを入力…"
			/>
			<button type="submit" className="btn btn-primary join-item">
				送信
			</button>
		</form>
	);
};

export default ChatInput;
