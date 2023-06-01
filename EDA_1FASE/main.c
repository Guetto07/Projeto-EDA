#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meio.h"
#include "utilizador.h"

Meio *meios = NULL; // Lista ligada vaziaaa
    int codigo;
    float preco, velocidade, bateria, autonomia;
    char tipo[50], geocodigo[50];

Cliente *clientes = NULL; // Lista ligada vazia
    char nome[100], morada[100], cidade[50], email[100];
    int idade, NIF, telefone;

carteira *dinheiros = NULL; // Lista ligada vazia
void cliente() {
    int opcao;
    do{
    printf("MENU CLIENTE\n");
    printf("1.Alugar Meios\n");
    printf("2.Listar Meios\n");
    printf("3.Localizacao de Meios\n");
    printf("0.Sair\n");
    printf("Opcao:\n");
    scanf("%d", &opcao);
    
    switch (opcao) {
        case 1:
            meios = alugarmeio(meios, dinheiros);
            break;
        case 2:
            listarmeios(meios);
            break;
        case 3:
            // printf("Localizacao\n");
            // scanf("%d", &codigo);
            break;
        default:
            printf("Opção inválida.\n");
    }
}while (opcao != 0);

}

void gestor() {

    int opcao;
    do{
    printf("MENU GESTOR\n");
    printf("1.Inserir Meio\n");
    printf("2.Remover Meio\n");
    printf("3.Listar Meios\n");
    printf("4.Inserir Cliente\n");
    printf("5.Remover Cliente\n");
    printf("0.Sair\n");
    printf("Opcao:\n");
    scanf("%d", &opcao);
    
    switch (opcao) {
        case 1:
            printf("Informe o codigo do meio de mobilidade: \n");
            scanf("%d", &codigo);
            printf("Informe o tipo do meio de mobilidade: \n");
            scanf("%s", tipo);
            printf("Informe o preco em euros do meio de mobilidade: \n");
            scanf("%f", &preco);
            printf("Informe a velocidade maxima do meio de mobilidade: \n");
            scanf("%f", &velocidade);
            printf("Informe a autonomia do meio de mobilidade em km: \n");
            scanf("%f", &autonomia);
            printf("Informe a capacidade da bateria do meio de mobilidade em kWh: \n");
            scanf("%f", &bateria);
            printf("Informe o geocodigo do meio de mobilidade: \n");
            scanf("%s", geocodigo);
            meios = inserirmeio(codigo, tipo, preco, velocidade, bateria, autonomia, geocodigo);
            // guardarmeio(meios);
            break;
        case 2:
            printf("Codigo do meio de mobilidade a remover?\n");
            scanf("%d", &codigo);
            // meios = removermeio(meios, codigo);
            break;
        case 3:
            listarmeios(meios);
            break;
        case 4:
            printf("Nome Completo: \n");
            scanf("%s", nome);
            printf("Idade: \n");
            scanf("%d", &idade);
            printf("NIF: \n");
            scanf("%d", &NIF);
            printf("Numero de telefone: \n");
            scanf("%d", &telefone);
            printf("Email: \n");
            scanf("%s", email);
            printf("Em que cidade resides: \n");
            scanf("%s", cidade);
            printf("Morada: \n");
            scanf("%s", morada);
            // clientes = inserirclientes(clientes, nome, idade, NIF, telefone, email, cidade, morada);
            // guardarclientes(clientes);
            break;
        case 5:
            printf("NIF do cliente que quer remover: \n");
            scanf("%d", &NIF);
            // removercliente(clientes, NIF);
            break;
        default:
            printf("Opção inválida.\n");
    }
}while (opcao != 0);

}

int main() {
    int escolha;
    printf("MENU INICIAL\n");
    printf("1.Cliente\n");
    printf("2.Gestor\n");
    printf("0.Sair\n");
    printf("Opcao:\n");
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            cliente();
            break;
        case 2:
            gestor(); 
            break;
        case 0:
            printf("A sair...");
        default:
            printf("Opção inválida.\n");
    }
    
    return 0;
}
