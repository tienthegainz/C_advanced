#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "train_graph.h"
int station=0;
void read_station(FILE *fptr);//gan cac gia tri dai dien cho cac station
int read_sys(FILE *fptr, Graph *in_sys);//khoi tao vao nap vao cac mang tau dien ngam
void search_conn(Graph * in_sys, int search,int sys_num);//tim kiem cac ga noi voi nha ga nay

int main(){
  FILE *fptr;
  char filename[]="train_database.txt";
  if((fptr=fopen(filename,"r"))==NULL){
    printf("Can't open %s\n", filename );
    return -1;
  }
  read_station(fptr);
  //printf("%d\n",station);
  Graph in_sys[MAX];
  int x=read_sys(fptr,in_sys);
  printf("%d\n", x);
  fclose(fptr);
  int search;
  printf("Nhap vao ten mot nha ga ma ban muon tim:");
  scanf("%d", &search);
  search_conn(in_sys,search-1,x);
}




void read_station(FILE *fptr){
  char str[50];
  char str1[50];
  char str2[50];
  int temp;
  fscanf(fptr,"%s",str);
  if(strcmp(str,"[STATIONS]")!=0){
    printf("No station, %s\n",str);
    return;
  }

  while(strcmp(str,"[LINES]")!=0){
    fscanf(fptr,"%s",str);
    if(strcmp(str,"[LINES]")!=0) {
      fscanf(fptr," %s %s %d",str1,str2,&temp);
      //printf("%s %s %s %d\n",str,str1,str2,temp);
    }
  }
  station=temp;
}

int read_sys(FILE *fptr, Graph *in_sys){
  int num[station];
  char str1[50];
  char str2[50];
  char c;
  int j=0,k=0,l=0;
  while(!feof(fptr)){
    k=0;
    int i=0;
    fscanf(fptr,"%s %s ",str1,str2);
    if(feof(fptr)) break;
    do{ //lay cac diem trong mang tau
      fscanf(fptr,"%d",&num[i]);
      c=fgetc(fptr);
      //printf("%d ", num[i]);
      i++;
    }
    while(c!='\n'&&c!='\0'&&i<=station);
    //printf("\n" );
    i--;
    //printf("i = %d j= %d k= %d\n", i,j,k);
    //printf("Breaked out\n");
    in_sys[j]=createGraph(station);
    while(k<=i){
      for(l=1 ;l<=(i-k);l++)
        connected(&in_sys[j],num[k],num[k+l]);
      k++;
    }
    j++;
  }
  return j;
}

void search_conn(Graph * in_sys, int search, int sys_num){
  int i=0,j=0;
  for(i=0; i<sys_num; i++)
    for(j=0;j<station;j++)
      if(in_sys[i].matrix[search][j]==1 && search!=j) printf("Nha ga so S%d o he thong %d duoc ket noi voi nha ga S%d\n", j+1,i+1,search+1);
}
