#include "../include/editor.h"

void exibirComandos() {
	c(5); printf("\t\t    --== "); c(11); printf("Lista de Comandos"); c(5); printf(" ==--\t\t");
	c(11); printf("\n  [p]"); c(10); printf(" Ponto"); c(7); printf(": Pinta um pixel nas coordenadas especificadas");
	c(11); printf("\n  [l]"); c(10); printf(" Linha"); c(7); printf(": Desenha uma linha na imagem");
    c(11); printf("\n\n  [v]"); c(10); printf(" Visualizar"); c(7); printf(": Desenha a imagem sem as r\x82guas esquerda e superior");
	c(11); printf("\n\n  [s]"); c(10); printf(" Sair"); c(7); printf(": Sai do editor e retorna ao menu\n");

}

void pintarPixel(Imagem * img) {

}

void pintarLinha(Imagem * img) {
    
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
