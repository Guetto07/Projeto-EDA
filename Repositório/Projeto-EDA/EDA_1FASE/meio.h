#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registo
{int codigo; // código do meio de mobilidade 
 char tipo[50]; //tipo do meio de mobilidade
 float preco;
 float velocidade;
 float bateria; 
 float autonomia;
 char geocodigo[50];
 struct registo *seguinte;
}Meio;

typedef struct pagar {
    float saldo;
    float valor;
    struct pagar* seguinte;
}carteira;

Meio *listarmeiosportipo(Meio* inicio, const char* tipo); //Faz a lista de meios por tipo de meios
void listarmeios(Meio * inicio); //Percorre a lista de meios de mobilidade e imprime as suas informações
int existemeio(Meio* inicio, int codigo); //Confirma se o meio já existe de acordo com o codigo
int guardarmeio(Meio* inicio); //Guarda o meio escrito pelo utilizador num ficheiro de texto
Meio *inserirmeio(Meio *inicio, int codigo, char tipo[], float preco, float velocidade, float bateria, float autonomia, char geocodigo[]); //Inserir um novo meio de mobilidade
Meio* removermeio(Meio* inicio, int codigo); //Remover um meio de mobilidade já existente
void lermeios(); 
void alugarmeio(Meio *inicio, carteira *carteira, int codigo);