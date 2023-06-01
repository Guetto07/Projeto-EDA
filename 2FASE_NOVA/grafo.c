#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

Vertice* criarVertice(int cod, char* localizacao, double visitado, Vertice* listaVertices) {
    Vertice* vertice = malloc(sizeof(Vertice));
    vertice->cod = cod;
    strcpy(vertice->localizacao, localizacao);
    vertice->visitado = visitado;
    vertice->meios = NULL;  // Definir os meios posteriormente
    vertice->arestas = NULL;  // Definir as arestas posteriormente
    vertice->proximo = NULL;

    if (listaVertices == NULL) {  // Se a lista está vazia
        listaVertices = vertice;
    } else {
        Vertice* atual = listaVertices;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = vertice;
    }
    return vertice;
}

Aresta* criarAresta(int codAresta, float peso, Aresta* listaArestas) {
    Aresta* aresta = malloc(sizeof(Aresta));
    aresta->codAresta = codAresta;
    aresta->peso = peso;
    aresta->proximo = NULL;

    if (listaArestas == NULL) {  // Se a lista está vazia
        listaArestas = aresta;
    } else {
        Aresta* atual = listaArestas;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = aresta;
    }

    return aresta;
}

Vertice* lerArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Vertice* listaVertices = NULL;
    Vertice* verticeAtual = NULL;

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* token = strtok(linha, ";");
        int codVertice = atoi(token);

        token = strtok(NULL, ";");
        char cidade[100];
        if (token != NULL) {
            strcpy(cidade, token);
        } else {
            // Lógica para lidar com token nulo (se necessário)
        }

        token = strtok(NULL, ";");
        int codAresta = atoi(token);

        token = strtok(NULL, ";");
        float peso = atof(token);

        if (listaVertices == NULL) {
            listaVertices = criarVertice(codVertice, cidade, 0, listaVertices);
            verticeAtual = listaVertices;
        } else {
            verticeAtual->proximo = criarVertice(codVertice, cidade, 0, listaVertices);
            verticeAtual = verticeAtual->proximo;
        }

        Aresta* aresta = criarAresta(codAresta, peso, NULL);
        // Inserir aresta no vértice
        if (verticeAtual->arestas == NULL) {
            verticeAtual->arestas = aresta;
        } else {
            Aresta* atual = verticeAtual->arestas;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = aresta;
        }
    }

    fclose(arquivo);
    return listaVertices;
}

void liberarGrafo(Vertice* listaVertices) {
    Vertice* atualVertice = listaVertices;
    while (atualVertice != NULL) {
        Aresta* atualAresta = atualVertice->arestas;
        while (atualAresta != NULL) {
            Aresta* proximaAresta = atualAresta->proximo;
            free(atualAresta);
            atualAresta = proximaAresta;
        }
        Vertice* proximoVertice = atualVertice->proximo;
        free(atualVertice);
        atualVertice = proximoVertice;
    }
}

void adicionarMeioNoVertice(char* localizacaoVertice, MeioMobilidade* listaMeios, Vertice* listaVertices) {
    Vertice* vertice = listaVertices;

    while (vertice != NULL) {
        if (strcmp(vertice->localizacao, localizacaoVertice) == 0) {
            // Vertice com a mesma localização encontrado
            MeioMobilidade* meio = listaMeios;

            while (meio != NULL) {
                if (strcmp(meio->localizacao, localizacaoVertice) == 0) {
                    // Meio de mobilidade com a mesma localização encontrado
                    if (vertice->meios == NULL) {
                        vertice->meios = meio;
                    } else {
                        MeioMobilidade* ultimoMeio = vertice->meios;
                        while (ultimoMeio->proximo != NULL) {
                            ultimoMeio = ultimoMeio->proximo;
                        }
                        ultimoMeio->proximo = meio;
                    }
                }
                meio = meio->proximo;
            }
        }
        vertice = vertice->proximo;
    }
}

void verificarMeiosNoVertice(Vertice* listaVertices) {
    char localizacao[N];
    printf("Digite a localizacao do vertice: ");
    scanf("%s", localizacao);

    Vertice* vertice = listaVertices;
    while (vertice != NULL) {
        if (strcmp(vertice->localizacao, localizacao) == 0) {
            // Vertice com a mesma localização encontrado
            if (vertice->meios == NULL) {
                printf("Nao existem meios de mobilidade nesse vertice.\n");
            } else {
                printf("Meios de mobilidade no vertice:\n");
                MeioMobilidade* meio = vertice->meios;
                while (meio != NULL) {
                    printf("MeioID: %d, Carga de Bateria: %.2f, Tipo de Meio: %s\n", meio->meioID, meio->cargaBateria, meio->tipoMeio);
                    meio = meio->proximo;
                }
            }
            return; // Termina a função após encontrar o vertice
        }
        vertice = vertice->proximo;
    }

    printf("Nao foi encontrado um vertice com a localizacao fornecida.\n");
}

