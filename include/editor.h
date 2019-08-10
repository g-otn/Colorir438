#ifndef EDITOR_H
#define EDITOR_H

#include "entrada.h"
#include "imagem.h"
#include <stdio.h>
#include <ctype.h>
#include <conio.h>

// Lê uma cor ([0-9]|[a-f]|[A-F]|-)
char lerCor(void);

// Exibe uma lista de comandos e suas descrições
void exibirComandos(void);

// Altera a cor de fundo da imagem (img.bg)
void alterarCorDeFundo(Imagem * img);

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
