#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->clientes = NULL;
    grafo->meios = NULL;
    grafo->numClientes = 0;
    grafo->numMeios = 0;
    return grafo;
}

void destruirGrafo(Grafo* grafo) {
    // Libere a memória ocupada pelos clientes
    Cliente* clienteAtual = grafo->clientes;
    while (clienteAtual != NULL) {
        Cliente* proximoCliente = clienteAtual->proximo;
        free(clienteAtual);
        clienteAtual = proximoCliente;
    }

    // Libere a memória ocupada pelos meios de mobilidade
    MeioMobilidade* meioAtual = grafo->meios;
    while (meioAtual != NULL) {
        MeioMobilidade* proximoMeio = meioAtual->proximo;
        free(meioAtual);
        meioAtual = proximoMeio;
    }

    free(grafo);
}
