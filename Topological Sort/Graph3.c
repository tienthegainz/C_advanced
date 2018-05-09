#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

typedef JRB Graph;
typedef struct graphdata{
  int id;
  char name[100];
  int ind; /*so vetor trỏ đến*/
  int outd; /*so vector trỏ đi*/
  Graph line; /*luu cac phan tu ma no tro toi*/
}gdata;

typedef struct Node{
  Graph data;
  struct Node *next;
}node;

typedef struct Queue{
  node *front;
  node *last;
  unsigned int size;
}queue;

void initqueue(queue * q){
  q->front=NULL;
  q->last=NULL;
  q->size=0;
}

Graph front(queue *q){
  return q->front->data;
}

Graph dequeue(queue *q){
  q->size--;
  node *tmp=q->front;
  Graph temp=tmp->data;
  q->front=q->front->next;
  free(tmp);
  return temp; /*Tra ve cay chua cac phan tu mà no tro toi*/
}

void enqueue(queue *q,Graph data){
  q->size++;
  if(q->front==NULL){
    q->front = (node*)malloc(sizeof(node));
    q->front->data = data;
    q->front->next=NULL;
    q->last=q->front;
  }
  else{
    q->last->next = (node*)malloc(sizeof(node));
    q->last->next->data=data;
    q->last->next->next=NULL;
    q->last=q->last->next;
  }
}

int emptyq(queue *q){
  if(q->size==0)
    return q->size;
}

Graph createGraph(){
  Graph graph;
  graph=make_jrb();
  return graph;
}

int hasEdge(Graph graph,int v1,int v2){
  Graph rnode=jrb_find_int(graph,v1);
  if(rnode!=NULL){
    gdata *g=(gdata*)rnode->val.v;
    Graph rnode1=jrb_find_int(g->line,v2);
    if(rnode1!=NULL) return 1;
    else return 0;
  }
  else return -1;
}
void addEdge(Graph *graph,int v1,int v2){
  int i=hasEdge(*graph,v1,v2);
  if(i==0){
    Graph rnode=jrb_find_int(*graph,v1);
    Graph rnode1;
    gdata *g,*g1;
    if(rnode!=NULL){
      rnode1=jrb_find_int(*graph,v2);
      g=(gdata*)rnode->val.v;
      g1=(gdata*)rnode1->val.v;
      g->outd++;
      g1->ind++;
      jrb_insert_int(g->line,g1->id,new_jval_v(g1));
    }
  }
  else if(i==1) printf("node %d and %d already connected",v1,v2);
  else printf("invalid node\n");
}

void printvertex(int x){
  printf("%d , ",x);
}

void tsort(Graph graph,void (*func)(int)){
  Graph rnode,rnode1;
  queue q;
  gdata *g,*g1;
  int indegree[100]={0};
  initqueue(&q);
  jrb_traverse(rnode,graph){
    g=(gdata*)rnode->val.v;
    indegree[g->id]=g->ind;
    if(indegree[g->id]==0){ /*node không có bố*/
      enqueue(&q,rnode);
    }
  }
  while(emptyq(&q)!=0){
    rnode=dequeue(&q);
    g=(gdata*)rnode->val.v; /*đi vào trong cây của các node không có bố trên xem nó chỉ vào đâu*/
    func(g->id);
    jrb_traverse(rnode1,g->line){
      g1=(gdata*)rnode1->val.v;
      indegree[g1->id]--; //vi moi lan not duoc tham la deu do mot node den
      if(indegree[g1->id]==0){
	       enqueue(&q,rnode1);
      }
    }
  }
}

int main(int argc,char **argv){
  gdata *g,*g1;
  Graph jobs,rnode;
  int i,fn;
  IS is;
  char name[100];
  char temp[100];
  char *token;
  if(argc<=1){
    fprintf(stderr,"usage: dpc files\n");
    exit(1);
  }
  jobs=createGraph();
  for(fn=1;fn<argc;fn++){
    is=new_inputstruct(argv[fn]);
    if (is == NULL) {
      perror(argv[fn]);
      exit(1);
    }
    while(get_line(is)>=0){
      strcpy(temp,is->fields[0]);
      g=(gdata*)malloc(sizeof(gdata));
      token=strtok(temp,"=");
      sscanf(token,"%*[^0123456789]%d",&g->id);
      token=strtok(NULL,"=");
      strcpy(g->name,token);
      g->ind=0;
      g->outd=0;
      g->line=createGraph();
      jrb_insert_int(jobs,g->id,new_jval_v(g));
    }
    jettison_inputstruct(is);
  }
  jrb_traverse(rnode, jobs) {
    g = (gdata *) rnode->val.v;
    printf("S%d %s\n", g->id, g->name);
  }
  addEdge(&jobs,0,6);
  addEdge(&jobs,0,1);
  addEdge(&jobs,0,4);
  addEdge(&jobs,1,2);
  addEdge(&jobs,2,7);
  addEdge(&jobs,2,5);
  addEdge(&jobs,3,8);
  addEdge(&jobs,3,4);
  addEdge(&jobs,4,5);
  addEdge(&jobs,6,3);
  addEdge(&jobs,6,2);
  addEdge(&jobs,7,8);
  addEdge(&jobs,9,6);
  tsort(jobs,printvertex);
}
