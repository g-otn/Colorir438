#include <stdlib.h>

typedef struct imagem_t
{
    unsigned int alt; // Altura
    unsigned int lar; // Largura
    int **pixels;
} Imagem;

Imagem imagem(int alt, int lar);

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

Imagem alterarResolucao(Imagem img, Alteracao alteracao, Direcao direcao);