import socket  # Biblioteca para comunicação via sockets
import json  # Biblioteca para manipulação de dados em formato JSON
import time  # Biblioteca para manipulação de tempo

# -------------------------------
# Configuração inicial do servidor
# -------------------------------

# Obtém o IP local do servidor
local_ip = socket.gethostbyname(socket.gethostname())  # Obtém o IP do host local

# Configuração do socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Cria um socket UDP
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)  # Habilita o modo de broadcast
sock.bind(('0.0.0.0', 5000))  # Associa o socket à porta 5000 para receber dados

# Cada player terá os dados enviados e um timestamp indicando a última atualização
players = {}  # Dicionário para armazenar os dados dos jogadores

TIMEOUT = 10  # Tempo em segundos para considerar o player desconectado
UPDATE_INTERVAL = 1  # Intervalo de timeout do socket para verificar atualizações

print(f"Servidor de jogo iniciado... IP: {local_ip}")  # Mensagem indicando que o servidor foi iniciado

# -------------------------------
# Loop principal do servidor
# -------------------------------
while True:
    sock.settimeout(UPDATE_INTERVAL)  # Define o intervalo de timeout para o socket
    try:
        # Aguarda receber dados de um jogador
        data, addr = sock.recvfrom(1024)  # Recebe até 1024 bytes de dados
        player_data = json.loads(data.decode())  # Decodifica os dados recebidos em formato JSON
        player_id = player_data["id"]  # Obtém o ID do jogador a partir dos dados recebidos

        # Armazena os dados do player e registra a hora atual
        player_data["last_seen"] = time.time()  # Adiciona o timestamp da última atualização
        players[player_id] = player_data  # Atualiza ou adiciona os dados do jogador no dicionário
    except socket.timeout:
        # Se não houver dados recebidos dentro do intervalo de timeout, continua o loop
        pass

    # -------------------------------
    # Remoção de jogadores desconectados
    # -------------------------------
    now = time.time()  # Obtém o timestamp atual
    # Lista de jogadores que não atualizaram seu timestamp dentro do período de TIMEOUT
    disconnected = [pid for pid, pdata in players.items() if now - pdata.get("last_seen", 0) > TIMEOUT]
    for pid in disconnected:
        del players[pid]  # Remove os jogadores desconectados do dicionário

    # -------------------------------
    # Exibição do estado atual dos jogadores
    # -------------------------------
    for pid, pdata in players.items():
        print(f"ID: {pid}, Dados: {pdata}")  # Exibe o ID e os dados de cada jogador no console

    # -------------------------------
    # Envio do estado dos jogadores via broadcast
    # -------------------------------
    broadcast_message = json.dumps(players).encode()  # Converte o dicionário de jogadores para JSON e codifica em bytes
    sock.sendto(broadcast_message, ('255.255.255.255', 5001))  # Envia os dados via broadcast na porta 5001