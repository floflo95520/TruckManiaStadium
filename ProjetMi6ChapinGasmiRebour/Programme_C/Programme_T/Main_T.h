#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAILLE 100


typedef struct Avl2{
  struct Avl2 * fg;
  struct Avl2 * fd;
  int equilibre;
  int routeId;
}Avl2;

typedef struct Avl{
struct Avl * fg;
struct Avl * fd;
int equilibre;

char nom[TAILLE];
int count;
int departCount;
Avl2 * Avl_interieur;
}Avl;

typedef struct chainon{
    Avl * noeud;
    struct chainon * suivant;
}chainon;

typedef struct{
    chainon * debut;
    chainon * fin;
}File;

//Fonctions_Insertion_T.c
Avl2 * creerAvlInterieur(int routeId);
Avl * creerAvl(char nom_ville[],int routeId, int Num_etape);
Avl2 *insertionAvlInterieur(Avl2 *a,int *h, int route_ID, int *v);
Avl *insertionAvl(Avl *a,int *h, int route_ID,int step_ID, char city_name[]);
Avl * creerAvlSecond(char nom_ville[],int departCount,int count);
Avl *insertionSecondAvl(Avl *a, Avl *b, int *h);
Avl *insertionTroisiemeAvl(Avl *a, Avl *b, int * h);

//Fonctions_Rotations_Avl_T.c
Avl* rotationGauche(Avl* a);
Avl* rotationDroite(Avl* a);
Avl* doubleRotationDroite(Avl* a);
Avl* doubleRotationGauche(Avl* a);
Avl2* rotationGauche2(Avl2* a);
Avl2* rotationDroite2(Avl2* a);
Avl2* doubleRotationDroite2(Avl2* a);
Avl2* doubleRotationGauche2(Avl2* a);
Avl* equilibrageAvl(Avl* a);
Avl2* equilibrageAvl2(Avl2* a);

//Construction_Avl_Données.c
Avl* construireAvl(Avl * a, int taille);
Avl *SecondAvl(File *f);
Avl * Avl10premieresvilles(Avl * a,File * f);

//Fonctions_Files_T.c
chainon *creationchainon(Avl *a);
void enfiler(File *f, Avl *a);
void defiler(File *f, Avl **b);
void avlDansFile(Avl * a, File *f);
void enfilerArbre(Avl *a, File *f);

#endif