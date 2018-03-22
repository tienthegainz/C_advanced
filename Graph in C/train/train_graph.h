#ifndef EXAMPLE_H_
#define EXAMPLE_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
typedef struct{
  int matrix[MAX][MAX];
  int sizemax;
} Graph;
Graph createGraph(int size); //khoi tao ma tran
void setEdge(Graph* graph,int v1); //thiet lap he thong
void connected(Graph* graph, int v1, int v2); //ket noi mang tau
int getConnectedVertices(Graph* graph, int vertex, int output); // return số các đỉnh liên thông
#endif
