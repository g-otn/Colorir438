#ifndef COLORIR438_H
#define COLORIR438_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "imagem.h"

Imagem lerColorir438(FILE *arquivo);

void salvarColorir438(Imagem img, char* caminho);

#endif
