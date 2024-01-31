#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_T.h"

#define TAILLE 100

Avl* construireAvl(Avl * a, int taille){

    FILE * fichier = fopen("fichierstemporaires/data_t.txt","r");
    if(fichier==NULL){
        exit(3);
    }
    char city_a[TAILLE];
    char city_b[TAILLE];
    int tempNumEtape;
    int tempRouteID;
    int r;

    r=fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b);
    //printf("%d %d %s %s",tempRouteID,tempNumEtape,city_a,city_b);
    if(r!=4){
        printf("Erreur lors de la récupération des données. Fin du programme.");
        exit(5);
    }
    a = creerAvl(city_a, tempRouteID, tempNumEtape);
    int equilibre = a->equilibre;
    a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b);


    for(int i = 0; i<taille;i++){
        fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b);
        /*if(r!=4){
        printf("Erreur lors de la récupération des données. Fin du programme.");
        exit(5);
    }*/
        a = insertionAvl(a, &equilibre, tempRouteID, tempNumEtape, city_a);
        a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b);
        
    }
    fclose(fichier);
    return a;

}

Avl *SecondAvl(File *f){
    Avl *tmp;
    int h;

    defiler(f, &tmp);
    Avl *n = creerAvlSecond(tmp->nom,tmp->departCount,tmp->count);

    while(f->debut != NULL){
        defiler(f, &tmp);
        h = n->equilibre;
        n = insertionSecondAvl(n, tmp, &h);
    }

    return n;
}


Avl * Avl10premieresvilles(Avl * a,File * f){
    if(f==NULL){
        exit(3);
    }
    Avl * tmp;
    defiler(f,&tmp);
    a=creerAvlSecond(tmp->nom,tmp->departCount,tmp->count);
    int equilibre=a->equilibre;
    while (f->debut!=NULL){
        defiler(f,&tmp);
        a=insertionTroisiemeAvl(a,tmp,&equilibre);
    }
    return a;
}
