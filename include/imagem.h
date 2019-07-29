#include <stdlib.h>

typedef struct colorir438_t
{
    unsigned int alt; // Altura
    unsigned int lar; // Largura
    int **pixels;
} Colorir438;

Colorir438 colorir438(int alt, int lar);

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

Colorir438 alterarResolucao(Colorir438 img, Alteracao alteracao, Direcao direcao);