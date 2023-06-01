#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meio.h"

Meio *inserirmeio(int codigo, const char* tipo, float preco, float velocidade, float autonomia, float bateria, const char* geocodigo) {
    Meio *meios = NULL;
    Meio *novo_meio = (Meio*)malloc(sizeof(Meio));
    if (novo_meio == NULL) {
        printf("Erro: Falha na alocação de memoria.\n");
    }

    novo_meio->codigo = codigo;
    novo_meio->preco = preco;
    novo_meio->velocidade = velocidade;
    novo_meio->autonomia = autonomia;
    novo_meio->bateria = bateria;
    strcpy(novo_meio->tipo, tipo);
    strcpy(novo_meio->geocodigo, geocodigo);
    novo_meio->seguinte = NULL;

    // Se a lista estiver vazia, insirir o novo meio de mobilidade como o primeiro nó
    if (meios == NULL) {
        meios = novo_meio;
    } else {
        // Encontre o último nó da lista ligada
        Meio* atual = meios;
        while (atual->seguinte != NULL) {
            atual = atual->seguinte;
        }

        // Insira o novo meio de mobilidade como o próximo nó do último nó
        atual->seguinte = novo_meio;
    }

    // Abrir o arquivo "meios.txt" em modo de escrita
    FILE* arquivo = fopen("meios.txt", "a"); //modo append
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo meios.txt.\n");
    }

    // Percorrer a lista ligada e gravar os meios de mobilidade no arquivo
    Meio* atual = meios;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s %.2f %.2f %.2f %.2f %s\n", atual->codigo, atual->tipo, atual->preco, atual->velocidade, atual->autonomia, atual->bateria, atual->geocodigo);
        atual = atual->seguinte;
    }

    // Fechar o arquivo após gravar todos os meios de mobilidade
    fclose(arquivo);
}

void listarmeios() {
    // Abrir o arquivo "meios.txt" em modo de leitura
    FILE* arquivo = fopen("meios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo meios.txt.\n");
        return;
    }

    // Ler e exibir os meios de mobilidade do arquivo
    int codigo;
    float preco, velocidade, bateria, autonomia;
    char tipo[50], geocodigo[50];

    printf("Lista de Meios de Mobilidade:\n");
    while (fscanf(arquivo, "%d %s %f %f %f %f %s", &codigo, tipo, &preco, &velocidade, &autonomia, &bateria, geocodigo) == 7) {
        printf("Codigo: %d\n", codigo);
        printf("Tipo: %s\n", tipo);
        printf("Preco: %.2f\n", preco);
        printf("Velocidade: %.2f\n", velocidade);
        printf("Autonomia: %.2f\n", autonomia);
        printf("Bateria: %.2f\n", bateria);
        printf("Geocodigo: %s\n", geocodigo);
        printf("--------------------------------\n");
    }

    // Fechar o arquivo após a leitura dos meios de mobilidade
    fclose(arquivo);
}

Meio *alugarmeio(Meio *meios, carteira *dinheiros) {
    // Mostrar lista de meios disponíveis
    listarmeios(meios);

    int codigo;
    printf("Informe o codigo do meio de mobilidade que deseja alugar: ");
    scanf("%d", &codigo);

    // Procurar o meio de mobilidade com o código informado
    Meio *atual = meios;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            // Verificar se há saldo suficiente para alugar o meio de mobilidade
            if (dinheiros == NULL || dinheiros->saldo < atual->preco) {
                printf("Saldo insuficiente para alugar este meio de mobilidade.\n");
                return meios;
            }

            // Subtrair o valor do meio de mobilidade do saldo
            dinheiros->saldo -= atual->preco;
            printf("Meio de mobilidade alugado com sucesso!\n");
            printf("Saldo restante: %.2f\n", dinheiros->saldo);
            return meios;
        }

        atual = atual->seguinte;
    }

    printf("Meio de mobilidade com o codigo informado nao encontrado.\n");
    return meios;
}

void removerMeioPorCodigo(int codigo) {
    // Abrir o arquivo "meios.txt" em modo de leitura e escrita
    FILE* arquivo = fopen("meios.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo meios.txt.\n");
        return;
    }

    Meio* meios = NULL;
    Meio* anterior = NULL;
    Meio* atual = NULL;
    Meio* excluido = NULL;

    // Ler os meios de mobilidade do arquivo e construir a lista ligada
    while (!feof(arquivo)) {
        Meio* novo_meio = (Meio*)malloc(sizeof(Meio));
        if (novo_meio == NULL) {
            printf("Erro: Falha na alocação de memória.\n");
            break;
        }

        if (fscanf(arquivo, "%d %s %f %f %f %f %s", &novo_meio->codigo, novo_meio->tipo, &novo_meio->preco,
                   &novo_meio->velocidade, &novo_meio->autonomia, &novo_meio->bateria, novo_meio->geocodigo) == 7) {
            novo_meio->seguinte = NULL;

            // Verificar se o meio atual é o meio a ser removido
            if (novo_meio->codigo == codigo) {
                excluido = novo_meio;
            } else {
                // Adicionar o meio atual à lista ligada
                if (meios == NULL) {
                    meios = novo_meio;
                } else {
                    atual->seguinte = novo_meio;
                }
                atual = novo_meio;
            }
        } else {
            free(novo_meio);
            break;
        }
    }

    // Verificar se o meio a ser removido foi encontrado
    if (excluido == NULL) {
        printf("Erro: Meio com o código %d não encontrado.\n", codigo);
    } else {
        // Remover o meio da lista ligada
        if (excluido == meios) {
            meios = excluido->seguinte;
        } else {
            anterior = meios;
            while (anterior->seguinte != excluido) {
                anterior = anterior->seguinte;
            }
            anterior->seguinte = excluido->seguinte;
        }

        // Voltar para o início do arquivo
        rewind(arquivo);

        // Percorrer a lista ligada e gravar os meios de mobilidade atualizados no arquivo
        atual = meios;
        while (atual != NULL) {
            fprintf(arquivo, "%d %s %.2f %.2f %.2f %.2f %s\n", atual->codigo, atual->tipo, atual->preco,
                    atual->velocidade, atual->autonomia, atual->bateria, atual->geocodigo);
            atual = atual->seguinte;
        }

        // Truncar o arquivo para remover os dados restantes
        int resultado = ftruncate(fileno(arquivo), ftell(arquivo));
        if (resultado != 0) {
            printf("Erro: Falha ao truncar o arquivo meios.txt.\n");
        }

        // Fechar o arquivo após a remoção do meio de mobilidade
        fclose(arquivo);

        // Liberar a memória alocada pelo meio removido
        free(excluido);
    }
}
