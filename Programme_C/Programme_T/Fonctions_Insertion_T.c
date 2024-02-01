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
  //On initialise les membres de la structure
  n->fg=NULL;
  n->fd=NULL;
  n->equilibre=0;
  n->count=1;
  strcpy(n->nom,nom_ville);
  //Si Num_etape==1, alors c'est une ville de départ
  if(Num_etape==1){
    n->departCount=1;
  }
  else{
    n->departCount=0;
  }
  //On crée l'Avl contenu dans un noeud du premier Avl qui va stocker les routes Id où la ville est traversée pour compter le nombre de fois que la ville est traversée
  n->Avl_interieur=creerAvlInterieur(routeId);

  return n;
}




Avl2 *insertionAvlInterieur(Avl2 *a,int *h, int route_ID, int *v){
  //On insère le route Id dans l'avl contenu dans un Noeud du premier Avl    
    if(a==NULL){
        *h = 1;
        return creerAvlInterieur(route_ID);
    }
    else if(route_ID < a->routeId){ //Avl trié en fonction des Route Id

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
    else if(strcmp(city_name, a->nom) < 0){ //Avl trié en fonction des noms de ville

        a->fg = insertionAvl(a->fg, h, route_ID, step_ID, city_name);
        *h = -*h;
    }
    else if(strcmp(city_name, a->nom) > 0){
        a->fd = insertionAvl(a->fd, h, route_ID, step_ID, city_name);
    }
    else{ //Si le noeud correspondant à la ville a déjà été créé
    //On met à jour les informations du noeud et on insère le route Id dans l'avl contenu dans le noeud
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

Avl * creerAvlSecond(char nom_ville[],int departCount,int count){ //Fonction qui crée un noeud pour le second Avl
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
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(b->count < a->count){
        a->fg = insertionSecondAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(b->count > a->count){
        a->fd = insertionSecondAvl(a->fd,b, h);
    }
    else{ //Si jamais il y a un doublon on ne fait rien
        *h = 0;
            
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

Avl *insertionTroisiemeAvl(Avl *a, Avl *b, int * h){ //Fonction pour insérer les noeud dans le dernier Avl trié en fonction des noms de ville
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(strcmp(b->nom,a->nom)<0){
        a->fg = insertionTroisiemeAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(strcmp(b->nom,a->nom)>0){
        a->fd = insertionTroisiemeAvl(a->fd,b, h);
    }
    else{
        *h = 0;       
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