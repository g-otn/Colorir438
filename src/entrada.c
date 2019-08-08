#include "../include/entrada.h"

// Lê a entrada de usuário removendo a quebra de linha no final e impedindo entradas vazias
void lerEntrada(char * destino, int tamanhoDestino) {
	c(7);
	do {
		fflush(stdin);
		fgets(destino, tamanhoDestino, stdin);
		if (strchr(destino, '\n') != NULL)
			*strchr(destino, '\n') = '\0';
	} while (destino[0] == '\0');
}