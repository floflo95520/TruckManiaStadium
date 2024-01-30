#ifndef PROTOTYPE_H
#define PROTOTYPE_H
#define TAILLE 100


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


#endif