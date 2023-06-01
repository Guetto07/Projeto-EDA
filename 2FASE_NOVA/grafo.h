#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

typedef struct Cliente {
    int clienteID;
    struct Cliente* proximo;
} Cliente;

typedef struct MeioMobilidade {
    int meioID;
    double cargaBateria;
    char localizacao[N];
    char tipoMeio[N];
    struct MeioMobilidade* proximo;
} MeioMobilidade;

typedef struct Vertice {
    int cod;
    char localizacao[N];
    double visitado;
    struct Aresta* arestas;
    struct MeioMobilidade* meios;
    struct Vertice* proximo;
} Vertice;

typedef struct Aresta
{
    int codAresta;
    float peso;
    struct Aresta* proximo;
}Aresta;

Vertice* criarVertice(int cod, char* localizacao, double visitado, Vertice* listaVertices);
Aresta* criarAresta(int codAresta, float peso, Aresta* listaArestas);
Vertice* lerArquivo(const char* nomeArquivo);
void liberarGrafo(Vertice* listaVertices);
void adicionarMeioNoVertice(char* localizacaoVertice, MeioMobilidade* listaMeios, Vertice* listaVertices);
void verificarMeiosNoVertice(Vertice* listaVertices);
