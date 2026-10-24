# TAD de Grafos em C

![linguagem](https://img.shields.io/badge/linguagem-C-00599C?logo=c&logoColor=white)
![disciplina](https://img.shields.io/badge/disciplina-T%C3%A9cnicas%20de%20Programa%C3%A7%C3%A3o-2e7d32)
![curso](https://img.shields.io/badge/curso-Engenharia%20da%20Computa%C3%A7%C3%A3o-1565c0)
![instituicao](https://img.shields.io/badge/IFMG-Campus%20Bambu%C3%AD-green)

Trabalho I da disciplina de **Técnicas de Programação** (Engenharia da Computação, IFMG Campus Bambuí). O projeto implementa um **Tipo Abstrato de Dados (TAD) para grafos** em C, com suporte a grafos dirigidos e não dirigidos, arestas múltiplas e laços, e usa essa estrutura para resolver o problema de **encontrar um trajeto entre dois vértices** de um grafo dirigido com arestas valoradas.

**Autores:**
- Paulo Henrique Ferreira · [@0pauloh](https://github.com/0pauloh)
- Maria Eduarda Saldanha Alves · [@mariasaldanhaa](https://github.com/mariasaldanhaa)

---

## 📑 Sumário

- [Sobre o projeto](#-sobre-o-projeto)
- [O que foi implementado](#-o-que-foi-implementado)
- [Estrutura do repositório](#-estrutura-do-repositório)
- [Conceitos usados](#-conceitos-usados)
- [A TAD Grafo](#-a-tad-grafo)
- [Como os dados são guardados](#-como-os-dados-são-guardados)
- [Decisões de projeto](#-decisões-de-projeto)
- [O procedimento Gcaminho](#-o-procedimento-gcaminho)
- [Formato do arquivo de grafo](#-formato-do-arquivo-de-grafo)
- [Como compilar e executar](#-como-compilar-e-executar)
- [Exemplos de uso](#-exemplos-de-uso)
- [Programa de testes interativo](#-programa-de-testes-interativo)
- [Validação e testes](#-validação-e-testes)
- [Limitações e melhorias futuras](#-limitações-e-melhorias-futuras)
- [Observações sobre a especificação](#-observações-sobre-a-especificação)
- [Referências](#-referências)

---

## 📖 Sobre o projeto

Grafos são modelos matemáticos usados para representar mapas, redes de computadores, circuitos elétricos, máquinas de estados e muitas outras estruturas. Um grafo **G(V, A)** é formado por um conjunto de **vértices** `V` e um conjunto de **arestas** `A` que ligam pares de vértices.

O trabalho tem **duas tarefas**:

1. **Implementar a TAD Grafo**: um módulo em C (`grafo.h` / `grafo.c`) com todas as operações descritas na especificação da disciplina.
2. **Implementar um procedimento de caminho** (`caminho.h` / `caminho.c`): dado um grafo dirigido, um vetor de pesos (distâncias) para as arestas, um vértice de partida e um de chegada, encontrar e imprimir um trajeto entre eles, **usando a TAD da tarefa 1**.

O programa principal de correção é fornecido pela professora: ele lê arquivos de entrada pré-definidos, usa o módulo Grafo e compara as saídas com as esperadas. Por isso, a TAD segue **exatamente** os nomes e comportamentos da especificação.

## ✅ O que foi implementado

- [x] Criação e destruição de grafos com capacidade máxima de vértices e arestas
- [x] Criação de vértices e arestas com identificadores sequenciais
- [x] Consultas de existência e busca de arestas (dirigidas e não dirigidas)
- [x] Percurso de todos os vértices e de todas as arestas
- [x] Estrelas de entrada, de saída e estrela simples de um vértice
- [x] Grau do vértice, detecção de laços, extremos de uma aresta e vizinho
- [x] Carregar e salvar grafos em arquivo texto
- [x] Programa de testes interativo com menu para todas as operações
- [ ] `Gcaminho` (módulo `caminho.h` / `caminho.c`): **em desenvolvimento**, será a próxima etapa

## 🗂️ Estrutura do repositório

```
trabalho-tecnicas-programacao/
├── .vscode/            # configurações do VS Code
└── grafo/
    ├── grafo.h         # tipo Grafo e protótipos das operações
    ├── grafo.c         # implementação da TAD
    ├── [main.c]        # programa de testes interativo (menu)
    └── [caminho.h / caminho.c]   # procedimento Gcaminho (a criar)
```

## 🧠 Conceitos usados

| Conceito | Definição adotada no trabalho |
|---|---|
| **Identificador do vértice** | Inteiro positivo, associado à ordem de criação (1, 2, 3, …) |
| **Identificador da aresta** | Inteiro positivo, associado à ordem de criação (1, 2, 3, …) |
| **Valor `0`** | Representa vértice ou aresta inexistente |
| **Grafo dirigido** | Arestas são pares ordenados `(v1, v2)` |
| **Grafo não dirigido** | Arestas são pares não ordenados: `{1,2}` equivale a `{2,1}` |
| **Aresta múltipla** | Duas ou mais arestas distintas ligando o mesmo par de vértices (permitido) |
| **Laço** | Aresta que parte de um vértice e chega nele mesmo (permitido) |
| **Grau** | Número de arestas incidentes no vértice (em grafos dirigidos, grau de saída + grau de entrada) |
| **Vértice isolado** | Vértice de grau zero |
| **Estrela de entrada `EE(v)`** | Arestas que chegam em `v` |
| **Estrela de saída `ES(v)`** | Arestas que saem de `v` |

## 🧱 A TAD Grafo

O tipo `Grafo` é um ponteiro para uma `struct`:

```c
typedef struct grafo {
    int v,         // máximo de vértices
        a,         // máximo de arestas
        V,         // quantidade atual de vértices
        A,         // quantidade atual de arestas
        *vertices, // espaço para os vértices
        *arestas;  // espaço para as arestas
} *Grafo;
```

### Convenção de nomes

Toda rotina começa com `G` seguido de uma letra que indica o **tipo de retorno**, e depois o nome da tarefa:

| Prefixo | Retorno |
|---|---|
| `GG...` | ponteiro `Grafo` |
| `GV...` | identificador de vértice |
| `GA...` | identificador de aresta |
| `GB...` | booleano (`1` ou `0`) |
| `GI...` | inteiro |

Nenhuma rotina imprime mensagem de erro. Quando algo dá errado, ela retorna o código convencionado (`0` ou `NULL`).

### Operações do grafo

| Operação | Descrição |
|---|---|
| `GGcriaGrafo(v, a)` | Cria um grafo com capacidade para `v` vértices e `a` arestas (`NULL` se faltar memória) |
| `GGdestroiGrafo(p)` | Libera a memória do grafo e retorna ponteiro nulo |
| `GVcriaVertice(p)` | Cria um vértice e retorna seu identificador (`0` se a capacidade acabou) |
| `GAcriaAresta(p, v1, v2)` | Cria a aresta `(v1, v2)` e retorna seu identificador (`0` se a capacidade acabou) |
| `GBexisteIdVertice(p, v)` | O vértice existe? |
| `GBexisteIdAresta(p, a)` | A aresta existe? |
| `GBexisteAresta(p, v1, v2)` | Existe aresta **não dirigida** entre `v1` e `v2`? |
| `GBexisteArestaDir(p, v1, v2)` | Existe aresta **dirigida** de `v1` para `v2`? |
| `GApegaAresta(p, v1, v2)` | Identificador da aresta não dirigida (`0` se não existir) |
| `GApegaArestaDir(p, v1, v2)` | Identificador da aresta dirigida (`0` se não existir) |
| `GVprimeiroVertice(p)` / `GVproximoVertice(p, v1)` | Percorrem os vértices em ordem crescente de identificador |
| `GAprimeiraAresta(p)` / `GAproximaAresta(p, a1)` | Percorrem as arestas em ordem crescente de identificador |
| `GInumeroVertices(p)` / `GInumeroVerticesMax(p)` | Quantidade atual e máxima de vértices |
| `GInumeroArestas(p)` / `GInumeroArestasMax(p)` | Quantidade atual e máxima de arestas |
| `GGcarregaGrafo(f)` | Cria e carrega um grafo a partir de um arquivo (`NULL` se inválido) |
| `GBsalvaGrafo(p, f)` | Salva o grafo em arquivo e indica se deu certo |

### Operações sobre vértices

| Operação | Descrição |
|---|---|
| `GIpegaGrau(p, v)` | Grau do vértice (`0` se não existir) |
| `GAprimaAresta(p, v)` / `GAproxAresta(p, v, a1)` | Percorrem a estrela do vértice (grafos não dirigidos) |
| `GAprimaEntrada(p, v)` / `GAproxEntrada(p, v, a1)` | Percorrem a estrela de **entrada** (grafos dirigidos) |
| `GAprimaSaida(p, v)` / `GAproxSaida(p, v, a1)` | Percorrem a estrela de **saída** (grafos dirigidos) |

### Operações sobre arestas

| Operação | Descrição |
|---|---|
| `GBarestaLaco(p, a)` | A aresta é um laço? (falso se não existir) |
| `GAlfa(p, a)` | Vértice de partida da aresta |
| `GOmega(p, a)` | Vértice de chegada da aresta |
| `GVvizinho(p, a, v1)` | Vértice no outro extremo da aresta `a`, dado `v1` |

> A TAD guarda **apenas a estrutura** do grafo: quais vértices existem e quais arestas os ligam. Informações extras, como a distância de cada aresta, não ficam dentro do grafo, e sim em vetores separados em que o identificador da aresta é a posição (por exemplo, `pesos[a]`). Isso será usado no `Gcaminho`.

## 💾 Como os dados são guardados

Os vértices ficam em um vetor de `v` posições e as arestas em um **vetor plano de `2 × a` posições**: cada aresta ocupa duas posições seguidas, a de partida e a de chegada. O identificador da aresta é a posição dela na ordem de criação (começando em 1).

Exemplo com o grafo dirigido da Figura 1 da especificação (8 arestas):

```
id da aresta:   1     2     3     4     5     6     7     8
arestas[]:    [ 6  1 | 6  3 | 3  6 | 1  3 | 1  2 | 2  3 | 2  2 | 5  4 ]
índice:         0  1   2  3   4  5   6  7   8  9  10 11  12 13  14 15
```

A aresta de identificador `k` está nas posições `2*(k-1)` (partida) e `2*(k-1)+1` (chegada).

## 🏗️ Decisões de projeto

- **Identificadores sequenciais.** O vértice criado em n-ésimo lugar recebe o identificador n, e o mesmo vale para as arestas. Como não existe remoção, os identificadores continuam sequenciais, e isso torna `GVprimeiroVertice`, `GVproximoVertice`, `GAprimeiraAresta` e `GAproximaAresta` operações de custo constante, sem varrer vetores.
- **`GVproximoVertice` e `GAproximaAresta`.** Retornam `v1 + 1` (ou `a1 + 1`) enquanto o resultado existir no grafo, e `0` caso contrário. Se o identificador recebido for menor que 1 e houver elementos, retornam `1`.
- **Arestas em vetor plano.** Guardar as duas pontas lado a lado evita criar uma `struct` por aresta e simplifica a alocação: um único `malloc` de `2 × a` inteiros.
- **Buscas lineares.** As operações de existência, busca de aresta, grau e estrelas percorrem o vetor de arestas (custo proporcional a `|A|`). Para percorrer uma estrela, `GAprox...` retoma a busca logo depois da aresta anterior, então o percurso completo de uma estrela custa `O(|A|)` no total.
- **Grau.** Um laço conta duas vezes no grau do vértice. A mesma função serve para grafos dirigidos (entrada + saída) e não dirigidos.
- **Dirigido ou não dirigido.** O grafo é criado do mesmo jeito nos dois casos. O que muda é o conjunto de operações usado para consultá-lo (`GBexisteAresta` contra `GBexisteArestaDir`, `GAprimaAresta` contra `GAprimaEntrada`/`GAprimaSaida`).
- **`GVvizinho`.** Retorna `0` se a aresta ou o vértice não existirem, ou se o vértice não for extremo da aresta. Em um laço, o vizinho é o próprio vértice.
- **Tratamento de erros.** `GGcriaGrafo` retorna `NULL` se a alocação falhar. `GVcriaVertice` e `GAcriaAresta` retornam `0` quando a capacidade máxima é atingida. Algumas rotinas checam ponteiro nulo por segurança, apesar de a especificação dizer que não é necessário.
- **Carga de arquivo.** `GGcarregaGrafo` valida o cabeçalho e cada linha, e libera a memória e fecha o arquivo em qualquer falha. Um arquivo com zero arestas é aceito, e o grafo é criado com capacidade para uma aresta, porque `GGcriaGrafo` exige `a > 0`.

## 🧭 O procedimento Gcaminho

> 🚧 **Em desenvolvimento.** Esta tarefa ainda não foi implementada. A seção abaixo descreve o que a especificação pede.

```c
void Gcaminho(Grafo g, float *pesos, int a, int b);
```

| Parâmetro | Significado |
|---|---|
| `g` | Grafo dirigido |
| `pesos` | Vetor de pesos das arestas, com tamanho `|A| + 1` (a posição `0` não é usada, então `pesos[id_da_aresta]` é direto) |
| `a` | Vértice de partida |
| `b` | Vértice de chegada |

**Comportamento esperado:**

- Se existe caminho de `a` até `b`, imprime o trajeto no formato `3 -> 6 -> 1 -> 2`.
- Se **não** existe caminho, imprime apenas o vértice de partida.

**Exemplo com o grafo dirigido da Figura 1 da especificação** (pesos todos iguais a 1):

| Partida | Chegada | Saída |
|---|---|---|
| 3 | 2 | `3 -> 6 -> 1 -> 2` |
| 1 | 4 | `1` |

**Algoritmo previsto:** Dijkstra.

## 📄 Formato do arquivo de grafo

Arquivo texto. A primeira linha traz o número de vértices e o de arestas. Cada linha seguinte descreve uma aresta com o vértice de partida e o de chegada.

Exemplo (grafo da Figura 2 da especificação: 6 vértices e 4 arestas):

```
6 4
1 6
1 2
6 2
5 4
```

## ⚙️ Como compilar e executar

### Pré-requisitos

- Compilador C (`gcc`, por exemplo)
- Git
- Opcional: uma IDE, como Code::Blocks ou CLion

Primeiro, clone o repositório:

```bash
git clone https://github.com/mariasaldanhaa/trabalho-tecnicas-programacao.git
cd trabalho-tecnicas-programacao/grafo
```

### Opção 1: terminal (gcc)

```bash
gcc -Wall -o testes main.c grafo.c
./testes
```

> Troque `main.c` pelo nome do programa principal. Para usar o `Gcaminho`, inclua também `caminho.c` na compilação.

### Opção 2: Code::Blocks (usado no desenvolvimento)

1. Crie um projeto em **File > New > Project > Console application** e escolha a linguagem **C**.
2. Remova o `main.c` que a IDE gera, ou substitua o conteúdo pelo programa de testes.
3. Adicione os arquivos do projeto em **Project > Add files...**: `grafo.c`, `grafo.h` e o programa de testes.
4. Compile e execute com **Build and run** (`F9`).

### Opção 3: CLion

O CLion usa CMake para compilar. Crie um arquivo `CMakeLists.txt` dentro da pasta `grafo/`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(grafo C)

set(CMAKE_C_STANDARD 11)

add_executable(testes main.c grafo.c)
```

Depois, abra a pasta `grafo/` no CLion (**File > Open**), espere o CMake carregar e execute com `Shift+F10`. Quando o `Gcaminho` estiver pronto, acrescente `caminho.c` na lista do `add_executable`.

## 💡 Exemplos de uso

**Criar e salvar um grafo:**

```c
#include "grafo.h"

int main(void) {
    int i;
    Grafo g = GGcriaGrafo(5, 5);

    for (i = 0; i < 5; i++)
        GVcriaVertice(g);

    GAcriaAresta(g, 1, 2);
    GAcriaAresta(g, 1, 3);
    GAcriaAresta(g, 2, 4);
    GAcriaAresta(g, 3, 5);
    GAcriaAresta(g, 4, 5);

    GBsalvaGrafo(g, "grafo.txt");
    GGdestroiGrafo(g);
    return 0;
}
```

**Carregar um grafo e imprimir todas as arestas:**

```c
#include <stdio.h>
#include "grafo.h"

int main(void) {
    int a;
    Grafo g = GGcarregaGrafo("grafo.txt");

    for (a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a))
        printf("(%d,%d)\n", GAlfa(g, a), GOmega(g, a));

    GGdestroiGrafo(g);
    return 0;
}
```

Saída esperada para o grafo salvo no exemplo anterior:

```
(1,2)
(1,3)
(2,4)
(3,5)
(4,5)
```

## 🖥️ Programa de testes interativo

O arquivo de testes oferece um menu no terminal para exercitar cada operação da TAD sem escrever código:

| Opções | O que fazem |
|---|---|
| 1 e 2 | Criar e deletar o grafo |
| 3 e 4 | Criar vértice e aresta |
| 5 a 10 | Existência de vértice e aresta, e busca de identificador de aresta (dirigida e não dirigida) |
| 11 a 14 | Percorrer vértices e arestas |
| 15 a 18 | Quantidades atuais e máximas |
| 19 e 20 | Carregar e salvar grafo em arquivo |
| 21 a 27 | Grau e estrelas do vértice |
| 28 e 29 | Laço, `GAlfa`, `GOmega` e `GVvizinho` |
| 30 | Sair |

## 🧪 Validação e testes

Cada operação da TAD foi exercitada pelo programa de testes interativo.

[vou colocar ainda]

## 🔧 Limitações e melhorias futuras

O que foi entregue segue a especificação, mas há pontos em que o grupo faria diferente numa próxima versão:

- **Tipo não opaco.** A `struct grafo` está definida por inteiro em `grafo.h`, então quem usa o módulo enxerga os campos (o programa de testes acessa `p->V`, `p->arestas` etc.). Numa TAD de verdade, o `.h` declararia só `struct grafo;` e `typedef struct grafo *Grafo;`, e a definição ficaria em `grafo.c`.
- **Vetor `vertices` redundante.** Como o identificador do vértice `i` é sempre `i`, o vetor guarda só `1, 2, 3, …`. Dá para guardar apenas a contagem `V` e checar existência com `1 <= v && v <= V`, em tempo constante.
- **Buscas lineares.** Estrelas, grau e busca de aresta custam `O(|A|)` por chamada. Com listas de adjacência (ou vetores de arestas por vértice), a estrela de um vértice custaria `O(grau)`.
- **Sem proteção contra inclusão dupla.** `grafo.h` não tem `#ifndef`/`#define`, então incluí-lo duas vezes na mesma unidade gera erro de redefinição.
- **`GAcriaAresta` não valida os extremos.** A especificação só exige espaço disponível, mas o módulo aceita arestas entre vértices que ainda não foram criados.
- **Liberação parcial em `GGcriaGrafo`.** Se uma das alocações internas falhar, a memória das outras não é liberada antes de retornar `NULL`.
- **Sem remoção.** Não há operação para remover vértices ou arestas; isso manteve os identificadores simples, mas limita o uso do módulo.

## 📝 Observações sobre a especificação

O enunciado pede que as suposições sejam registradas. Estas foram as escolhas do grupo onde o texto é omisso ou inconsistente:

| Ponto | Observação | Escolha do grupo |
|---|---|---|
| Nome da operação de salvar | A tabela traz `GBsalvaGrado`, mas o exemplo de código usa `GBsalvaGrafo` | Adotado `GBsalvaGrafo` |
| Vértices de uma aresta | O exemplo 3.2 chama `GValfa` e `GVomega`, mas a tabela define `GAlfa` e `GOmega` | Adotados `GAlfa` e `GOmega` |
| Fim do percurso de arestas | O exemplo 3.2 testa `a != NULL`, mas a especificação usa `0` para aresta inexistente | Todas as operações retornam `0` |
| Retorno de `GAproxEntrada` | A saída é nomeada `a1` na tabela, mas o pós-requisito fala de `a2` | Retorna a próxima aresta da estrela de entrada, ou `0` |
| Grau de vértice com laço | A especificação não diz como contar | O laço conta duas vezes |
| Grafo dirigido ou não dirigido | A TAD não diferencia os dois | Mesma criação; muda apenas as operações de consulta |
| Arquivo sem arestas | `GGcriaGrafo` exige `a > 0` | O grafo carregado tem capacidade para uma aresta |

## 📚 Referências

- SCHILDT, Herbert. C, completo e total. Tradução e revisão técnica de Roberto 
Carlos Mayer. 3. ed. rev. e atual. São Paulo: Makron Books, 1997.

- COHEN, Marcelo. Modularização em C. Porto Alegre: Pontifícia Universidade 
Católica do Rio Grande do Sul (PUCRS), mar. 2013. Disponível em: 
(https://www.inf.pucrs.br/flash/progswb/present/U01_progC/makefiles/handout.html). 
Acesso em: 21 set. 2026. 

- UNIVERSITAT POLITÈCNICA DE VALÈNCIA. Curso Teoría básica de grafos y 
análisis de 4 conocidos problemas. YouTube, jun. 2019. Playlist (43 vídeos). 
Disponível em: (https://www.youtube.com/playlist?list=PL5098BF5A01819B3B). 
Acesso em: 13 out. 2026. 

- CRUZ, Adriano Joaquim de Oliveira. Curso de linguagem C. Rio de Janeiro: 
Universidade Federal do Rio de Janeiro, Núcleo de Computação Eletrônica, 2011. 
Disponível em: 
(https://drive.google.com/file/d/1-74hvZLnP1DcSO8dk5HUFxaPNUH47jW_/view). 
Acesso em: 18 out. 2026. 

- FEOFILOFF, Paulo; KOHAYAKAWA, Yoshiharu; WAKABAYASHI, Yoshiko. Uma 
introdução sucinta à teoria dos grafos. 2004. Disponível em: 
(https://www.ime.usp.br/~pf/teoriadosgrafos/). Acesso em: 18 out. 2026. 

---

<sub>Trabalho I · Técnicas de Programação · Engenharia da Computação · IFMG Campus Bambuí</sub>
