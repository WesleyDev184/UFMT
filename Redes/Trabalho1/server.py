import socket
import json
import time

# Obtém o IP local do servidor
local_ip = socket.gethostbyname(socket.gethostname())

# Configuração do socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.bind(('0.0.0.0', 5000))

# Cada player terá os dados enviados e um timestamp indicando a última atualização
players = {}

TIMEOUT = 10  # tempo em segundos para considerar o player desconectado
UPDATE_INTERVAL = 1  # intervalo de timeout do socket

print(f"Servidor de jogo iniciado... IP: {local_ip}")

while True:
    sock.settimeout(UPDATE_INTERVAL)
    try:
        data, addr = sock.recvfrom(1024)
        player_data = json.loads(data.decode())
        player_id = player_data["id"]

        # Armazena os dados do player e registra a hora atual
        player_data["last_seen"] = time.time()
        players[player_id] = player_data
    except socket.timeout:
        # Se não houver dados, apenas continua
        pass

    # Remove os players que não atualizaram seu timestamp no período de TIMEOUT
    now = time.time()
    disconnected = [pid for pid, pdata in players.items() if now - pdata.get("last_seen", 0) > TIMEOUT]
    for pid in disconnected:
        del players[pid]

    for pid, pdata in players.items():
        print(f"ID: {pid}, Dados: {pdata}")

    # Envia o estado de todos os jogadores via broadcast
    broadcast_message = json.dumps(players).encode()
    sock.sendto(broadcast_message, ('255.255.255.255', 5001))  # Broadcast na porta 5001