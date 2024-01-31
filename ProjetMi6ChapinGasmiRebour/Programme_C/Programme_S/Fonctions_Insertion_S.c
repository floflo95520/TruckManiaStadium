#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_S.h"

Ptrajet creerNoeud(int NouveauId, float distance){
  Ptrajet n=malloc(sizeof(trajet));
  if(n==NULL){
  printf("Erreur d'allocation mémoire.");
  exit(1);
  }
  n->Id=NouveauId;
  n->max=distance;
  n->min=distance;
  n->max_min=0;
  n->somme=distance;
  n->count=1;
n->moyenne=n->somme/n->count;
  n->equilibre=0;
  n->fg=NULL;
  n->fd=NULL;
return n;
}

Ptrajet creerNoeudSecond(int NouveauId, float Nvmax, float Nvmin, float Nvmax_min, float NvSomme, int NvCount, float NvMoyenne){
Ptrajet n=malloc(sizeof(trajet));
if(n==NULL){
printf("Problème d'allocation mémoire. Fin du programme.");
exit(2);
}
n->Id=NouveauId;
n->max=Nvmax;
n->min=Nvmin;
n->max_min=Nvmax_min;
n->somme=NvSomme;
n->count=NvCount;
n->moyenne=NvMoyenne;

n->fg=NULL;
n->fd=NULL;
n->equilibre=0;
return n;
}


Ptrajet insertAvl( Ptrajet t, int NumId, float NewDistance, int *h ){
  if(t==NULL){
  *h=1;
  return creerNoeud(NumId,NewDistance);
  }
  else if(NumId < t->Id){
  t->fg=insertAvl(t->fg, NumId, NewDistance, h);
  *h=-*h;
  }
  else if(NumId > t->Id){
  t->fd=insertAvl(t->fd,NumId,NewDistance, h);
  }
  else{
  *h=0;
  if(NewDistance > t->max){
  t->max=NewDistance;
  }
  else if(NewDistance < t->min){
  t->min=NewDistance;
  }
  t->max_min= (t->max)-(t->min);
  t->somme+=NewDistance;
  t->count=t->count+1;
  t->moyenne=t->somme/t->count;
  return t;
  }

if(*h!=0){
t->equilibre+=*h;
t=equilibrageAVL(t);
if(t->equilibre==0){
*h=0;
}
else{
*h=1;
}
}
return t;
}

//a=nouveau AVL
//b=Ancien AVL

Ptrajet insertAvlSecond(Ptrajet a, Ptrajet b, int *h){
  if(a==NULL){
    return creerNoeudSecond(b->Id, b->max, b->min, b->max_min, b->somme, b->count, b->moyenne);
  }
  else if(b->max_min < a->max_min){
    a->fg=insertAvlSecond(a->fg,b,h);
    *h=-*h;
  }
  else if(b->max_min > a->max_min){
    a->fd=insertAvlSecond(a->fd,b,h);
  }
  else{
  *h=0;
  return a;
  }
  
  if(*h!=0){
  a->equilibre = a->equilibre + *h;
  a=equilibrageAVL(a);
  
  if(a->equilibre==0){
  *h=0;
  }
  else{
  *h=1;
  }
  }
  return a;
  
}


