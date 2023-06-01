#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main() {
    Vertice* listaVertices = NULL;
    int cod;
    char localizacao[100];
    double visitado;

    Aresta* listaArestas = NULL;
    int codAresta;
    float peso;

    MeioMobilidade* listaMeios = NULL;
    int localizacaoVertice;
    
    int escolha;
    printf("Menu\n");
    printf("1. Criar um novo vertice\n");
    printf("2. Criar uma aresta\n");
    printf("3. Adicionar um meio num vertice\n");
    printf("4. Localizacao de um meio pelo vertice\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("Digite o codigo do vertice: ");
            scanf("%d", &cod);
            printf("Digite a localizacao do vertice: ");
            scanf(" %[^\n]", localizacao);
            printf("Digite o valor visitado do vertice: ");
            scanf("%lf", &visitado);

            Vertice* novoVertice = criarVertice(cod, localizacao, visitado, listaVertices);
            if (novoVertice != NULL) {
                printf("Vertice criado com sucesso.\n");
            } else {
                printf("Erro ao criar o vertice.\n");
            }
            break;
        case 2:
            printf("Digite o codigo da aresta: ");
            scanf("%d", &codAresta);
            printf("Digite o peso da aresta: ");
            scanf("%f", &peso);

            Aresta* novaAresta = criarAresta(codAresta, peso, listaArestas);
            if (novaAresta != NULL) {
                printf("Aresta criada com sucesso.\n");
            } else {
                printf("Erro ao criar a aresta.\n");
            }
            break;
        // case 3:
        //     printf("Digite a localização do vértice: ");
        //     scanf("%s", localizacaoVertice);

        //     adicionarMeioNoVertice(localizacaoVertice, listaMeios, listaVertices);
        //     printf("Meio de mobilidade adicionado ao vértice com sucesso.\n");
        //     break;
        // case 4:
        //     printf("Digite a localização do vértice: ");
        //     scanf("%s", localizacaoVertice);

        //     Vertice* vertice = encontrarVerticePorLocalizacao(localizacaoVertice, listaVertices);
        //     if (vertice == NULL) {
        //         printf("Vértice não encontrado.\n");
        //     } else {
        //         MeioMobilidade* meio = encontrarMeioPorLocalizacao(localizacaoVertice, listaMeios);
        //         if (meio == NULL) {
        //             printf("Meio de mobilidade não encontrado.\n");
        //         } else {
        //             printf("Meio de mobilidade encontrado no mesmo vértice.\n");
        //         }
        //     }
        //     break;
        default:
            printf("Escolha invalida.\n");
            break;
    }

    lerArquivo("grafos.txt");
    void liberarGrafo(listaVertices);

    return 0;

}
