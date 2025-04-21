import socket
import json

# Obtém o IP local do servidor
local_ip = socket.gethostbyname(socket.gethostname())

# Configuração do socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.bind(('0.0.0.0', 5000))

players = {}

print(f"Servidor de jogo iniciado... IP: {local_ip}")

while True:
    data, addr = sock.recvfrom(1024)
    player_data = json.loads(data.decode())

    player_id = player_data["id"]
    players[player_id] = player_data  # Atualiza estado do jogador

    # Envia o estado de todos os jogadores via broadcast
    broadcast_message = json.dumps(players).encode()
    sock.sendto(broadcast_message, ('255.255.255.255', 5001))  # Broadcast na porta 5001