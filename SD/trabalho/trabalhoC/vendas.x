struct VendaDiariaArgs {
    int filialId;
};

struct ProdutosMaisVendidosArgs {
    int filialId;
    int quantidade;
};

/* Usando uma lista encadeada para retornar a lista de produtos */
struct Produto {
    string nome<>;
    struct Produto *proximo;
};

typedef struct Produto *ListaProdutos;

program VENDAS_PROG {
    version VENDAS_VERSION {
        double OBTERTOTALVENDASDIARIAS(VendaDiariaArgs) = 1;
        ListaProdutos LISTARPRODUTOSMAISVENDIDOS(ProdutosMaisVendidosArgs) = 2;
    } = 1;
} = 0x20000001;