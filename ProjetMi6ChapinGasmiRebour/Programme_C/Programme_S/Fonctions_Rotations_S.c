#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_S.h"

//Algorithme permettant l'équilibrage d'un Avl

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