import socket
import sys

host = sys.argv[1]

try: 
  ip = socket.gethostbyname(host)

except socket.error as e:
  print(f"Não foi possível resolver o endereço de {host}")
  sys.exit(1)

print(f"O IP de {host}:{ip}")