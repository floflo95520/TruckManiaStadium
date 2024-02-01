#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_T.h"

#define TAILLE 100






void recup10premieresvaleurs(Avl * a, File * f, int *i ){
    if(a!=NULL && *i<=10){
recup10premieresvaleurs(a->fd,f,i);
*i=*i+1;
if(*i<=10){
enfiler(f,a);
}
recup10premieresvaleurs(a->fg,f,i);
}

}




void fileDansFichier(File * f){
    if(f==NULL){
        exit(6);
    }
    FILE * fichier=fopen("fichierstemporaires/data_t_temp.csv","w");
    if(fichier==NULL){
        exit(7);
    }
    Avl * tmp;

while(f->debut!=NULL){
//On insère les valeurs de la file dans le fichier
defiler(f,&tmp);
fprintf(fichier,"%s;%d;%d\n",tmp->nom,tmp->count,tmp->departCount);
}
fclose(fichier);

}



void liberermemoire(Avl * a){
  if(a!=NULL){
  liberermemoire(a->fg);
  liberermemoire(a->fd);
  free(a);
}
}

int main(int argc,char ** argv){
    int nb_lignes=atoi(argv[1]); // On récupère le nombre de lignes passé en argument lors de l'exécution du programme
    Avl * premierAvl=NULL;
    //On construit le premier avl qui récupère chaque ville et le nombre de fois qu'elle est traversée + le nombre de fois qu'elle apparait en ville de départ
    premierAvl=construireAvl(premierAvl,nb_lignes);
    File f={NULL,NULL};
    //On met le premier Avl dans une file
    avlDansFile(premierAvl,&f);
    Avl * secondAvl=NULL;
    //On va creer le second Avl qui sera trié en fonction du nombre de fois qu'une ville est traversée, à l'aide de la file qui contient le premier Avl
    secondAvl=SecondAvl(&f);
    int i=0;
    //On récupère à l'aide d'une file les 10 villes qui ont été le plus traversées du second Avl
    recup10premieresvaleurs(secondAvl,&f,&i);
    Avl* troisiemeAvl=NULL;
    //On crée alors le dernier Avl qui va contenir les 10 villes les plus traversées qui seront triées par ordre alphabétique
    troisiemeAvl=Avl10premieresvilles(troisiemeAvl,&f);
    //On met cet Avl dans une file
    avlDansFile(troisiemeAvl,&f);
    //A l'aide de cette file on écrit les données dans un nouveau fichier .csv
    fileDansFichier(&f);
    //On libère le premier, le second et le troisième Avl dès que les données sont bien inscrites dans le fichier .csv
    liberermemoire(premierAvl);
    liberermemoire(secondAvl);
    liberermemoire(troisiemeAvl);




    return 0;
}