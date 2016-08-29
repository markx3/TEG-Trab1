#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int contaVertices() {
	int tam = 0;

	int v1, v2, nr;
	FILE *in = fopen("grafo.txt", "r");
	while(fscanf(in, "%d %d %d", &v1, &v2, &nr) != EOF) {
		if (v1 > tam) tam = v1;
		if (v2 > tam) tam = v2;
	}
	fclose(in);
	return tam;
}

void contaArestas() {
	FILE *in = fopen("grafo.txt", "r");
	ARESTAS = 0;
	while(!feof(in)) {
		if(fgetc(in) == '\n') {
			ARESTAS++;
		}
	}	
}

/* Abrir arquivo com as relações da matriz de adjacencia não direcionada */
void openFileGrafoAd(int **matriz, int direcionado) {
	int vertice1, vertice2, relacionamento;
	int i, j;
	FILE *in = fopen("grafo.txt", "r");

	/* Atribuindo o número de arestas aos vértices correspondentes */
	while(fscanf(in, "%i %i %i #", &vertice1, &vertice2, &relacionamento) != EOF) {
		if(direcionado == 2) {
			matriz[vertice1-1][vertice2-1] = relacionamento;
			matriz[vertice2-1][vertice1-1] = relacionamento;
		} else {
			matriz[vertice1-1][vertice2-1] = 1;
		}
	}
	fclose(in);
}

void openFileGrafoId(int **matriz, int direcionado) {
	int i = 0, j;
	int verticeOrigem, verticeDestino, aresta;
	printf("ARESTAS = %d\n openFileGrafoId\n", ARESTAS);
	
	FILE *in = fopen("grafo.txt", "r");
	while(fscanf(in, "%i %i %i #", &verticeOrigem, &verticeDestino, &aresta) != EOF) {



			if(direcionado == 2) {
				matriz[i][verticeOrigem-1] = 1;
				matriz[i][verticeDestino-1] = 1;
			} else {
				matriz[i][verticeOrigem-1] = 1;
				matriz[i][verticeDestino-1] = -1;
			}
			if (i < ARESTAS) i++;
	}
	fclose(in);
}

/* Função para calcular o grau de um vértice do grafo */
int calculaGrau(int vertice, int **vetor) {
	int grau = 0, i;
	for(i = 0; i < VERTICES; i++) {
		if(vetor[vertice][i] != -1)
			grau += vetor[vertice][i];
	}
	return grau;
}

void mostrarMatrizAd(int **matriz) {
	int i;
	for(i = 0; i < VERTICES; i++) {
		int j;
		for(j = 0; j < VERTICES; j++) {
			if(matriz[i][j] != -11)
				printf("%i ", matriz[i][j]);		

		}
		printf("\n");

	}		
}

void mostrarMatrizId(int **matriz) {
	int i, j;
	for (i = 0; i < ARESTAS; i++) {
		for (j = 0; j < VERTICES; j++) {
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}
}


void excluiVerticeAd(int no) {
	int v1, v2, r;
	FILE *in = fopen("grafo.txt", "r");
	FILE *out = fopen("saida.txt", "w");
	VERTICES--;
	while(fscanf(in, "%i %i %i #", &v1, &v2, &r) != EOF) {
		if(v1 != no && v2 != no) {
			if (v1 > no) v1--;
			if (v2 > no) v2--;
			fprintf(out, "%i %i %i\n", v1, v2, r);
		}
	}	
	remove("grafo.txt");
	rename("saida.txt", "grafo.txt");	
	fclose(in);
	fclose(out);
}

int **alocaMatriz(int linhas, int colunas) {
	int i;
	int **matriz = (int **) calloc(linhas, sizeof(int*)); // LINHAS
	for(i = 0; i < linhas; i++) {
		matriz[i] = (int *) calloc(colunas, sizeof(int)); // COLUNAS
	}
	return matriz;
}

int **liberaMatriz(int **matriz) {
	int i;
	for(i = 0; i < VERTICES; i++) {
		matriz[i] = NULL;
		free(matriz[i]);
	}
	free(matriz);
	return NULL;
}

void insereNoAd() {
	int or = 0, dest = 0, nrel = 0, flag = 1;
	FILE *fp = fopen("grafo.txt", "a");
	int i = 0;
	printf("Insira o nó e suas relações (da mesma forma que do arquivo grafo.txt)\n");
	while (flag != 0) {
		scanf("%d %d %d", &or, &dest, &nrel);
		fprintf(fp, "%d %d %d\n", or, dest, nrel);
		printf("Deseja inserir outra relação?\n1 - Sim\n0 - Não\n");
		scanf("%d", &flag);
	} 
	fclose(fp);
}

void exclusaoAd(int **matriz, int d) {
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
					VERTICES = contaVertices();
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
}

void insercaoAd(int **matriz, int d) {
	int insercao;
			printf("Deseja inserir um vertice?\n1. Sim; 2. Não\n");
			do {
				scanf("%i", &insercao);
				if(insercao == 1) {
					insereNoAd();
					matriz = liberaMatriz(matriz);
					VERTICES = contaVertices();
					contaArestas();
					matriz = alocaMatriz(VERTICES, VERTICES);
					openFileGrafoAd(matriz, d);
					mostrarMatrizAd(matriz);
				} 
			} while (insercao != 1 && insercao != 2);
}

void exclusaoId(int **matriz, int d) {
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
					contaArestas();
					printf("aloca\n");
					VERTICES = contaVertices();
					contaArestas();
					matriz = alocaMatriz(ARESTAS, VERTICES);
					openFileGrafoId(matriz, d);
					mostrarMatrizId(matriz);
				} else if (exclusao == 2) {
					break;
				} else {
					printf("Invalido.\n");
				}		
			
			} while(exclusao != 1 && exclusao != 2);
}

void insercaoId(int **matriz, int d) {
	int insercao;
			printf("Deseja inserir um vertice?\n1. Sim; 2. Não\n");
			do {
				scanf("%i", &insercao);
				if(insercao == 1) {
					insereNoAd();
					matriz = liberaMatriz(matriz);
					VERTICES = contaVertices();
					contaArestas();
					matriz = alocaMatriz(ARESTAS, VERTICES);
					openFileGrafoId(matriz, d);
					mostrarMatrizId(matriz);
				} 
			} while (insercao != 1 && insercao != 2);
}