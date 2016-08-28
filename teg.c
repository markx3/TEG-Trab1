#include <stdio.h>
#include <stdlib.h>

int VERTICES = 0;
int ARESTAS = 0;

int openFileVertices() {
	int tam;
	/* Lendo o tamanho de vértices do grafo */
	FILE *in = fopen("vertices.txt", "r");
	while(fscanf(in, "%i", &tam) != EOF) {
			return tam;
	}
	return tam;
}

void contaArestas() {
	FILE *in = fopen("grafo.txt", "r");
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
	for(i = 0; i < VERTICES; i++) {
		for (j = 0; j < VERTICES; j++) {
			matriz[i][j] = 0;
		}
	}

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
	while(fscanf(in, "%i %i %i #", &v1, &v2, &r) != EOF) {
		if(v1 != no && v2 != no) {
			fprintf(out, "%i %i %i\n", v1, v2, r);
		}		
	}	
	remove("grafo.txt");
	rename("saida.txt", "grafo.txt");	
	fclose(in);
	fclose(out);
	VERTICES--;
}

int **alocaMatriz(int linhas, int colunas) {
	int i;
	int **matriz = (int **) calloc(linhas, sizeof(int)); // LINHAS
			for(i = 0; i < VERTICES; i++) {
				matriz[i] = (int *) calloc(colunas, sizeof(int)); // COLUNAS
	}
	return matriz;
}

int **liberaMatriz(int **matriz) {
	int i;
	for(i = 0; i < VERTICES; i++) {
		free(matriz[i]);
	}
	free(matriz);
	return NULL;
}

int main(void) {	
	VERTICES = openFileVertices();
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
					printf("exclui");
					excluiVerticeAd(no);
					printf("LIBERA");
					matriz = liberaMatriz(matriz);
					printf("aloca");
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
