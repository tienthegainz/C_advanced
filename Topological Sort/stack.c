#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stack.h"
void make_stack(stack *s){
  (*s).top=NULL;
}
int isEmpty_stack(stack s){
  return(s.top==NULL);
}
void push_stack(stack *s,char y[]){
  node *new=(node *)malloc(sizeof(node));
  /*tao bo nho dong cho bien moi*/
  //new->data.num=y.num;
  strcpy(new->data.name,y.name);
  if((*s).top==NULL){
    (*s).top=new;
  }
  else{
    new->next=(*s).top;
    (*s).top=new;
  }
}
void pop_stack(stack *s,el_type *y){
  if(!isEmpty_stack(*s)){
  node *cur=(*s).top;
  //(*y).num=(*s).top->data.num;
  strcpy((*y).name,(*s).top->data.name);
  /*luu gia tri truoc khi xoa*/
  (*s).top=(*s).top->next;
  free(cur);
  }
  else printf("Stack is empty now\n");
}
