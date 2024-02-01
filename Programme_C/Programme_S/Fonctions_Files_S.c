#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_S.h"

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