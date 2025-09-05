import ChatLayout from "@/components/chat/ChatLayout";
import { createFileRoute } from "@tanstack/react-router";

export const Route = createFileRoute("/")({
	component: Index,
});

function Index() {
	return (
		<div className="h-full p-4">
			<ChatLayout />
		</div>
	);
}
