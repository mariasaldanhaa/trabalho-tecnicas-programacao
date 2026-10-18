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
    p->arestas = malloc(p->a * 2 * sizeof(int)); // esta sendo reservado espaco duas vezes, porque sao dois vertices

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
        p->vertices[p->V - 1] = p->V; // armazena o identificador do vertice no vetor
    } else {
        return 0;
    }
    return p->V;
}

// funcao para criar aresta
int GAcriaAresta(Grafo p, int v1, int v2) {
    if (p->A < p->a) {
        p->A++; // identificador para cada aresta
        p->arestas[(p->A - 1) * 2] = v1; // Cada aresta ocupa duas posicoes no vetor: v1 e v2
        p->arestas[((p->A - 1) * 2) + 1] = v2;

        return p->A;
    } else {
        return 0;
    }
}

// funcao de id do vertice existente
int GBexisteIdVertice(Grafo p, int v) {
    for (int i = 0; i < p->V; i++) {
        if (v == p->vertices[i]) {
            return 1;
        }
    }
    return 0;
}

// funcao de id da aresta existente
int GBexisteIdAresta(Grafo p, int a) {
    for (int i = 0; i < p->A; i++) {
        if (a == p->arestas[i]) {
            return 1;
        }
    }
    return 0;
}

// funcao de se existe aresta nao dirigida
int GBexisteAresta(Grafo p, int v1, int v2) {
    for (int i = 0; i < p->A; i++) {
        // calculos que foram usados para identificar cada aresta
        int partida = i * 2;
        int chegada = i * 2 + 1;

        if ((v1 == p->arestas[partida] && v2 == p->arestas[chegada])
            || (v2 == p->arestas[partida] && v1 == p->arestas[chegada])
            ) {
            return 1;
        }
    }
    return 0;
}

// funcao de se existe aresta dirigida
int GBexisteArestaDir(Grafo p, int v1, int v2) {
    for (int i = 0; i < p->A; i++) {
        // calculos que foram usados para identificar cada aresta
        int partida = i * 2;
        int chegada = i * 2 + 1;

        if (v1 == p->arestas[partida] && v2 == p->arestas[chegada]) {
            return 1;
        }
    }
    return 0;
}

// funcao de pegar o identificador de uma aresta dirigida
int GApegaArestaDir(Grafo p, int v1, int v2) {
    for (int i = 0; i < p->A; i++) {
        int partida = i * 2;
        int chegada = i * 2 + 1;

        // se existir a aresta
        if (v1 == p->arestas[partida] && v2 == p->arestas[chegada]) {
            int a = i + 1;
            return a;
        }
    }
    return 0;
}

// funcao de pegar identifcador de uma aresta nao dirigida
int GApegaAresta(Grafo p, int v1, int v2) {
    for (int i = 0; i < p->A; i++) {
        // calculos que foram usados para identificar cada aresta
        int partida = i * 2;
        int chegada = i * 2 + 1;

        if ((v1 == p->arestas[partida] && v2 == p->arestas[chegada])
            || (v2 == p->arestas[partida] && v1 == p->arestas[chegada])
            ) {
            int a = i + 1;
            return a;
        }
    }
    return 0;
}

// funcao para pegar o primeiro vertice do grafo
int GVprimeiroVertice(Grafo p) {
    if (p == NULL) {
        return 0;
    }

    // como foi feito sequencialmente os identificadores,
    // entao o primeiro id sempre sera 1
    if (p->V > 0) {
        int v = p->vertices[0];
        return v;
    }
    return 0;
}

// funcao para pegar o proximo vertice do grafo
int GVproximoVertice(Grafo p, int v1) {
    // -- COLOCAR NO RELATORIO --
    // como os identificadores dos vertices sao sequenciais,
    // nao e necessario percorrer o vetor com um for.
    // a variavel maximo armazena a quantidade de vertices criados.
    // se nao existir um identificador maior que v1, retorna 0.
    //
    // OBS: de acordo com o pos-requisito, devemos retornar o menor
    // identificador existente que seja maior que v1.
    // como os identificadores sao sequenciais, basta calcular v1 + 1,
    // desde que esse identificador exista no grafo.
    //
    // como nao ha funcao para remover vertices nesta implementacao,
    // os identificadores permanecem sequenciais.

    // funcao de protecao antes de acessar a qtd de vertices,
    // apesar que nao esta no requisito
    if (p == NULL) {
        return 0;
    }

    int maximo = p->V;
    int v2;

    // condicao para garantir quando ha vertices e v1 eh menor
    // que 1, a funcao retorna o primeiro id valido
    if (maximo > 0 && v1 < 1) {
        return 1;
    }

    if (maximo > 0) {
        if (v1 < maximo) {
            v2 = v1 + 1;
            return v2;
        }
    }
    return 0;
}

// funcao para pegar a primeira aresta do grafo
int GAprimeiraAresta(Grafo p) {
    // so para seguranca (colocar no relatorio)
    if (p == NULL) {
        return 0;
    }

    // como os id's das arestas sao sequenciais,
    // entao o primeiro sempre sera 1
    if (p->A > 0) {
        return 1;
    }
    return 0;
}

// funcao para pegar a proxima aresta do grafo
int GAproximaAresta(Grafo p, int a1) {
    // protecao adicional
    if (p == NULL) {
        return 0;
    }

    int maximo = p->A;
    int a2;

    if (maximo > 0 && a1 < 1) {
        return 1;
    }

    // mesma logica dos vertices
    if (maximo > 0) {
        if (a1 < maximo) {
            a2 = a1 + 1;
            return a2;
        }
    }

    return 0;
}

// funcao para pegar o numero de vertices no grafo
int GInumeroVertices(Grafo p) {
    // seguranca adicional
    if (p == NULL) {
        return 0;
    }

    int nv = p->V;

    return nv;
}
