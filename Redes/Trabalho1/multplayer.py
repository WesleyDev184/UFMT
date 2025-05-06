import socket  # Biblioteca para comunicação via sockets
import json  # Biblioteca para manipulação de dados em formato JSON
import threading  # Biblioteca para trabalhar com threads
import random  # Biblioteca para gerar números aleatórios

# -------------------------------
# Classe para gerenciar o cliente multiplayer
# -------------------------------
class MultiplayerClient:
    def __init__(self, server_ip='10.1.17.122', send_port=5000, recv_port=5001):
        """
        Inicializa o cliente multiplayer.
        :param server_ip: Endereço IP do servidor.
        :param send_port: Porta para envio de dados.
        :param recv_port: Porta para recepção de dados.
        """
        self.player_id = random.randint(1000, 9999)  # Gera um ID único para o jogador
        self.server_ip = server_ip  # IP do servidor
        self.send_port = send_port  # Porta para envio de dados

        # Cria um socket para envio de dados (UDP)
        self.send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Cria um socket para recepção de dados via broadcast (UDP)
        self.recv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.recv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Permite reutilizar a porta
        self.recv_sock.bind(('', recv_port))  # Associa o socket à porta de recepção

        self.players = {}  # Dicionário para armazenar o estado dos jogadores

        # Inicia uma thread para receber atualizações do servidor
        threading.Thread(target=self.receive_updates, daemon=True).start()

    # -------------------------------
    # Função para receber atualizações do servidor
    # -------------------------------
    def receive_updates(self):
        """
        Recebe atualizações do servidor e atualiza o estado dos jogadores.
        """
        while True:  # Loop infinito para receber dados continuamente
            try:
                data, _ = self.recv_sock.recvfrom(4096)  # Recebe até 4096 bytes de dados
                self.players = json.loads(data.decode())  # Decodifica os dados JSON recebidos
            except Exception as e:  # Trata possíveis erros
                print("Erro ao receber atualizações:", e)  # Exibe o erro no console

    # -------------------------------
    # Função para enviar o estado do jogador ao servidor
    # -------------------------------
    def send_player_state(self, x, y, u=1, v=0, status="vivo", bullets=None, score=None, human_image=None):
        """
        Envia o estado atual do jogador para o servidor.
        :param x: Posição X do jogador.
        :param y: Posição Y do jogador.
        :param u: Direção do jogador.
        :param v: Animação do jogador.
        :param status: Status do jogador ("vivo" ou "morto").
        :param bullets: Lista de balas disparadas pelo jogador.
        :param score: Pontuação do jogador.
        :param human_image: Sprite do jogador.
        """
        # Cria um dicionário com o estado do jogador
        player_state = {
            "id": self.player_id,  # ID único do jogador
            "x": x,  # Posição X
            "y": y,  # Posição Y
            "u": u,  # Direção
            "v": v,  # Animação
            "status": status  # Status ("vivo" ou "morto")
        }
        if bullets is not None:  # Adiciona as balas, se fornecidas
            player_state["bullets"] = bullets
        if score is not None:  # Adiciona a pontuação, se fornecida
            player_state["score"] = score
        if human_image is not None:  # Adiciona o sprite do jogador, se fornecido
            player_state["human_image"] = human_image

        # Envia o estado do jogador para o servidor em formato JSON
        self.send_sock.sendto(json.dumps(player_state).encode(), (self.server_ip, self.send_port))