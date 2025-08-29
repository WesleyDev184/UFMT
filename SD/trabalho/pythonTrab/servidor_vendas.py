import rpyc
from rpyc.utils.server import ThreadedServer
from threading import Lock

class ServicoVendas(rpyc.Service):
    def __init__(self):
        self._dados_filiais = {
            "A": {
                "total_vendas": 0.0,
                "produtos_vendidos": [],
                "vendas_detalhadas": []
            },
            "B": {
                "total_vendas": 0.0,
                "produtos_vendidos": [],
                "vendas_detalhadas": []
            }
        }
        self._lock = Lock()

    def on_connect(self, conn):
        print("Conexão estabelecida.")

    def on_disconnect(self, conn):
        print("Conexão finalizada.")

    def exposed_ObterTotalVendasDiarias(self, filialId):
        """ Retorna o valor total das vendas do dia para uma filial específica. """
        print(f"Recebida solicitação de total de vendas para a filial: {filialId}")
        with self._lock:
            filial = self._dados_filiais.get(filialId)
            if filial:
                return filial["total_vendas"]
            return 0.0

    def exposed_ListarProdutosMaisVendidos(self, filialId, quantidade):
        """ Retorna uma lista dos N produtos mais vendidos do dia para uma filial. """
        print(f"Recebida solicitação dos {quantidade} produtos mais vendidos para a filial: {filialId}")
        with self._lock:
            filial = self._dados_filiais.get(filialId)
            if filial:
                return filial["produtos_vendidos"][-quantidade:] if len(filial["produtos_vendidos"]) >= quantidade else filial["produtos_vendidos"]
            return []

    def exposed_AdicionarVenda(self, filialId, produto, valor):
        """ Adiciona uma nova venda para uma filial. """
        print(f"Adicionando venda: Filial {filialId}, Produto: {produto}, Valor: R$ {valor:.2f}")
        with self._lock:
            filial = self._dados_filiais.get(filialId)
            if filial:
                filial["total_vendas"] += valor
                filial["produtos_vendidos"].append(produto)
                filial["vendas_detalhadas"].append({"produto": produto, "valor": valor})
                print(f"Venda adicionada com sucesso! Total atual da filial {filialId}: R$ {filial['total_vendas']:.2f}")
                return True
            print(f"Filial {filialId} não encontrada!")
            return False

    def exposed_ListarFiliaisDisponiveis(self):
        """ Retorna a lista de filiais disponíveis. """
        return list(self._dados_filiais.keys())

    def exposed_ObterResumoFilial(self, filialId):
        """ Retorna um resumo completo da filial. """
        with self._lock:
            filial = self._dados_filiais.get(filialId)
            if filial:
                return {
                    "filial_id": filialId,
                    "total_vendas": filial["total_vendas"],
                    "quantidade_produtos": len(filial["produtos_vendidos"]),
                    "produtos_vendidos": filial["produtos_vendidos"],
                    "vendas_detalhadas": filial["vendas_detalhadas"]
                }
            return None

if __name__ == "__main__":
    porta = 18861
    print(f"Iniciando servidor RPyC na porta {porta}...")
    servidor = ThreadedServer(ServicoVendas, port=porta)
    servidor.start()