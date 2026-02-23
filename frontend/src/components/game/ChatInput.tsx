import { useState } from "react";

interface ChatInputProps {
	onSendMessage: (text: string) => void;
	disabled?: boolean;
}

const ChatInput = ({ onSendMessage, disabled = false }: ChatInputProps) => {
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
				placeholder={
					disabled ? "観戦者はチャットできません" : "コメントを入力…"
				}
				disabled={disabled}
			/>
			<button
				type="submit"
				className="btn btn-primary join-item"
				disabled={disabled}
			>
				送信
			</button>
		</form>
	);
};

export default ChatInput;
