#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_S.h"

Ptrajet premierAvl(Ptrajet t, int N){
FILE * f=fopen("fichierstemporaires/data_s.txt","r");
if(f==NULL){
printf("Erreur d'ouverture du fichier. Fin du programme.");
exit(7);
}
int i=0;
int TmpId=0;
float TmpDistance=0;


int r=fscanf(f,"%d %f", &TmpId, &TmpDistance);
if(r!=2){
  printf("Erreur lors de la récupération des données. Fin du programme");
  exit(5);
}
t=creerNoeud(TmpId,TmpDistance);
i=1;
int eq=t->equilibre;

while(i!=N){
r=fscanf(f,"%d %f", &TmpId, &TmpDistance);
if(r!=2){
  printf("Erreur lors de la récupération des données. Fin du programme");
  exit(5);
}
t=insertAvl(t,TmpId,TmpDistance,&eq);

i++;
}
fclose(f);
return t;
}

Ptrajet secondAvl(Ptrajet t, File * f){
  if(f==NULL){
  printf("Erreur de file. Fin du programme");
  exit(12);
  }
  Ptrajet temp;
  defiler(f,&temp);
  t=creerNoeudSecond(temp->Id,temp->max,temp->min,temp->max_min,temp->somme,temp->count,temp->moyenne);
  int h;
  
  while(f->tete!=NULL){
  defiler(f,&temp);
  h=t->equilibre;
  t=insertAvlSecond(t,temp,&h);
  }
return t;
}