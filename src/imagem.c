#include "../include/imagem.h"

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
        _textcolor(15);
        ultimoC = 15;
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
                if (!desenharRegua && x == 0 && y > 0)
                    printf("\n"); // Pula linha caso não entre no if de desenhar a régua onde a linha é pulada, pois o desenharRegua == 0

                // Desenhando imagem (0, 0) até (img.lar, img.alt)
                if (img.pixels[y][x] == ' ') // Transparente
                    if (desenharRegua) // Editando
                    {
                        if (img.bg == '-')
                            printf("  ");
                        else
                        {
                            c(img.bg < 58 ? img.bg - 48 : img.bg - 55); // '0'-'9' -> 0-9, 'A'-'F' -> 10-15
                            printf("[]"); // Visível na edição
                        }
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

void liberarImagem(Imagem *img)
{
    for (int y = 0; y < img->alt; y++)
        free(img->pixels[y]);
    free(img->pixels);
    img->pixels = NULL;
}

const int RED[16] = { 0,   0,   0,   0, 128, 128, 128, 192, 128,   0,   0,   0, 255, 255, 255, 255 };
const int GREEN[16] = { 0,   0, 128, 128,   0,   0, 128, 192, 128,   0, 255, 255,   0,   0, 255, 255 };
const int BLUE[16] = { 0, 128,   0, 128,   0, 128,   0, 192, 128, 255,   0, 255,   0, 255,   0, 255 };

int RGBparaCorCMD(unsigned char red, unsigned char green, unsigned char blue)
{
    int menorCor = -1;
    unsigned char menorDiferenca = 255;
    
    for (int cor = 0; cor < 16; cor++)
    {
        int diferenca = abs(RED[cor] - red) + abs(GREEN[cor] - green) + abs(BLUE[cor] - blue);
        if (diferenca < menorDiferenca)
        {
            menorCor = cor;
            menorDiferenca = diferenca;
        }
    }

    return menorCor;
}

Imagem lerBitmap(Bitmap *bm)
{
    Imagem img = criarImagem(bm_height(bm), bm_width(bm), '-');
    unsigned char red, green, blue;

    // Lê pixels e os atribui na imagem
    for (int y = 0; y < img.alt; y++)
        for (int x = 0; x < img.lar; x++)
        {
            bm_get_rgb(bm_get(bm, x, y), &red, &green, &blue);
            img.pixels[y][x] = RGBparaCorCMD(red, green, blue);
        }

    return img;
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

	// Lê como .c438
	rewind(arquivo);
	char filtro[11];
	fgets(filtro, sizeof filtro, arquivo);
	if (strcmp(filtro, "Colorir438") == 0)
		return lerColorir438(arquivo);      
    
    // Lê como .bmp
    rewind(arquivo);
    Bitmap *bm = bm_load_fp(arquivo);
    if (bm)
		return lerBitmap(bm);
    
    // Arquivo não reconehcido
    c(12); printf("O arquivo em \""); c(3); printf("%s", caminhoArquivo); c(12); printf("\" n\xC6o esta em um formato suportado.");
    return criarImagem(0, 0, '-');
}
