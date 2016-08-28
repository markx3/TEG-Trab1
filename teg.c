#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"





int main(void) {	
	VERTICES = openFileVertices();
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
					
				} else {
					printf("Invalido.\n");
				}
			} while(d != 2 && d != 1);
			
			
			int exclusao;
			printf("Deseja excluir um vertice?\n 1. Sim; 2. Não\n");
			do {
				scanf("%i", &exclusao);
				if(exclusao == 1) {
					int no;
					printf("Qual vertice deseja excluir?\n");
					scanf("%i", &no);
					printf("exclui\n");
					excluiVerticeAd(no);
					printf("LIBERA\n");
					matriz = liberaMatriz(matriz);
					printf("aloca\n");
					VERTICES = openFileVertices();
					contaArestas();
					matriz = alocaMatriz(VERTICES, VERTICES);
					openFileGrafoAd(matriz, d);
					mostrarMatrizAd(matriz);
				} else if (exclusao == 2) {
					break;
				} else {
					printf("Invalido.\n");
				}		
			
			} while(exclusao != 1 && exclusao != 2);
			
			
			
			break;
			
		case 2:
		
			/* Alocando a matriz */
			matriz = alocaMatriz(ARESTAS, VERTICES);

			openFileGrafoId(matriz);
			break;
			
		default:
			printf("Opção inválida. Encerrando...\n");
	}
	
	
	
	return 0;
}
