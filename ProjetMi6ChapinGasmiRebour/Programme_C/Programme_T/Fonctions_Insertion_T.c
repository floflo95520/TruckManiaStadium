#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_T.h"

#define TAILLE 100

Avl2 * creerAvlInterieur(int routeId){
  Avl2 * n=malloc(sizeof(Avl2));
  if(n==NULL){
  exit(1);
  }
  n->fg=NULL;
  n->fd=NULL;
  n->equilibre=0;


  n->routeId=routeId;

  return n;

}

Avl * creerAvl(char nom_ville[],int routeId, int Num_etape){
  Avl * n=malloc(sizeof(Avl));
  if(n==NULL){
    exit(1);
  }
  n->fg=NULL;
  n->fd=NULL;
  n->equilibre=0;
  n->count=1;
  strcpy(n->nom,nom_ville);
  if(Num_etape==1){
    n->departCount=1;
  }
  else{
    n->departCount=0;
  }
  n->Avl_interieur=creerAvlInterieur(routeId);

  return n;
}




Avl2 *insertionAvlInterieur(Avl2 *a,int *h, int route_ID, int *v){
  
    
    if(a==NULL){
        *h = 1;
        return creerAvlInterieur(route_ID);
    }
    else if(route_ID < a->routeId){

        a->fg = insertionAvlInterieur(a->fg, h, route_ID, v);
        *h = -*h;
    }
    else if(route_ID > a->routeId){
        a->fd = insertionAvlInterieur(a->fd, h, route_ID, v);
    }
    else{
        *h = 0;
        *v = -1;
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl2(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl *insertionAvl(Avl *a,int *h, int route_ID,int step_ID, char city_name[]){
    if(a==NULL){
        *h = 1;
        return creerAvl(city_name, route_ID, step_ID);
    }
    else if(strcmp(city_name, a->nom) < 0){

        a->fg = insertionAvl(a->fg, h, route_ID, step_ID, city_name);
        *h = -*h;
    }
    else if(strcmp(city_name, a->nom) > 0){
        a->fd = insertionAvl(a->fd, h, route_ID, step_ID, city_name);
    }
    else{ //already in
        *h = 0;
        int x = a->Avl_interieur->equilibre;
        int v = 0;
        a->Avl_interieur = insertionAvlInterieur(a->Avl_interieur,&x, route_ID, &v);
        if(v != -1){
            a->count++;
        }
        if(step_ID==1){
            a->departCount = (a->departCount) + 1;
        }
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl * creerAvlSecond(char nom_ville[],int departCount,int count){
    Avl* n = malloc(sizeof(Avl));
    if (n == NULL) {
        exit(3); 
    }
    strcpy(n->nom, nom_ville);
    n->departCount = departCount;
    n->count = count;

    n -> fg = NULL;
    n -> fd = NULL;
    n->equilibre = 0;
    return n;
}

Avl *insertionSecondAvl(Avl *a, Avl *b, int *h){
    //printf("in\n");
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(b->count < a->count){
        //printf("in");
        a->fg = insertionSecondAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(b->count > a->count){
        a->fd = insertionSecondAvl(a->fd,b, h);
    }
    else{ //already in
        *h = 0;
        //printf("b SOL is %d and a SOL is %d\n", b->size, a->size);        
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl *insertionTroisiemeAvl(Avl *a, Avl *b, int * h){
    //printf("in\n");
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(strcmp(b->nom,a->nom)<0){
        //printf("in");
        a->fg = insertionTroisiemeAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(strcmp(b->nom,a->nom)>0){
        a->fd = insertionTroisiemeAvl(a->fd,b, h);
    }
    else{ //already in
        *h = 0;
        //printf("b SOL is %d and a SOL is %d\n", b->size, a->size);        
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}