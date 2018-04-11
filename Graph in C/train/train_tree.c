#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
//#include "dllist.h"

typedef struct {
  char name[100];
  int v;
} Train;
typedef struct {
  char name[100];
  JRB sys;
} Graph;

int main(int argc, char **argv){
  Train tr[10];
  Graph graph[20];
  int fn,i=0,j=0;
  IS is;
  int state;
  int tmp;
  char name[100];
  JRB rnode;
  if (argc <= 1) {
    fprintf(stderr, "usage: train data-files\n");
    exit(1);
  }
  for (fn = 1; fn < argc; fn++){
    is = new_inputstruct(argv[fn]);
    if (is == NULL) { perror(argv[fn]); exit(1); };
    while(get_line(is) >= 0){
      if(is->NF==1){
        if(strcmp(is->fields[is->NF-1],"[STATIONS]") == 0) {
          //printf("1\n");
          state =1;
          printf("Bat dau load du lieu tau\n" );
        }
        else if(strcmp(is->fields[is->NF-1],"[LINES]") == 0) state =2;
        else {
          fprintf(stderr, "File %s, Line %d: Not the proper format\n", is->name, is->line);
          exit(1);
        }
      }
      else if(state ==1 && is->NF ==4&&sscanf(is->fields[is->NF-1], "%d", &tmp) == 1 && sscanf(is->fields[0], "%s", name) == 1){
        //printf("%s %d\n",name,tmp);
        strcpy(tr[i].name, name);
        //printf("1\n");
        tr[i].v=tmp;
        //printf("2\n" );
        printf("%d.%s %d\n",i, tr[i].name,tr[i].v);
        i++;
      }
      else if(state==2 && is->NF>2){
        strcpy(graph[j].name,is->fields[0]);
        graph[j].sys=make_jrb();
        int x;
        for(int x=2;x<is->NF;x++){
          int num=atoi(is->fields[x]);
          Jval y = new_jval_i(num);
          jrb_insert_int(graph[j].sys,y.i,y);
        }
        printf("\n" );
        j++;
      }
    }
    jettison_inputstruct(is);
  }
  j--;
  for(;j>=0;j--){
    printf("%s.", graph[j].name);
    jrb_traverse(rnode,graph[j].sys)
      printf("%d ",rnode->val.i);
    printf("\n" );
  }
}
