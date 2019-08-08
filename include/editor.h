#ifndef EDITOR_H
#define EDITOR_H

#include "../include/imagem.h"
#include <stdio.h>
#include <conio.h>

// Exibe uma lista de comandos e suas descrições
void exibirComandos();

// Troca o valor de uma posição na matriz de pixels da img
void pintarPixel(Imagem * img);

// Troca valores de pixels da img formando uma linha
void pintarLinha(Imagem * img);

#endif