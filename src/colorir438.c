#include "../include/colorir438.h"
#include "../include/imagem.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

Imagem lerColorir438(FILE *arquivo)
{
    // Lê as dimensoes da imagem
    int alt, lar;
    fseek(arquivo, 11, SEEK_SET); // Pula para depois do "Colorir438 "
    fscanf(arquivo, "%d %d", &lar, &alt);

    Imagem img = criarImagem(alt, lar);

    // Lê os valores dos pixels
    fseek(arquivo, 2, SEEK_CUR);
    for (int i = 0; i < alt; i++)
        for (int j = 0; j < lar; j++)
        {
            int ch = fgetc(arquivo);
            if (ch == '\n')
                ch = fgetc(arquivo);
            if (ch < 58)
                img.pixels[i][j] = ch - 48; // Converte do int (48-57) = char ('0'-'9') para int (48-57)-48 = cores (0-9)
            else
                img.pixels[i][j] = ch - 55; // Converte do int (65-70)+55 = char ('A'-'F') para int (65-70) - 55 = cores (10-16)
        }
    fclose(arquivo);

    return img;
}

void salvarColorir438(Imagem img, char *caminho)
{
}
