#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "grafo.h"
#include "listar.h"
#include "trajeto.h"

void salvarDadosTexto(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        return;
    }

    // Escreva os dados dos clientes no arquivo
    fprintf(arquivo, "%d\n", grafo->numClientes);
    Cliente* clienteAtual = grafo->clientes;
    while (clienteAtual != NULL) {
        fprintf(arquivo, "%d %.6f %.6f\n", clienteAtual->clienteID, clienteAtual->latitude, clienteAtual->longitude);
        clienteAtual = clienteAtual->proximo;
    }

    // Escreva os dados dos meios de mobilidade elétrica no arquivo
    fprintf(arquivo, "%d\n", grafo->numMeios);
    MeioMobilidade* meioAtual = grafo->meios;
    while (meioAtual != NULL) {
        fprintf(arquivo, "%d %.6f %.6f %.2f\n", meioAtual->meioID, meioAtual->latitude, meioAtual->longitude, meioAtual->cargaBateria);
        meioAtual = meioAtual->proximo;
    }

    fclose(arquivo);
}

Grafo* carregarDadosTexto(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        return NULL;
    }

    Grafo* grafo = criarGrafo();

    // Leia os dados dos clientes do arquivo
    fscanf(arquivo, "%d", &(grafo->numClientes));
    Cliente* clienteAnterior = NULL;
    for (int i = 0; i < grafo->numClientes; i++) {
        Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
        fscanf(arquivo, "%d %lf %lf", &(cliente->clienteID), &(cliente->latitude), &(cliente->longitude));
        cliente->proximo = NULL;

        if (clienteAnterior == NULL) {
            grafo->clientes = cliente;
        } else {
            clienteAnterior->proximo = cliente;
        }

        clienteAnterior = cliente;
    }

    // Leia os dados dos meios de mobilidade elétrica do arquivo
    fscanf(arquivo, "%d", &(grafo->numMeios));
    MeioMobilidade* meioAnterior = NULL;
    for (int i = 0; i < grafo->numMeios; i++) {
        MeioMobilidade* meio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));
        fscanf(arquivo, "%d %lf %lf %lf", &(meio->meioID), &(meio->latitude), &(meio->longitude), &(meio->cargaBateria));
        meio->proximo = NULL;

        if (meioAnterior == NULL) {
            grafo->meios = meio;
        } else {
            meioAnterior->proximo = meio;
        }

        meioAnterior = meio;
    }

    fclose(arquivo);
    return grafo;
}

void salvarDadosBinarios(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    // Salve os dados dos clientes no arquivo
    fwrite(&(grafo->numClientes), sizeof(int), 1, arquivo);
    Cliente* clienteAtual = grafo->clientes;
    while (clienteAtual != NULL) {
        fwrite(clienteAtual, sizeof(Cliente), 1, arquivo);
        clienteAtual = clienteAtual->proximo;
    }

    // Salve os dados dos meios de mobilidade elétrica no arquivo
    fwrite(&(grafo->numMeios), sizeof(int), 1, arquivo);
    MeioMobilidade* meioAtual = grafo->meios;
    while (meioAtual != NULL) {
        fwrite(meioAtual, sizeof(MeioMobilidade), 1, arquivo);
        meioAtual = meioAtual->proximo;
    }

    fclose(arquivo);
}

Grafo* carregarDadosBinarios(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return NULL;
    }

    Grafo* grafo = criarGrafo();

    // Carregue os dados dos clientes do arquivo
    fread(&(grafo->numClientes), sizeof(int), 1, arquivo);
    Cliente* clienteAnterior = NULL;
    for (int i = 0; i < grafo->numClientes; i++) {
        Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
        fread(cliente, sizeof(Cliente), 1, arquivo);
        cliente->proximo = NULL;

        if (clienteAnterior == NULL) {
            grafo->clientes = cliente;
        } else {
            clienteAnterior->proximo = cliente;
        }

        clienteAnterior = cliente;
    }

    // Carregue os dados dos meios de mobilidade elétrica do arquivo
    fread(&(grafo->numMeios), sizeof(int), 1, arquivo);
    MeioMobilidade* meioAnterior = NULL;
    for (int i = 0; i < grafo->numMeios; i++) {
        MeioMobilidade* meio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));
        fread(meio, sizeof(MeioMobilidade), 1, arquivo);
        meio->proximo = NULL;

        if (meioAnterior == NULL) {
            grafo->meios = meio;
        } else {
            meioAnterior->proximo = meio;
        }

        meioAnterior = meio;
    }

    fclose(arquivo);
    return grafo;
}
