#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void) {	
	VERTICES = contaVertices();
	printf("VERTICES = %d\n", VERTICES);
	contaArestas();
	int menu;
	int **matriz;

	printf("1. Adjacencia; 2. Incidência\n");
	scanf("%i", &menu);
	
	switch(menu) {
		case 1:	
			/* Alocando a matriz */
			matriz = alocaMatriz(VERTICES, VERTICES);
			
			int d;
			do {
				
				printf("1. Direcionado; 2. Não direcionado.\n");
				scanf("%i", &d);
			
				if(d == 2 || d == 1) {
					openFileGrafoAd(matriz, d);
					printf("TAMANHO: %i\n", VERTICES);
					
					mostrarMatrizAd(matriz);
					printf("\nMatriz Adj. do Complemento de G:\n");
					if (d == 2) matrAdjComplemento(matriz);
					
				} else {
					printf("Invalido.\n");
				}
			} while(d != 2 && d != 1);
			
			int i;

			printf("\n");
			for (i = 0; i < VERTICES; i++) {
				printf("Grau do vértice %i = %i\n", i+1, calculaGrau(i, matriz));
			}
			printf("\n");

			exclusaoAd(matriz, d);
			
			insercaoAd(matriz, d);
			
			
			break;
			
		case 2:
		
			/* Alocando a matriz */
			contaArestas();
			VERTICES = contaVertices();
			matriz = alocaMatriz(ARESTAS, VERTICES);

			printf("ARESTAS = %d\n", ARESTAS);
			d = 0;
			printf("1. Direcionado; 2. Não direcionado\n");
			scanf("%d", &d);
			openFileGrafoId(matriz, d);
			mostrarMatrizId(matriz);
			exclusaoId(matriz, d);
			insercaoId(matriz, d);
			break;
			


		default:
			printf("Opção inválida. Encerrando...\n");
	}
	
	
	
	return 0;
}
