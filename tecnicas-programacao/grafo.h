// Alunos: Paulo Henrique Ferreira e Maria Eduarda Saldanha Alves

// definindo a estrutura grafo e Grafo será o nome de um ponteiro para ela
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
