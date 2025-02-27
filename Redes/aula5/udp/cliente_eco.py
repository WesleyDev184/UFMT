from socket import *
import sys

if len(sys.argv) < 3:
  print(f"Uso: python3 {sys.argv[0]} <ip_servidor> <porta_servidor>")
  sys.exit(1)

server_addr = (sys.argv[1], int(sys.argv[2]))

sock = socket(AF_INET, SOCK_DGRAM)
print(f"Conectando-se a {server_addr}")

try:
  while True:
    msg = input("Digite uma mensagem: ")
    sock.sendto(msg.encode(), server_addr)
    msg, addr = sock.recvfrom(1024)
    print(f"Recebido de {addr}: {msg.decode()}")
except Exception as e:
  print(f"Erro: {e}")
except KeyboardInterrupt:
  print("Cliente encerrado")
finally:
  sock.close()
  print("Conexão encerrada")