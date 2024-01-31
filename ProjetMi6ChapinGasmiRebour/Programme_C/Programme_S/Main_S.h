#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

//Creation_Avl_S.c
Ptrajet premierAvl(Ptrajet t, int N);
Ptrajet secondAvl(Ptrajet t, File * f);

//Fonctions_Files_S.c
void enfiler(File * f, Ptrajet t);
void defiler(File *f, Ptrajet * tra);
void enfilerArbre(Ptrajet t, File *f);

//Fonctions_Insertion_S.c

Ptrajet creerNoeud(int NouveauId, float distance);
Ptrajet creerNoeudSecond(int NouveauId, float Nvmax, float Nvmin, float Nvmax_min, float NvSomme, int NvCount, float NvMoyenne);
Ptrajet insertAvl( Ptrajet t, int NumId, float NewDistance, int *h );
Ptrajet insertAvlSecond(Ptrajet a, Ptrajet b, int *h);

//Fonctions_Rotations_S.c
Ptrajet rotationGauche(Ptrajet t);
Ptrajet rotationDroite(Ptrajet t);
Ptrajet doubleRotationGauche(Ptrajet t);
Ptrajet doubleRotationDroite(Ptrajet t);
Ptrajet equilibrageAVL(Ptrajet t);





#endif