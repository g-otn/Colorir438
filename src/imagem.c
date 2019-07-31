#include "../include/imagem.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int ultimoC = -1;
int ultimoB = -1;

void c(int cor)
{
    if (ultimoC != cor)
    {
        ultimoC = cor;
        _textcolor(cor);
    }
}

void b(int cor)
{
    if (ultimoB != cor)
    {
        ultimoB = cor;
        _textbackground(cor);
    }
}

Imagem criarImagem(int alt, int lar)
{
    Imagem img;

    img.alt = alt;
    img.lar = lar;
    img.pixels = (int **)malloc(alt * sizeof(int *));
    for (int y = 0; y < alt; y++)
        img.pixels[y] = (int *)calloc(lar, sizeof(int));

    return img;
}

void desenharImagem(Imagem img, int desenharRegua)
{
    int y, x;
    desenharRegua *= -1; // 0 -> 0 e 1 -> -1, para o x e o y ficarem -1 e a régua ser exibida

    for (y = desenharRegua; y < img.alt; y++)
    {
        c(15);
        for (x = desenharRegua; x < img.lar; x++)
        {
            if (y < 0 && x < 0)
            { // Espaçamento no comeco da "tabela" (-1, -1)
                printf("  ");
            }
            else if (y < 0)
            {                 // Desenhando régua horizontal (0, -1) até (img.lar, -1)
                if (!(x % 2)) // Se o numero na régua horizontal for par
                    b(1 + x / 10 - 2 * (x / 20));
                else
                    b(0);
                printf("%2d", x % 10);
            }
            else if (x < 0)
            {                 // Desenhando régua vertical (-1, 0) até (-1, img.alt)
                if (!(y % 2)) // Se o numero na régua vertical for par
                    b(1 + y / 10 - 2 * (y / 20));
                else
                    b(0);
                printf("\n%2d", y % 100);
            }
            else
            {
                if (x == 0 && y > 0 && !desenharRegua)
                    printf("\n"); // Pula linha caso não entre no if de desenhar a régua onde a linha é pulada, pois o desenharRegua == 0

                // Desenhando imagem (0, 0) até (img.lar, img.alt)
                b(0);
                c(img.pixels[y][x]);
                printf("%c%c", 219, 219);
            }
        }
    }
    printf("\n");
}

Imagem alterarResolucao(Imagem img, Alteracao alteracao, Direcao direcao)
{
    Imagem novaImg;

    if (direcao == VERTICAL)
    {
        novaImg = criarImagem(img.alt + alteracao, img.lar);

        int menorAlt = alteracao == DIMINUIR ? novaImg.alt : img.alt;
        for (int y = 0; y < menorAlt; y++)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[novaImg.alt - 1][x] = 15;
    }
    else // Horizontal
    {
        novaImg = criarImagem(img.alt, img.lar + alteracao);

        int menorLar = alteracao == DIMINUIR ? novaImg.lar : img.lar;
        for (int y = 0; y < novaImg.alt; y++)
            for (int x = 0; x < menorLar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            for (int y = 0; y < novaImg.alt; y++)
                novaImg.pixels[y][novaImg.lar - 1] = 15;
    }

    return novaImg;
}

void liberarImagem(Imagem *img)
{
    for (int y = 0; y < img->alt; y++)
        free(img->pixels[y]);
    free(img->pixels);
    img->pixels = NULL;
}
