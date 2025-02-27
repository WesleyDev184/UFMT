from socket import *

# AF_INET: IPv4 (camada de rede)
# SOCK_DGRAM: protocolo UDP (camada de transporte)
host = '127.0.0.1'
port = 5000

sock = socket(AF_INET, SOCK_DGRAM)
sock.bind((host, port))
print(f'Servidor eco iniciado em {sock.getsockname()}')

while True:
  try:
    msg, addr = sock.recvfrom(1024)
    print(f'Recebido de {addr}: {msg.decode()}')
    sock.sendto(msg.upper(), addr) # addr e o destino da mensagem 
  except Exception as e:
    print(f'Erro: {e}')
    break
  except KeyboardInterrupt:
    print('Servidor encerrado')
    break


sock.close()