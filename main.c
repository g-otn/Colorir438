/*
	Colorir438 - Baseado no programa do slide do Prof. Dr. Silvio do Lago Pereira sobre Coloracao (IED-001) do dpto. de TI da FATEC-SP
    Gabriel Otani Pereira - Mar 2019
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct alteracoes { // Fila circular que guarda as alteracoes nos pixels para desfazer/refazer
	int pixels[10][3]; // Guarda os valores dos pixels [x, y, cor]
	int atual; // Marca os próximos valores a serem lidos caso seja desfeito
	int inicio; // Marca o comeco da fila, até onde pode ser
	int fim; // Marca o fim da fila, até onde há alterações a serem lidas
} alteracoes;

void criarNovaImagem(int limparMemoria);
void abrirArquivo(void);
void lerColorir438(FILE *arquivo);
void lerBmp(FILE *arquivo);
void carregarExemplo(void);

void desenhar(int mostrarRegua, int alt, int lar, int img[alt][lar]);
void editar(int alt, int lar, int img[alt][lar]);

void exibirAjuda(void);
void pintar(int preencher, int alt, int lar, int img[alt][lar]);
void linha(int alt, int lar, int img[alt][lar]);
void desfazer(alteracoes a, int alt, int lar, int img[alt][lar]);
void refazer(alteracoes a, int alt, int lar, int img[alt][lar]);
char *salvar(char *nomeArquivo, int alt, int lar, int img[alt][lar]);

int main(void) {
	int opcao;

	do {
		system("cls");
		opcao = -1;
		_textcolor(5); printf("\t\t\t--== "); 
		_textcolor(11); printf("Colorir");
		_textcolor(13); printf("438");
		_textcolor(5); printf(" ==--");
		_textcolor(8);
		printf("\nCriado por Gabriel Otani Pereira em Mar 2019\nBaseado no programa do slide do Prof. Dr. Silvio do Lago Pereira sobre Coloracao (IED-001) do dpto. de TI da FATEC-SP");
		_textcolor(3);
		printf("\n1 -> Para criar umaNova imagem");
		printf("\n2 -> Abrir imagem (.bmp, .colorir438)");
		printf("\n3 -> Carregar imagem de exemplo");
		printf("\n4 -> Criar imagem com valores em memoria");
		printf("\n5 -> Sair\n");

		// Lê a opcao do menu
		_textcolor(7); printf("Digite uma opcao (1-5): ");
		_textcolor(15);
		do {
			fflush(stdin);
			scanf("%d", &opcao);
		} while (opcao < 1 || opcao > 5);

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

void criarNovaImagem(int limparMemoria) {
	int alt = -1, lar = -1;
	printf("Digite as dimensoes da imagem ("); _textcolor(3); printf("largura altura"); _textcolor(15); printf("), separadas por espaco (Ex: \""); _textcolor(3); printf("20 15"); _textcolor(15); printf("\"): ");
	
	char entrada[8];
	do {
		fgets(entrada, sizeof entrada, stdin);
	} while (sscanf(entrada, "%d %d\n", &lar, &alt) < 2);

	int img[alt][lar];
	if (limparMemoria)
		for (int i = 0; i < alt; i++)
			for (int j = 0; j < lar; j++)
				img[i][j] = 15;
	desenhar(1, alt, lar, img);
	editar(alt, lar, img);
}

void abrirArquivo(void) {
	_textcolor(7); printf("Digite o nome ou caminho do arquivo ("); _textcolor(3); printf("exemplo.Colorir438, ./Minhas Imagens/imagem.bmp, C:\\Users\\..."); _textcolor(15); printf("):\n");
	_textcolor(15);

	// Lê o caminho do arquivo
	char caminhoArquivo[100];
	fflush(stdin);
	getchar();
	fgets(caminhoArquivo, sizeof caminhoArquivo, stdin);
	*strchr(caminhoArquivo, '\n') = '\0'; // Remove o \n do caminhoArquivo

	// Recupera o arquivo
	FILE *arquivo = fopen(caminhoArquivo, "r");

	// Checagem de arquivo indisponível ou inexistente
	if (arquivo == NULL) {
		printf("Arquivo em \""); _textcolor(3); printf("%s", caminhoArquivo); _textcolor(15); printf("\" nao encontrado!");
		getchar();
		return;
	}
	// Checagem de arquivo vazio
	fseek(arquivo, 0, SEEK_END);
	if (ftell(arquivo) == 0) {
		printf("Arquivo em \""); _textcolor(3); printf("%s", caminhoArquivo); _textcolor(15); printf("\" vazio!");
		getchar();
		return;
	}

	// Filtrador de tipo de arquivo (.bmp ou .Colorir438)
	rewind(arquivo);
	char filtro[11];
	fgets(filtro, sizeof filtro, arquivo); // Guarda os 10 primeiros chars do arquivo
	if (strcmp(filtro, "Colorir438") == 0) { // filtro é igual a "Colorir438"
		printf("Formato identificado: .Colorir438 ("); _textcolor(2); printf("%s", filtro); _textcolor(15); printf(")");
		lerColorir438(arquivo); // ler como .Colorir438
	} else if (strstr(filtro, "BM") != NULL) { // "BM" está contido em filtro
		printf("Formato identificado: .bmp ("); _textcolor(2); printf("%s", filtro); _textcolor(15); printf(")");
		lerBmp(arquivo); // ler como .bmp
	} else {
		printf("Formato nao reconhecido ("); _textcolor(12); printf("%s", filtro); _textcolor(15); printf("), tente um .bmp de 24bits ou um .Colorir438");
		getchar();
	}
}

void lerColorir438(FILE *arquivo) {
	// Lê as dimensoes da imagem
	int alt, lar;
	fseek(arquivo, 11, SEEK_SET); // Pula para depois do "Colorir438 "
	fscanf(arquivo, "%d %d", &lar, &alt);
	printf("Dimensoes da imagem identificados: %dx%d", lar, alt);

	// Lê os valores dos pixels
	int img[alt][lar];
	fseek(arquivo, 2, SEEK_CUR);
	for (int i = 0; i < alt*lar; i++) {
		char c = fgetc(arquivo);
		if (c < 58) {
			img[i/lar][i%alt] = c - 48;
			printf("\nbyte #%d: int %d char %c\tint-48 %d", i, c, c, c-48); // Converte do int (48-57) = char ('0'-'9') para int (48-57)-48 = (0-9)
		} else {
			img[i/lar][i%alt] = c - 55;
			printf("\nbyte #%d: int %d char %c\tint-55 %d", i, c, c, c-55); // Converte do int (65-70)+55 = char ('A'-'F') para int (65-70)-55 = (10-16)
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
		int bitspp; // Bits por pixel (1, 4, 8, 16, 24 ou 32 bits) -> (2 [monochromatic], 16 [txtcolor], 256, RGB, RGBA) (2^n colors)
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
	getchar();
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
	//system("cls");

	int y, x;
	mostrarRegua *= -1; // mostrarRegua 0 -> 0, 1 -> -1, para o x e o y ficarem -1 e a régua ser exibida

	for (y = mostrarRegua; y < alt; y++) {
		_textcolor(15);
		for (x = mostrarRegua; x < lar; x++) {
			if (y < 0 && x < 0) { // Espaçamento no comeco da "tabela" (-1, -1)
				printf("  ");
			} else if (y < 0) { // Desenhando régua horizontal (0, -1) até (lar, -1)
				if (!(x%2)) // Se o numero na régua horizontal for par
					_textbackground(1 + x/10 - 2*(x/20));
				else
					_textbackground(0);
				printf("%2d", x%10);
			} else if (x < 0) { // Desenhando régua vertical (-1, 0) até (-1, alt)
				if (!(y%2)) // Se o numero na régua vertical for par
					_textbackground(1 + y/10 - 2*(y/20));
				else
					_textbackground(0);
				printf("\n%2d", y%100);
			} else {
				if (x == 0 && y > 0 && !mostrarRegua)
					printf("\n"); // Pula linha caso não entre no if de desenhar a régua onde a linha é pulada, pois o mostrarRegua == 0
				
				// Desenhando imagem (0, 0) até (lar, alt)
					_textbackground(0);
					_textcolor(img[y][x]);
					printf("%c%c", 219, 219);
			}
		}
	}
	printf("\n\n");
}

void editar(int alt, int lar, int img[alt][lar]) {
	desenhar(1, alt, lar, img);

	alteracoes a;
	a.atual = 0;
	a.inicio = 0;
	a.fim = 0;

	char nomeArquivo[50]; // Guarda o nome do arquivo para não reinserir
	char cmd;

	do {
		_textcolor(7); printf("Digite um comando (");
		_textcolor(3); printf("a -> Ajuda, s -> Sair");
		_textcolor(7); printf("): ");
		_textcolor(15); 

		// Lê o comando
		fflush(stdin);
		char entrada[3];
		do {
			fgets(entrada, sizeof entrada, stdin);
			if (strchr(entrada, '\n') != NULL)
				*strchr(entrada, '\n') = '\0';
		} while (sscanf(entrada, "%c", &cmd) < 1);

		// Filtra o comando
		switch (cmd) {
			case 'a': // A - Mensagem de Ajuda: Exibe comandos e suas sintaxes
				exibirAjuda();
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
				strcpy(nomeArquivo, salvar(nomeArquivo, alt, lar, img));
				break;
			case 'v':
				desenhar(0, alt, lar, img);
				break;
			case 's':
				return;
		}

		// Redesenha a imagem alterada
		if (cmd != 'a' && cmd != 'v') {
			desenhar(1, alt, lar, img);
		}
	} while (1);
}

void exibirAjuda(void) {
	_textcolor(15); printf("\n\tLista de comandos");
	_textcolor(3); printf("\np -> Ponto"); _textcolor(7); printf(": Pinta um pixel nas coordenadas especificadas");
	_textcolor(3); printf("\nb -> Balde"); _textcolor(7); printf(": Preenche todos os pixels da area de mesma cor");
	_textcolor(3); printf("\nl -> Linha"); _textcolor(7); printf(": Desenha uma linha na imagem");
	_textcolor(3); printf("\nd -> Desfazer"); _textcolor(7); printf(": Desfaz a ultima modificacao na imagem");
	_textcolor(3); printf("\nr -> Refazer"); _textcolor(7); printf(": Refaz a ultima modificacao desfeita na imagem");
	_textcolor(3); printf("\ng -> Gravar"); _textcolor(7); printf(": Salva a imagem em um arquivo");
	_textcolor(3); printf("\nv -> Visualizar"); _textcolor(7); printf(": Desenha a imagem sem as reguas esquerda e superior");
	_textcolor(3); printf("\ns -> Sair"); _textcolor(7); printf(": Sai do modo de edicao e retorna ao menu\n");
}

void pintar(int preencher, int alt, int lar, int img[alt][lar]) {
	_textcolor(15); printf("\n\tCores: ");
	_textbackground(8); _textcolor(0); printf("0"); _textbackground(0);
	for (int i = 1; i < 16; i++) {
		_textcolor(i); printf(" %d", i);
	}

	int cor, y, x;
}

void linha(int alt, int lar, int img[alt][lar]) {
	_textcolor(15); printf("\n\tCores: ");
	_textbackground(8); _textcolor(0); printf("0"); _textbackground(0);
	for (int i = 1; i < 16; i++) {
		_textcolor(i); printf(" %d", i);
	}

}

void desfazer(alteracoes a, int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações a desfazer
	if (a.atual == a.inicio) {
		printf("Nao ha alteracoes a serem desfeitas (voce pode desfazer %d e refazer %d alteracoes)", a.atual - a.inicio, a.fim - a.atual);
		getchar();
		return;
	}

	// Checa qual é a situação do a.inicio e a.fim e realiza a troca de valores entre img e a.items
}
void refazer(alteracoes a, int alt, int lar, int img[alt][lar]) {
	// Checa se há alterações desfeitas a refazer
	if (a.atual == a.fim) {
		printf("Nao ha alteracoes a serem refeitas (voce pode desfazer %d e refazer %d alteracoes)", a.atual - a.inicio, a.fim - a.atual);
		getchar();
		return;
	}	
}

char *salvar(char *nomeArquivo, int alt, int lar, int img[alt][lar]) {
	// Lê o nome do arquivo
	if (nomeArquivo[0] == '\0') {
		printf("Digite um nome para o arquivo: ");
		do {
			fflush(stdin);
			fgets(nomeArquivo, sizeof nomeArquivo, stdin);
			if (strchr(nomeArquivo, '\n') != NULL)
				*strchr(nomeArquivo, '\n') = '\0';
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
		printf("\nNao foi possivel criar/abrir o arquivo, evite nomes longos e caracteres especiais ("); _textcolor(12); printf("\\ / * ? \" < > |"); _textcolor(15); printf(")");
		getchar();
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
