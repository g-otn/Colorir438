#include "../include/editor.h"

char lerCor(void)
{
    // Exibe as cores disponíveis
    printf("Escolha uma cor: ");
    for (int i = 0; i < 16; i++) {
        if (i == 7)
            c(0);
        b(i); printf(" %c ", i < 10 ? i + 48 : i + 55); b(0); printf(" ");
    }
    c(8); printf("["); c(11); printf("-"); c(8); printf("]");
    printf("\n");

    // Lê a cor escolhida
    int cor;
    do 
    {
        cor = toupper(_getch());
    } while (!isdigit(cor) && (cor < 65 || cor > 70) && cor != '-'); // Enquanto não é [0-9]|[A-F]|-

    return cor;
}

void lerCoordenada(int * x, int * y, Imagem * img)
{
    char coordenadas[10];

    do
    {
        do 
        {
            lerEntrada(coordenadas, 10);
        } while (sscanf(coordenadas, "%d %d\n", x, y) < 2);
        if (*y < 0 || *y > img->lar || *y < 0 || *y > img->lar)
        {
			c(12); printf("Digite um valor X de "); c(3); printf("0 a %d", img->lar - 1); c(12); printf(" e um valor Y de "); c(3); printf("0 a %d", img->alt - 1); c(12); printf(".\n");
            c(7);
        } else
            break;
    } while (1);
}

void exibirComandos(void)
{
	c(5);  printf("\t\t    --== "); c(11); printf("Lista de Comandos"); c(5); printf(" ==--\t\t");
	c(5);  printf("\n  Ferramentas");
    c(11); printf("\n  [P]"); c(10); printf(" Ponto"); c(7); printf(": Pinta um pixel");
	c(11); printf("\n  [L]"); c(10); printf(" Linha"); c(7); printf(": Desenha uma linha na imagem");
    c(11); printf("\n  [F]"); c(10); printf(" Fundo"); c(7); printf(": Altera a cor de fundo da imagem");
    c(11); printf("\n  [teclas de seta]"); c(10); printf(" Alterar tamanho"); c(7); printf(": Altera a altura e a largura da imagem\n");

    c(5);  printf("\n  Arquivo");
    c(11); printf("\n  [V]"); c(10); printf(" Visualizar"); c(7); printf(": Desenha a imagem sem as r\x82guas esquerda e superior");
	
    c(11); printf("\n\n  [S]"); c(10); printf(" Sair"); c(7); printf(": Sai do editor e retorna ao menu\n");

}

void pintarPixel(Imagem * img)
{
    char cor = lerCor();
    int x, y;
    
    c(7); printf("Digite a coordenada do come\x87o da reta, separada por espa\x87o (Ex: x5 y9: \""); c(3); printf("5 9"); c(7); printf("\"): ");
	lerCoordenada(&x, &y, img);

    img->pixels[y][x] = cor == '-' ? ' ' : cor;
}

void pintarLinha(Imagem * img)
{
    char cor = lerCor();

	int x1, y1;
    c(7); printf("Digite a coordenada do come\x87o da reta, separada por espa\x87o (Ex: x5 y9: \""); c(3); printf("5 9"); c(7); printf("\"): ");    
    lerCoordenada(&x1, &y1, img);

	int x2, y2;
    c(7); printf("Digite a coordenada do final da reta, separada por espa\x87o (Ex: x5 y9: \""); c(3); printf("5 9"); c(7); printf("\"): "); 
    lerCoordenada(&x2, &y2, img);

    // Calcula os valores usados no calculo dos pixels pertencentes a linha
	struct {
		struct {
			int x;
			int y;
		} dist;
		float passo;
	} d; // Dados da Linha

	// Cálcula a distância vertical e horizontal (co, ca)
	d.dist.x = abs(x1 - x2);
	d.dist.y = abs(y1 - y2);

	// Decide por qual eixo iterar (impede d.passo de ser >= 1, pulando pixels (ex: a cada 1x, andar 4y: deixa 3 pixels sem pintar))
	if (d.dist.x <= d.dist.y)
    {
		// Primeiro calculo de d.passo, sem correcao de direcao
		d.passo = (float)d.dist.x / (float)d.dist.y;

		// Correção de direção caso seja da esquerda para a direita
		if (x1 > x2)
			d.passo *= -1;
		
		// Correção de direção caso seja da de baixo para cima
		if (y1 >= y2)
			d.passo *= -1;
		c(6);

		// Pinta os pixels
		float x;
		int y;
		if (y1 < y2)
        {
			x = x1 + 0.5; // Arredondamento para cima (<0.5) e para baixo (>=0.5), já que ex: (int)0.5 = 0; (int)0.9 = 0; então (int)(0.5+0.5) = 1 e (int)(0.9+0.5) = 1
			for (y = y1; y <= y2; y++)
            {
				img->pixels[y][(int)x] = cor;
				x += d.passo;
			}
		} else
        {
			x = x2 + 0.5;
			for (y = y2; y <= y1; y++)
            {
				img->pixels[y][(int)x] = cor;
				x += d.passo;
			}
		}
	} else
    {
		// Primeiro calculo de d.passo, sem correcao de direcao
		d.passo = (float)d.dist.y / (float)d.dist.x;

		// Correção de direção caso seja da de baixo para cima
		if (y1 > y2)
			d.passo *= -1;
		
		// Correção de direção caso seja da esquerda para a direita
		if (x1 >= x2)
            d.passo *= -1;
		c(6);

		// Pinta os pixels
		int x;
		float y;
		if (x1 < x2)
        {
			y = y1 + 0.5;
			for (x = x1; x <= x2; x++)
            {
				img->pixels[(int)y][x] = cor;
				y += d.passo;
			}
		} else
        {
			y = y2 + 0.5;
			for (x = x2; x <= x1; x++)
            {
				img->pixels[(int)y][x] = cor;
				y += d.passo;
			}
		}
	}
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