#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meio.h"

//Faz a lista de meios por tipo de meios
Meio *listarmeiosportipo(Meio* inicio, const char* tipo)
{
    while (inicio != NULL)
    {
        if (strcmp(inicio->tipo, tipo) == 0)
        {
            printf("%d %s %f %f %f %f %s\n", inicio->codigo, inicio->tipo, inicio->preco, inicio->velocidade, inicio->autonomia, inicio->bateria, inicio->geocodigo);
        }
        inicio = inicio->seguinte;
    }
}

void lermeios()
{
    FILE* fp;
    fp = fopen("meios.txt", "r"); // Modo de leitura
    if (fp != NULL)
    {
        int codigo;
        char tipo[100];
        float preco, velocidade, autonomia, bateria;
        char geocodigo[100];

        while (fscanf(fp, "%d %99s %f %f %f %f %99s", &codigo, tipo, &preco, &velocidade, &autonomia, &bateria, geocodigo) == 7)
        {
            Meio *meios = inserirmeio(meios, codigo, tipo, preco, velocidade, bateria, autonomia, geocodigo);
        }

        fclose(fp);
    }
    else
    {
        printf("Erro ao abrir o arquivo.\n");
    }
}

//Percorre a lista de meios de mobilidade e imprime as suas informações
void listarmeios(Meio * inicio)
{
    lermeios();
while (inicio != NULL)
 {printf("%d %s %f %f %f %f %s\n",inicio->codigo, inicio->tipo, inicio->preco, inicio->velocidade, inicio->autonomia, inicio->bateria, inicio->geocodigo);
  inicio = inicio->seguinte;
 }
}

//Confirma se o meio já existe de acordo com o codigo
int existemeio(Meio* inicio, int codigo)
{while(inicio!=NULL)
  {if (inicio->codigo == codigo) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

//Guarda o meio escrito pelo utilizador num ficheiro de texto
int guardarmeio(Meio* inicio)
{FILE* fp;
 fp = fopen("meios.txt","a"); 
 if (fp!=NULL)
 {
 Meio* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d;%s;%f;%f;%f;%f;%s\n", aux->codigo, aux->tipo, aux->preco, aux->velocidade, aux->autonomia, aux->bateria, aux->geocodigo);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

//Inserir um novo meio de mobilidade
Meio *inserirmeio(Meio *inicio, int codigo, char tipo[], float preco, float velocidade, float bateria, float autonomia, char geocodigo[])
{
 if (!existemeio(inicio, codigo)) //Confirma a existencia de um meio de mobilidade com o mesmo codigo já inserido na lista
 {Meio *novo = malloc(sizeof(struct registo)); //Criado um novo nó e determinado o tamanho da alocação
  if (novo != NULL)
  //Os dados são inseridos na estrutura "novo"
  {novo->codigo = codigo;
   strcpy(novo->tipo,tipo);
   novo->preco = preco;
   novo->velocidade = velocidade;
   novo->bateria = bateria;
   novo->autonomia = autonomia;
   strcpy(novo->geocodigo,geocodigo);
   novo->seguinte = inicio; //Ligação entre o novo nó e o resto da lista
   return(novo);
  }
 } else return(inicio);
}   

//Remover um meio de mobilidade já existente
Meio* removermeio(Meio* inicio, int codigo) 
{
 Meio *anterior=inicio, *atual=inicio, *aux; //declarados 3 ponteiros representando o inicio da lista

 if (atual==NULL) 
    return(NULL); //verifica se a lista está vazia
 else if (atual->codigo == codigo) // Remove o meio de mobilidade com o codigo especificado
 {aux = atual->seguinte;
  free(atual); //libera a memória alocada para o nó que está a ser removido
  return(aux);
 }
 //Remoção do meio de mobilidade, se o mesmo nao for o primeiro da lista
 else
 {while ((atual!=NULL)&&(atual->codigo!=codigo)) 
  {anterior = atual;
   atual = atual->seguinte; //Pula o nó atual e passa para o nó seguinte
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}

void alugarmeio(Meio *inicio, carteira *carteira, int codigo) {
    Meio *meio = inicio;

    while (meio != NULL) {
        if (meio->codigo == codigo) {
            if (carteira->saldo < meio->preco) {
                printf("Saldo insuficiente para alugar o meio de mobilidade.\n");
                return;
            }

            // Subtrair o valor do meio de mobilidade do saldo da carteira
            carteira->saldo -= meio->preco;

            printf("Meio de mobilidade alugado com sucesso!\n");
            return;
        }

        meio = meio->seguinte;
    }

    printf("Meio de mobilidade não encontrado.\n");
}
