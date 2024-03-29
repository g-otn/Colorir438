#ifndef IMAGEM_H
#define IMAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "bmp.h"

typedef struct imagem_t
{
    int alt; // Altura
    int lar; // Largura
    int bg;  // Cor de fundo
    int **pixels;
} Imagem;

int ultimoC; // Guarda a última cor utilizada em c()
int ultimoB; // Guarda a última cor utilizada em b()

void c(int cor); // Troca a cor do caractere
void b(int cor); // Troca a cor de fundo do caractere

#include "colorir438.h"

// Atribui os parâmetros à nova Imagem e aloca memória para os pixels
Imagem criarImagem(int alt, int lar, int bg);

// Limpa a tela e escreve os pixels na tela com ou sem a régua guia
void desenharImagem(Imagem img, int desenharRegua);

// Libera a memória alocada para os pixels
void liberarImagem(Imagem *img);

// Representam o valor RGB de cada uma das 16 cores do cmd.
const int R[16], G[16], B[16];

// Converte um valor RGB para uma das 16 cores do cmd.
int RGBparaCorCMD(unsigned char r, unsigned char g, unsigned char b);

// Lê os pixels de arquivos compatíveis com bmp.h e os retorna em uma Imagem
Imagem lerBitmap(Bitmap *bm);

// Identifica o tipo de arquivo (.c438 ou .bmp) e retorna a Imagem lida do arquivo
Imagem lerImagem(char *caminhoArquivo);

#endif
