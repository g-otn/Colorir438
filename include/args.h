#ifndef ARGS_H
#define ARGS_H

#include "imagem.h"
#include "colorir438.h"

// Utilizado para voltar ao menu
extern void mostrarMenu(void);

// Analisa os argumentos para abrir o editor, ler arquivos e/ou desenhar imagens
void analisarArgumentos(int argc, char **argv);

#endif

