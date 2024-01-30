#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <Prototype_S.h>







  
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
defiler(f,&temp);
fprintf(data,"%d;%d;%f;%f;%f;%f\n", i,temp->Id,temp->min,temp->moyenne,temp->max,temp->max_min);
i++;
}
fclose(data);
}


/*void affichefile(File f){
if(f.tete==f.queue){
printf("problème");
exit(100);
}
chainon * tmp=f.tete;
while(tmp!=NULL){
printf("%d %f %f %f %f %d \n",tmp->tr->Id,tmp->tr->max,tmp->tr->min,tmp->tr->max_min,tmp->tr->moyenne, tmp->tr->count);
tmp=tmp->suivant;
}
}*/

void liberermemoire(Ptrajet t){
  if(t!=NULL){
  liberermemoire(t->fg);
  liberermemoire(t->fd);
  free(t);
}
}












  

int main(int argc, char ** argv){
int nb_ligne=atoi(argv[1]);
File f={NULL,NULL};
Ptrajet t;
t=premierAvl(t,nb_ligne);
enfilerArbre(t,&f);

Ptrajet trajet;
trajet=secondAvl(trajet,&f);

File f1={NULL,NULL};
int i=0;
recup50premieresvaleurs(&f1,trajet,&i);

remplirfichier(&f1);
liberermemoire(t);
liberermemoire(trajet);


return 0;
}





