import { Button } from "@/components/ui/button";
import { Client } from "@stomp/stompjs";
import { createFileRoute } from "@tanstack/react-router";
import { useCallback, useEffect, useRef, useState } from "react";
import SockJS from "sockjs-client";

const WEBSOCKET_URL = "http://localhost:8080/ws-chat";

export const Route = createFileRoute("/teste")({
	component: Chat,
});

type ChatMessage = {
	sender: string;
	content: string;
	type: "CHAT" | "JOIN" | "LEAVE";
};

function Chat() {
	const [messages, setMessages] = useState<ChatMessage[]>([]);
	const [connectionStatus, setConnectionStatus] =
		useState<string>("Desconectado");
	const [username, setUsername] = useState<string>("");
	const [isJoined, setIsJoined] = useState<boolean>(false);
	const [messageInput, setMessageInput] = useState<string>("");
	const stompClient = useRef<Client | null>(null);
	const messagesEndRef = useRef<HTMLDivElement>(null);

	// Auto scroll para a última mensagem
	const scrollToBottom = useCallback(() => {
		messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
	}, []);

	useEffect(() => {
		scrollToBottom();
	}, [scrollToBottom]);

	// Conecta ao WebSocket quando o componente é montado
	useEffect(() => {
		console.log("Tentando conectar ao WebSocket:", WEBSOCKET_URL);
		setConnectionStatus("Conectando...");

		const socket = new SockJS(WEBSOCKET_URL);
		stompClient.current = new Client({
			webSocketFactory: () => socket,
			onConnect: () => {
				console.log("Conectado ao STOMP");
				setConnectionStatus("Conectado");
				if (stompClient.current) {
					// Subscreve ao tópico público para receber mensagens
					stompClient.current.subscribe("/topic/public", (msg) => {
						console.log("Mensagem recebida:", msg.body);
						try {
							const receivedMessage: ChatMessage = JSON.parse(msg.body);
							console.log("Mensagem parseada:", receivedMessage);
							setMessages((prev) => {
								console.log("Mensagens anteriores:", prev);
								const newMessages = [...prev, receivedMessage];
								console.log("Novas mensagens:", newMessages);
								return newMessages;
							});
						} catch (error) {
							console.error("Erro ao parsear mensagem:", error);
						}
					});
				}
			},
			onStompError: (frame) => {
				console.error("Erro STOMP:", frame);
				setConnectionStatus("Erro STOMP");
			},
			onWebSocketError: (error) => {
				console.error("Erro WebSocket:", error);
				setConnectionStatus("Erro WebSocket");
			},
			onDisconnect: () => {
				console.log("Desconectado");
				setConnectionStatus("Desconectado");
			},
		});

		stompClient.current.activate();

		return () => {
			if (stompClient.current) {
				stompClient.current.deactivate();
			}
		};
	}, []);

	// Função para entrar no chat
	const joinChat = () => {
		if (!username.trim()) {
			alert("Por favor, digite um nome de usuário");
			return;
		}

		if (!stompClient.current || !stompClient.current.connected) {
			alert("Conexão WebSocket não estabelecida");
			return;
		}

		const joinMessage: ChatMessage = {
			sender: username,
			content: `${username} entrou no chat`,
			type: "JOIN",
		};

		try {
			stompClient.current.publish({
				destination: "/app/chat.addUser",
				body: JSON.stringify(joinMessage),
			});
			setIsJoined(true);
			console.log("Usuário entrou no chat:", username);
		} catch (error) {
			console.error("Erro ao entrar no chat:", error);
		}
	};

	// Função para enviar mensagem de teste
	const sendTestMessage = () => {
		const testMessage: ChatMessage = {
			sender: "Sistema",
			content: "Mensagem de teste local",
			type: "CHAT",
		};

		console.log("Adicionando mensagem de teste:", testMessage);
		setMessages((prev) => [...prev, testMessage]);
	};

	// Função para enviar mensagem
	const sendMessage = () => {
		if (!messageInput.trim()) return;

		if (!stompClient.current || !stompClient.current.connected) {
			console.error("Cliente STOMP não está conectado");
			return;
		}

		const message: ChatMessage = {
			sender: username,
			content: messageInput,
			type: "CHAT",
		};

		try {
			stompClient.current.publish({
				destination: "/app/chat.sendMessage",
				body: JSON.stringify(message),
			});
			setMessageInput("");
			console.log("Mensagem enviada:", message);
		} catch (error) {
			console.error("Erro ao enviar mensagem:", error);
		}
	};

	// Função para sair do chat
	const leaveChat = () => {
		if (stompClient.current?.connected) {
			const leaveMessage: ChatMessage = {
				sender: username,
				content: `${username} saiu do chat`,
				type: "LEAVE",
			};

			stompClient.current.publish({
				destination: "/app/chat.sendMessage",
				body: JSON.stringify(leaveMessage),
			});
		}
		setIsJoined(false);
		setUsername("");
		setMessages([]);
	};

	// Função para lidar com Enter no input
	const handleKeyPress = (e: React.KeyboardEvent) => {
		if (e.key === "Enter" && !e.shiftKey) {
			e.preventDefault();
			if (isJoined) {
				sendMessage();
			} else {
				joinChat();
			}
		}
	};

	// Renderiza mensagem baseada no tipo
	const renderMessage = (msg: ChatMessage, idx: number) => {
		console.log(`Renderizando mensagem ${idx}:`, msg);
		const isSystemMessage = msg.type === "JOIN" || msg.type === "LEAVE";
		const isOwnMessage = msg.sender === username && msg.type === "CHAT";

		console.log(
			`isSystemMessage: ${isSystemMessage}, isOwnMessage: ${isOwnMessage}, username: ${username}`,
		);

		return (
			<li
				key={`${msg.sender}-${msg.content}-${idx}`}
				className={`p-3 rounded-lg ${
					isSystemMessage
						? "bg-gray-800 text-gray-400 text-center italic border border-gray-700"
						: isOwnMessage
							? "bg-blue-600 text-white ml-auto max-w-xs shadow-lg"
							: "bg-gray-700 text-white border border-gray-600 mr-auto max-w-xs shadow-lg"
				}`}
			>
				{!isSystemMessage && (
					<div
						className={`text-sm font-semibold mb-1 ${
							isOwnMessage ? "text-blue-100" : "text-gray-300"
						}`}
					>
						{msg.sender}
					</div>
				)}
				<div className={isSystemMessage ? "text-gray-400" : "text-white"}>
					{msg.content}
				</div>
			</li>
		);
	};

	// Se o usuário ainda não entrou no chat
	if (!isJoined) {
		return (
			<div className="h-full bg-gradient-to-br from-gray-900 to-gray-800 flex items-center justify-center">
				<div className="bg-gray-800 border border-gray-700 p-8 rounded-lg shadow-lg max-w-md w-full">
					<h1 className="text-2xl font-bold text-center mb-6 text-white">
						🍌 BananaChat
					</h1>

					<div className="mb-4">
						<p className="text-sm mb-2 text-gray-300">
							Status da conexão:{" "}
							<span
								className={
									connectionStatus === "Conectado"
										? "text-green-400 font-semibold"
										: "text-red-400 font-semibold"
								}
							>
								{connectionStatus}
							</span>
						</p>
					</div>

					<div className="space-y-4">
						<div>
							<label
								htmlFor="username-input"
								className="block text-sm font-medium text-gray-300 mb-2"
							>
								Digite seu nome:
							</label>
							<input
								id="username-input"
								type="text"
								value={username}
								onChange={(e) => setUsername(e.target.value)}
								onKeyPress={handleKeyPress}
								className="w-full p-3 bg-gray-700 border border-gray-600 text-white rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent placeholder-gray-400"
								placeholder="Seu nome..."
								disabled={connectionStatus !== "Conectado"}
							/>
						</div>

						<Button
							onClick={joinChat}
							disabled={connectionStatus !== "Conectado" || !username.trim()}
							className="w-full bg-blue-600 hover:bg-blue-700 text-white"
						>
							Entrar no Chat
						</Button>
					</div>
				</div>
			</div>
		);
	}

	// Interface principal do chat
	return (
		<div className="min-h-screen bg-gradient-to-br from-gray-900 to-gray-800">
			<div className="container mx-auto max-w-4xl h-screen flex flex-col">
				{/* Header */}
				<div className="bg-gray-800 border-b border-gray-700 shadow-sm p-4">
					<div className="flex justify-between items-center">
						<h1 className="text-xl font-bold text-white">🍌 BananaChat</h1>
						<div className="flex items-center space-x-4">
							<span className="text-sm text-gray-300">
								Conectado como:{" "}
								<strong className="text-white">{username}</strong>
							</span>
							<Button
								onClick={leaveChat}
								variant="outline"
								className="text-red-400 border-red-600 hover:bg-red-900 hover:text-red-300"
							>
								Sair
							</Button>
						</div>
					</div>
				</div>

				{/* Área de mensagens */}
				<div className="flex-1 bg-gray-900 overflow-hidden">
					<div className="h-full flex flex-col">
						<div className="flex-1 overflow-y-auto p-4">
							<ul className="space-y-3">
								{messages.map((msg, idx) => {
									console.log(`Renderizando mensagem ${idx}:`, msg);
									return renderMessage(msg, idx);
								})}
							</ul>
							<div ref={messagesEndRef} />
						</div>

						{/* Input de mensagem */}
						<div className="bg-gray-800 border-t border-gray-700 p-4">
							<div className="flex space-x-2 mb-2">
								<Button
									onClick={sendTestMessage}
									variant="outline"
									className="text-xs px-2 py-1 text-gray-300 border-gray-600 hover:bg-gray-700"
								>
									Teste Local
								</Button>
							</div>
							<div className="flex space-x-2">
								<input
									type="text"
									value={messageInput}
									onChange={(e) => setMessageInput(e.target.value)}
									onKeyPress={handleKeyPress}
									className="flex-1 p-3 bg-gray-700 border border-gray-600 text-white rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent placeholder-gray-400"
									placeholder="Digite sua mensagem..."
									disabled={connectionStatus !== "Conectado"}
								/>
								<Button
									onClick={sendMessage}
									disabled={
										connectionStatus !== "Conectado" || !messageInput.trim()
									}
									className="px-6 bg-blue-600 hover:bg-blue-700 text-white"
								>
									Enviar
								</Button>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
}
