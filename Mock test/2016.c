#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
#define MAX 100
typedef struct{
  char name[MAX];
  JRB graph;
}graph;
typedef struct{
  int rel_w;
  char name[MAX];
}list;
typedef struct{
  char name[MAX];
  int id;
  int weight;
  int truoc;
  int checked;
}road;


graph* init_graph(char x[]){
  graph * g= (graph*) malloc(sizeof(graph));
  strcpy(g->name,x);
  g->graph= make_jrb();
  return g;
}
void copy_data(list ds[],int count, int rel, char name[]){
  ds[count].rel_w = rel;
  strcpy(ds[count].name,name);
}
int cmpfunc (const void * a, const void * b){
   list *x = (list *)a;
   list *y = (list *)b;
   return ((*y).rel_w-(*x).rel_w);
}
void print_list(list ds[],int count){
  printf("Cac san pham lien quan:\n");
  for(int x=0;x<=count;x++) printf("%s voi he so lien quan %d\n", ds[x].name,ds[x].rel_w);
}
void init_road(road arr[],int num,char x[],int id){
  strcmp(arr[num].name,x);
  arr[num].id=id;
  arr[num].weight=-1;
  arr[num].truoc=-1;
  arr[num].checked=0;
}
int find_id_arr(road arr[],int num,int id){
  for(int i=0;i<=num;i++){
    if(arr[i].id==id) return i;
  }
  return -1;
}
void clear(road arr[],int ele_count,int pos){ //xoa bo viec check du lieu de lam cai moi
  for(int i=0;i<=ele_count;i++) {
    arr[i].checked =0;
    arr[i].weight=-1;
    arr[i].truoc=-1;
  }
  arr[pos].weight=0;
  arr[pos].truoc=pos;
}
int uncheck_short(road arr[], int num){
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
void FSP(JRB pdt_list,road arr[],int ele_count,int pos1,int pos2){ //tim duong ngan nhat theo Djtras
  JRB rnode;
  arr[pos1].checked=1;
  rnode = jrb_find_int(pdt_list,arr[pos1].id);
  graph *g = (graph*) (rnode->val.v);
  int x;
  jrb_traverse(rnode,g->graph){
    x=find_id_arr(arr,ele_count,rnode->key.i);
    if(arr[x].checked ==0){
      printf("Xet: %d -> %d\n",arr[pos1].id,arr[x].id);
      if(x == pos2){
        arr[pos2].weight = rnode->val.i + arr[pos1].weight;
        arr[pos2].truoc = arr[pos1].id;
        return;
      }
      else if(rnode->val.i + arr[pos1].weight < arr[x].weight ||
      arr[x].weight == -1){
        arr[x].weight = rnode->val.i + arr[pos1].weight;
        arr[x].truoc = arr[pos1].id;
        }
      }
  }
  FSP(pdt_list,arr,ele_count,uncheck_short(arr,ele_count),pos2);
}
void print_path(road arr[],int ele_count,int pos1, int pos2){
  int x,count=0;
  if(arr[pos2].truoc == -1){
    printf("Khong co duong di\n");
    return;
  }
  x=pos2;
  printf("Do dai duong di: %d\n", arr[x].weight);
  do{
    printf("%d -> %d\n",arr[x].id, arr[x].truoc);
    x = find_id_arr(arr,ele_count,arr[x].truoc);
    count ++;
  }
  while(x != pos1&&count<=ele_count);
}

int main(int argc, char const *argv[]) { /*product.txt order.txt*/
  if (argc <= 1) {
    fprintf(stderr, "No command or not enough file\n");
    exit(1);
  }
  int check;//su dung de chay menu
  IS is;
  JRB pdt_list,rnode,rnode1,rnode2;
  pdt_list=make_jrb();
  int ele_count=-1;//dem so phan tu trong arr duoi
  road arr[20];//dung de luu duong di ngan nhat tu dau do den dau do
  do{
    printf("1.Doc file san pham va in ra danh sach san pham\n");
    printf("2.Doc file lich su va in ra danh sach giao dich\n");
    printf("3.HIen thi muc do lien quan giua 2 san pham\n");
    printf("4.In ra danh sach san pham co lien quan den nhau\n");
    printf("5.Hien thi quan he giua 2 san pham\n");
    printf("6.Thoat\n");
    printf("Chon option nao:\n");
    scanf("%d",&check);
    switch(check){
      case 1:{
        printf("Danh sach san pham\n");
        is = new_inputstruct(argv[1]);
        if (is == NULL) { perror(argv[2]); exit(1); };
        while(get_line(is)>=0){
          int x = atoi(is->fields[0]);
          jrb_insert_int(pdt_list,x,new_jval_v(init_graph(is->fields[1])));
          ele_count++;
          init_road(arr,ele_count,is->fields[1],x);
          printf("%s.%s\n",is->fields[0],is->fields[1]);
        }
        jettison_inputstruct(is);
      }
      break;
      case 2:{
        printf("Lich su mua ban\n");
        is = new_inputstruct(argv[2]);
        if (is == NULL) { perror(argv[2]); exit(1); };
        while(get_line(is)>=0){
          for(int i=0;i<is->NF;i++){
            int pro = atoi(is->fields[i]);
            rnode=jrb_find_int(pdt_list,pro);
            if(rnode==NULL){
              printf("Can't find product\n");
              break;
            }
            graph* g = (graph*)(rnode->val.v);
            printf("%s ",g->name);
            for(int j=0;j<is->NF;j++){
              if(j != i){
                rnode1= jrb_find_int(g->graph,atoi(is->fields[j]));
                if(rnode1 == NULL){
                  jrb_insert_int(g->graph,atoi(is->fields[j]),new_jval_i(1));
                  //printf("Tao moi san pham %d\n", atoi(is->fields[j]));
                }
                else{
                  rnode1->val.i ++;
                }
              }
            }
          }
          printf("\n");
        }
      }
      break;
      case 3:{
        int id1,id2;
        printf("Nhap vao day id cua 2 san pham (id1 id2):");
        scanf("%d %d",&id1,&id2);
        rnode = jrb_find_int(pdt_list,id1);
        if(rnode == NULL){
          printf("Khong tim thay san pham\n");
          break;
        }
        graph *g = (graph*) (rnode->val.v);
        rnode1 = jrb_find_int(g->graph,id2);
        if(rnode1 == NULL) printf("Hai san pham %d va %d tren khong lien gi den nhau\n",id1,id2);
        else printf("Muc do lien quan cua 2 san pham %d va %d: %d\n",id1,id2,rnode1->val.i);
      }
      break;
      case 4:{
        int id;
        list ds[MAX];
        printf("Nhap vao san pham ban tim kiem:");
        scanf("%d",&id);
        rnode = jrb_find_int(pdt_list,id);
        if(rnode == NULL) printf("Khong tim thay san pham tren\n");
        else{
          graph *g = (graph*) (rnode->val.v);
          int count=0;
          jrb_traverse(rnode1,g->graph){
            rnode2 = jrb_find_int(pdt_list,rnode1->key.i);
            graph *g1 = (graph*) (rnode2->val.v);
            copy_data(ds,count,rnode1->val.i,g1->name); //bug
            count ++;
          }
          qsort(ds, count, sizeof(list), cmpfunc);
          print_list(ds,count-1);
        }
      }
      break;
      case 5:{
        int id1, id2;
        int pos1, pos2;
        printf("Nhap vao id cua 2 san pham ban muon kiem tra quan he (id1 id2):");
        scanf("%d %d", &id1,&id2);
        pos1 = find_id_arr(arr,ele_count,id1);
        pos2 = find_id_arr(arr,ele_count,id2);
        printf("Vi tri: %d - %d\n", pos1, pos2);
        if(pos1 == -1 || pos2 == -1){
          printf("Khong co san pham tren\n");
          break;
        }
        clear(arr,ele_count,pos1);
        FSP(pdt_list,arr,ele_count,pos1,pos2);
        print_path(arr,ele_count,pos1,pos2);
      }
      break;
    }
  }
  while(check!=6);
}
