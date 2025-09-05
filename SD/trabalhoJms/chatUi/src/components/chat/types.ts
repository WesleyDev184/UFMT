export type Message = {
	id: string;
	text: string;
	fromMe?: boolean;
	time?: string;
};

export type Conversation = {
	id: string;
	title: string;
	lastMessage?: string;
	messages: Message[];
};
