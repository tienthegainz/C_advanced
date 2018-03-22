#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "train_graph.h"

Graph createGraph(int size){ //khoi tao ma tran
  Graph new;
  new.sizemax=size;
  return new;
}

void setEdge(Graph* graph,int v1){ //thiet lap he thong ban dau
  int i,j,x,y;
  for(x = 1 ; x <= v1 ; x++) //setup toan bo he thong ve so 0
    for(y = 1 ; y <= v1 ; y++) (*graph).matrix[x][y]=0;
  for(x =1; x<= v1 ; x++) (*graph).matrix[x][x]=0; //moi diem deu connect voi chinh no
}

void connected(Graph* graph, int v1, int v2){ //ket noi cac mang tau
  (*graph).matrix[v1][v2] =1;
  (*graph).matrix[v2][v1] =1;
  printf("Da ket noi dinh %d-%d\n",v1,v2);
}

/*int getConnectedVertices(Graph* graph, int vertex, int output){ // return số các đỉnh liên thông

}*/
