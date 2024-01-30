#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <Prototype_S.h>

Ptrajet premierAvl(Ptrajet t, int N){
FILE * f=fopen("fichierstemporaires/data_s.txt","r");
if(f==NULL){
printf("Erreur d'ouverture du fichier. Fin du programme.");
exit(7);
}
int i=0;
int TmpId=0;
float TmpDistance=0;


fscanf(f,"%d %f", &TmpId, &TmpDistance);
t=creerNoeud(TmpId,TmpDistance);
i=1;
int eq=t->equilibre;

while(i!=N){
fscanf(f,"%d %f", &TmpId, &TmpDistance);
t=insertAvl(t,TmpId,TmpDistance,&eq);

i++;
}
fclose(f);
return t;
}
 
void enfiler(File * f, Ptrajet t){
if(t==NULL){
printf("Erreur dans l'enfilement. Fin du programme");
exit(8);
}
chainon * n=malloc(sizeof(chainon));
if(n==NULL){
printf("Erreur d'allocation mémoire. Fin du programme.");
exit(2);
}
n->tr=t;
n->suivant=NULL;

if(f->tete==NULL){
f->tete=n;
f->queue=n;
}
else{
f->queue->suivant=n;
f->queue=f->queue->suivant;
}
}

void defiler(File *f, Ptrajet * tra){
if(f==NULL){
printf("Erreur de file. Fin du programme.");
exit(11);
}

if(f->tete==f->queue){
*tra=f->tete->tr;
f->tete=NULL;
f->queue=NULL;
}
else{
*tra=f->tete->tr;
chainon * temp=f->tete;
f->tete=f->tete->suivant;
free(temp);
}
}

void enfilerArbre(Ptrajet t, File *f){
if(t!=NULL){
enfiler(f,t);
enfilerArbre(t->fg,f);
enfilerArbre(t->fd,f);
}
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