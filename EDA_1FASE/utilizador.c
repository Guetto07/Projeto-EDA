#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilizador.h"
#include "meio.h"

void inserircliente(Cliente *novoCliente) {
    // Abrir o arquivo "clientes.txt" em modo de escrita
    FILE *arquivo = fopen("clientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo clientes.txt.\n");
        return;
    }

    // Escrever os dados do novo cliente no arquivo
    fprintf(arquivo, "%s %s %s %s %d %d %d\n", novoCliente->nome, novoCliente->morada, novoCliente->cidade,
            novoCliente->email, novoCliente->idade, novoCliente->NIF, novoCliente->telefone);

    // Fechar o arquivo após a inserção do cliente
    fclose(arquivo);
}

void removercliente(int NIF) {
    // Abrir o arquivo "clientes.txt" em modo de leitura e escrita
    FILE *arquivo = fopen("clientes.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo clientes.txt.\n");
        return;
    }

    Cliente *clientes = NULL;
    Cliente *anterior = NULL;
    Cliente *atual = NULL;
    Cliente *excluido = NULL;

    // Ler os clientes do arquivo e construir a lista ligada
    while (!feof(arquivo)) {
        Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
        if (novoCliente == NULL) {
            printf("Erro: Falha na alocação de memória.\n");
            break;
        }

        if (fscanf(arquivo, "%s %s %s %s %d %d %d", novoCliente->nome, novoCliente->morada, novoCliente->cidade,
                   novoCliente->email, &novoCliente->idade, &novoCliente->NIF, &novoCliente->telefone) == 7) {
            novoCliente->seguinte = NULL;

            // Verificar se o cliente atual é o cliente a ser removido
            if (novoCliente->NIF == NIF) {
                excluido = novoCliente;
            } else {
                // Adicionar o cliente atual à lista ligada
                if (clientes == NULL) {
                    clientes = novoCliente;
                } else {
                    atual->seguinte = novoCliente;
                }
                atual = novoCliente;
            }
        } else {
            free(novoCliente);
            break;
        }
    }

    // Verificar se o cliente a ser removido foi encontrado
    if (excluido == NULL) {
        printf("Erro: Cliente com o NIF %d não encontrado.\n", NIF);
    } else {
        // Remover o cliente da lista ligada
        if (excluido == clientes) {
            clientes = excluido->seguinte;
        } else {
            anterior = clientes;
            while (anterior->seguinte != excluido) {
                anterior = anterior->seguinte;
            }
            anterior->seguinte = excluido->seguinte;
        }

        // Voltar para o início do arquivo
        rewind(arquivo);

        // Percorrer a lista ligada e gravar os clientes atualizados no arquivo
        atual = clientes;
        while (atual != NULL) {
            fprintf(arquivo, "%s %s %s %s %d %d %d\n", atual->nome, atual->morada, atual->cidade,
                    atual->email, atual->idade, atual->NIF, atual->telefone);
            atual = atual->seguinte;
        }

        // Truncar o arquivo para remover os dados restantes
        int resultado = ftruncate(fileno(arquivo), ftell(arquivo));
        if (resultado != 0) {
            printf("Erro: Falha ao truncar o arquivo clientes.txt.\n");
        }

        // Fechar o arquivo após a remoção do cliente
        fclose(arquivo);

        // Liberar a memória alocada pelo cliente removido
        free(excluido);
    }
}

// //Guarda clientes no ficheiro de texto 
// int guardarclientes(Cliente *inicio)
// {FILE* fp;
//  fp = fopen("clientes.txt","a");
//  if (fp!=NULL)
//  {
//  Cliente* aux= inicio;
//  while (aux != NULL)
//  {
//   fprintf(fp,"%s;%d;%d;%s;%d;%s;%s\n", aux->nome, aux->idade, aux->NIF, aux->email, aux->telefone, aux->cidade, aux->morada);
//   aux = aux->seguinte;
//  }
//  fclose(fp);
//  return(1);
//  }
//  else return(0);
// }

// //Confirma se o cliente já existe de acordo com o NIF
// int existecliente(Cliente* inicio, int NIF)
// {while(inicio!=NULL)
//   {if (inicio->NIF == NIF) return(1);
//    inicio = inicio->seguinte;
//   }
//  return(0);
// }

// //Inserir um novo cliente
// Cliente *inserirclientes(Cliente* inicio, char nome[], int idade, int NIF, int telefone, char email[], char cidade[], char morada[])
// {
//     if (!existecliente(inicio, NIF))
//     {
//         Cliente* novo = malloc(sizeof(Cliente));
//         if (novo != NULL)
//         {
//             strcpy(novo->nome, nome);
//             strcpy(novo->morada, morada);
//             strcpy(novo->cidade, cidade);
//             strcpy(novo->email, email);
//             novo->idade = idade;
//             novo->NIF = NIF;
//             novo->telefone = telefone;
//             novo->seguinte = inicio;
//             return novo;
//         }
//     }
//     else
//     {
//         return inicio;
//     }
// }

// //Remover um cliente existente
// Cliente* removercliente(Cliente* inicio, int NIF) 
// {
//     Cliente *anterior = NULL, *atual = inicio, *aux;

//     while (atual != NULL && atual->NIF != NIF) {
//         anterior = atual;
//         atual = atual->seguinte;
//     }

//     if (atual == NULL) {
//         printf("Cliente com NIF %d nao encontrado.\n", NIF);
//         return inicio;
//     }

//     if (anterior == NULL) {
//         inicio = atual->seguinte;
//     } else {
//         anterior->seguinte = atual->seguinte;
//     }

//     free(atual);
//     printf("Cliente com NIF %d removido com sucesso.\n", NIF);
//     return inicio;
// }
