#include "../include/colorir438.h"

Imagem lerColorir438(FILE *arquivo)
{
    int alt = 0, lar = 0, bg;
    
    fseek(arquivo, 11, SEEK_SET); // Pula para depois do "Colorir438 "
    
    Imagem img;
    if (fscanf(arquivo, "%d %d %[0123456789ABCDEFG-]", &lar, &alt, &bg) < 3 || alt < 1 || lar < 1) {
        c(12); printf("O Colorir438 possui valores inv\xA0lidos.");
        _getch();
        img = criarImagem(0, 0, '-');
    } else
        img = criarImagem(alt, lar, bg);

    // Lê os valores dos pixels
    fseek(arquivo, 2, SEEK_CUR); // Vai para o começo da 'matriz' de pixels
    for (int y = 0; y < alt; y++)
        for (int x = 0; x < lar; x++)
        {
            int ch = fgetc(arquivo);

            if (ch == EOF) { // Encerra leitura se acabou os caracteres
                fclose(arquivo);
                c(14); printf("O Colorir438 (%dx%d) possui %d pixels n\xC6o preenchidos (%d/%d), a partir de (x%d, y%d). Eles aparecer\xC6o em preto.", img.lar, img.alt, (img.lar * img.alt) - (y * img.lar + x), y * img.lar + x, img.lar * img.alt, x, y);
                _getch();
                return img;
            }

            // Ignora quebra de linha
            while (ch == '\n')
                ch = fgetc(arquivo);

            if (ch == EOF) { // Encerra leitura se acabou os caracteres
                fclose(arquivo);
                c(14); printf("O Colorir438 (%dx%d) possui %d pixels n\xC6o preenchidos (%d/%d), a partir de (x%d, y%d). Eles aparecer\xC6o em preto.", img.lar, img.alt, (img.lar * img.alt) - (y * img.lar + x), y * img.lar + x, img.lar * img.alt, x, y);
                _getch();
                return img;
            }
            
            if (ch == ' ')
                img.pixels[y][x] = ' ';     // Marca como pixel transparente
            else if (ch < 58)
                img.pixels[y][x] = ch - 48; // Converte do int (48-57) = char ('0'-'9') para int (48-57)-48 = cores (0-9)
            else
                img.pixels[y][x] = ch - 55; // Converte do int (65-70) = char ('A'-'F') para int (65-70) - 55 = cores (10-16)
        }
    

    if (fgetc(arquivo) != EOF) {
        c(14); printf("O Colorir438 possui mais pixels do que sua resolu\x87\xC6o suporta (%dx%d). Eles n\xC6o ser\xC6o exibidos.", img.lar, img.alt);
        _getch();
    }
    
    fclose(arquivo);
    return img;
}

void salvarColorir438(Imagem img, char *caminho)
{
}
