/*
	Colorir438 - Baseado no programa do slide do Prof. Dr. Silvio do Lago Pereira sobre Coloracao (IED-001) do dpto. de TI da FATEC-SP
    Gabriel Otani Pereira - Mar 2019
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#define c _textcolor
#define b _textbackground
#define MAX_ALTERACOES 30

typedef struct alteracoes { // Guarda as alteracoes nos pixels para desfazer/refazer
	int pixels[MAX_ALTERACOES][3]; // Guarda os valores dos pixels [x, y, cor]
	int atual; // Índice em pixels[][]
	int topo; // Marca a quantidade de alteracoes armazenadas
} alteracoes;

void criarNovaImagem(int limparMemoria);
void abrirArquivo(void);
void lerColorir438(FILE *arquivo);
void lerBmp(FILE *arquivo);
void carregarExemplo(void);

void desenhar(int mostrarRegua, int alt, int lar, int img[alt][lar]);
void editar(int alt, int lar, int img[alt][lar]);

void exibirComandos(void);
void pintar(int preencher, int alt, int lar, int img[alt][lar]);
void linha(int alt, int lar, int img[alt][lar]);
void desfazer(alteracoes a, int alt, int lar, int img[alt][lar]);
void refazer(alteracoes a, int alt, int lar, int img[alt][lar]);
char *salvar(char *nomeArquivo, int alt, int lar, int img[alt][lar]);

int main(void) {
	int opcao;

	do {
		do {
			system("cls");
			opcao = -1;
			printf("\n\t"); c(5); printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
			printf("\n\t"); c(5); printf("\xBA  "); c(5); printf("\t\t    --== "); c(11); printf("Colorir"); c(13); printf("438"); c(5); printf(" ==--\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  ") ;c(8); printf("\tCriado por Gabriel Otani Pereira em Mar 2019\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  "); c(11); printf("[1]"); c(10); printf(" Nova imagem\t\t\t\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  "); c(11); printf("[2]"); c(10); printf(" Abrir imagem (.bmp, .colorir438)\t\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  "); c(11); printf("[3]"); c(10); printf(" Carregar imagem de exemplo\t\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  "); c(11); printf("[4]"); c(10); printf(" Criar imagem com valores em memoria\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xBA  "); c(11); printf("[5]"); c(10); printf(" Sair\t\t\t\t\t\t"); c(5); printf("\xBA  ");
			printf("\n\t"); c(5); printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
			
			// Lê a opcao do menu
			c(7); printf("\n\nDigite uma opcao (1-5): "); c(15);
			opcao = _getch() - '0'; // Transforma '1' em 1, '2' em 2, etc
		} while (opcao < 1 || opcao > 5);

		printf("\n");

		switch (opcao) {
			case 1:
				criarNovaImagem(1);
				break;
			case 2:
				abrirArquivo();
				break;
			case 3:
				carregarExemplo();
				break;
			case 4:
				criarNovaImagem(0);
				break;
		}
	} while (opcao != 5);

	return 0;
}

void criarNovaImagem(int limparEspacos) {
	int alt = -1, lar = -1;
	
	char entrada[8];
	do {
		printf("Digite as dimensoes da imagem ("); c(3); printf("largura altura"); c(15); printf("), separadas por espaco (Ex: \""); c(3); printf("20 15"); c(15); printf("\"): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);
	} while (sscanf(entrada, "%d %d\n", &lar, &alt) < 2);

	int img[alt][lar];
	if (limparEspacos)
		for (int i = 0; i < alt; i++)
			for (int j = 0; j < lar; j++)
				img[i][j] = 15;
				
	editar(alt, lar, img);
}

void abrirArquivo(void) {
	// Lê o caminho do arquivo
	char caminhoArquivo[100];
	do {
		c(7); printf("Digite o nome ou caminho do arquivo ("); c(3); printf("exemplo.colorir438, ./Imagens/imagem.bmp, C:\\Users\\..."); c(15); printf("): \n");
		c(15);
		fflush(stdin);
		fgets(caminhoArquivo, sizeof caminhoArquivo, stdin);
		if (strchr(caminhoArquivo, '\n') != NULL)
			*strchr(caminhoArquivo, '\n') = '\0';
	} while (caminhoArquivo[0] == '\0');

	// Recupera o arquivo
	FILE *arquivo = fopen(caminhoArquivo, "r");

	// Checagem de arquivo indisponível
	if (arquivo == NULL) {
		printf("Arquivo em \""); c(3); printf("%s", caminhoArquivo); c(15); printf("\" nao encontrado!");
		_getch();
		return;
	}
	// Checagem de arquivo vazio
	fseek(arquivo, 0, SEEK_END);
	if (ftell(arquivo) == 0) {
		printf("Arquivo em \""); c(3); printf("%s", caminhoArquivo); c(15); printf("\" vazio!");
		_getch();
		return;
	}

	// Filtrador de tipo de arquivo (.bmp ou .Colorir438)
	rewind(arquivo);
	char filtro[11];
	fgets(filtro, sizeof filtro, arquivo); // Guarda os 10 primeiros chars do arquivo
	if (strcmp(filtro, "Colorir438") == 0) { // filtro é igual a "Colorir438"
		printf("Formato identificado: .Colorir438 ("); c(2); printf("%s", filtro); c(15); printf(")");
		lerColorir438(arquivo); // ler como .Colorir438
	} else if (strstr(filtro, "BM") != NULL) { // "BM" está contido em filtro
		printf("Formato identificado: .bmp ("); c(2); printf("%s", filtro); c(15); printf(")");
		lerBmp(arquivo); // ler como .bmp
	} else {
		printf("Formato nao reconhecido ("); c(12); printf("%s", filtro); c(15); printf("), tente um .bmp de 24bits ou um .Colorir438");
		_getch();
	}
}

void lerColorir438(FILE *arquivo) {
	// Lê as dimensoes da imagem
	int alt, lar;
	fseek(arquivo, 11, SEEK_SET); // Pula para depois do "Colorir438 "
	fscanf(arquivo, "%d %d", &lar, &alt);
	//printf("Dimensoes da imagem identificados: %dx%d", lar, alt);

	// Lê os valores dos pixels
	int img[alt][lar];
	fseek(arquivo, 2, SEEK_CUR);
	for (int i = 0; i < alt*lar; i++) {
		char c = fgetc(arquivo);
		if (c < 58) {
			img[i/lar][i%alt] = c - 48; // Converte do int (48...57) = char ('0'...'9') para int (48...57)-48 = (0...9)
			//printf("\nbyte #%d: int %d char %c\tint-48 %d", i, c, c, c-48); 
		} else {
			img[i/lar][i%alt] = c - 55; // Converte do int (65...70)+55 = char ('A'...'F') para int (65...70)-55 = (10...16)
			//printf("\nbyte #%d: int %d char %c\tint-55 %d", i, c, c, c-55); 
		}
	}
	fclose(arquivo);
	
	editar(alt, lar, img);
}

void lerBmp(FILE *arquivo) {
	// Recupera informações para leitura do arquivo
	struct {
		int imgDataStart; // Byte onde os dados da imagem começam
		struct {
			int alt;
			int lar;
		} tam; // Dimensões da imagem
		int bitspp; // Bits por pixel (1, 4, 8, 16, 24 ou 32 bits) -> (2, 16 [txtcolor/cmd color], 256, RGB, RGBA) (2^n colors)
	} meta;
	fseek(arquivo, 10, SEEK_SET);
	meta.imgDataStart = fgetc(arquivo);
	fseek(arquivo, 18, SEEK_SET);
	meta.tam.lar = fgetc(arquivo);
	fseek(arquivo, 20, SEEK_SET);
	meta.tam.alt = fgetc(arquivo);
	fseek(arquivo, 28, SEEK_SET);
	
	// Lê e armazena os valores dos pixels
	int i = 0;
	while(!feof(arquivo)) {
		printf("\nbyte #%d\tint: %d", i, fgetc(arquivo));
		i++;
	}
	fclose(arquivo);

	printf("Metadata do .bmp\n\tDimensoes: %dx%d\n\tComeco dos bytes dos pixels: %d\n\tBits por pixel: %d", meta.tam.lar, meta.tam.alt, meta.imgDataStart, meta.bitspp);
	_getch();
}

void carregarExemplo(void) {
	int ex[9][9] = {
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

	editar(9, 9, ex);
}

void desenhar(int mostrarRegua, int alt, int lar, int img[alt][lar]) {
	system("cls");

	int y, x;
	mostrarRegua *= -1; // mostrarRegua 0 -> 0, 1 -> -1, para o x e o y ficarem -1 e a régua ser exibida

	for (y = mostrarRegua; y < alt; y++) {
		c(15);
		for (x = mostrarRegua; x < lar; x++) {
			if (y < 0 && x < 0) { // Espaçamento no comeco da "tabela" (-1, -1)
				printf("  ");
			} else if (y < 0) { // Desenhando régua horizontal (0, -1) até (lar, -1)
				if (!(x%2)) // Se o numero na régua horizontal for par
					b(1 + x/10 - 2*(x/20));
				else
					b(0);
				printf("%2d", x%10);
			} else if (x < 0) { // Desenhando régua vertical (-1, 0) até (-1, alt)
				if (!(y%2)) // Se o numero na régua vertical for par
					b(1 + y/10 - 2*(y/20));
				else
					b(0);
				printf("\n%2d", y%100);
			} else {
				if (x == 0 && y > 0 && !mostrarRegua)
					printf("\n"); // Pula linha caso não entre no if de desenhar a régua onde a linha é pulada, pois o mostrarRegua == 0
				
				// Desenhando imagem (0, 0) até (lar, alt)
					b(0);
					c(img[y][x]);
					printf("%c%c", 219, 219);
			}
		}
	}
	printf("\n\n");
}

void editar(int alt, int lar, int img[alt][lar]) {
	desenhar(1, alt, lar, img);

	alteracoes a;
	a.atual = -1;
	a.topo = -1;

	char nomeArquivo[50]; // Guarda o nome do arquivo para não reinserir
	char cmd;

	do { 
		// Lê o comando
		c(7); printf("Digite um comando ("); c(11); printf("[a]"); c(10); printf(" Ajuda"); c(7); printf(", "); c(11); printf("[s]"); c(10); printf(" Sair"); c(7); printf("): "); c(15);
		cmd = _getch();
		printf("\n");

		// Filtra o comando
		switch (cmd) {
			case 'a': // A - Mensagem de Ajuda: Exibe comandos e suas sintaxes
				exibirComandos();
				break;
			case 'p': // P - Ponto/Pintar: Pinta um pixel
				pintar(0, alt, lar, img);
				break;
			case 'b': // B - Balde: Preenche todas os pixels da área de mesma cor
				pintar(1, alt, lar, img);
				break;
			case 'l': // L - Linha: Desenha uma linha na imagem
				linha(alt, lar, img);
				break;
			case 'd': // D - Desfazer: Desfaz ultima modificação -
				desfazer(a, alt, lar, img);
				break;
			case 'r': // R - Refazer: Refaz ultima modificao desfeita
				refazer(a, alt, lar, img);
				break;
			case 'g': // G - Gravar: Salva a imagem em um arquivo
				strcpy(nomeArquivo, salvar(nomeArquivo, alt, lar, img)); // Guarda o nome do arquivo retornado (digitado em salvar()) em nomeArquivo
				break;
			case 'v': // V - Visualizar: Mostra o arquivo sem as réguas
				desenhar(0, alt, lar, img);
				break;
			case 's': // S - Sair: Volta ao menu principal
				return;
		}

		if (cmd != 'v' && cmd != 'a')
			desenhar(1, alt, lar, img);
	} while (1);
}

void exibirComandos(void) {
	c(5); printf("\t\t    --== "); c(11); printf("Lista de Comandos"); c(5); printf(" ==--\t\t");
	c(11); printf("\n  [p]"); c(10); printf(" Ponto"); c(7); printf(": Pinta um pixel nas coordenadas especificadas");
	c(11); printf("\n  [b]"); c(10); printf(" Balde"); c(7); printf(": Preenche todos os pixels da area de mesma cor");
	c(11); printf("\n  [l]"); c(10); printf(" Linha"); c(7); printf(": Desenha uma linha na imagem");
	c(11); printf("\n  [d]"); c(10); printf(" Desfazer"); c(7); printf(": Desfaz a ultima modificacao na imagem");
	c(11); printf("\n  [r]"); c(10); printf(" Refazer"); c(7); printf(": Refaz a ultima modificacao desfeita na imagem");
	c(11); printf("\n  [g]"); c(10); printf(" Gravar"); c(7); printf(": Salva a imagem em um arquivo");
	c(11); printf("\n  [v]"); c(10); printf(" Visualizar"); c(7); printf(": Desenha a imagem sem as reguas esquerda e superior");
	c(11); printf("\n  [s]"); c(10); printf(" Sair"); c(7); printf(": Sai do modo de edicao e retorna ao menu\n");
}

void pintar(int preencher, int alt, int lar, int img[alt][lar]) {
	c(15); printf("\tCores: "); b(8); c(0); printf("0"); b(0);
	for (int i = 1; i < 16; i++) {
		c(i); printf(" %d", i);
	}
	printf("\n");

	int cor;
	char entrada[7];
	do {
		printf("Escolha uma cor (0-15): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);
	} while (sscanf(entrada, "%d\n", &cor) != 1);

	entrada[0] = '\0';
	entrada[1] = '\0';
	entrada[2] = '\0';
	
	int x, y;
	do {
		printf("Digite as coordenadas do pixel a ser alterado ("); c(3); printf("x y"); c(15); printf("), separadas por espaco (Ex: \""); c(3); printf("32 10"); c(15); printf("\"): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);
	} while (sscanf(entrada, "%d %d\n", &x, &y) != 2);

	img[y][x] = cor;
}

void linha(int alt, int lar, int img[alt][lar]) {
	c(15); printf("\n\tCores: "); b(8); c(0); printf("0"); b(0);
	for (int i = 1; i < 16; i++) {
		c(i); printf(" %d", i);
	}

}

void desfazer(alteracoes a, int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações a desfazer
	if (a.atual == 0) {
		printf("Nao ha alteracoes a serem desfeitas (voce pode refazer %d alteracoes)",  a.topo - a.atual);
		_getch();
		return;
	}

	// Checa qual é a situação do a.inicio e a.fim e realiza a troca de valores entre img e a.items
}
void refazer(alteracoes a, int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações desfeitas a refazer
	if (a.atual == a.topo) {
		printf("Nao ha alteracoes a serem refeitas (voce pode desfazer %d alteracoes)", a.atual);
		_getch();
		return;
	}	
}

char *salvar(char *nomeArquivo, int alt, int lar, int img[alt][lar]) {
	// Lê o nome do arquivo
	if (nomeArquivo[0] == '\0') {
		do {
			printf("Digite um nome para o arquivo: ");
			fflush(stdin);
			fgets(nomeArquivo, sizeof nomeArquivo, stdin);
		} while (nomeArquivo[0] == '\0');
	}

	// Prepara para criar e escrever no arquivo
	_mkdir("./Imagens", 0777); // Cria a pasta caso inexistente
	char caminhoArquivo[71];
	sscanf("./Imagens/", "%s", caminhoArquivo);
	strncat(caminhoArquivo, nomeArquivo, 50);
	strcat(caminhoArquivo, ".colorir438");
	FILE *arquivo = fopen(caminhoArquivo, "w");
	if (arquivo == NULL) {
		printf("\nNao foi possivel criar/abrir o arquivo, evite nomes longos e caracteres especiais ("); c(12); printf("\\ / * ? \" < > |"); c(15); printf(")");
		_getch();
		return "\0";
	}

	// Escreve no arquivo
	printf("Gravando valores em \"%s\"", caminhoArquivo);
	fprintf(arquivo, "Colorir438 %d %d\n", lar, alt);
	for (int i = 0; i < alt*lar; i++)
		if (img[i/lar][i%alt] < 10)
			fprintf(arquivo, "%c", img[i/lar][i%alt] + 48); // Converte do int (0-9) para (0-9)+48 = (48-57)ºdec = char ('0'-'9') (Apenas para melhor leitura externa)
		else
			fprintf(arquivo, "%c", img[i/lar][i%alt] + 55); // Converte do int (10-15) para (10-15)+55 = (65-70)ºdec = char ('A'-'F') (Apenas para melhor leitura externa)
	
	fclose(arquivo);
	return nomeArquivo;
}
