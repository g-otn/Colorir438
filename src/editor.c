#include "../include/editor.h"
#include "../include/entrada.h"
#include "../include/imagem.h"
#include <stdio.h>
#include <conio.h>

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
