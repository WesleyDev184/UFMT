#include <stdio.h>

int main() {
    int n, i;
    scanf("%d", &n);
    int altura_atual, altura_anterior, tipo_anterior, cndtn = 1;
    scanf("%d", &altura_anterior); // lê a primeira medida
    tipo_anterior = 0; // começa sem tipo definido
    for(i=1; i<n; i++) {
        scanf("%d", &altura_atual);
        if((altura_atual > altura_anterior && tipo_anterior == -1) ||
           (altura_atual < altura_anterior && tipo_anterior == 1)) {
            cndtn = 0; // não satisfaz a condição
            break;
        }
        // define o tipo de acordo com a altura atual e anterior
        tipo_anterior = (altura_atual > altura_anterior) ? 1 : -1;
        altura_anterior = altura_atual;
    }
    printf("%d\n", cndtn);
    return 0;
}
