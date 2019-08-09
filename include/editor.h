#ifndef EDITOR_H
#define EDITOR_H

#include "entrada.h"
#include "imagem.h"
#include <stdio.h>
#include <conio.h>

// Exibe uma lista de comandos e suas descrições
void exibirComandos(void);

// Troca o valor de uma posição na matriz de pixels da img
void pintarPixel(Imagem * img);

// Troca valores de pixels da img formando uma linha
void pintarLinha(Imagem * img);

typedef enum direcao_t
{
    HORIZONTAL,
    VERTICAL
} Direcao;

typedef enum alteracao_t
{
    AUMENTAR = 1,
    DIMINUIR = -1
} Alteracao;

// Copia os valores de img.pixels para uma nova Imagem com tamanho diferente em uma dimensão
Imagem alterarResolucao(Imagem img, Alteracao alteracao, Direcao direcao);

#endif
