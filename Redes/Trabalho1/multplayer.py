import socket
import json
import threading
import random

class MultiplayerClient:
    def __init__(self, server_ip='127.0.1.1', send_port=5000, recv_port=5001):
        self.player_id = random.randint(1000, 9999)
        self.server_ip = server_ip
        self.send_port = send_port

        # Socket para envio
        self.send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Socket para recepção via broadcast
        self.recv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.recv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.recv_sock.bind(('', recv_port))

        self.players = {}

        # Thread para receber atualizações
        threading.Thread(target=self.receive_updates, daemon=True).start()

    def receive_updates(self):
        while True:
            try:
                data, _ = self.recv_sock.recvfrom(4096)
                self.players = json.loads(data.decode())
            except Exception as e:
                print("Erro ao receber atualizações:", e)

    def send_player_state(self, x, y, u=1, v=0, status="vivo", bullets=None, score=None):
        player_state = {
            "id": self.player_id,
            "x": x,
            "y": y,
            "u": u,
            "v": v,
            "status": status
        }
        if bullets is not None:
            player_state["bullets"] = bullets
        if score is not None:
            player_state["score"] = score
        self.send_sock.sendto(json.dumps(player_state).encode(), (self.server_ip, self.send_port))