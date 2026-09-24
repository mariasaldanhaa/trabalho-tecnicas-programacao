#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

// arquivo para testes
int main() {
    Grafo p = NULL;
    int v, a, opcao, continuar = true, v1, v2, id;

    while (continuar) {
        printf("\n---- OPCOES ----");
        printf("\n1 - Criar Grafo");
        printf("\n2 - Deletar Grafo");
        printf("\n3 - Criar Vertice");
        printf("\n4 - Criar Aresta");
        printf("\n5 - Sair");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        while (opcao < 0) {
            printf("\n---- OPCOES ----");
            printf("\n1 - Criar Grafo");
            printf("\n2 - Deletar Grafo");
            printf("\n3 - Criar Vertice");
            printf("\n4 - Criar Aresta");
            printf("\n5 - Sair");

            printf("\nOpcao: ");
            scanf("%d", &opcao);
        }

        switch (opcao) {
            case 1:
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

                printf("Maximo de vertices: %d\n", p->v);
                printf("Maximo de arestas: %d\n", p->a);
                printf("Quantidade de vertices: %d\n", p->V);
                printf("Quantidade de arestas: %d\n", p->A);
                break;
            case 2:
                int resp;

                printf("\nTem certeza? (1 - SIM / 0 - NAO) ");
                scanf("%d", &resp);

                while (resp != 1 && resp != 0) {
                    printf("\nTem certeza? (1 - SIM / 0 - NAO) ");
                    scanf("%d", &resp);
                }

                if (resp == 1) {
                    if(p != NULL) {
                        p = GGdestroiGrafo(p);
                        if (p == NULL) {
                            printf("\nGRAFO APAGADO");
                        }
                    }
                }
                break;
            case 3:
                id = GVcriaVertice(p);
                if (id != 0) {
                    printf("\nVertice criado.");
                    printf("\nQtd vertices atuais: %d", p->V);
                }
                break;
            case 4:
                printf("Informe o vertice inicial: ");
                scanf("%d", &v1);

                printf("Informe o vertice final para a ligacao %d: ", v1);
                scanf("%d", &v2);

                id = GAcriaAresta(p, v1, v2);
                if (id != 0) printf("Aresta (%d, %d) criado.", v1, v2);

                printf("\n-- Lista de vertices --");
                for (int i = 0; i < p->A; i++) {
                    int va = p->arestas[i * 2];
                    int vb = p->arestas[i * 2 + 1];

                    printf("\n(%d, %d)", va, vb);
                }
                break;
            case 5:
                continuar = 0;
                break;
        }
    }
}
