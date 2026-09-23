#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// funcao para a criacao de grafo, determinando as qtds
// maximas de vertices e arestas
Grafo GGcriaGrafo(int v, int a) {
    Grafo p;

    p = malloc(sizeof(struct grafo)); // reservando espaco para o proprio grafo

    if (p == NULL) {
        return NULL;
    }

    // ja que a funco esta criando o grafo desde do comeco,
    // entao os vertices e arestas precisam iniciar como 0
    p->V = 0;
    p->A = 0;

    p->v = v; // guardar os maximos
    p->a = a;

    p->vertices = malloc(v * sizeof(int)); // reserva um espaco de memoria para
    p->arestas = malloc(a * sizeof(int));  // para cada v e a

    if (p->vertices == NULL || p ->arestas == NULL) {
        return NULL;
    }

    return p;
}

// funcao pra deletar o grafo
Grafo GGdestroiGrafo(Grafo p) {
    // apagando os vertices e as arestas primeiro,
    // ja que se nao apagar, pode acontecer vazamento de memoria
    free(p->vertices);
    free(p->arestas);
    free(p);

    p = NULL; // isso serviu pra deixar explicito que o ponteiro nao esta
              // apontando para nenhuma regiao valida na memoria

    return p;
}

// funcao para criar vertice
int GVcriaVertice(Grafo p) {
    if (p->V < p->v) {
        p->V++; // cada vertice criado, aumenta mais um para o atual
        p->vertices[p->V - 1] = p->V; // vai alocando na lista de vertices
    } else {
        return 0;
    }
    return p->V;
}

// funcao para criar aresta (nao foi finalizada ainda)
int GAcriaAresta(Grafo p, ) {
    if (p->A < p->a) {
        p->A++
        p->arestas[p->A - 1] = p->A;
    } else {
        return 0;
    }
}
