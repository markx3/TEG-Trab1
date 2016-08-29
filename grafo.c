#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int openFileVertices() {
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

	/* Atribuindo 0 à matriz */
	/*for(i = 0; i < VERTICES; i++) {
		for (j = 0; j < VERTICES; j++) {
			matriz[i][j] = 0;
		}
	}*/

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

void openFileGrafoId(int **matriz) {
	int i, j;
	int verticeOrigem, verticeDestino, aresta;
	/* Atribuindo 0 à matriz */
	for(i = 0; i < ARESTAS; i++) {
		for(j = 0; j < VERTICES; j++) {
			matriz[i][j] = 0;
		}		
	}
	
	FILE *in = fopen("grafo.txt", "r");
	while(fscanf(in, "%i %i u%i #", &verticeOrigem, &verticeDestino, &aresta) != EOF) {
			matriz[aresta][verticeOrigem] = 1;
			matriz[aresta][verticeDestino] = 1;
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
			for(i = 0; i < VERTICES; i++) {
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
	char buf[100];
	int or = 0, dest = 0, nrel = 0, flag = 1;
	FILE *fp = fopen("grafo.txt", "a");
	int i = 0;
	printf("Insira o nó e suas relações (da mesma forma que do arquivo grafo.txt)\nEntre com 0 para encerrar a entrada.\n");
	while (flag != 0) {
		scanf("%d %d %d", &or, &dest, &nrel);
		fprintf(fp, "%d %d %d\n", or, dest, nrel);
		printf("Deseja inserir outra relação?\n");
		scanf("%d", &flag);
	} 
	FILE *vert = fopen("vertices.txt", "w");
	VERTICES++;
	fprintf(vert, "%d", VERTICES);
	fclose(vert);
	fclose(fp);
}