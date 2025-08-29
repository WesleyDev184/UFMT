#include "vendas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double vendas_filial_1 = 1500.50;
static char *produtos_filial_1[] = {"Produto A", "Produto B", "Produto C"};

static double vendas_filial_2 = 3250.75;
static char *produtos_filial_2[] = {"Produto D", "Produto E", "Produto F", "Produto G"};


double *
obtertotalvendasdiarias_1_svc(VendaDiariaArgs *argp, struct svc_req *rqstp)
{
	static double  result;

	printf("Recebido pedido de total de vendas para filial: %d\n", argp->filialId);

	if (argp->filialId == 1) {
		result = vendas_filial_1;
	} else if (argp->filialId == 2) {
		result = vendas_filial_2;
	} else {
		result = 0.0;
	}

	return &result;
}

ListaProdutos *
listarprodutosmaisvendidos_1_svc(ProdutosMaisVendidosArgs *argp, struct svc_req *rqstp)
{
	static ListaProdutos  result = NULL;
    xdr_free((xdrproc_t)xdr_ListaProdutos, (char *)&result);
    
    printf("Recebido pedido de produtos mais vendidos para filial: %d (top %d)\n", argp->filialId, argp->quantidade);

    char **produtos_source = NULL;
    int num_produtos = 0;

    if (argp->filialId == 1) {
        produtos_source = produtos_filial_1;
        num_produtos = sizeof(produtos_filial_1) / sizeof(char*);
    } else if (argp->filialId == 2) {
        produtos_source = produtos_filial_2;
        num_produtos = sizeof(produtos_filial_2) / sizeof(char*);
    } else {
        return &result; 
    }

    int count = (argp->quantidade < num_produtos) ? argp->quantidade : num_produtos;
    
    ListaProdutos *current = &result;
    for (int i = 0; i < count; i++) {
        *current = (struct Produto *)malloc(sizeof(struct Produto));
        (*current)->nome = strdup(produtos_source[i]);
        (*current)->proximo = NULL;
        current = &((*current)->proximo);
    }

	return &result;
}