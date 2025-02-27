from socket import *
import sys
import json

if len(sys.argv) < 3:
    print(f"Uso: python3 {sys.argv[0]} <ip_servidor> <porta_servidor>")
    sys.exit(1)

server_addr = (sys.argv[1], int(sys.argv[2]))

sock = socket(AF_INET, SOCK_DGRAM)
print(f"Conectando-se a {server_addr}")

def send_request(command):
    sock.sendto(command.encode(), server_addr)
    response, addr = sock.recvfrom(1024)
    return response.decode()

try:
    while True:
        print("\nMenu:")
        print("1. Info")
        print("2. List")
        print("3. Insert <nome>")
        print("4. Resolve <nome>")
        print("5. Sair")
        choice = input("Escolha uma opção: ")

        if choice == '1':
            response = send_request("info")
            print(f"Resposta: {response}")
        elif choice == '2':
            response = send_request("list")
            print(f"Resposta: {response}")
        elif choice.startswith('3'):
            name = input("Digite o nome para inserir: ")
            response = send_request(f"insert {name}")
            print(f"Resposta: {response}")
        elif choice.startswith('4'):
            name = input("Digite o nome para resolver: ")
            response = send_request(f"resolve {name}")
            print(f"Resposta: {response}")
        elif choice == '5':
            print("Encerrando cliente...")
            break
        else:
            print("Opção inválida. Tente novamente.")
except Exception as e:
    print(f"Erro: {e}")
except KeyboardInterrupt:
    print("Cliente encerrado")
finally:
    sock.close()
    print("Conexão encerrada")