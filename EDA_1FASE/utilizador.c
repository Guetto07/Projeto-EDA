// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "utilizador.h"
// #include "meio.h"

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
