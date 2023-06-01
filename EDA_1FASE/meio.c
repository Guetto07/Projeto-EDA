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

    // Se a lista estiver vazia, insira o novo meio de mobilidade como o primeiro nó
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



// //Faz a lista de meios por tipo de meios
// Meio *listarmeiosportipo(Meio* inicio, const char* tipo)
// {
//     while (inicio != NULL)
//     {
//         if (strcmp(inicio->tipo, tipo) == 0)
//         {
//             printf("%d %s %f %f %f %f %s\n", inicio->codigo, inicio->tipo, inicio->preco, inicio->velocidade, inicio->autonomia, inicio->bateria, inicio->geocodigo);
//         }
//         inicio = inicio->seguinte;
//     }
// }

// void lermeios()
// {
//     FILE* fp;
//     fp = fopen("meios.txt", "r"); // Modo de leitura
//     if (fp != NULL)
//     {
//         int codigo;
//         char tipo[100];
//         float preco, velocidade, autonomia, bateria;
//         char geocodigo[100];

//         while (fscanf(fp, "%d %99s %f %f %f %f %99s", &codigo, tipo, &preco, &velocidade, &autonomia, &bateria, geocodigo) == 7)
//         {
//             Meio *meios = inserirmeio(meios, codigo, tipo, preco, velocidade, bateria, autonomia, geocodigo);
//         }

//         fclose(fp);
//     }
//     else
//     {
//         printf("Erro ao abrir o arquivo.\n");
//     }
// }

// //Percorre a lista de meios de mobilidade e imprime as suas informações
// void listarmeios(Meio * inicio)
// {
//     lermeios();
// while (inicio != NULL)
//  {printf("%d %s %f %f %f %f %s\n",inicio->codigo, inicio->tipo, inicio->preco, inicio->velocidade, inicio->autonomia, inicio->bateria, inicio->geocodigo);
//   inicio = inicio->seguinte;
//  }
// }

// //Confirma se o meio já existe de acordo com o codigo
// int existemeio(Meio* inicio, int codigo)
// {while(inicio!=NULL)
//   {if (inicio->codigo == codigo) return(1);
//    inicio = inicio->seguinte;
//   }
//  return(0);
// }

// //Guarda o meio escrito pelo utilizador num ficheiro de texto
// int guardarmeio(Meio* inicio)
// {FILE* fp;
//  fp = fopen("meios.txt","a"); 
//  if (fp!=NULL)
//  {
//  Meio* aux= inicio;
//  while (aux != NULL)
//  {
//   fprintf(fp,"%d;%s;%f;%f;%f;%f;%s\n", aux->codigo, aux->tipo, aux->preco, aux->velocidade, aux->autonomia, aux->bateria, aux->geocodigo);
//   aux = aux->seguinte;
//  }
//  fclose(fp);
//  return(1);
//  }
//  else return(0);
// }

// //Inserir um novo meio de mobilidade
// Meio *inserirmeio(Meio *inicio, int codigo, char tipo[], float preco, float velocidade, float bateria, float autonomia, char geocodigo[])
// {
//  if (!existemeio(inicio, codigo)) //Confirma a existencia de um meio de mobilidade com o mesmo codigo já inserido na lista
//  {Meio *novo = malloc(sizeof(struct registo)); //Criado um novo nó e determinado o tamanho da alocação
//   if (novo != NULL)
//   //Os dados são inseridos na estrutura "novo"
//   {novo->codigo = codigo;
//    strcpy(novo->tipo,tipo);
//    novo->preco = preco;
//    novo->velocidade = velocidade;
//    novo->bateria = bateria;
//    novo->autonomia = autonomia;
//    strcpy(novo->geocodigo,geocodigo);
//    novo->seguinte = inicio; //Ligação entre o novo nó e o resto da lista
//    return(novo);
//   }
//  } else return(inicio);
// }   

// //Remover um meio de mobilidade já existente
// Meio* removermeio(Meio* inicio, int codigo) 
// {
//  Meio *anterior=inicio, *atual=inicio, *aux; //declarados 3 ponteiros representando o inicio da lista

//  if (atual==NULL) 
//     return(NULL); //verifica se a lista está vazia
//  else if (atual->codigo == codigo) // Remove o meio de mobilidade com o codigo especificado
//  {aux = atual->seguinte;
//   free(atual); //libera a memória alocada para o nó que está a ser removido
//   return(aux);
//  }
//  //Remoção do meio de mobilidade, se o mesmo nao for o primeiro da lista
//  else
//  {while ((atual!=NULL)&&(atual->codigo!=codigo)) 
//   {anterior = atual;
//    atual = atual->seguinte; //Pula o nó atual e passa para o nó seguinte
//   }
//   if (atual==NULL) return(inicio);
//   else
//   {anterior->seguinte = atual->seguinte;
//    free(atual);
//    return(inicio);
//   }
//  }
// }

// void alugarmeio(Meio *inicio, carteira *carteira, int codigo) {
//     Meio *meio = inicio;

//     while (meio != NULL) {
//         if (meio->codigo == codigo) {
//             if (carteira->saldo < meio->preco) {
//                 printf("Saldo insuficiente para alugar o meio de mobilidade.\n");
//                 return;
//             }

//             // Subtrair o valor do meio de mobilidade do saldo da carteira
//             carteira->saldo -= meio->preco;

//             printf("Meio de mobilidade alugado com sucesso!\n");
//             return;
//         }

//         meio = meio->seguinte;
//     }

//     printf("Meio de mobilidade não encontrado.\n");
// }
