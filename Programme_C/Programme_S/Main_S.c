#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Main_S.h"







  
void recup50premieresvaleurs(File *f, Ptrajet t, int *i){
if(t!=NULL && *i<=50){
recup50premieresvaleurs(f,t->fd,i);

*i=*i+1;
if(*i<=50){
enfiler(f,t);
}

recup50premieresvaleurs(f,t->fg,i);
}
}

void remplirfichier(File * f){
if(f==NULL){
printf("Erreur de file. Fin du programme.");
exit(14);
}
FILE * data=fopen("fichierstemporaires/data_s.csv","w");
if(data==NULL){
printf("Erreur lors de l'ouverture du fichier. Fin du programme.");
exit(13);
}
Ptrajet temp;
int i=1;
while(f->tete!=NULL){
//On insère les valeurs de la file dans le fichier
defiler(f,&temp);
fprintf(data,"%d;%d;%f;%f;%f;%f\n", i,temp->Id,temp->min,temp->moyenne,temp->max,temp->max_min);
i++;
}
fclose(data);
}



void liberermemoire(Ptrajet t){
  if(t!=NULL){
  liberermemoire(t->fg);
  liberermemoire(t->fd);
  free(t);
}
}












  

int main(int argc, char ** argv){
//On récupère le nombre de lignes passé en argument lors de l'exécution du programme
int nb_ligne=atoi(argv[1]);
File f={NULL,NULL};
Ptrajet t=NULL;
//on crée le premier avl qui, dans chaque noeud va stocker chaque trajet avec toutes les informations utiles
t=premierAvl(t,nb_ligne);
//On enfile l'arbre
enfilerArbre(t,&f);

Ptrajet trajet=NULL;
//On crée un second avl trié en fonction de la valeur max-min
trajet=secondAvl(trajet,&f);

File f1={NULL,NULL};
int i=0;
//on récupère les 50 premières valeurs du second Avl...
recup50premieresvaleurs(&f1,trajet,&i);
//...qu'on insère dans le fichier qui contiendra les données finales 
remplirfichier(&f1);
//on libère la mémoire des avl une fois que les données ont été insérées dans le fichier
liberermemoire(t);
liberermemoire(trajet);


return 0;
}





