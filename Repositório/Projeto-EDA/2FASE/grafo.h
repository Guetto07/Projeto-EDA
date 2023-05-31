#ifndef GRAFO_H
#define GRAFO_H

typedef struct Cliente {
    int clienteID;
    double latitude;
    double longitude;
    struct Cliente* proximo;
} Cliente;

typedef struct MeioMobilidade {
    int meioID;
    double latitude;
    double longitude;
    double cargaBateria;
    struct MeioMobilidade* proximo;
} MeioMobilidade;

typedef struct Grafo {
    Cliente* clientes;
    MeioMobilidade* meios;
    int numClientes;
    int numMeios;
} Grafo;

Grafo* criarGrafo();
void destruirGrafo(Grafo* grafo);

#endif  // GRAFO_H
