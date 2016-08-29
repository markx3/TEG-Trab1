#ifndef _GRAFO_H
#define _GRAFO_H

int VERTICES;
int ARESTAS;

int contaVertices();

void contaArestas();

/* Abrir arquivo com as relações da matriz de adjacencia não direcionada */
void openFileGrafoAd(int **matriz, int direcionado);

void openFileGrafoId(int **matriz, int direcionado);

/* Função para calcular o grau de um vértice do grafo */
int calculaGrau(int vertice, int **vetor);
void mostrarMatrizAd(int **matriz);
void mostrarMatrizId(int **matriz);

void excluiVerticeAd(int no);

int **alocaMatriz(int linhas, int colunas);
int **liberaMatriz(int **matriz);
void insereNoAd();
void exclusaoAd(int **matriz, int d);
void insercaoAd(int **matriz, int d);
void exclusaoId(int **matriz, int d);
void insercaoId(int **matriz, int d);
void matrAdjComplemento(int **matriz);

#endif
