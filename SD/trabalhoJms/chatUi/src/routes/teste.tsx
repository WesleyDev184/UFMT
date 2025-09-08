import { Button } from "@/components/ui/button";
import { Client } from "@stomp/stompjs";
import { createFileRoute } from "@tanstack/react-router";
import { useCallback, useEffect, useRef, useState } from "react";
import SockJS from "sockjs-client";

const WEBSOCKET_URL = "http://localhost:8080/ws-chat";
const API_BASE_URL = "http://localhost:8080/api";

export const Route = createFileRoute("/teste")({
  component: Chat,
});

type ChatMessage = {
  sender: string;
  content: string;
  type: "CHAT" | "JOIN" | "LEAVE";
  timestamp?: string;
};

type ChatHistoryDto = {
  sender: string;
  content: string;
  type: string;
  timestamp: string;
};

function Chat() {
  const [messages, setMessages] = useState<ChatMessage[]>([]);
  const [connectionStatus, setConnectionStatus] =
    useState<string>("Desconectado");
  const [username, setUsername] = useState<string>("");
  const [isJoined, setIsJoined] = useState<boolean>(false);
  const [messageInput, setMessageInput] = useState<string>("");
  const [isLoadingHistory, setIsLoadingHistory] = useState<boolean>(false);
  const [isAutoUpdating, setIsAutoUpdating] = useState<boolean>(false);
  const stompClient = useRef<Client | null>(null);
  const messagesEndRef = useRef<HTMLDivElement>(null);

  // Auto scroll para a última mensagem
  const scrollToBottom = useCallback(() => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
  }, []);

  useEffect(() => {
    scrollToBottom();
  }, [scrollToBottom]);

  // Função para recarregar histórico manualmente
  const refreshHistory = async () => {
    const historyMessages = await fetchChatHistory();
    setMessages(historyMessages);
  };

  // Atualização automática do histórico a cada 30 segundos quando o usuário está no chat
  useEffect(() => {
    if (!isJoined) return;

    const intervalId = setInterval(async () => {
      console.log("Atualizando histórico automaticamente...");
      setIsAutoUpdating(true);
      try {
        const latestHistory = await fetchChatHistory();
        setMessages((prevMessages) => {
          // Verifica se há novas mensagens para evitar atualizações desnecessárias
          if (latestHistory.length !== prevMessages.length) {
            console.log("Novas mensagens encontradas, atualizando...");
            return latestHistory;
          }
          return prevMessages;
        });
      } catch (error) {
        console.error("Erro na atualização automática do histórico:", error);
      } finally {
        setIsAutoUpdating(false);
      }
    }, 30000); // 30 segundos

    return () => {
      clearInterval(intervalId);
    };
  }, [isJoined]);

  // Atualiza histórico quando a janela volta ao foco
  useEffect(() => {
    if (!isJoined) return;

    const handleFocus = async () => {
      console.log("Janela voltou ao foco, atualizando histórico...");
      setIsAutoUpdating(true);
      try {
        const latestHistory = await fetchChatHistory();
        setMessages(latestHistory);
      } catch (error) {
        console.error("Erro ao atualizar histórico no foco:", error);
      } finally {
        setIsAutoUpdating(false);
      }
    };

    window.addEventListener("focus", handleFocus);

    return () => {
      window.removeEventListener("focus", handleFocus);
    };
  }, [isJoined]);
  const fetchChatHistory = async (): Promise<ChatMessage[]> => {
    try {
      setIsLoadingHistory(true);
      console.log("Buscando histórico de mensagens...");

      const response = await fetch(`${API_BASE_URL}/chat/history`);
      if (!response.ok) {
        throw new Error(`Erro HTTP: ${response.status}`);
      }

      const history: ChatHistoryDto[] = await response.json();
      console.log("Histórico recebido:", history);

      // Converte o formato do histórico para o formato das mensagens
      const convertedMessages: ChatMessage[] = history.map((item) => ({
        sender: item.sender,
        content: item.content,
        type: item.type as "CHAT" | "JOIN" | "LEAVE",
        timestamp: item.timestamp,
      }));

      console.log("Mensagens convertidas:", convertedMessages);
      return convertedMessages;
    } catch (error) {
      console.error("Erro ao buscar histórico:", error);
      return [];
    } finally {
      setIsLoadingHistory(false);
    }
  };

  // Conecta ao WebSocket quando o componente é montado
  useEffect(() => {
    const initializeChat = async () => {
      console.log("Inicializando chat...");

      // 1. Primeiro busca o histórico
      const historyMessages = await fetchChatHistory();
      setMessages(historyMessages);

      // 2. Depois conecta ao WebSocket
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

                // Adiciona timestamp se não tiver
                if (!receivedMessage.timestamp) {
                  receivedMessage.timestamp = new Date().toISOString();
                }

                setMessages((prev) => {
                  console.log(
                    "Adicionando mensagem às mensagens anteriores:",
                    prev
                  );
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
    };

    initializeChat();

    return () => {
      if (stompClient.current) {
        stompClient.current.deactivate();
      }
    };
  }, []);

  // Função para entrar no chat
  const joinChat = async () => {
    if (!username.trim()) {
      alert("Por favor, digite um nome de usuário");
      return;
    }

    if (!stompClient.current || !stompClient.current.connected) {
      alert("Conexão WebSocket não estabelecida");
      return;
    }

    // Atualiza o histórico automaticamente quando o usuário entra
    console.log("Atualizando histórico antes de entrar no chat...");
    const latestHistory = await fetchChatHistory();
    setMessages(latestHistory);

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

    // Formatar timestamp
    const formatTimestamp = (timestamp?: string) => {
      if (!timestamp) return "";
      try {
        const date = new Date(timestamp);
        return date.toLocaleTimeString("pt-BR", {
          hour: "2-digit",
          minute: "2-digit",
        });
      } catch {
        return "";
      }
    };

    console.log(
      `isSystemMessage: ${isSystemMessage}, isOwnMessage: ${isOwnMessage}, username: ${username}`
    );

    return (
      <li
        key={`${msg.sender}-${msg.content}-${idx}-${msg.timestamp}`}
        className={`p-3 rounded-lg ${
          isSystemMessage
            ? "bg-gray-800 text-gray-400 text-center italic border border-gray-700"
            : isOwnMessage
            ? "bg-blue-600 text-white ml-auto max-w-xs shadow-lg"
            : "bg-gray-700 text-white border border-gray-600 mr-auto max-w-xs shadow-lg"
        }`}
      >
        {!isSystemMessage && (
          <div className="flex justify-between items-center mb-1">
            <div
              className={`text-sm font-semibold ${
                isOwnMessage ? "text-blue-100" : "text-gray-300"
              }`}
            >
              {msg.sender}
            </div>
            {msg.timestamp && (
              <div
                className={`text-xs ${
                  isOwnMessage ? "text-blue-200" : "text-gray-400"
                }`}
              >
                {formatTimestamp(msg.timestamp)}
              </div>
            )}
          </div>
        )}
        <div className={isSystemMessage ? "text-gray-400" : "text-white"}>
          {msg.content}
        </div>
        {isSystemMessage && msg.timestamp && (
          <div className="text-xs text-gray-500 mt-1">
            {formatTimestamp(msg.timestamp)}
          </div>
        )}
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

          {isLoadingHistory && (
            <div className="mb-4 text-center">
              <div className="text-sm text-yellow-400 mb-2">
                Carregando histórico de mensagens...
              </div>
              <div className="w-full bg-gray-700 rounded-full h-2">
                <div
                  className="bg-yellow-400 h-2 rounded-full animate-pulse"
                  style={{ width: "60%" }}
                ></div>
              </div>
            </div>
          )}

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
    <div className="h-full bg-gradient-to-br from-gray-900 to-gray-800">
      <div className="container mx-auto max-w-4xl h-full flex flex-col">
        {/* Header */}
        <div className="bg-gray-800 border-b border-gray-700 shadow-sm p-4">
          <div className="flex justify-between items-center">
            <div className="flex items-center space-x-3">
              <h1 className="text-xl font-bold text-white">🍌 BananaChat</h1>
              {isAutoUpdating && (
                <div className="flex items-center text-xs text-blue-400">
                  <div className="w-2 h-2 bg-blue-400 rounded-full animate-pulse mr-1"></div>
                  Sincronizando
                </div>
              )}
            </div>
            <div className="flex items-center space-x-4">
              <div className="text-right">
                <div className="text-sm text-gray-300">
                  Conectado como:{" "}
                  <strong className="text-white">{username}</strong>
                </div>
                <div className="text-xs text-gray-400">
                  Histórico atualiza automaticamente
                </div>
              </div>
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
              {messages.length > 0 && (
                <div className="text-center mb-4 space-y-2">
                  <div className="inline-flex items-center px-3 py-1 rounded-full text-xs bg-gray-700 text-gray-300 border border-gray-600">
                    📜 {messages.length} mensagem(s) carregada(s) do histórico
                  </div>
                  {isAutoUpdating && (
                    <div className="inline-flex items-center px-2 py-1 rounded-full text-xs bg-blue-600 text-blue-100 ml-2">
                      🔄 Atualizando...
                    </div>
                  )}
                </div>
              )}
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
                <Button
                  onClick={refreshHistory}
                  variant="outline"
                  className="text-xs px-2 py-1 text-gray-300 border-gray-600 hover:bg-gray-700"
                  disabled={isLoadingHistory || isAutoUpdating}
                >
                  {isLoadingHistory || isAutoUpdating
                    ? "Carregando..."
                    : "🔄 Sincronizar Agora"}
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
