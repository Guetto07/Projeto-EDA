#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "grafo.h"

void salvarDadosTexto(Grafo* grafo, const char* nomeArquivo);
Grafo* carregarDadosTexto(const char* nomeArquivo);
void salvarDadosBinarios(Grafo* grafo, const char* nomeArquivo);
Grafo* carregarDadosBinarios(const char* nomeArquivo);

#endif  // ARQUIVO_H
