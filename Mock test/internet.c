#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
#define MAX 100
#define INF 10000
typedef struct{ //luu vao trong cay JRB
  char name[MAX];
  int deg;
  JRB edge;
} data;
typedef struct{ //luu duong di ngan nhat
  char name[MAX];
  int id;
  int weight;
  int truoc;
  int sau;
  int checked;
}road;
typedef struct{
  int id1;
  int id2;
  int weight;
}rel;

data* init_struct(char name[]){ //khoi tao cay con nho
  data *g = (data *) malloc(sizeof(data));
  strcpy(g->name,name);
  g->deg=0;
  g->edge=make_jrb();
  return g;
}
void add_edge(JRB g, int id1, int id2, int weight){ /* them canh vao vo huong*/
  JRB rnode;
  rnode = jrb_find_int(g,id1);
  if(rnode==NULL){
    printf("Can't find ID1\n");
    return;
  }
  data *j = (data*) (rnode->val.v);
  jrb_insert_int(j->edge,id2,new_jval_i(weight));
  j->deg++;
  rnode = jrb_find_int(g,id2);
  if(rnode==NULL){
    printf("Can't find ID2\n");
    return;
  }
  j = (data*) (rnode->val.v);
  jrb_insert_int(j->edge,id1,new_jval_i(weight));
  j->deg++;
}
char* get_vertex_name(JRB j,int id){ /*tim ten theo id*/
  JRB rnode = jrb_find_int(j,id);
  if(rnode == NULL) return NULL;
  data *g = (data*) (rnode->val.v);
  return(g->name);
}
void init_road(road arr[],int num,char x[],int id){ //khoi tao duong di
  strcpy(arr[num].name,x);
  arr[num].id=id;
  arr[num].weight=INF;
  arr[num].truoc=-1;
  arr[num].sau=-1;
  arr[num].checked=0;
}
int find_pos_arr(road arr[],int num,int id){ //tim kiem xem id cua no nam o vi tri nao
  for(int i=0;i<=num;i++){
    if(arr[i].id==id) return i;
  }
  return -1;
}
void clear_arr(road arr[],int ele_count,int pos){ //xoa sach du lieu trong arr
  for(int i=0;i<=ele_count;i++) {
    arr[i].checked =0;
    arr[i].weight=INF;
    arr[i].truoc=-1;
    arr[i].sau=-1;
  }
  arr[pos].weight=0;
  arr[pos].truoc=pos;
}
int uncheck_short(road arr[], int num){ //tra ve vi tri node nho nhat ma chua duoc kiem tra
  int check=1000;
  int val;
  for(int i=0;i<=num;i++){
    if(arr[i].weight<check && arr[i].checked==0 && arr[i].weight!= -1) {
      check = arr[i].weight;
      val = i;
    }
  }
  return val;
}
//cay JRB, arr luu duong di, so phan tu cua arr,vi tri xuat phat, vi tri dich
void FSP(JRB j,road arr[],int ele_count,int pos1,int pos2){ //tim duong ngan nhat theo dijkstra
  JRB rnode;
  arr[pos1].checked=1;
  rnode = jrb_find_int(j,arr[pos1].id);
  data *g = (data*) (rnode->val.v);
  int x;
  jrb_traverse(rnode,g->edge){
    x=find_pos_arr(arr,ele_count,rnode->key.i);
    if(arr[x].checked ==0){
      //printf("Xet: %d -> %d\n",arr[pos1].id,arr[x].id);
      if(x == pos2){
        if(rnode->val.i + arr[pos1].weight < arr[x].weight){
          arr[pos2].weight = rnode->val.i + arr[pos1].weight;
        }
        arr[pos2].truoc = arr[pos1].id;
        arr[pos1].sau = arr[pos2].id;
        printf("Thanh cong\n");
        return;
      }
      else if(rnode->val.i + arr[pos1].weight < arr[x].weight){
        arr[x].weight = rnode->val.i + arr[pos1].weight;
        arr[x].truoc = arr[pos1].id;
        arr[pos1].sau = arr[x].id;
        }
      }
  }
  FSP(j,arr,ele_count,uncheck_short(arr,ele_count),pos2);
}
void print_path(road arr[],int ele_count,int pos1, int pos2){ //in ra do dai va duong di
  int x,count=0;
  if(arr[pos2].truoc == -1){
    printf("Khong co duong di\n");
    return;
  }
  x=pos1;
  printf("Do dai duong di: %d\n", arr[pos2].weight);
  do{
    printf("%d %s\n",arr[x].id, arr[x].name);
    x = find_pos_arr(arr,ele_count,arr[x].sau);
    count ++;
  }
  while(x != pos2&&count<=ele_count);
  printf("%d %s\n",arr[pos2].id, arr[pos2].name);
}
int id_comp(int id,int arr[],int num){
  for(int i=0;i<num;i++) if(arr[i]==id) return 1;
  return 0;
}
void print_edge(rel arr[],int count){
  printf("%d\n", count);
  for(int i=0;i<count;i++){
    printf("%d %d %d\n",arr[i].id1,arr[i].id2,arr[i].weight );
  }
}

