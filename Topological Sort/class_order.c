#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
#define MAX 100
typedef struct graphdata{
  int outd; /*so vector trỏ đi*/
  JRB line; /*luu cac phan tu ma no tro toi*/
}gdata;

typedef struct Node{
  char data[MAX];
  struct Node *next;
}node;

typedef struct Queue{
  node *front;
  node *last;
  unsigned int size;
}queue;

gdata init_gdata(){
  gdata temp;
  int outd = 0;
  temp.line = make_jrb();
  return temp;
}

void initqueue(queue * q){
  q->front=NULL;
  q->last=NULL;
  q->size=0;
}

char* front(queue *q){
  return q->front->data;
}

char* dequeue(queue *q){
  q->size--;
  node *tmp=q->front;
  char* temp;
  strcpy(temp,tmp->data);
  q->front=q->front->next;
  free(tmp);
  return temp; /*Tra ve ten chua cac phan tu mà no tro toi*/
}

void enqueue(queue *q,char* data){
  q->size++;
  if(q->front==NULL){
    q->front = (node*)malloc(sizeof(node));
    strcpy(q->front->data, data);
    q->front->next=NULL;
    q->last=q->front;
  }
  else{
    q->last->next = (node*)malloc(sizeof(node));
    strcpy(q->last->next->data, data);
    q->last->next->next=NULL;
    q->last=q->last->next;
  }
}

int emptyq(queue *q){
  if(q->size==0)
    return q->size;
}

void tsort(JRB graph,queue *q){
  JRB rnode;
  gdata *g;
  if(graph->val.v == NULL) {
    printf("There is no class\n");
    return;
  }
  jrb_rtraverse(rnode,graph){ /*di vao xem tung node*/
    g= (gdata*) (rnode->val.v);
  }
}

int main(int argc,char **argv){
  int fn;
  IS is;
  int state=0;
  JRB class, rnode, rnode2;
  class = make_jrb();
  if (argc <= 1) {
    fprintf(stderr, "usage: train data-files\n");
    exit(1);
  }
  for (fn = 1; fn < argc; fn++){
    is = new_inputstruct(argv[fn]);
    if (is == NULL) { perror(argv[fn]); exit(1); };
    while(get_line(is) >= 0){
      if(strcmp(is->fields[0],"[ClassList]")==0){
        state=1;
        printf("Class list: Code name - Class name\n");
      }
      else if(strcmp(is->fields[0],"[ClassOrder]")==0){
        state=2;
        printf("Order of classes:\n" );
      }
      else if(state == 1){
        gdata temp;
        temp = init_gdata();
        jrb_insert_str(class, strdup(is->fields[0]), new_jval_v(temp));
        for(int i=0;i<is->NF;i++) printf("%s ", is->fields[i]);
        printf("\n");
      }
      else if(state == 2 && is->NF ==3){
        rnode = jrb_find_str(class, is->fields[0]);
        if(rnode == NULL){
          printf("There is no class. Error\n");
          return 0;
        }
        gdata* temp;
        temp =(gdata*)rnode->val.v; //bug
        temp->outd ++;
        jrb_insert_str(temp->line,strdup(is->fields[2]),new_jval_v(NULL));
      }
    }
  }
    jettison_inputstruct(is);

}
