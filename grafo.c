#include <stdio.h>
#include "grafo.h"

// funcao para testes
int main() {
    Grafo p;
    int v, a;

    printf("Maximo de vertices previstos: ");
    scanf("%d", &v);

    printf("\nMaximo de arestas previstos: ");
    scanf("%d", &a);

    while (v <= 0 || a <= 0) {
        printf("\n -- OPS! INFORME NOVAMENTE --");
        printf("\nMaximo de vertices previstos: ");
        scanf("%d", &v);

        printf("\nMaximo de arestas previstos: ");
        scanf("%d", &a);
    }

    p = GGcriaGrafo(v, a);
    if (p == NULL) {
        printf("\nErro ao criar o grafo.");
        return 1;
    }
}

// funcao para a criacao de grafo, determinando as qtds
// maximas de vertices e arestas
Grafo GGcriaGrafo(int v, int a) {
    Grafo p;

    // ja que a funco esta criando o grafo desde do comeco,
    // entao os vertices e arestas precisam iniciar como 0
    p->v = 0;
    p->a = 0;

}
