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
defiler(f,&tmp);
fprintf(fichier,"%s;%d;%d\n",tmp->nom,tmp->count,tmp->departCount);
}
fclose(fichier);

}

void infixe(Avl* a) {
    //infix display
    if (a!=NULL) {
        infixe(a->fg);
        printf("%s;%d;%d\n", a->nom, a->count, a->departCount);
        //fprintf(file_final,"%d;%.4f;%.4f;%.4f;%.4f\n",a->routeID, a->min, a->moy, a->max, a->max_miness_min);
        infixe(a->fd);
    }
    //tail -50 final_file.txt | tac
}

void liberermemoire(Avl * a){
  if(a!=NULL){
  liberermemoire(a->fg);
  liberermemoire(a->fd);
  free(a);
}
}

int main(int argc,char ** argv){
    int nb_lignes=atoi(argv[1]);
    Avl * premierAvl=NULL;
    premierAvl=construireAvl(premierAvl,nb_lignes);
    //infixe(premierAvl);
    File f={NULL,NULL};
    enfilerArbre(premierAvl,&f);
    Avl * secondAvl=NULL;
    secondAvl=SecondAvl(&f);
    //infixe(secondAvl);
    int i=0;
    recup10premieresvaleurs(secondAvl,&f,&i);
    Avl* troisiemeAvl=NULL;
    troisiemeAvl=Avl10premieresvilles(troisiemeAvl,&f);
    //infixe(troisiemeAvl);
    avlDansFile(troisiemeAvl,&f);
    fileDansFichier(&f);
    liberermemoire(premierAvl);
    liberermemoire(secondAvl);




    return 0;
}