#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_T.h"

#define TAILLE 100








chainon *creationchainon(Avl *a){
    chainon *n = malloc(sizeof(chainon));
    if(n==NULL){exit(8);}
    n->suivant = NULL;
    n->noeud= a;
    return n;
}

void enfiler(File *f, Avl *a){
    if(a==NULL){exit(5);}
    chainon*n = creationchainon(a);
    if(f->debut==NULL){
        f->debut=n;
        f->fin=n;
    }
    else{
        f->fin->suivant = n;
        f->fin = f->fin->suivant;
    }
}

void defiler(File *f, Avl **b){
    if(f==NULL){exit(9);}
    chainon *n = f->debut;
    if(n==NULL){exit(55);}
    *b = n->noeud;
    f->debut = f->debut->suivant;

    if(f->debut==NULL){
        f->fin=NULL;
    }
    free(n);

}

void avlDansFile(Avl * a, File *f){
    if(a!=NULL){
        avlDansFile(a->fg,f);
        enfiler(f,a);
        avlDansFile(a->fd,f);
    }

}

