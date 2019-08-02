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
    fseek(arquivo, 2, SEEK_CUR); // Vai para o começo da 'matriz' de pixels
    for (int y = 0; y < alt; y++)
        for (int x = 0; x < lar; x++)
        {
            int ch = fgetc(arquivo);

            if (ch == EOF) { // Encerra leitura se acabou os caracteres
                fclose(arquivo);
                c(14); printf("A arquivo (%dx%d) possui %d pixels nao-preenchidos (%d/%d), a partir de (x%d, y%d). Eles aparecerao em preto.", img.lar, img.alt, (img.lar * img.alt) - (y * img.lar + x), y * img.lar + x, img.lar * img.alt, x, y);
                _getch();
                return img;
            }

            // Ignora quebra de linha
            while (ch == '\n')
                ch = fgetc(arquivo);

            if (ch == EOF) { // Encerra leitura se acabou os caracteres
                fclose(arquivo);
                c(14); printf("A arquivo (%dx%d) possui %d pixels nao-preenchidos (%d/%d), a partir de (x%d, y%d). Eles aparecerao em preto.", img.lar, img.alt, (img.lar * img.alt) - (y * img.lar + x), y * img.lar + x, img.lar * img.alt, x, y);
                _getch();
                return img;
            }
            
            if (ch == ' ')
                img.pixels[y][x] = ' ';     // Marca como pixel transparente
            else if (ch < 58)
                img.pixels[y][x] = ch - 48; // Converte do int (48-57) = char ('0'-'9') para int (48-57)-48 = cores (0-9)
            else
                img.pixels[y][x] = ch - 55; // Converte do int (65-70)+55 = char ('A'-'F') para int (65-70) - 55 = cores (10-16)
        }
    

    if (fgetc(arquivo) != EOF) {
        c(14); printf("O arquivo possui mais pixels do que sua resolucao suporta (%dx%d). Eles serao ignorados.", img.lar, img.alt);
    }

    fclose(arquivo);
    return img;
}

void salvarColorir438(Imagem img, char *caminho)
{
}
