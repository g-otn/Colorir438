#include "../include/imagem.h"
#include <stdlib.h>

Imagem imagem(int alt, int lar)
{
    Imagem img;

    img.alt = alt;
    img.lar = lar;
    img.pixels = (int **)malloc(alt * sizeof(int *));
    for (int y = 0; y < alt; y++)
        img.pixels[y] = (int *)malloc(lar * sizeof(int));

    return img;
}

Imagem alterarResolucao(Imagem img, Alteracao alteracao, Direcao direcao)
{
    Imagem novaImg;

    if (direcao == VERTICAL)
    {
        novaImg = imagem(img.alt + alteracao, img.lar);

        int menorAlt = alteracao == DIMINUIR ? novaImg.alt : img.alt;
        for (int y = 0; y < menorAlt; y++)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[novaImg.alt - 1][x] = 15;
    }
    else
    {
        novaImg = imagem(img.alt, img.lar + alteracao);

        int menorLar = alteracao == DIMINUIR ? novaImg.lar : img.lar;
        for (int y = 0; y < novaImg.alt; y++)
            for (int x = 0; x < menorLar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            for (int y = 0; y < novaImg.lar; y++)
                novaImg.pixels[y][novaImg.lar - 1] = 15;
    }

    return novaImg;
}