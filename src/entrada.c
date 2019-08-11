#include "../include/entrada.h"

void lerEntrada(char * destino, int tamanhoDestino) {
	do {
		fflush(stdin);
		fgets(destino, tamanhoDestino, stdin);
		if (strchr(destino, '\n') != NULL)
			*strchr(destino, '\n') = '\0';
	} while (destino[0] == '\0');
}
