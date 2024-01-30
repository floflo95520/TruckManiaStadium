#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <Prototype_S.h>

typedef struct trajet{
int Id;
float max;
float min;
float max_min;
float moyenne;
int somme;
int count;
int equilibre;
struct trajet * fg;
struct trajet * fd;
}trajet;

typedef struct chainon{
trajet * tr;
struct chainon * suivant;
}chainon;

typedef struct{
chainon * tete;
chainon * queue;
}File;

typedef struct trajet * Ptrajet;

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

Ptrajet rotationGauche(Ptrajet t){
  if(t==NULL){
  exit(5);
  }
  Ptrajet pivot;
  int eq_a,eq_p;
  pivot=t->fd;
  t->fd=pivot->fg;
  pivot->fg=t;
  eq_a=t->equilibre;
  eq_p=pivot->equilibre;
  t->equilibre=eq_a-fmax(eq_p,0)-1;
  int min1=fmin(eq_a-2,eq_a+eq_p-2);
  pivot->equilibre=fmin(min1,eq_p-1);
  t=pivot;
  return t;
}

Ptrajet rotationDroite(Ptrajet t){
  if(t==NULL){
  exit(6);
  }
  Ptrajet pivot;
  int eq_a,eq_p;
  pivot=t->fg;
  t->fg=pivot->fd;
  pivot->fd=t;
  eq_a=t->equilibre;
  eq_p=pivot->equilibre;
  t->equilibre=eq_a-fmin(eq_p,0)+1;
  int max1=fmax(eq_a+2,eq_a+eq_p+2);
  pivot->equilibre=fmax(max1,eq_p+1);
  t=pivot;
  return t;
}

Ptrajet doubleRotationGauche(Ptrajet t){
  if(t==NULL){
    exit(1);
  }
  t->fd=rotationDroite(t->fd);
  return rotationGauche(t);
}

Ptrajet doubleRotationDroite(Ptrajet t){
  if(t==NULL){
    exit(2);
  }
  t->fg=rotationGauche(t->fg);
  return rotationDroite(t);
}

Ptrajet equilibrageAVL(Ptrajet t){
if(t==NULL){
exit(10);
}
if(t->equilibre >= 2){
  if(t->fd->equilibre >= 0){
    return rotationGauche(t);
  }
  else{
    return doubleRotationGauche(t);
  }
}
else if(t->equilibre <= -2){
  if(t->fg->equilibre <= 0){
    return rotationDroite(t);
  }
  else{
    return doubleRotationDroite(t);
  }
}
return t;
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


