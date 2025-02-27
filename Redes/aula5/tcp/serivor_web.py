from socket import *
import os

# AF_INET: IPv4 (camada de rede)
# SOCK_DGRAM: protocolo UDP (camada de transporte)
host = ''
port = 8080

sock = socket(AF_INET, SOCK_STREAM)
sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1) # permite reutilizar a porta
sock.bind((host, port))
print(f'Servidor eco tcp iniciado em {sock.getsockname()}')
sock.listen(30) # 3 conexões simultâneas

while True:
  try:
    conn, addr = sock.accept()
    print(f'Conectado a {addr}')
    req = conn.recv(2048)
    print(f'Requisicao de {addr}:\n {req.decode()}')
    linha_1 = req.decode().split('\n')[0]
    metodo, recurso, protocolo = linha_1.split(' ')
    print(f'Recurso: {recurso}, Método: {metodo}, Protocolo: {protocolo}')

    if recurso == '/':
      recurso = 'index.html'

    if os.path.exists(recurso):
      with open(recurso, 'rb') as f:
        html = f.read()
        conn.send('HTTP/1.1 200 OK\r\n\r\n'.encode())
        conn.send(html)
    else:
      conn.send('HTTP/1.1 404 Not Found\r\n\r\n'.encode())
      conn.send('<h1>404 Not Found</h1>'.encode())

    conn.close()
  except Exception as e:
    print(f'Erro: {e}')
    break
  except KeyboardInterrupt:
    print('Servidor encerrado')
    break

sock.close()
print('Conexão encerrada')