int main(int argc, char const *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "No command\n");
    exit(1);
  }
  if(strcmp(argv[1],"-h")==0){
    printf("C-advanced 2015\n");
    return 0;
  }
  else if(strcmp(argv[1],"-v")==0){
    IS is;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    get_line(is);
    int x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      for(int i=0;i<is->NF;i++) {
        printf("%s ", is->fields[i]);
      }
      printf("\n");
      x--;
    }
    return 0;
  }
  else if(strcmp(argv[1],"-w")==0){
    if (argc <= 1) {
      fprintf(stderr, "No command\n");
      exit(1);
    }
    IS is;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    JRB line,rnode;
    line=make_jrb();
    /*doc file:
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      do_something;
      x--;
    }
    */
    get_line(is);
    int x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      jrb_insert_int(line,atoi(is->fields[0]),new_jval_v(init_struct(is->fields[1])));
      x--;
    }
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      add_edge(line,atoi(is->fields[0]),atoi(is->fields[1]),atoi(is->fields[2]));
      x--;
    }
    jettison_inputstruct(is);
    int id1 = atoi(argv[3]);
    int id2 = atoi(argv[4]);
    rnode=jrb_find_int(line,id1);
    if(rnode == NULL){
      printf("Can't find this ID\n" );
      return -1;
    }
    data *g = (data*) (rnode->val.v);
    jrb_traverse(rnode,g->edge){
        if(rnode->key.i == id2) {
          printf("%d\n",rnode->val.i);
          return 0;
        }
    }
    printf("-1\n");
    return 0;
  }
  else if(strcmp(argv[1],"-n")==0){
    if (argc <= 1) {
      fprintf(stderr, "No command\n");
      exit(1);
    }
    IS is;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    JRB line,rnode;
    line=make_jrb();
    /*doc file:
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      do_something;
      x--;
    }
    */
    get_line(is);
    int x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      jrb_insert_int(line,atoi(is->fields[0]),new_jval_v(init_struct(is->fields[1])));
      x--;
    }
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      add_edge(line,atoi(is->fields[0]),atoi(is->fields[1]),atoi(is->fields[2]));
      x--;
    }
    jettison_inputstruct(is);
    int id1 = atoi(argv[3]);
    rnode=jrb_find_int(line,id1);
    if(rnode == NULL){
      printf("Can't find this ID\n" );
      return -1;
    }
    data *g = (data*) (rnode->val.v);
    printf("%d\n",g->deg);
    jrb_traverse(rnode,g->edge){
        printf("%d %s %d\n",rnode->key.i,get_vertex_name(line,rnode->key.i),rnode->val.i);
    }
    return 0;
  }
  else if(strcmp(argv[1],"-p")==0){
    if (argc <= 1) {
      fprintf(stderr, "No command\n");
      exit(1);
    }
    IS is;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    JRB line,rnode;
    line=make_jrb();
    int id1 = atoi(argv[3]);
    int id2 = atoi(argv[4]);
    get_line(is);
    int x = atoi(is->fields[0]);
    road arr[MAX];/*shortest B1*/
    int ele_count=0;/*shortest B1*/
    while(x>0){
      get_line(is);
      jrb_insert_int(line,atoi(is->fields[0]),new_jval_v(init_struct(is->fields[1])));
      init_road(arr,ele_count,is->fields[1],atoi(is->fields[0]));/*shortest B2*/
      ele_count++;/*shortest B2*/
      x--;
    }
    ele_count--;/*shortest B2*/
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      add_edge(line,atoi(is->fields[0]),atoi(is->fields[1]),atoi(is->fields[2]));
      x--;
    }
    clear_arr(arr,ele_count,find_pos_arr(arr,ele_count,id1));/*shortest B3*/
    FSP(line,arr,ele_count,find_pos_arr(arr,ele_count,id1),find_pos_arr(arr,ele_count,id2));/*shortest B4*/
    print_path(arr,ele_count,find_pos_arr(arr,ele_count,id1),find_pos_arr(arr,ele_count,id2));/*shortest B5*/
    jettison_inputstruct(is);
    return 0;
  }
  else if(strcmp(argv[1],"-s")==0){
    if (argc <= 1) {
      fprintf(stderr, "No command\n");
      exit(1);
    }
    IS is;
    is = new_inputstruct(argv[2]);
    if (is == NULL) { perror(argv[2]); exit(1); };
    JRB line;
    line=make_jrb();
    int num_vertex=argc-3;
    int id[num_vertex];
    for(int a=0;a<num_vertex;a++)
      id[a]=atoi(argv[a+3]);
    get_line(is);
    int x = atoi(is->fields[0]);
    printf("%d\n", num_vertex);
    while(x>0){
      get_line(is);
      int y = atoi(is->fields[0]);
      if(id_comp(y,id,num_vertex)){
        for(int i=0;i<is->NF;i++) printf("%s ",is->fields[i]);
        printf("\n");
      }
      x--;
    }
    rel arr[MAX];
    int count=0;
    get_line(is);
    x = atoi(is->fields[0]);
    while(x>0){
      get_line(is);
      int y = atoi(is->fields[0]);
      int z = atoi(is->fields[1]);
      if(id_comp(y,id,num_vertex)&&id_comp(z,id,num_vertex)){
        arr[count].id1=y;
        arr[count].id2=z;
        arr[count].weight=atoi(is->fields[2]);
        count++;
      }
      x--;
    }
    print_edge(arr,count);
    jettison_inputstruct(is);
    return 0;
  }
}
