#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "arquivo.h"
#include "listar.h"
#include "trajeto.h"

void exibirMenu() {
    printf("===== MENU =====\n");
    printf("1. Salvar dados em arquivo de texto\n");
    printf("2. Carregar dados de arquivo de texto\n");
    printf("3. Salvar dados em arquivo binário\n");
    printf("4. Carregar dados de arquivo binário\n");
    printf("5. Listar meios de mobilidade em um raio\n");
    printf("6. Calcular trajeto do caixeiro viajante\n");
    printf("0. Sair\n");
    printf("=================\n");
}

int main() {
    Grafo* grafo = criarGrafo();
    int escolha;

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
            {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo de texto: ");
                scanf("%s", nomeArquivo);
                salvarDadosTexto(grafo, nomeArquivo);
                printf("Dados salvos em arquivo de texto.\n");
                break;
            }
            case 2:
            {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo de texto: ");
                scanf("%s", nomeArquivo);
                Grafo* novoGrafo = carregarDadosTexto(nomeArquivo);
                if (novoGrafo != NULL) {
                    destruirGrafo(grafo);
                    grafo = novoGrafo;
                    printf("Dados carregados do arquivo de texto.\n");
                }
                break;
            }
            case 3:
            {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo binário: ");
                scanf("%s", nomeArquivo);
                salvarDadosBinarios(grafo, nomeArquivo);
                printf("Dados salvos em arquivo binário.\n");
                break;
            }
            case 4:
            {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo binário: ");
                scanf("%s", nomeArquivo);
                Grafo* novoGrafo = carregarDadosBinarios(nomeArquivo);
                if (novoGrafo != NULL) {
                    destruirGrafo(grafo);
                    grafo = novoGrafo;
                    printf("Dados carregados do arquivo binário.\n");
                }
                break;
            }
            case 5:
            {
                double latitude, longitude, raio;
                int tipoMeio;
                printf("Digite a latitude: ");
                scanf("%lf", &latitude);
                printf("Digite a longitude: ");
                scanf("%lf", &longitude);
                printf("Digite o tipo de meio de mobilidade (0 para todos): ");
                scanf("%d", &tipoMeio);
                printf("Digite o raio: ");
                scanf("%lf", &raio);
                listarMeiosNoRaio(grafo, latitude, longitude, tipoMeio, raio);
                break;
            }
            case 6:
            {
                double capacidadeCaminhao;
                printf("Digite a capacidade do caminhão: ");
                scanf("%lf", &capacidadeCaminhao);
                calcularTrajeto(grafo, capacidadeCaminhao);
                break;
            }
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        
        printf("\n");
    } while (escolha != 0);

    destruirGrafo(grafo);

    return 0;
}
