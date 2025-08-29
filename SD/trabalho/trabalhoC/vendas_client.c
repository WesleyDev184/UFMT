#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"

void obter_total_filial(CLIENT *clnt, int filial_id)
{
    VendaDiariaArgs args;
    args.filialId = filial_id;
    double *resultado;

    resultado = obtertotalvendasdiarias_1(&args, clnt);
    if (resultado == NULL)
    {
        fprintf(stderr, "Problemas ao chamar a função remota 'ObterTotalVendasDiarias'\n");
        return;
    }
    printf("Vendas totais da Filial %d: R$ %.2f\n", filial_id, *resultado);
}

void obter_total_todas_filiais(CLIENT *clnt)
{
    printf("\n=== Total de Vendas de Todas as Filiais ===\n");
    double total_geral = 0.0;

    for (int i = 1; i <= 5; i++)
    {
        VendaDiariaArgs args;
        args.filialId = i;
        double *resultado;

        resultado = obtertotalvendasdiarias_1(&args, clnt);
        if (resultado != NULL)
        {
            printf("Filial %d: R$ %.2f\n", i, *resultado);
            total_geral += *resultado;
        }
        else
        {
            printf("Filial %d: Não disponível\n", i);
        }
    }
    printf("TOTAL GERAL: R$ %.2f\n", total_geral);
    printf("==========================================\n");
}

void listar_produtos_filial(CLIENT *clnt, int filial_id, int quantidade)
{
    ProdutosMaisVendidosArgs args;
    args.filialId = filial_id;
    args.quantidade = quantidade;
    ListaProdutos *resultado;

    resultado = listarprodutosmaisvendidos_1(&args, clnt);
    if (resultado == NULL)
    {
        fprintf(stderr, "Problemas ao chamar a função remota 'ListarProdutosMaisVendidos'\n");
        return;
    }

    printf("Produtos mais vendidos na Filial %d (top %d):\n", filial_id, quantidade);
    struct Produto *current = *resultado;
    int posicao = 1;
    while (current != NULL)
    {
        printf("  %d. %s\n", posicao, current->nome);
        current = current->proximo;
        posicao++;
    }

    xdr_free((xdrproc_t)xdr_ListaProdutos, (char *)resultado);
}

void listar_top_produtos_todas_filiais(CLIENT *clnt, int quantidade)
{
    printf("\n=== Top %d Produtos de Todas as Filiais ===\n", quantidade);

    for (int i = 1; i <= 5; i++)
    { 
        printf("\nFilial %d:\n", i);
        ProdutosMaisVendidosArgs args;
        args.filialId = i;
        args.quantidade = quantidade;
        ListaProdutos *resultado;

        resultado = listarprodutosmaisvendidos_1(&args, clnt);
        if (resultado != NULL && *resultado != NULL)
        {
            struct Produto *current = *resultado;
            int posicao = 1;
            while (current != NULL)
            {
                printf("  %d. %s\n", posicao, current->nome);
                current = current->proximo;
                posicao++;
            }
            xdr_free((xdrproc_t)xdr_ListaProdutos, (char *)resultado);
        }
        else
        {
            printf("  Nenhum produto disponível\n");
        }
    }
    printf("==========================================\n");
}

void mostrar_menu()
{
    printf("\n--- Menu de Monitoramento ---\n");
    printf("1) Ver total de vendas de uma filial\n");
    printf("2) Ver total de vendas de todas as filiais (ampliado)\n");
    printf("3) Listar produtos mais vendidos de uma filial\n");
    printf("4) Listar top N produtos para todas as filiais (ampliado)\n");
    printf("5) Sair\n");
    printf("Escolha uma opção: ");
}

int main(int argc, char *argv[])
{
    CLIENT *clnt;
    char *host;
    int opcao, filial_id, quantidade;

    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <hostname_servidor>\n", argv[0]);
        exit(1);
    }
    host = argv[1];

    clnt = clnt_create(host, VENDAS_PROG, VENDAS_VERSION, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

    printf("Conectado ao servidor de vendas em %s\n", host);

    while (1)
    {
        mostrar_menu();

        if (scanf("%d", &opcao) != 1)
        {
            printf("Opção inválida! Digite um número.\n");
            while (getchar() != '\n')
                ; 
            continue;
        }

        switch (opcao)
        {
        case 1:
            printf("Digite o ID da filial (1-5): ");
            if (scanf("%d", &filial_id) == 1 && filial_id >= 1 && filial_id <= 5)
            {
                obter_total_filial(clnt, filial_id);
            }
            else
            {
                printf("ID de filial inválido! Use valores de 1 a 5.\n");
                while (getchar() != '\n')
                    ;
            }
            break;

        case 2:
            obter_total_todas_filiais(clnt);
            break;

        case 3:
            printf("Digite o ID da filial (1-5): ");
            if (scanf("%d", &filial_id) == 1 && filial_id >= 1 && filial_id <= 5)
            {
                printf("Digite a quantidade de produtos (1-10): ");
                if (scanf("%d", &quantidade) == 1 && quantidade >= 1 && quantidade <= 10)
                {
                    listar_produtos_filial(clnt, filial_id, quantidade);
                }
                else
                {
                    printf("Quantidade inválida! Use valores de 1 a 10.\n");
                    while (getchar() != '\n')
                        ; 
                }
            }
            else
            {
                printf("ID de filial inválido! Use valores de 1 a 5.\n");
                while (getchar() != '\n')
                    ; 
            }
            break;

        case 4:
            printf("Digite a quantidade de produtos para listar (1-10): ");
            if (scanf("%d", &quantidade) == 1 && quantidade >= 1 && quantidade <= 10)
            {
                listar_top_produtos_todas_filiais(clnt, quantidade);
            }
            else
            {
                printf("Quantidade inválida! Use valores de 1 a 10.\n");
                while (getchar() != '\n')
                    ; 
            }
            break;

        case 5:
            printf("Encerrando o cliente...\n");
            clnt_destroy(clnt);
            return 0;

        default:
            printf("Opção inválida! Escolha uma opção de 1 a 5.\n");
            break;
        }

        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n')
            ;      
        getchar(); 
    }

    clnt_destroy(clnt);
    return 0;
}