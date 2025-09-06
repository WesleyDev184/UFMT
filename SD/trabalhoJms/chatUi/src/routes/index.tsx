import ChatLayout from "@/components/chat/ChatLayout";
import { createFileRoute } from "@tanstack/react-router";

export const Route = createFileRoute("/")({
	component: Index,
});

function Index() {
	return (
		<div className="h-full flex flex-col justify-center items-center border border-red-700 border-dashed">
			<ChatLayout />
		</div>
	);
}
