#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int ultimoC; // Guarda a última cor utilizada em c()
int ultimoB; // Guarda a última cor utilizada em b()

void c(int cor); // Troca a cor do caractere
void b(int cor); // Troca a cor de fundo do caractere

typedef struct imagem_t
{
    int alt; // Altura
    int lar; // Largura
    int **pixels;
} Imagem;

// Atribui alt e lar à nova Imagem e aloca memória para os pixels
Imagem imagem(int alt, int lar);

// Limpa a tela e escreve os pixels na tela com ou sem a régua guia
void desenharImagem(Imagem img, int desenharRegua);

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

void liberarImagem(Imagem *img);
