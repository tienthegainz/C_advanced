#include <stdio.h>
int n=7;
int m=3;
int a[7];
void init(){
  int i;
  for(i=0;i<m;i++) a[i]=1;
  for(;i<n;i++) a[i]=0;
}
void print(){
  for(int i=n-1;i>=0;i--) printf("%d", a[i]);
  printf("\n");
}
void swap(int x, int y){
  int c=a[x];
  a[x]=a[y];
  a[y]=c;
}
void try(int x){
  int i,j;
  for(i=x;a[i]!=1&&i>-1;i--); printf("Gia tri cua i:%d\n",i );
  if(i==-1) return;
  j=i;
  while(a[j+1]!=1&&j<(n-1)){
    swap(j+1,j);
    print();
    try(j);
    j++;
  }
  if(x!=n) swap(i,j);
  if(x==n) return;
}
int main() {
  /* code */
  init();
  print();
  try(n);
  return 0;
}
