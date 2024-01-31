#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_T.h"

#define TAILLE 100

Avl* rotationGauche(Avl* a){
    if (a==NULL){
        printf("hi");
        exit(2);
    }
    int eq_a, eq_p;
    Avl* pivot;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(fmin(eq_a-2, eq_a+eq_p-2), eq_p-1);

    a = pivot;
    return a;
}

Avl* rotationDroite(Avl* a) {
    if (a == NULL) {
        printf("hi");
        exit(2);
    }

    int eq_a, eq_p;
    Avl* pivot;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - fmin(eq_p, 0) + 1;
    double max1 = fmax(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = fmax(max1, eq_p + 1);

    a = pivot;
    return a;
}

Avl* doubleRotationDroite(Avl* a){
    if (a == NULL) {
        exit(2);
    }
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

Avl* doubleRotationGauche(Avl* a){
    if (a == NULL) {
        exit(2);
    }
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

Avl2* rotationGauche2(Avl2* a){
    if (a==NULL){
        printf("hi");Avl* doubleRotationGauche(Avl* a);
        exit(2);
    }
    int eq_a, eq_p;
    Avl2* pivot;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(fmin(eq_a-2, eq_a+eq_p-2), eq_p-1);

    a = pivot;
    return a;
}



Avl2* rotationDroite2(Avl2* a) {
    if (a == NULL) {
        printf("hi");
        exit(2);
    }

    int eq_a, eq_p;
    Avl2* pivot;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - fmin(eq_p, 0) + 1;
    double first_compare = fmax(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = fmax(first_compare, eq_p + 1);

    a = pivot;
    return a;
}



Avl2* doubleRotationDroite2(Avl2* a){
    if (a == NULL) {
        exit(2);
    }
    a->fg = rotationGauche2(a->fg);
    return rotationDroite2(a);
}



Avl2* doubleRotationGauche2(Avl2* a){
    if (a == NULL) {
        exit(2);
    }
    a->fd = rotationDroite2(a->fd);
    return rotationGauche2(a);
}


Avl* equilibrageAvl(Avl* a) {
    if (a==NULL) {
        exit(2);
    }

    if (a->equilibre >= 2) {
        if (a->fd->equilibre >= 0) {
            //printf("rotation left : ");
            return rotationGauche(a);
        } else {
            return doubleRotationGauche(a);
            //printf("double rotation left : ");
        }
    } else if (a->equilibre <= -2) {
        if (a->fg->equilibre <= 0) {
            //printf("rotation right : ");
            return rotationDroite(a);
        } else {
            //printf("double rotation right : ");
            return doubleRotationDroite(a);
        }
    }
    return a;
}

Avl2* equilibrageAvl2(Avl2* a) {
    if (a==NULL) {
        exit(2); // Ou une gestion d'erreur appropriée
    }

    if (a->equilibre >= 2) {
        if (a->fd->equilibre >= 0) {
            //printf("rotation left : ");
            return rotationGauche2(a);
        } else {
            return doubleRotationGauche2(a);
            //printf("double rotation left : ");
        }
    } else if (a->equilibre <= -2) {
        if (a->fg->equilibre <= 0) {
            //printf("rotation right : ");
            return rotationDroite2(a);
        } else {
            //printf("double rotation right : ");
            return doubleRotationDroite2(a);
        }
    }
    return a;
}