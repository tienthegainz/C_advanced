#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "train_graph.h"
int station=0;
void read_station(FILE *fptr);//gan cac gia tri dai dien cho cac station
void read_sys(FILE *fptr, Graph *in_sys);//khoi tao vao nap vao cac mang tau dien ngam

int main(){
  FILE *fptr;
  char filename[]="train_database.txt";
  if((fptr=fopen(filename,"r"))==NULL){
    printf("Can't open %s\n", filename );
    return -1;
  }
  read_station(fptr);
  //printf("%d\n",station);
  Graph *in_sys;
  read_sys(fptr,in_sys);
  fclose(fptr);
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

void read_sys(FILE *fptr, Graph *in_sys){
  int num[station];
  char str1[50];
  char str2[50];
  char c;
  int j=1,k=1,l=1;
  while(!feof(fptr)){
    int i=1;
    fscanf(fptr,"%s %s ",str1,str2);
    if(feof(fptr)) break;
    do{ //lay cac diem trong mang tau
      fscanf(fptr,"%d",&num[i]);
      c=fgetc(fptr);
      printf("%d %c\n", num[i],c);
      i++;
    }
    while(c!='\n'&&c!='\0'&&i<=station);
    printf("Breaked out\n");
    in_sys[j]=createGraph(station);
    while(k<=i){
      for(l=1 ;l<=(i-k);l++)
      connected(&in_sys[j],k,k+l);
    }
  }
}
