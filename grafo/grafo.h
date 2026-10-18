// Alunos: Paulo Henrique Ferreira e Maria Eduarda Saldanha Alves

// definindo a estrutura grafo e Grafo sera o nome de um ponteiro para ela
typedef struct grafo {
    int v, // maximo de vertices
        a, // maximo de arestas
        V, // qtd atual de vertices
        A, // qtd atual de arestas
        *vertices, // espaco para vertices
        *arestas; // espaco para arestas
} *Grafo;

Grafo GGcriaGrafo(int v, int a);
Grafo GGdestroiGrafo(Grafo grafo);
int GVcriaVertice(Grafo grafo);
int GAcriaAresta(Grafo p, int v1, int v2);
int GBexisteIdVertice(Grafo p, int v);
int GBexisteIdAresta(Grafo p, int a);
int GBexisteAresta(Grafo p, int v1, int v2);
int GBexisteArestaDir(Grafo p, int v1, int v2);
int GApegaArestaDir(Grafo p, int v1, int v2);
int GApegaAresta(Grafo p, int v1, int v2);
int GVprimeiroVertice(Grafo p);
int GVproximoVertice(Grafo p, int v1);
int GAprimeiraAresta(Grafo p);
int GAproximaAresta(Grafo p, int a1);
int GInumeroVertices(Grafo p);
