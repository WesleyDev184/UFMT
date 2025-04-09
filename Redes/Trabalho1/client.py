import socket
import json
import threading
import time
import random

player_id = random.randint(1000, 9999)

# Socket para envio
send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Socket para recepção via broadcast
recv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
recv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
recv_sock.bind(('', 5001))

def receive_updates():
    while True:
        data, _ = recv_sock.recvfrom(4096)
        players = json.loads(data.decode())
        print("Atualização dos jogadores:", players)

# Thread para receber updates
threading.Thread(target=receive_updates, daemon=True).start()

# Loop de envio
while True:
    player_state = {
        "id": player_id,
        "x": random.randint(0, 100),
        "y": random.randint(0, 100),
        "status": "vivo"
    }

    send_sock.sendto(json.dumps(player_state).encode(), ('10.1.17.122', 5000))
    time.sleep(1)