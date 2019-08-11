#include "../include/colorir438.h"
#include "../include/editor.h"
#include "../include/entrada.h"
#include "../include/imagem.h"
#include <stdio.h>
#include <conio.h>

// Cria uma nova imagem preenchida com pixels transparentes e a abre no editor
void criarNovaImagem(void);

// Tenta abrir um caminho inserido e ler e editar a Imagem no arquivo
void abrirImagem(void);

// Entra no loop do editor
void editar(Imagem img);

// Preenche os pixels de uma Imagem e abre ela no editor
void carregarExemplo(void);

// Altera o fundo e desenha a imagem sem réguas
void visualizarImagem(Imagem img);

int main(int argc, char **argv)
{
	c(7);

	// Visualiza a imagem passada no argumento
	if (argc > 1) // Há argumentos
	{
		Imagem img = lerImagem(argv[1]);
		
		if (img.alt > 0) // Imagem válida
			visualizarImagem(img);
		
		liberarImagem(&img);
		return 0; // Não abre o menu nem o editor
	}

	// Loop do menu principal
	int opcao;
	do
	{
		system("cls");

		printf("\n\t"); c(5); printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
		printf("\n\t"); c(5); printf("\xBA  "); c(5); 	printf("\t\t    --== "); c(11); printf("Colorir"); c(13); printf("438"); c(5); printf(" ==--\t\t"); c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xBA  "); c(8); 	printf(" Criado por g-otn (https://github.com/g-otn) - 2019\t"); 									c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xBA  "); c(11); 	printf("[1]"); c(10); printf(" Nova imagem\t\t\t\t\t"); 											c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xBA  "); c(11); 	printf("[2]"); c(10); printf(" Abrir imagem (.c438)\t\t\t\t"); 										c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xBA  "); c(11); 	printf("[3]"); c(10); printf(" Carregar imagem de exemplo\t\t\t"); 									c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xBA  "); c(11); 	printf("[4]"); c(10); printf(" Sair\t\t\t\t\t\t"); 													c(5); printf("\xBA  ");
		printf("\n\t"); c(5); printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");

		// Lê a opcao do menu
		do
		{
			fflush(stdin);
			opcao = -1;
			
			// TODO: adicionar filtro de números (evitar spam com ctrl+v acidental)
			opcao = _getch() - '0'; // Transforma '1' em 1, '2' em 2, etc
			fflush(stdin);
		} while (opcao < 1 || opcao > 5);

		printf("\n");

		switch (opcao)
		{
		case 1:
			criarNovaImagem();
			break;
		case 2:
			abrirImagem();
			break;
		case 3:
			carregarExemplo();
			break;
		}
	} while (opcao != 4);

	c(7);
	return 0;
}

void criarNovaImagem(void)
{
	int alt = 0, lar = 0;
	char entrada[10];

	// Lê alt e lar
	while (1)
	{
		do 
		{
			c(7); printf("Digite uma largura e uma altura (Ex: 20x15: \""); c(3); printf("20 15"); c(7); printf("\"): ");
			lerEntrada(entrada, 10);
		} while (sscanf(entrada, "%d %d\n", &lar, &alt) < 2);
		if (alt < 1 && alt < 1)
		{
			c(12); printf("Digite uma largura e uma altura maiores que 0.\n");
		} else
			break;
	}

	editar(criarImagem(alt, lar, '8'));
}

void abrirImagem(void)
{
	c(7); printf("Digite o caminho do arquivo (Ex: "); c(3); printf("exemplo.c438"); c(7); printf(", "); c(3); printf("./Imagens/exemplo2.bmp"); c(7); printf(", "); c(3); printf("C:\\Users\\..."); c(7); printf("): \n");
	char caminhoArquivo[260];
	lerEntrada(caminhoArquivo, 260);
	Imagem img = lerImagem(caminhoArquivo);
	if (img.alt > 0)
		editar(img);
}

void carregarExemplo(void)
{
	Imagem img = criarImagem(9, 9, '-');
	int florTmp[9][9] = {
		{11, 11, 11, 11, 11, 11, 11, 11, 11},
		{11, 11, 11, 6, 14, 6, 11, 11, 11},
		{11, 11, 14, 14, 4, 14, 14, 11, 11},
		{11, 11, 11, 14, 2, 14, 11, 11, 11},
		{11, 11, 11, 2, 2, 11, 11, 11, 11},
		{11, 11, 11, 11, 2, 11, 11, 11, 11},
		{11, 11, 11, 11, 2, 2, 11, 11, 11},
		{11, 11, 11, 11, 2, 11, 11, 11, 11},
		{6, 6, 6, 6, 6, 6, 6, 6, 6}
	};

	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			img.pixels[y][x] = florTmp[y][x];

	editar(img);
}

void visualizarImagem(Imagem img)
{
	if (img.bg != '-') 
	{
		// Pinta o console inteiro com a cor de fundo (img.bg)
		char comando[9];
		sprintf(comando, "color %c0", img.bg);
		system(comando);
		printf("img.bg: %d cmd: %s\n", img.bg, comando);
	}
	desenharImagem(img, 0);
	_getch(); // Evita consoles de pop-up de fecharem sozinhos
	system("color 07"); // Volta às cores padrão
}

void editar(Imagem img)
{
	int comando;
	
	system("cls");
	desenharImagem(img, 1);

	do {	
		fflush(stdin);
        c(14); printf("\nLargura %d, Altura %d", img.lar, img.alt);

		c(7); printf("\nDigite um comando ("); c(11); printf("[A]"); c(10); printf(" Ajuda"); c(7); printf(", "); c(11); printf("[S]"); c(10); printf(" Sair"); c(7); printf("): "); c(15);
		comando = _getch();
		printf("\n");

		switch (tolower(comando)) {
			case 'a':
				exibirComandos();
				break;
			case '1':
			case 'p':
				pintarPixel(&img);
				system("cls");
				desenharImagem(img, 1);	
				break;
			case '2':
			case 'l':
				pintarLinha(&img);
				system("cls");
				desenharImagem(img, 1);	
				break;
			case '3':
			case 'f':
				img.bg = lerCor();
				img.bg = img.bg == ' ' ? '-' : img.bg < 10 ? img.bg + 48 : img.bg + 55;
				system("cls");
				desenharImagem(img, 1);	
				break;
			case '4':
			case 'm':
				img = moverImagem(img);
				system("cls");
				desenharImagem(img, 1);	
				break;
				// 5, 6: desfazer refazer
			case '7':
			case 'v':
				system("cls");
				visualizarImagem(img);
				system("cls");
				desenharImagem(img, 1);	
				break;
			case 224: // Inicio da sequência retornada por _getch() ao utilizar teclas de seta
				switch (_getch()) { // Diferencia as teclas de seta
					case 72: // Cima
						img = alterarResolucao(img, DIMINUIR, VERTICAL);
						break;
					case 80: // Baixo
						img = alterarResolucao(img, AUMENTAR, VERTICAL);
						break;
					case 77: // Direita
						img = alterarResolucao(img, AUMENTAR, HORIZONTAL);
						break;
					case 75: // Esquerda
						img = alterarResolucao(img, DIMINUIR, HORIZONTAL);
						break;
				}
				system("cls");
				desenharImagem(img, 1);
				break;
				// 7, 8: salvar salvar como
			case '0':
			case 's':
				liberarImagem(&img);
				return;
			default:
				c(12); printf("Comando incorreto, digite '"); c(11); printf("A"); c(12); printf("' para uma lista de comandos. ");
				break;
		}
	} while (1);
}
