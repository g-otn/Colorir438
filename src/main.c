#include "../include/imagem.h"
#include "../include/colorir438.h"

// Lê a entrada de usuário removendo a quebra de linha no final e impedindo entradas vazias
void lerEntrada(char * destino, int tamanhoDestino);

// Tenta abrir um caminho inserido e ler e editar a Imagem no arquivo
void abrirImagem(void);

// Entra no loop do editor
void editar(Imagem img);

// Preenche os pixels de uma Imagem e abre ela no editor
void carregarExemplo(void);

int main(int argc, char **argv)
{
	c(7);

	// Visualiza a imagem passada no argumento
	if (argc > 1) // Há argumentos
	{
		Imagem img = lerImagem(argv[1]);
		
		if (img.alt > 0) { // Imagem válida
			if (img.bg != '-') {
				// Pinta o console inteiro com a cor de fundo (img.bg)
				char comando[9];
				sprintf(comando, "color %c0", img.bg);
				system(comando);
			}
			desenharImagem(img, 0);
		}
		
		liberarImagem(&img);
		_getch(); // Evita consoles de pop-up de fecharem sozinhos
		system("color 07");
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
		printf("\n\t"); c(5); printf("\xBA  "); c(11); 	printf("[2]"); c(10); printf(" Abrir imagem (.bmp, .c438)\t\t\t"); 									c(5); printf("\xBA  ");
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

void lerEntrada(char * destino, int tamanhoDestino) {
	c(7);
	do {
		fflush(stdin);
		fgets(destino, tamanhoDestino, stdin);
		if (strchr(destino, '\n') != NULL)
			*strchr(destino, '\n') = '\0';
	} while (destino[0] == '\0');
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

void editar(Imagem img)
{
	desenharImagem(img, 1);
	c(12); printf("Ainda n\xC6o implementado.");
	_getch();
	liberarImagem(&img);
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