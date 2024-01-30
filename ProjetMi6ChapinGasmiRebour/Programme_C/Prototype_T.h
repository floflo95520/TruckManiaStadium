#ifndef PROTOTYPE_H
#define PROTOTYPE_H
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

#endif