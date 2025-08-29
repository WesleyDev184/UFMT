import rpyc
import sys

def mostrar_menu():
    print("\n" + "="*50)
    print("         SISTEMA DE MONITORAMENTO DE VENDAS")
    print("="*50)
    print("1. Adicionar Venda")
    print("2. Consultar Total de Vendas por Filial")
    print("3. Listar Produtos Mais Vendidos")
    print("4. Resumo Completo da Filial")
    print("5. Listar Filiais Disponíveis")
    print("0. Sair")
    print("="*50)

def adicionar_venda(conn):
    try:
        filiais = conn.root.ListarFiliaisDisponiveis()
        print(f"\nFiliais disponíveis: {', '.join(filiais)}")
        
        filial = input("Digite o ID da filial (A, B): ").strip().upper()
        if filial not in filiais:
            print("Filial inválida!")
            return
        
        produto = input("Digite o nome do produto: ").strip()
        if not produto:
            print("Nome do produto não pode estar vazio!")
            return
        
        valor_str = input("Digite o valor da venda (R$): ").strip()
        try:
            valor = float(valor_str)
            if valor <= 0:
                print("Valor deve ser maior que zero!")
                return
        except ValueError:
            print("Valor inválido! Digite um número.")
            return
        
        sucesso = conn.root.AdicionarVenda(filial, produto, valor)
        if sucesso:
            print(f"✓ Venda adicionada com sucesso!")
        else:
            print("✗ Erro ao adicionar venda.")
            
    except Exception as e:
        print(f"Erro ao adicionar venda: {e}")

def consultar_total_vendas(conn):
    try:
        filiais = conn.root.ListarFiliaisDisponiveis()
        print(f"\nFiliais disponíveis: {', '.join(filiais)}")
        
        filial = input("Digite o ID da filial para consultar: ").strip().upper()
        if filial not in filiais:
            print("Filial inválida!")
            return
        
        total = conn.root.ObterTotalVendasDiarias(filial)
        print(f"\nTotal de vendas da Filial {filial}: R$ {total:.2f}")
        
    except Exception as e:
        print(f"Erro ao consultar vendas: {e}")

def listar_produtos_vendidos(conn):
    try:
        filiais = conn.root.ListarFiliaisDisponiveis()
        print(f"\nFiliais disponíveis: {', '.join(filiais)}")
        
        filial = input("Digite o ID da filial: ").strip().upper()
        if filial not in filiais:
            print("Filial inválida!")
            return
        
        quantidade_str = input("Quantos produtos listar: ").strip()
        try:
            quantidade = int(quantidade_str)
            if quantidade <= 0:
                print("Quantidade deve ser maior que zero!")
                return
        except ValueError:
            print("Quantidade inválida! Digite um número.")
            return
        
        produtos = conn.root.ListarProdutosMaisVendidos(filial, quantidade)
        if produtos:
            print(f"\nÚltimos {len(produtos)} produtos vendidos na Filial {filial}:")
            for i, produto in enumerate(produtos, 1):
                print(f"  {i}. {produto}")
        else:
            print(f"Nenhum produto encontrado para a Filial {filial}.")
            
    except Exception as e:
        print(f"Erro ao listar produtos: {e}")

def mostrar_resumo_filial(conn):
    try:
        filiais = conn.root.ListarFiliaisDisponiveis()
        print(f"\nFiliais disponíveis: {', '.join(filiais)}")
        
        filial = input("Digite o ID da filial: ").strip().upper()
        if filial not in filiais:
            print("Filial inválida!")
            return
        
        resumo = conn.root.ObterResumoFilial(filial)
        if resumo:
            print(f"\n" + "="*40)
            print(f"RESUMO DA FILIAL {resumo['filial_id']}")
            print("="*40)
            print(f"Total de Vendas: R$ {resumo['total_vendas']:.2f}")
            print(f"Quantidade de Produtos: {resumo['quantidade_produtos']}")
            
            if resumo['vendas_detalhadas']:
                print("\nVendas Detalhadas:")
                for i, venda in enumerate(resumo['vendas_detalhadas'], 1):
                    print(f"  {i}. {venda['produto']} - R$ {venda['valor']:.2f}")
            else:
                print("\nNenhuma venda registrada ainda.")
            print("="*40)
        else:
            print("Filial não encontrada!")
            
    except Exception as e:
        print(f"Erro ao obter resumo: {e}")

def main():
    try:
        # Verificar se o IP foi passado como argumento
        if len(sys.argv) > 1:
            ip_servidor = sys.argv[1]
        else:
            ip_servidor = input("Digite o IP do servidor (pressione Enter para localhost): ").strip()
            if not ip_servidor:
                ip_servidor = "localhost"
        
        print(f"Conectando ao servidor de vendas em {ip_servidor}...")
        conn = rpyc.connect(ip_servidor, 18861)
        print("✓ Conectado ao servidor de vendas!\n")

        while True:
            mostrar_menu()
            opcao = input("Escolha uma opção: ").strip()
            
            if opcao == "1":
                adicionar_venda(conn)
            elif opcao == "2":
                consultar_total_vendas(conn)
            elif opcao == "3":
                listar_produtos_vendidos(conn)
            elif opcao == "4":
                mostrar_resumo_filial(conn)
            elif opcao == "5":
                filiais = conn.root.ListarFiliaisDisponiveis()
                print(f"\nFiliais disponíveis: {', '.join(filiais)}")
            elif opcao == "0":
                print("\nEncerrando cliente...")
                break
            else:
                print("\nOpção inválida! Tente novamente.")
            
            input("\nPressione Enter para continuar...")
        
        conn.close()
        print("Conexão encerrada. Até logo!")

    except ConnectionRefusedError:
        print("✗ Erro: A conexão foi recusada. O servidor está em execução?")
    except KeyboardInterrupt:
        print("\n\nEncerrando cliente...")
    except Exception as e:
        print(f"Ocorreu um erro inesperado: {e}")

if __name__ == "__main__":
    main()