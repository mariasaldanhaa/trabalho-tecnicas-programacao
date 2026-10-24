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

    // -- aprendizado (so pra registrar pra quando for estudar futuramente)--
    // como os id's sao sequenciais, nao foi
    // preciso de for, mas antes eu coloquei da seguinte maneira:
    // int GBexisteIdAresta(Grafo p, int a) {
    //      for (int i = 0; i < p->A; i++) {
    //          if (a == p->arestas[i]) {
    //              return 1;
    //          }
    //      }
    //      return 0;
    // }
    // So que na hora de fazer o teste e ao criar vertices e arestas,
    // eu percebi que afetou algumas funcoes como GBarestaLaco, GAlfa
    // GOmega e GVvizinho por conta dessa funcao. Motivo? se eu criasse um
    // laco e fizesse a verificacao com GBarestaLaco, deveria retornar 'Sim',
    // porem retornou 'Nao', porque percorria o vetor 'arestas' e comparava o id
    // informado diretamente com os valores dos vertices armazenados, mas cada
    // aresta ocupa duas posicoes e seu id eh determinado pela posicao par.
    // Entao, decidi fazer a busca no vetor por uma verificacao do intervalo do id
    // RESUMINDO: erro basico de logica

    if (p == NULL) {
        return 0;
    }

    if (a >= 1 && a <= p->A) {
        return 1;
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




// numero maximo de vertices previsto
int GInumeroVerticesMax(Grafo p) {
    if (p == NULL) return 0;
    return p->v;
}

// numero atual de arestas
int GInumeroArestas(Grafo p) {
    if (p == NULL) return 0;
    return p->A;
}

// numero maximo de arestas previsto
int GInumeroArestasMax(Grafo p) {
    if (p == NULL) return 0;
    return p->a;
}

// carrega grafo de arquivo: primeira linha V A; depois, uma aresta por linha
Grafo GGcarregaGrafo(const char *f) {
    FILE *arq;
    int nv, na, v1, v2;
    Grafo p;

    if (f == NULL || (arq = fopen(f, "r")) == NULL) return NULL;
    if (fscanf(arq, "%d %d", &nv, &na) != 2 || nv <= 0 || na < 0) {
        fclose(arq);
        return NULL;
    }

    p = GGcriaGrafo(nv, na > 0 ? na : 1);
    if (p == NULL) {
        fclose(arq);
        return NULL;
    }

    for (int i = 0; i < nv; i++) {
        if (GVcriaVertice(p) == 0) {
            GGdestroiGrafo(p);
            fclose(arq);
            return NULL;
        }
    }

    for (int i = 0; i < na; i++) {
        if (fscanf(arq, "%d %d", &v1, &v2) != 2 ||
            GAcriaAresta(p, v1, v2) == 0) {
            GGdestroiGrafo(p);
            fclose(arq);
            return NULL;
        }
    }

    fclose(arq);
    return p;
}

// salva grafo no formato definido no enunciado
int GBsalvaGrafo(Grafo p, const char *f) {
    FILE *arq;
    if (p == NULL || f == NULL || (arq = fopen(f, "w")) == NULL) return 0;

    fprintf(arq, "%d %d\n", p->V, p->A);
    for (int i = 0; i < p->A; i++) {
        fprintf(arq, "%d %d\n", p->arestas[2 * i], p->arestas[2 * i + 1]);
    }

    if (fclose(arq) != 0) return 0;
    return 1;
}

// grau do vertice (um laco conta duas vezes, como usual em grafos nao dirigidos)
int GIpegaGrau(Grafo p, int v) {
    int grau = 0;
    if (!GBexisteIdVertice(p, v)) return 0;

    for (int i = 0; i < p->A; i++) {
        int v1 = p->arestas[2 * i];
        int v2 = p->arestas[2 * i + 1];
        if (v1 == v) grau++;
        if (v2 == v) grau++;
    }
    return grau;
}

// primeira aresta incidente ao vertice (grafo nao dirigido)
int GAprimaAresta(Grafo p, int v) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = 0; i < p->A; i++) {
        if (p->arestas[2*i] == v || p->arestas[2*i+1] == v) return i + 1;
    }
    return 0;
}

// proxima aresta incidente ao vertice (grafo nao dirigido)
int GAproxAresta(Grafo p, int v, int a1) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = a1; i < p->A; i++) {
        if (p->arestas[2*i] == v || p->arestas[2*i+1] == v) return i + 1;
    }
    return 0;
}

// primeira aresta que chega ao vertice (grafo dirigido)
int GAprimaEntrada(Grafo p, int v) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = 0; i < p->A; i++) {
        if (p->arestas[2*i+1] == v) return i + 1;
    }
    return 0;
}

// proxima aresta que chega ao vertice (grafo dirigido)
int GAproxEntrada(Grafo p, int v, int a1) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = a1; i < p->A; i++) {
        if (p->arestas[2*i+1] == v) return i + 1;
    }
    return 0;
}

// primeira aresta que sai do vertice (grafo dirigido)
int GAprimaSaida(Grafo p, int v) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = 0; i < p->A; i++) {
        if (p->arestas[2*i] == v) return i + 1;
    }
    return 0;
}

// proxima aresta que sai do vertice (grafo dirigido)
int GAproxSaida(Grafo p, int v, int a1) {
    if (!GBexisteIdVertice(p, v)) return 0;
    for (int i = a1; i < p->A; i++) {
        if (p->arestas[2*i] == v) return i + 1;
    }
    return 0;
}

// informa se a aresta e um laco
int GBarestaLaco(Grafo p, int a) {
    if (!GBexisteIdAresta(p, a)) return 0;
    return p->arestas[2*(a-1)] == p->arestas[2*(a-1)+1];
}

// vertice de partida da aresta
int GAlfa(Grafo p, int a) {
    if (!GBexisteIdAresta(p, a)) return 0;
    return p->arestas[2*(a-1)];
}

// vertice de chegada da aresta
int GOmega(Grafo p, int a) {
    if (!GBexisteIdAresta(p, a)) return 0;
    return p->arestas[2*(a-1)+1];
}

// outro extremo da aresta em relacao ao vertice informado
int GVvizinho(Grafo p, int a, int v1) {
    int x, y;
    if (!GBexisteIdAresta(p, a) || !GBexisteIdVertice(p, v1)) return 0;
    x = GAlfa(p, a);
    y = GOmega(p, a);
    if (x == v1) return y;
    if (y == v1) return x;
    return 0;
}

