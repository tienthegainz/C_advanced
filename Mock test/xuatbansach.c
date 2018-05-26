/*Da hoan thanh xong*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
#define MAX 100
typedef struct{
  int vector_num;
  char name[MAX];
  JRB graph;
} graph;


graph* init_graph(char x[]){
  graph *g = (graph*) malloc(sizeof(graph));
  g->vector_num;
  strcpy(g->name,x);
  g->graph=make_jrb();
  return g;
}

int main(int argc, char const *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "No command\n");
    exit(1);
  }
  if(strcmp(argv[1],"help")==0){
    printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
    return 0;
  }
  else if(strcmp(argv[1],"about")==0){
    printf("C advanced 20142 final exam.\n");
    return 0;
  }
  else if(strcmp(argv[1],"i2n")==0){
    JRB book_list,rnode;
    book_list=make_jrb();
    IS is;
    int book_num;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      jrb_insert_int(book_list,id,new_jval_s(strdup(is->fields[0])));
      book_num--;
    }
    jettison_inputstruct(is);
    int id = atoi(argv[3]);
    rnode=jrb_find_int(book_list,id);
    if(rnode==NULL) printf("NOT FOUND\n");
    printf("%s\n",rnode->val.s);
  }
  else if(strcmp(argv[1],"n2i")==0){
    JRB book_list,rnode;
    book_list=make_jrb();
    IS is;
    int book_num;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      jrb_insert_str(book_list,strdup(is->fields[0]),new_jval_i(id));
      book_num--;
    }
    jettison_inputstruct(is);
    rnode=jrb_find_str(book_list,argv[3]);
    if(rnode==NULL) printf("NOT FOUND\n");
    printf("%d\n",rnode->val.i);
  }
  else if(strcmp(argv[1],"cc")==0){ /*tim tat cac cac sach duoc trich dan chung cua i va j ./pr cc file_name i j*/
    JRB book_list,rnode,rnode1;
    book_list=make_jrb();
    IS is;
    int book_num,vector_line;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    vector_line=atoi(is->fields[1]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      graph * temp;
      temp=init_graph(is->fields[0]);
      jrb_insert_int(book_list,id,new_jval_v(temp));
      book_num--;
    }
    //chua co bug
    while(vector_line>0){
      get_line(is);
      int id = atoi(is->fields[0]);
      rnode=jrb_find_int(book_list,id);
      if(rnode == NULL) {
        printf("ERROR\n");
        return 0;
      }
      graph * sub;
      sub = (graph*)(rnode->val.v);
      int id1=atoi(is->fields[1]);
      jrb_insert_int(sub->graph,id1,new_jval_v(NULL));
      vector_line--;
    }
    jettison_inputstruct(is);
    rnode=jrb_find_int(book_list,atoi(argv[3]));
    rnode1=jrb_find_int(book_list,atoi(argv[4]));
    graph *sub = (graph*)(rnode->val.v);
    graph *sub1 = (graph*)(rnode1->val.v);
    jrb_traverse(rnode,sub->graph){
      rnode1= jrb_find_int(sub1->graph,rnode->key.i);
      if(rnode1 != NULL){
        rnode1=jrb_find_int(book_list,rnode->key.i);
        printf("%s\n", ((graph*)(rnode1->val.v))->name);
      }
    }
  }
  else if(strcmp(argv[1],"cr")==0){/*tim tat cac cac sach trich dan chung i va j ./pr cr file_name i j*/
    JRB book_list,rnode,rnode1;
    book_list=make_jrb();
    IS is;
    int book_num,vector_line;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    vector_line=atoi(is->fields[1]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      graph * temp;
      temp=init_graph(is->fields[0]);
      jrb_insert_int(book_list,id,new_jval_v(temp));
      book_num--;
    }
    while(vector_line>0){
      get_line(is);
      int id = atoi(is->fields[1]);
      rnode=jrb_find_int(book_list,id);
      if(rnode == NULL) {
        printf("ERROR\n");
        return 0;
      }
      graph * sub;
      sub = (graph*)(rnode->val.v);
      int id1=atoi(is->fields[0]);
      jrb_insert_int(sub->graph,id1,new_jval_v(NULL));
      vector_line--;
    }
    jettison_inputstruct(is);
    rnode=jrb_find_int(book_list,atoi(argv[3]));
    rnode1=jrb_find_int(book_list,atoi(argv[4]));
    graph *sub = (graph*)(rnode->val.v);
    graph *sub1 = (graph*)(rnode1->val.v);
    jrb_traverse(rnode,sub->graph){
      rnode1= jrb_find_int(sub1->graph,rnode->key.i);
      if(rnode1 != NULL){
        rnode1=jrb_find_int(book_list,rnode->key.i);
        printf("%s\n", ((graph*)(rnode1->val.v))->name);
      }
    }
  }
  else if(strcmp(argv[1],"odg")==0){ /*./pr odg file_name k in ra ten cua tat ca cac an pham trich dan khong qua k an pham. */
    JRB book_list,rnode,rnode1;
    book_list=make_jrb();
    IS is;
    int book_num,vector_line;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    vector_line=atoi(is->fields[1]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      graph * temp;
      temp=init_graph(is->fields[0]);
      jrb_insert_int(book_list,id,new_jval_v(temp));
      book_num--;
    }
    //chua co bug
    while(vector_line>0){
      get_line(is);
      int id = atoi(is->fields[0]);
      rnode=jrb_find_int(book_list,id);
      if(rnode == NULL) {
        printf("ERROR\n");
        return 0;
      }
      graph * sub;
      sub = (graph*)(rnode->val.v); //bug o day
      int id1=atoi(is->fields[1]);
      sub->vector_num++;
      jrb_insert_int(sub->graph,id1,new_jval_v(NULL));
      vector_line--;
    }
    jettison_inputstruct(is);
    int k = atoi(argv[3]);
    jrb_traverse(rnode,book_list){
      graph *g = (graph*)(rnode->val.v);
      if(g->vector_num > k) printf("%s\n", g->name);
    }
  }
  else if(strcmp(argv[1],"rel")==0){ /*./pr rel file_name i : in ra cac an pham duoc i trich dan va ca cac an pham ma duoc cac an pham do trich dan*/
    JRB book_list,rnode,rnode1,rnode2,rnode3;
    book_list=make_jrb();
    IS is;
    int book_num,vector_line;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    book_num=atoi(is->fields[0]);
    vector_line=atoi(is->fields[1]);
    while(book_num>0){
      int id;
      get_line(is);
      id=atoi(is->fields[1]);
      graph * temp;
      temp=init_graph(is->fields[0]);
      jrb_insert_int(book_list,id,new_jval_v(temp));
      book_num--;
    }
    while(vector_line>0){
      get_line(is);
      int id = atoi(is->fields[0]);
      rnode=jrb_find_int(book_list,id);
      if(rnode == NULL) {
        printf("ERROR\n");
        return 0;
      }
      graph * sub;
      sub = (graph*)(rnode->val.v);
      int id1=atoi(is->fields[1]);
      sub->vector_num++;
      jrb_insert_int(sub->graph,id1,new_jval_v(NULL));
      vector_line--;
    }
    jettison_inputstruct(is);
    int find = atoi(argv[3]);
    rnode = jrb_find_int(book_list,find);
    graph * g = (graph *)(rnode->val.v);
    jrb_traverse(rnode,g->graph){
      rnode1= jrb_find_int(book_list,rnode->key.i);
      if(rnode1 != NULL){
        graph * g1 = (graph *)(rnode1->val.v);
        printf("%s\n", g1->name);
        jrb_traverse(rnode2,g1->graph){
          rnode3= jrb_find_int(book_list,rnode2->key.i);
          if(rnode3 != NULL){
            printf("%s\n", ((graph*)(rnode3->val.v))->name);
          }
        }
      }
    }
  }
  return 0;
}
