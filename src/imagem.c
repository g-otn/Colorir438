#include "../include/imagem.h"
#include <stdlib.h>

Colorir438 colorir438(int alt, int lar)
{
    Colorir438 img;

    img.alt = alt;
    img.lar = lar;
    img.pixels = (int **)malloc(alt * sizeof(int *));
    for (int y = 0; y < alt; y++)
        img.pixels[y] = (int *)malloc(lar * sizeof(int));

    return img;
}

// Copia a matriz img
Colorir438 alterarResolucao(Colorir438 img, Alteracao alteracao, Direcao direcao)
{
    Colorir438 novaImg;

    if (direcao == VERTICAL)
    {
        novaImg = colorir438(img.alt + alteracao, img.lar);

        int menorAlt = alteracao == DIMINUIR ? novaImg.alt : img.alt;
        for (int y = 0; y < menorAlt; y++)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        for (int x = 0; x < novaImg.lar; x++)
            novaImg.pixels[novaImg.alt - 1][x] = 15;
    }
    else
    {
        novaImg = colorir438(img.alt, img.lar + alteracao);

        int menorLar = alteracao == DIMINUIR ? novaImg.lar : img.lar;
        for (int y = 0; y < novaImg.alt; y++)
            for (int x = 0; x < menorLar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        for (int y = 0; y < novaImg.lar; y++)
            novaImg.pixels[y][novaImg.lar - 1] = 15;
    }

    return novaImg;
}