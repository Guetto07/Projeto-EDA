#include <stdio.h>

typedef struct clientes
{
    char nome[100], morada[100], cidade[50], email[50];
    int idade, NIF, telefone;
    struct clientes *seguinte;
}Cliente;

// int guardarclientes(Cliente *inicio); //Guarda clientes no ficheiro de texto 
// int existecliente(Cliente* inicio, int NIF); //Confirma se o cliente já existe de acordo com o NIF
// Cliente *removercliente(Cliente* inicio, int nif); //Remover um cliente existente
// Cliente *inserirclientes(Cliente* inicio, char nome[], int idade, int NIF, int telefone, char email[], char cidade[], char morada[]); //Inserir um novo cliente