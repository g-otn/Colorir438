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

void exibirComandos(void)
{
	c(5);  printf("\t\t    --== "); c(11); printf("Lista de Comandos"); c(5); printf(" ==--\t\t");
	c(5);  printf("\n  Ferramentas");
    c(11); printf("\n  [p]"); c(10); printf(" Ponto"); c(7); printf(": Pinta um pixel");
	c(11); printf("\n  [l]"); c(10); printf(" Linha"); c(7); printf(": Desenha uma linha na imagem");
    c(11); printf("\n  [f]"); c(10); printf(" Fundo"); c(7); printf(": Altera a cor de fundo da imagem");
    c(11); printf("\n  [teclas de seta]"); c(10); printf(" Alterar tamanho"); c(7); printf(": Altera a altura e a largura da imagem\n");

    c(5);  printf("\n  Arquivo");
    c(11); printf("\n  [v]"); c(10); printf(" Visualizar"); c(7); printf(": Desenha a imagem sem as r\x82guas esquerda e superior");
	
    c(11); printf("\n\n  [s]"); c(10); printf(" Sair"); c(7); printf(": Sai do editor e retorna ao menu\n");

}

void pintarPixel(Imagem * img)
{
    char cor = lerCor();
    int x, y;
    
    // Lê as coordenadas do pixel
    char coordenadas[10];
    while (1)
    {
        do 
        {
            c(7); printf("Digite a coordenada do pixel, separada por espa\x87o (Ex: x5 y9: \""); c(3); printf("5 9"); c(7); printf("\"): ");
            lerEntrada(coordenadas, 10);
        } while (sscanf(coordenadas, "%d %d\n", &x, &y) < 2);
        if (x < 0 || x > img->lar || y < 0 || y > img->lar)
        {
			c(12); printf("Digite um valor X de "); c(3); printf("0 a %d", img->lar - 1); c(12); printf(" e um valor Y de "); c(3); printf("0 a %d", img->alt - 1); c(12); printf(".\n");
        } else
            break;
    }

    img->pixels[y][x] = cor == '-' ? ' ' : cor;
}

void pintarLinha(Imagem * img)
{
    
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
