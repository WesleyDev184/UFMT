from socket import *

# AF_INET: IPv4 (camada de rede)
# SOCK_DGRAM: protocolo UDP (camada de transporte)
host = ''
port = 5000

sock = socket(AF_INET, SOCK_STREAM)
sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sock.bind((host, port))
print(f'Servidor eco tcp iniciado em {sock.getsockname()}')
sock.listen(3) # 3 conexões simultâneas

while True:
  try:
    conn, addr = sock.accept()
    print(f'Conectado a {addr}')
    msg = conn.recv(1024)
    print(f'Recebido de {addr}: {msg.decode()}')
    conn.send(msg.upper())
    conn.close()
  except Exception as e:
    print(f'Erro: {e}')
    break
  except KeyboardInterrupt:
    print('Servidor encerrado')
    break

sock.close()
print('Conexão encerrada')