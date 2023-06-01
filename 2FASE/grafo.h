#ifndef GRAFO_H
#define GRAFO_H

typedef struct Cliente {
    int clienteID;
    struct Cliente* proximo;
} Cliente;

typedef struct MeioMobilidade {
    int meioID;
    double cargaBateria;
    char locazicao;
    struct MeioMobilidade* proximo;
} MeioMobilidade;

typedef struct Vertice {
    int cod;
    char localizacao;
    double visitado;
    int numClientes;
    int numMeios;
    MeioMobilidade* meios;
    Vertice* proximo;
} Vertice;

typedef struct Aresta
{
    int codAresta;
    float peso;
}Aresta;


Grafo* criarGrafo();
void destruirGrafo(Grafo* grafo);

#endif  // GRAFO_H
