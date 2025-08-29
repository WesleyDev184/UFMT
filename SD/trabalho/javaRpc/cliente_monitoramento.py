import sys
import xmlrpc.client
from typing import List

DEFAULT_FILIAIS = ["A", "B", "C", "D", "E", "F", "G", "H"]

def normalize_filial(raw: str) -> str:
    raw = raw.strip()
    if not raw:
        return ""
    # aceita 'A' ou 'Filial A'
    if raw.lower().startswith("filial"):
        return raw.split()[-1].upper()
    if len(raw) == 1 and raw.upper() in [c for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"]:
        return f"{raw.upper()}"
    return raw

def as_float(val) -> float:
    if val is None:
        return 0.0
    if isinstance(val, (int, float)):
        return float(val)
    try:
        return float(str(val))
    except Exception:
        return 0.0

def print_produtos(produtos):
    if not produtos:
        print("  (nenhum produto retornado)")
        return
    for i, p in enumerate(produtos, 1):
        print(f"  {i}) {p}")

def menu_loop(client):
    while True:
        print("\n--- Menu de Monitoramento ---")
        print("1) Ver total de vendas de uma filial")
        print("2) Ver total de vendas de todas as filiais (ampliado)")
        print("3) Listar produtos mais vendidos de uma filial")
        print("4) Listar top N produtos para todas as filiais (ampliado)")
        print("5) Sair")
        opc = input("Escolha uma opção: ").strip()
        if opc == "1":
            raw = input("Digite o ID da filial (ex: A ou 'Filial A'): ").strip()
            fid = normalize_filial(raw)
            try:
                resp = client.vendas.obterTotalVendasDiarias(fid)
                print(f"Vendas totais da {fid}: R$ {as_float(resp):.2f}")
            except Exception as e:
                print(f"Erro ao obter vendas: {e}")
        elif opc == "2":
            print("Totais das filiais:")
            for short in DEFAULT_FILIAIS:
                fid = normalize_filial(short)
                try:
                    resp = client.vendas.obterTotalVendasDiarias(fid)
                    print(f"  {fid}: R$ {as_float(resp):.2f}")
                except Exception as e:
                    print(f"  Erro na {fid}: {e}")
        elif opc == "3":
            raw = input("Digite o ID da filial (ex: A): ").strip()
            fid = normalize_filial(raw)
            n_raw = input("Quantos produtos (N): ").strip()
            try:
                n = int(n_raw) if n_raw else 5
            except Exception:
                n = 5
            try:
                produtos = client.vendas.listarProdutosMaisVendidos(fid, n)
                print(f"Produtos mais vendidos na {fid}:")
                print_produtos(produtos)
            except Exception as e:
                print(f"Erro ao listar produtos: {e}")
        elif opc == "4":
            n_raw = input("Quantos top produtos por filial (N): ").strip()
            try:
                n = int(n_raw) if n_raw else 3
            except Exception:
                n = 3
            for short in DEFAULT_FILIAIS:
                fid = normalize_filial(short)
                try:
                    produtos = client.vendas.listarProdutosMaisVendidos(fid, n)
                    print(f"\n{fid}:")
                    print_produtos(produtos)
                except Exception as e:
                    print(f"  Erro na {fid}: {e}")
        elif opc == "5":
            print("Saindo.")
            return
        else:
            print("Opção inválida. Tente novamente.")

def main():
    host = input("Digite o IP/host do servidor (enter = localhost): ").strip()
    if not host:
        host = "127.0.0.1"
    server_url = f"http://{host}:8080/xmlrpc"
    print(f"Conectando a {server_url} ...")
    try:
        client = xmlrpc.client.ServerProxy(server_url, allow_none=True)
        menu_loop(client)
    except Exception as e:
        print(f"Erro conectando ao servidor XML-RPC: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()