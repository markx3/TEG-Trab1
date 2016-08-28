#ifndef _GRAFO_H
#define _GRAFO_H

int VERTICES;
int ARESTAS;

int openFileVertices();

void contaArestas();

/* Abrir arquivo com as relações da matriz de adjacencia não direcionada */
void openFileGrafoAd(int **matriz, int direcionado);

void openFileGrafoId(int **matriz);

/* Função para calcular o grau de um vértice do grafo */
int calculaGrau(int vertice, int **vetor);
void mostrarMatrizAd(int **matriz);

void excluiVerticeAd(int no);

int **alocaMatriz(int linhas, int colunas);
int **liberaMatriz(int **matriz);

#endif
