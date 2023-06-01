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

Meio *inserirmeio(int codigo, const char* tipo, float preco, float velocidade, float autonomia, float bateria, const char* geocodigo);
void listarmeios();
Meio *alugarmeio(Meio *meios, carteira *dinheiros);
void removerMeioPorCodigo(int codigo);