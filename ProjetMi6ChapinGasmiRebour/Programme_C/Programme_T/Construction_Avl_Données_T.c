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
        exit(3); // Si l'ouverture du fichier a échoué
    }
    char city_a[TAILLE];
    char city_b[TAILLE];
    int tempNumEtape;
    int tempRouteID;
    int r=0;

    r=fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b); // On récupère la première ligne du fichier data_t.txt
    //printf("%d %d %s %s",tempRouteID,tempNumEtape,city_a,city_b);
    if(r!=4){
        printf("Erreur lors de la récupération des données. Fin du programme.");
        exit(5);
    }
    a = creerAvl(city_a, tempRouteID, tempNumEtape); // On s'en sert pour créer le premier noeud de l'avl
    int equilibre = a->equilibre;
    // On ajoute la deuxièmre ville de la première ligne avec 0 comme numéro d'étape car la ville d'arrivée n'est jamais la ville de départ d'un trajet même pour la première étape
    a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b);


    for(int i = 1; i<taille;i++){
        r=fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b);
        if(r!=4){
        printf("Erreur lors de la récupération des données. Fin du programme.");
        exit(5);
    }
    // on insère chaque ville qu'on récupère tout en gardant le 0 pour la ville d'arrivée de l'étape
        a = insertionAvl(a, &equilibre, tempRouteID, tempNumEtape, city_a);
        a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b); 
        
    }
    //On ferme le fichier
    fclose(fichier);
    return a;

}

Avl *SecondAvl(File *f){
    Avl *tmp;
    int h=0;
    //On défile le premier élément de la file pour créer notre second Avl trié en fonction des counts
    defiler(f, &tmp);
    Avl *n = creerAvlSecond(tmp->nom,tmp->departCount,tmp->count);
    h = n->equilibre;
    //On fait la même chose jusqu'à ce que la file soit vide
    while(f->debut != NULL){
        defiler(f, &tmp);
        n = insertionSecondAvl(n, tmp, &h);
    }

    return n;
}


Avl * Avl10premieresvilles(Avl * a,File * f){
    if(f==NULL){
        exit(3);
    }
    Avl * tmp;
    //On défile le premier élément de la file pour créer notre Avl final trié en fonction du nom de ville
    defiler(f,&tmp);
    a=creerAvlSecond(tmp->nom,tmp->departCount,tmp->count);
    int equilibre=a->equilibre;
    //On fait la même chose jusqu'à ce que la file soit vide
    while (f->debut!=NULL){
        defiler(f,&tmp);
        a=insertionTroisiemeAvl(a,tmp,&equilibre);
    }
    return a;
}
