/*
	Colorir438 - Cria, edita e mostra imagens no console
	Baseado no programa do slide do Prof. Dr. Silvio do Lago Pereira sobre Coloracao (IED-001) do dpto. de TI da FATEC-SP
    Criador por Gabriel Otani Pereira - Mar 2019
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#define c _textcolor
#define b _textbackground
#define MAX_ALTERACOES 1 + 50

typedef struct FilaAlteracoes { // Fila circular que guarda as alteracoes nos pixels para desfazer/refazer
	int pixels[MAX_ALTERACOES][3]; // Guarda os valores dos pixels [x, y, cor]
	int atual; // Índice em pixels[][]
	int inicio; // Guarda a alteração mais antiga
	int fim; // Guarda a alteração mais recente e marca a quantidade de alteracoes armazenadas
} FilaAlteracoes;

FilaAlteracoes a;
char nomeArquivo[50]; // Guarda o nome do arquivo para não reinserir

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
void desfazer(int alt, int lar, int img[alt][lar]);
void refazer(int alt, int lar, int img[alt][lar]);
void salvar(int alt, int lar, int img[alt][lar]);

int main(void) {
	int opcao;

	do {
		nomeArquivo[0] = '\0';

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
		filtro[2] = '\0'; // Faz com que o filtro como %s seja só os primeiros 2 bytes ("BM")
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
	for (int i = 0; i < alt; i++) {
		for (int j = 0; j < lar; j++) {
			char ch = fgetc(arquivo);
			if (ch == '\n') {
				printf("ch\\n: %c", ch);
				ch = fgetc(arquivo);}
			if (ch < 58) {
				img[i][j] = ch - 48; // Converte do int (48...57) = char ('0'...'9') para int (48...57)-48 = (0...9)
				c(6); printf("\nbyte #%d (%d, %d): int %d char %c\tint-48 ", i*lar+j, i, j, ch, ch);
				c(ch-48); printf("%d", img[i][j]);
			} else {
				img[i][j] = ch - 55; // Converte do int (65...70)+55 = char ('A'...'F') para int (65...70)-55 = (10...16)
				c(6); printf("\nbyte #%d (%d, %d): int %d char %c\tint-55 ", i*lar+j, i, j, ch, ch);
				c(ch-55); printf("%d", img[i][j]);
			}
		}
	}
	fclose(arquivo);

	// [DEBUG Info] .colorir438 metadados
	c(13); printf("\nMetadata do .colorir438");
	c(7); printf("\nDimensoes: "); c(3); printf("%d", lar); c(7); printf("x"); c(3); printf("%d", alt);
	_getch();

	// Aviso para imagens grandes
	if (lar > 60 || alt > 100) {
		c(14); printf("\nA imagem eh grande (%dx%d), eh recomendado maximizar a janela e diminuir o tamanho da fonte.", lar, alt);
		if (lar > 200)
			printf(" Os pixels talvez nao aparecerao na tela corretamente");
		_getch();
	}
	
	editar(alt, lar, img);
}

void lerBmp(FILE *arquivo) {
	// Guarda metadados recuperados do arquivo
	struct {
		struct {
			int alt;
			int lar;
		} tam; // Dimensões da imagem
		int dadosImgIni; // Byte onde os dados da imagem começam
		int bitspp; // Bits por pixel (1, 4, 8, 16, 24 ou 32 bits)
		int paddingLinha; // Espaçamento em bytes até a próxima linha de pixels
	} meta;

	// Recupera informações para leitura dos pixels
	// Lê como Windows BITMAPINFOHEADER
	fseek(arquivo, 10, SEEK_SET);
	meta.dadosImgIni = fgetc(arquivo);
	fseek(arquivo, 18, SEEK_SET);
	meta.tam.lar = fgetc(arquivo);
	fseek(arquivo, 22, SEEK_SET);
	meta.tam.alt = fgetc(arquivo);
	fseek(arquivo, 28, SEEK_SET);
	meta.bitspp = fgetc(arquivo);
	
	// Lê e armazena os valores dos pixels
	rewind(arquivo);
	for (int i = 0; !feof(arquivo); i++)
		printf("\nbyte #%d\tint: %d", i, fgetc(arquivo)); // [DEBUG Info] .bmp bytes

	// [DEBUG Info] .bmp metadados
	c(13); printf("\nMetadados do .bmp");
	c(7); printf("\nDimensoes: "); c(3); printf("%dx%d", meta.tam.lar, meta.tam.alt);
	c(7); printf("\nInicio dos valores dos pixels: "); c(3); printf("%d", meta.dadosImgIni); 
	c(7); printf("\nBits por pixel: "); c(3); printf("%d", meta.bitspp);

	c(14);
	fseek(arquivo, 2, SEEK_SET);
	printf("\n#2: tamanho arquivo: %d", fgetc(arquivo));
	fseek(arquivo, 14, SEEK_SET);
	printf("\n#14: tamanho DIB header: %d", fgetc(arquivo));
	fseek(arquivo, 34, SEEK_SET);
	printf("\n#34: tamanho imagem (rowsize*altura): %d", fgetc(arquivo));
	fseek(arquivo, 46, SEEK_SET);
	printf("\n#46: numero de cores: %d", fgetc(arquivo));

	if (meta.bitspp <= 8)
		printf("\nBits por pixel (color depth) <= 8 (%d), color table existente", meta.bitspp);

	// Dados dos pixels
	int paddingLinha = (int)(floorf((meta.bitspp*meta.tam.lar+31)/32)*4) - meta.tam.lar; // RowSize - largura da imagem
	printf("\nrowsize: %d\npadding da linha: %d", paddingLinha + meta.tam.lar, paddingLinha);
	printf("\nArray de dados dos pixels da imagem:");
	fseek(arquivo, meta.dadosImgIni, SEEK_SET);
	c(6);
	for (int y = meta.tam.alt - 1; y >= 0; y--) {
		for (int x = 0; x < meta.tam.lar; x++) {
			printf("\n(%d, %d): %d ", x, y, fgetc(arquivo));
		}
		printf("\npulando padding:");
		for (int p = 0; p < paddingLinha; p++)
			printf(" %d", fgetc(arquivo));
		//fseek(arquivo, paddingLinha, SEEK_CUR); // Pula o padding da linha no arquivo
	}

	_getch();
	fclose(arquivo);
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
	printf("\n");
}

void editar(int alt, int lar, int img[alt][lar]) {
	desenhar(1, alt, lar, img);

	// Reinicia o FilaAlteracoes a
	a.atual = 0;
	a.fim = 0;
	a.inicio = 0;

	char cmd;

	do {
		// Mostra informações sobre o arquivo e alterações
		if (nomeArquivo[0] != '\0') {
			c(8); printf("Editando \""); c(7); printf("%s", nomeArquivo); c(8); printf("\" (%dx%d) ", lar, alt);
		} else {
			c(8); printf("Editando nova imagem (%dx%d) ", lar, alt);
		}
		if (a.inicio <= a.atual)
			printf("Desfazer: %d/%d ", a.atual - a.inicio, MAX_ALTERACOES - 1);
		else
			printf("Desfazer: %d/%d ", a.atual + (MAX_ALTERACOES - a.inicio), MAX_ALTERACOES - 1);
		if (a.atual <= a.fim)
			printf("Refazer: %d", a.fim - a.atual);
		else
			printf("Refazer: %d", a.fim + (MAX_ALTERACOES - a.atual));
		
		// [DEBUG Info] dados da FilaAlteracoes
		// c(14); printf("\natual: %d fim: %d inicio: %d", a.atual, a.fim, a.inicio);
		// c(6); for (int i = 0; i < MAX_ALTERACOES; i++) {
		// 	printf("\n%d: [%d, %d, %d]", i, a.pixels[i][0], a.pixels[i][1], a.pixels[i][2]);
		// 	if (i == a.atual) printf(" <= atual");
		// 	if (i == a.inicio) printf(" <- inicio");
		// 	if (i == a.fim) printf(" <- fim");
		// } c(15);

		// Lê o comando
		c(7); printf("\nDigite um comando ("); c(11); printf("[a]"); c(10); printf(" Ajuda"); c(7); printf(", "); c(11); printf("[s]"); c(10); printf(" Sair"); c(7); printf("): "); c(15);
		cmd = _getch();
		printf("\n");

		// Filtra o comando
		switch (tolower(cmd)) {
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
				printf("Nao eh possivel desfazer uma linha, continuar? [s/n]");
				if (_getch() == 's')
					linha(alt, lar, img);
				break;
			case 'd': // D - Desfazer: Desfaz ultima modificação -
				desfazer(alt, lar, img);
				break;
			case 'r': // R - Refazer: Refaz ultima modificao desfeita
				refazer(alt, lar, img);
				break;
			case 'v': // V - Visualizar: Mostra o arquivo sem as réguas
				desenhar(0, alt, lar, img);
				break;
			case 'n': // N - reNomear: Renomeia a imagem e salva em um arquivo
				nomeArquivo[0] = '\0';
			case 'g': // G - Gravar: Salva a imagem em um arquivo
				salvar(alt, lar, img); // Guarda o nome do arquivo retornado (digitado em salvar()) em nomeArquivo
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
	c(11); printf("\n\n  [v]"); c(10); printf(" Visualizar"); c(7); printf(": Desenha a imagem sem as reguas esquerda e superior");
	c(11); printf("\n  [g]"); c(10); printf(" Gravar"); c(7); printf(": Salva a imagem em um arquivo");
	c(11); printf("\n  [n]"); c(10); printf(" reNomear"); c(7); printf(": Renomeia a imagem e salva em um arquivo");
	c(11); printf("\n  [s]"); c(10); printf(" Sair"); c(7); printf(": Sai do modo de edicao e retorna ao menu\n");
}

void pintar(int preencher, int alt, int lar, int img[alt][lar]) {
	c(15); printf("\tCores: "); b(8); c(0); printf("0"); b(0);
	for (int i = 1; i < 16; i++) {
		c(i); printf(" %d", i);
	}
	printf("\n");

	char entrada[8];

	// Lê a cor do pixel
	int cor;
	do {
		printf("Escolha uma cor (0-15): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);
		
		if (sscanf(entrada, "%d\n", &cor) == 1) { // Checagem de entrada inválida
			if (cor < 0 || cor > 15) { // Checagem de cor inválida
				printf("Cor invalida ("); c(12); printf("%d", cor); c(15); printf("). Escolha uma cor de "); c(3); printf("0 a 15", lar - 1); c(15); printf("\n");
			} else
				break;
		}
	} while (1);

	for (int i = 0; i < 8; i++)
		entrada[i] = '\0';
	
	// Lê as coordenadas do pixel
	int x, y;
	do {
		printf("Digite as coordenadas do pixel ("); c(3); printf("x y"); c(15); printf(") a ser pintado, separadas por espaco (Ex: \""); c(3); printf("32 10"); c(15); printf("\"): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);

		// Checagem de coordenada inválida
		if (sscanf(entrada, "%d %d\n", &x, &y) == 2) { // Checagem de entrada inválida
			if (x < 0 || x >= lar || y < 0 || y >= alt) { // Checagem de coordenada inválida
				printf("Coordenada invalida ("); c(12); printf("%d %d", x, y); c(15); printf("). Use uma posicao x de "); c(3); printf("0 a %d", lar - 1); c(15); printf(" e uma posicao y de "); c(3); printf("0 a %d", alt - 1); c(15); printf("\n");
			} else
				break;
		}
	} while (1);

	// Armazena a alteração
	a.pixels[a.atual][0] = img[y][x];
	a.pixels[a.atual][1] = x;
	a.pixels[a.atual][2] = y;
	// Gerencia os índices do armazenamento
	a.atual++;
	if (a.atual == MAX_ALTERACOES)
		a.atual = 0;
	if (a.atual == a.inicio)
		a.inicio++;
	if (a.inicio == MAX_ALTERACOES)
		a.inicio = 0;
	a.fim = a.atual; // Descarta alterações desfeitas

	// Altera a cor nas coordenadas
	img[y][x] = cor;
}

void linha(int alt, int lar, int img[alt][lar]) {
	c(15); printf("\n\tCores: "); b(8); c(0); printf("0"); b(0);
	for (int i = 1; i < 16; i++) {
		c(i); printf(" %d", i);
	}
	printf("\n");

	char entrada[8];

	// Lê a cor do pixel
	int cor;
	do {
		printf("Escolha uma cor (0-15): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);
		
		if (sscanf(entrada, "%d\n", &cor) == 1) { // Checagem de entrada inválida
			if (cor < 0 || cor > 15) { // Checagem de cor inválida
				printf("Cor invalida ("); c(12); printf("%d", cor); c(15); printf("). Escolha uma cor de "); c(3); printf("0 a 15", lar - 1); c(15); printf("\n");
			} else
				break;
		}
	} while (1);

	for (int i = 0; i < sizeof entrada; i++)
		entrada[i] = '\0';
	
	// Lê as coordenadas da linha
	int x1, y1;
	do {
		printf("Digite as coordenadas do comeco da reta ("); c(3); printf("x1 y1"); c(15); printf("), separadas por espaco (Ex: \""); c(3); printf("2 10"); c(15); printf("\"): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);

		if (sscanf(entrada, "%d %d\n", &x1, &y1) == 2) { // Checagem de entrada inválida
			if (x1 < 0 || x1 >= lar || y1 < 0 || y1 >= alt) { // Checagem de coordenada inválida
				printf("Coordenada invalida ("); c(12); printf("%d %d", x1, y1); c(15); printf("). Use uma posicao x de "); c(3); printf("0 a %d", lar - 1); c(15); printf(" e uma posicao y de "); c(3); printf("0 a %d", alt - 1); c(15); printf("\n");
			} else
				break;
		}
	} while (1);

	for (int i = 0; i < 8; i++)
		entrada[i] = '\0';

	int x2, y2;
	do {
		printf("Digite as coordenadas do final da reta ("); c(3); printf("x2 y2"); c(15); printf("), separadas por espaco (Ex: \""); c(3); printf("2 10"); c(15); printf("\"): ");
		fflush(stdin);
		fgets(entrada, sizeof entrada, stdin);

		if (sscanf(entrada, "%d %d\n", &x2, &y2) == 2) { // Checagem de entrada inválida
			if (x2 < 0 || x2 >= lar || y2 < 0 || y2 >= alt) { // Checagem de coordenada inválida
				printf("Coordenada invalida ("); c(12); printf("%d %d", x2, y2); c(15); printf("). Use uma posicao x de "); c(3); printf("0 a %d", lar - 1); c(15); printf(" e uma posicao y de "); c(3); printf("0 a %d", alt - 1); c(15); printf("\n");
			} else
				break;
		}
	} while (1);

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
	c(14); printf("Distancia horizontal(x): %d vertical(y): %d", d.dist.x, d.dist.y); c(15);

	// Decide por qual eixo iterar (impede d.passo de ser >= 1, pulando pixels (ex: a cada 1x, andar 4y: deixa 3 pixels sem pintar))
	if (d.dist.x <= d.dist.y) {
		// Primeiro calculo de d.passo, sem correcao de direcao
		d.passo = (float)d.dist.x / (float)d.dist.y;

		// Correção de direção caso seja da esquerda para a direita
		if (x1 > x2)
			d.passo *= -1;
		c(14); printf("\nd.dist.x(%d) <= d.dist.y (%d), iterando pelo y e adicionando d.passo(%f) ao x", d.dist.x, d.dist.y, d.passo);
		
		// Correção de direção caso seja da de baixo para cima
		if (y1 < y2) {
			printf("\nRegra de posicao: y1(%d) eh menor que y2(%d), indo de [x1y1](%d, %d) para [x2,y2](%d, %d)", y1, y2, x1, y1, x2, y2);
			printf("\nRegra de preenchimento: a cada 1y, andar %fx", d.passo);
		} else {
			d.passo *= -1;
			printf("\nRegra de posicao: y2(%d) eh menor/= que y1(%d), indo de [x2y2](%d, %d) para [x1,y1](%d, %d)", y2, y1, x2, y2, x1, y1);
			printf("\nRegra de preenchimento: a cada 1y, andar %fx", d.passo);
		}
		c(6);

		// Pinta os pixels
		float x;
		int y;
		if (y1 < y2) {
			x = x1 + 0.5; // Arredondamento para cima (<0.5) e para baixo (>=0.5), já que ex: (int)0.5 = 0; (int)0.9 = 0; então (int)(0.5+0.5) = 1 e (int)(0.9+0.5) = 1
			for (y = y1; y <= y2; y++) {
				printf("\nx: %f y: %d", x, y);
				img[y][(int)x] = cor;
				x += d.passo;
			}
		} else {
			x = x2 + 0.5;
			for (y = y2; y <= y1; y++) {
				printf("\nx: %f y: %d", x, y);
				img[y][(int)x] = cor;
				x += d.passo;
			}
		}
	} else {
		// Primeiro calculo de d.passo, sem correcao de direcao
		d.passo = (float)d.dist.y / (float)d.dist.x;

		// Correção de direção caso seja da de baixo para cima
		if (y1 > y2)
			d.passo *= -1;
		c(14); printf("\nd.dist.y(%d) < d.dist.x (%d), iterando pelo x e adicionando d.passo(%f) ao y", d.dist.y, d.dist.x, d.passo);
		
		// Correção de direção caso seja da esquerda para a direita
		if (x1 < x2) {
			printf("\nRegra de posicao: x1(%d) eh menor que x2(%d), indo de [x1y1](%d, %d) para [x2,y2](%d, %d)", x1, x2, x1, y1, x2, y2);
			printf("\nRegra de preenchimento: a cada 1x, andar %fy", d.passo);
		} else {
			d.passo *= -1;
			printf("\nRegra de posicao: x2(%d) eh menor/= que x1(%d), indo de [x2y2](%d, %d) para [x1,y1](%d, %d)", x2, x1, x2, y2, x1, y1);
			printf("\nRegra de preenchimento: a cada 1x, andar %fy", d.passo);
		}
		c(6);

		// Pinta os pixels
		int x;
		float y;
		if (x1 < x2) {
			y = y1 + 0.5;
			for (x = x1; x <= x2; x++) {
				printf("\nx: %d y: %f", x, y);
				img[(int)y][x] = cor;
				y += d.passo;
			}
		} else {
			y = y2 + 0.5;
			for (x = x2; x <= x1; x++) {
				printf("\nx: %d y: %f", x, y);
				img[(int)y][x] = cor;
				y += d.passo;
			}
		}
	}
	
	_getch();
}

void desfazer(int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações a desfazer
	if (a.atual == a.inicio) {
		printf("Nao ha alteracoes a serem desfeitas\n");
		_getch();
		return;
	}

	// Altera o a.atual uma alteracao para trás (volta para a última alteração)
	if (a.atual > 0)
		a.atual--;
	else
		a.atual = MAX_ALTERACOES - 1;

	int tmp_cor = img[a.pixels[a.atual][2]][a.pixels[a.atual][1]];
	
	// Desfaz a alteração nas coordenadas (x a.pixels[a.atual][1]], y a.pixels[a.atual][2]) com a cor em a.pixels[a.atual][0]
	printf("\nDesfazendo (x %d, y %d) com a cor %d (era %d)\n", a.pixels[a.atual][1], a.pixels[a.atual][2], a.pixels[a.atual][0], img[a.pixels[a.atual][2]][a.pixels[a.atual][1]]);
	img[a.pixels[a.atual][2]][a.pixels[a.atual][1]] = a.pixels[a.atual][0];

	a.pixels[a.atual][0] = tmp_cor;

}

void refazer(int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações desfeitas a refazer
	if (a.atual == a.fim) {
		printf("Nao ha alteracoes a serem refeitas\n");
		_getch();
		return;
	}

	int tmp_cor = img[a.pixels[a.atual][2]][a.pixels[a.atual][1]];

	// Refaz a alteração nas coordenadas (x a.pixels[a.atual][1]], y a.pixels[a.atual][2]) com a cor em a.pixels[a.atual][0]
	printf("\nRefazendo (x %d, y %d) com a cor %d (era %d)\n", a.pixels[a.atual][1], a.pixels[a.atual][2], a.pixels[a.atual][0], img[a.pixels[a.atual][2]][a.pixels[a.atual][1]]);
	img[a.pixels[a.atual][2]][a.pixels[a.atual][1]] = a.pixels[a.atual][0];

	a.pixels[a.atual][0] = tmp_cor;

	// Altera o a.atual uma alteracao para frente (avança o que o último desfazer voltou)
	if (a.atual < MAX_ALTERACOES - 1)
		a.atual++;
	else
		a.atual = 0;
}

void salvar(int alt, int lar, int img[alt][lar]) {
	// Lê o nome do arquivo
	if (nomeArquivo[0] == '\0') {
		do {
			printf("Digite um nome para o arquivo: ");
			fflush(stdin);
			fgets(nomeArquivo, sizeof nomeArquivo, stdin);
		} while (nomeArquivo[0] == '\0');
		*strchr(nomeArquivo, '\n') = '\0'; // Remove '\n' do final da string em nomeArquivo
	}

	// Prepara para criar e escrever no arquivo
	_mkdir("./Imagens", 0777); // Cria a pasta caso inexistente
	char caminhoArquivo[71];
	sscanf("./Imagens/", "%s", caminhoArquivo);
	strncat(caminhoArquivo, nomeArquivo, 50);
	strcat(caminhoArquivo, ".colorir438"); // Adiciona ".colorir438" no final do nomeArquivo
	FILE *arquivo = fopen(caminhoArquivo, "w");
	if (arquivo == NULL) {
		printf("Nao foi possivel criar/abrir o arquivo, evite nomes longos e caracteres especiais ("); c(12); printf("\\ / * ? \" < > |"); c(15); printf(")");
		_getch();
		return;
	}

	// Escreve no arquivo
	printf("Gravando valores em \"%s\"\n", caminhoArquivo);
	fprintf(arquivo, "Colorir438 %d %d", lar, alt);
	for (int i = 0; i < alt; i++) {
		fprintf(arquivo, "\n");
		for (int j = 0; j < lar; j++)
			if (img[i][j] < 10)
				fprintf(arquivo, "%c", img[i][j] + 48); // Converte do int (0-9) para (0-9)+48 = (48-57)ºdec = char ('0'-'9') (Apenas para melhor leitura externa)
			else
				fprintf(arquivo, "%c", img[i][j] + 55); // Converte do int (10-15) para (10-15)+55 = (65-70)ºdec = char ('A'-'F') (Apenas para melhor leitura externa)
	}
	
	fclose(arquivo);
}
