#include "../include/imagem.h"
#include "../include/colorir438.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Imagem criarImagem(int alt, int lar, int bg)
{
    Imagem img;

    img.alt = alt;
    img.lar = lar;
    img.bg = bg;
    img.pixels = (int **)malloc(alt * sizeof(int *));
    for (int y = 0; y < alt; y++) {
        img.pixels[y] = (int *)malloc(lar * sizeof(int));
        for (int x = 0; x < lar; x++)
            img.pixels[y][x] = ' ';
    }

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
                b(0);
            }
            else
            {
                if (x == 0 && y > 0 && !desenharRegua)
                    printf("\n"); // Pula linha caso não entre no if de desenhar a régua onde a linha é pulada, pois o desenharRegua == 0

                // Desenhando imagem (0, 0) até (img.lar, img.alt)
                if (img.pixels[y][x] == ' ') // Transparente
                    if (desenharRegua) // Editando
                    {
                        c(img.bg == '-' ? 0 : (img.bg < 58 ? img.bg - 48 : img.bg - 55)); // Transforma '0'-'9' em 0-9 e 'A'-'F' em 10-15
                        printf("[]"); // Visível na edição
                    } 
                    else
                        printf("  "); // Invisível na visualização
                else                         // Cor
                {
                    c(img.pixels[y][x]);
                    printf("%c%c", 219, 219);
                }
            }
        }
    }
    printf("\n");
}

Imagem alterarResolucao(Imagem img, Alteracao alteracao, Direcao direcao)
{
    // Restrição para imagens não ficarem menores que 1x1
    if (alteracao == DIMINUIR)
        if ((img.alt == 1 && direcao == VERTICAL) || (img.lar == 1 && direcao == HORIZONTAL))
            return img;

    Imagem novaImg;

    // Copia os pixels de img para novaImg, que possui alt/lar diferente(s))
    if (direcao == VERTICAL)
    {
        novaImg = criarImagem(img.alt + alteracao, img.lar, img.bg);

        int menorAlt = alteracao == DIMINUIR ? novaImg.alt : img.alt;
        for (int y = 0; y < menorAlt; y++)
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            // Preenche a linha adicionada
            for (int x = 0; x < novaImg.lar; x++)
                novaImg.pixels[novaImg.alt - 1][x] = ' ';
    }
    else // Horizontal
    {
        novaImg = criarImagem(img.alt, img.lar + alteracao, img.bg);

        int menorLar = alteracao == DIMINUIR ? novaImg.lar : img.lar;
        for (int y = 0; y < novaImg.alt; y++)
            for (int x = 0; x < menorLar; x++)
                novaImg.pixels[y][x] = img.pixels[y][x];
        if (alteracao == AUMENTAR)
            // Preenche a coluna adicionada
            for (int y = 0; y < novaImg.alt; y++)
                novaImg.pixels[y][novaImg.lar - 1] = ' ';
    }

    liberarImagem(&img);
    return novaImg;
}

void liberarImagem(Imagem *img)
{
    for (int y = 0; y < img->alt; y++)
        free(img->pixels[y]);
    free(img->pixels);
    img->pixels = NULL;
}

Imagem lerImagem(char *caminhoArquivo)
{
    // Tenta abrir o arquivo
	FILE *arquivo = fopen(caminhoArquivo, "r");

	// Checagem de arquivo indisponível
	if (!arquivo)
    {
        c(12); printf("N\xC6o foi possivel abrir o arquivo em \"");
        c(3); printf("%s", caminhoArquivo); c(12); printf("\".");
        _getch();
		return criarImagem(0, 0, '-');
	}
	// Checagem de arquivo vazio
	fseek(arquivo, 0, SEEK_END);
	if (ftell(arquivo) == 0)
    {
		c(12); printf("O arquivo em \""); c(3); printf("%s", caminhoArquivo); c(12); printf("\" est\xA0 vazio!");
		_getch();
		return criarImagem(0, 0, '-');
	}

	// Filtrador de tipo de arquivo (.bmp ou .Colorir438)
	rewind(arquivo);
	char filtro[11];
	fgets(filtro, sizeof filtro, arquivo); // Guarda os 10 primeiros chars do arquivo
	if (strcmp(filtro, "Colorir438") == 0)
    {
		return lerColorir438(arquivo); // ler como .Colorir438
	} 
    // else if (strstr(filtro, "BM") != NULL)
    // {
	// 	filtro[2] = '\0'; // Faz com que o filtro como %s seja só os primeiros 2 bytes ("BM")
	// 	printf("Formato identificado: .bmp ("); c(2); printf("%s", filtro); c(7); printf(")");
	// 	//return lerBmp(arquivo); // ler como .bmp
	// } 
    else
    {
		c(12); printf("O arquivo em \""); c(3); printf("%s", caminhoArquivo); c(12); printf("\" n\xC6o esta em um formato suportado.");
        return criarImagem(0, 0, '-');
	}
}
