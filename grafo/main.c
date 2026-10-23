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
        printf("\n5 - Verificar se um vertice existe");
        printf("\n6 - Verificar se uma aresta existe");
        printf("\n7 - Verificar se existe aresta nao dirigida");
        printf("\n8 - Verificar se existe aresta dirigida");
        printf("\n9 - Pegar id da aresta dirigida");
        printf("\n10 - Pegar id da aresta nao dirigida");
        printf("\n11 - Pegar id do primeiro vertice");
        printf("\n12 - Pegar id do proximo vertice");
        printf("\n13 - Pegar id da primeira aresta");
        printf("\n14 - Pegar id da proxima aresta");
        printf("\n15 - Pegar o numero de vertices no grafo");
        printf("\n16 - Pegar o numero maximo de vertices");
        printf("\n17 - Pegar o numero de arestas");
        printf("\n18 - Pegar o numero maximo de arestas");
        printf("\n19 - Carregar grafo de arquivo");
        printf("\n20 - Salvar grafo em arquivo");
        printf("\n21 - Pegar grau de um vertice");
        printf("\n22 - Pegar primeira aresta incidente");
        printf("\n23 - Pegar proxima aresta incidente");
        printf("\n24 - Pegar primeira aresta de entrada");
        printf("\n25 - Pegar proxima aresta de entrada");
        printf("\n26 - Pegar primeira aresta de saida");
        printf("\n27 - Pegar proxima aresta de saida");
        printf("\n28 - Verificar se aresta e laco");
        printf("\n29 - Pegar alfa, omega e vizinho");
        printf("\n30 - Sair");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        while (opcao < 1 || opcao > 30) {
            printf("\n---- OPCOES ----");
            printf("\n1 - Criar Grafo");
            printf("\n2 - Deletar Grafo");
            printf("\n3 - Criar Vertice");
            printf("\n4 - Criar Aresta");
            printf("\n5 - Verificar se um vertice existe");
            printf("\n6 - Verificar se uma aresta existe");
            printf("\n7 - Verificar se existe aresta nao dirigida");
            printf("\n8 - Verificar se existe aresta dirigida");
            printf("\n9 - Pegar id da aresta dirigida");
            printf("\n10 - Pegar id da aresta nao dirigida");
            printf("\n11 - Pegar id do primeiro vertice");
            printf("\n12 - Pegar id do proximo vertice");
            printf("\n14 - Pegar id da proxima aresta");
            printf("\n15 - Pegar o numero de vertices no grafo");
            printf("\n16 - Pegar o numero maximo de vertices");
            printf("\n17 - Pegar o numero de arestas");
            printf("\n18 - Pegar o numero maximo de arestas");
            printf("\n19 - Carregar grafo de arquivo");
            printf("\n20 - Salvar grafo em arquivo");
            printf("\n21 - Pegar grau de um vertice");
            printf("\n22 - Pegar primeira aresta incidente");
            printf("\n23 - Pegar proxima aresta incidente");
            printf("\n24 - Pegar primeira aresta de entrada");
            printf("\n25 - Pegar proxima aresta de entrada");
            printf("\n26 - Pegar primeira aresta de saida");
            printf("\n27 - Pegar proxima aresta de saida");
            printf("\n28 - Verificar se aresta e laco");
            printf("\n29 - Pegar alfa, omega e vizinho");
            printf("\n30 - Sair");

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
                int idVertice, existeVertice;
                printf("\nInforme o ID do vertice que queira consultar: ");
                scanf("%d", &idVertice);

                existeVertice = GBexisteIdVertice(p, idVertice);

                if (existeVertice == 1) {
                    printf("\nO vertice existe!");
                } else {
                    printf("\nO vertice nao existe!");
                }

                break;
            case 6:
                int idAresta, existeAresta;
                printf("\nInforme o ID da aresta que queira consultar: ");
                scanf("%d", &idAresta);

                existeAresta = GBexisteIdAresta(p, idAresta);

                if (existeAresta == 1) {
                    printf("\nA aresta existe!");
                } else {
                    printf("\nA aresta nao existe!");
                }

                break;
            case 7:
                printf("\n -- ARESTA NAO DIRIGIDA --");
                int partida, chegada, existeArestaNDir;

                printf("\nInforme o vertice de partida: ");
                scanf("%d", &partida);

                printf("\nInforme o vertice de chegada: ");
                scanf("%d", &chegada);

                existeArestaNDir = GBexisteAresta(p, partida, chegada);

                if (existeArestaNDir == 1) {
                    printf("\nA aresta nao dirigida existe!");
                } else {
                    printf("\nA aresta nao dirigida nao existe !");
                }

                break;
            case 8:
                printf("\n -- ARESTA DIRIGIDA --");
                int partidaDir, chegadaDir, existeArestaDir;

                printf("\nInforme o vertice de partida: ");
                scanf("%d", &partidaDir);

                printf("\nInforme o vertice de chegada: ");
                scanf("%d", &chegadaDir);

                existeArestaDir = GBexisteArestaDir(p, partidaDir, chegadaDir);

                if (existeArestaDir == 1) {
                    printf("\nA aresta dirigida existe!");
                } else {
                    printf("\nA aresta dirigida nao existe !");
                }

                break;
            case 9:
                printf("\n -- ID DA ARESTA DIRIGIDA --");
                int partidaIdDir, chegadaIdDir, idDir;

                printf("\nInforme o vertice de partida: ");
                scanf("%d", &partidaIdDir);

                printf("\nInforme o vertice de chegada: ");
                scanf("%d", &chegadaIdDir);

                idDir = GApegaArestaDir(p, partidaIdDir, chegadaIdDir);

                if (idDir != 0) {
                    printf("\nID da aresta dirigida: %d", idDir);
                } else {
                    printf("\nA aresta dirigida nao existe !");
                }
                break;
            case 10:
                printf("\n -- ID DA ARESTA NAO DIRIGIDA --");
                int partidaIdNDir, chegadaIdNDir, idNDir;

                printf("\nInforme o vertice de partida: ");
                scanf("%d", &partidaIdNDir);

                printf("\nInforme o vertice de chegada: ");
                scanf("%d", &chegadaIdNDir);

                idNDir = GApegaAresta(p, partidaIdNDir, chegadaIdNDir);

                if (idNDir != 0) {
                    printf("\nID da aresta nao dirigida: %d", idNDir);
                } else {
                    printf("\nA aresta nao dirigida nao existe!");
                }
                break;
            case 11:
                int idPrimeiro;

                printf("\n -- ID DO PRIMEIRO VERTICE --");

                idPrimeiro = GVprimeiroVertice(p);

                if (idPrimeiro != 0) {
                    printf("\nID do primeiro vertice: %d", idPrimeiro);
                } else {
                    printf("\nNao existe vertice criado!");
                }
                break;
            case 12:
                int idProximo;

                printf("\n -- ID DO PROXIMO VERTICE --");
                printf("\nInforme o id do vertice: ");
                scanf("%d", &v1);

                idProximo = GVproximoVertice(p, v1);

                if (idProximo != 0) {
                    printf("\nID do proximo vertice: %d", idProximo);
                } else {
                    printf("\nNao existe vertice criado ou nao existe proximo!");
                }

                break;
            case 13:
                int idAPrimeira;

                printf("\n -- ID DA PRIMEIRA ARESTA --");

                idAPrimeira = GAprimeiraAresta(p);

                if (idAPrimeira != 0) {
                    printf("\nID da primeira aresta: %d", idAPrimeira);
                } else {
                    printf("\nNao existe aresta criada!");
                }
                break;
            case 14:
                int idAProxima, a1;

                printf("\n -- ID DA PROXIMA ARESTA --");
                printf("\nInforme o id da aresta: ");
                scanf("%d", &a1);

                idAProxima = GAproximaAresta(p, a1);

                if (idAProxima != 0) {
                    printf("\nID da proxima aresta: %d", idAProxima);
                } else {
                    printf("\nNao existe aresta criado ou nao existe proximo!");
                }
                break;
            case 15:
                int nv = GInumeroVertices(p);

                if (p != NULL) {
                    printf("\nQtd de vertices: %d", nv);
                } else {
                    printf("Nao foi criado nenhum grafo");
                }
                break;

            case 16:
                if (p != NULL)
                    printf("\nMaximo de vertices: %d", GInumeroVerticesMax(p));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 17:
                if (p != NULL)
                    printf("\nNumero de arestas: %d", GInumeroArestas(p));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 18:
                if (p != NULL)
                    printf("\nMaximo de arestas: %d", GInumeroArestasMax(p));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 19: {
                char arquivo[256];
                printf("\nNome do arquivo para carregar: ");
                scanf("%255s", arquivo);
                Grafo novo = GGcarregaGrafo(arquivo);
                if (novo != NULL) {
                    if (p != NULL)
                        p = GGdestroiGrafo(p);
                    p = novo;
                    printf("\nGrafo carregado!");
                } else {
                    printf("\nNao foi possivel carregar o grafo.");
                }
                break;
            }
            case 20: {
                char arquivo[256];
                printf("\nNome do arquivo para salvar: ");
                scanf("%255s", arquivo);
                if (p != NULL && GBsalvaGrafo(p, arquivo))
                    printf("\nGrafo salvo!");
                else
                    printf("\nNao foi possivel salvar o grafo.");
                break;
            }
            case 21:
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                if (p != NULL)
                    printf("\nGrau do vertice: %d", GIpegaGrau(p, v1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 22:
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                if (p != NULL)
                    printf("\nPrimeira aresta incidente: %d", GAprimaAresta(p, v1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 23: {
                int a1;
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                printf("Informe o ID da aresta anterior: ");
                scanf("%d", &a1);
                if (p != NULL)
                    printf("\nProxima aresta incidente: %d", GAproxAresta(p, v1, a1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            }
            case 24:
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                if (p != NULL)
                    printf("\nPrimeira aresta de entrada: %d", GAprimaEntrada(p, v1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 25: {
                int a1;
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                printf("Informe o ID da aresta anterior: ");
                scanf("%d", &a1);
                if (p != NULL)
                    printf("\nProxima aresta de entrada: %d", GAproxEntrada(p, v1, a1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            }
            case 26:
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                if (p != NULL)
                    printf("\nPrimeira aresta de saida: %d", GAprimaSaida(p, v1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            case 27: {
                int a1;
                printf("\nInforme o ID do vertice: ");
                scanf("%d", &v1);
                printf("Informe o ID da aresta anterior: ");
                scanf("%d", &a1);
                if (p != NULL)
                    printf("\nProxima aresta de saida: %d", GAproxSaida(p, v1, a1));
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            }
            case 28: {
                int a1;
                printf("\nInforme o ID da aresta: ");
                scanf("%d", &a1);
                if (p != NULL)
                    printf("\nAresta e laco? %s", GBarestaLaco(p, a1) ? "Sim" : "Nao");
                else
                    printf("\nNao foi criado nenhum grafo");
                break;
            }
            case 29: {
                int a1;
                printf("\nInforme o ID da aresta: ");
                scanf("%d", &a1);
                if (p != NULL && GBexisteIdAresta(p, a1)) {
                    printf("\nAlfa: %d", GAlfa(p, a1));
                    printf("\nOmega: %d", GOmega(p, a1));
                    printf("\nInforme o outro vertice para consultar vizinho: ");
                    scanf("%d", &v1);
                    printf("\nVizinho: %d", GVvizinho(p, a1, v1));
                } else {
                    printf("\nGrafo nao criado ou aresta inexistente");
                }
                break;
            }
            case 30:
                continuar = 0;
                break;
        }
    }
}
