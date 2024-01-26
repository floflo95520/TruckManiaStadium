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

Ptrajet creerNoeud(int NouveauId, float distance){
  Ptrajet n=malloc(sizeof(trajet));
  if(n==NULL){
  printf("Erreur d'allocation mémoire.");
  exit(1);
  }
  n->Id=NouveauId;
  n->max=distance;
  n->min=distance;
  n->max_min=0;
  n->somme=distance;
  n->count=1;
n->moyenne=n->somme/n->count;
  n->equilibre=0;
  n->fg=NULL;
  n->fd=NULL;
return n;
}

Ptrajet creerNoeudSecond(int NouveauId, float Nvmax, float Nvmin, float Nvmax_min, float NvSomme, int NvCount, float NvMoyenne){
Ptrajet n=malloc(sizeof(trajet));
if(n==NULL){
printf("Problème d'allocation mémoire. Fin du programme.");
exit(2);
}
n->Id=NouveauId;
n->max=Nvmax;
n->min=Nvmin;
n->max_min=Nvmax_min;
n->somme=NvSomme;
n->count=NvCount;
n->moyenne=NvMoyenne;

n->fg=NULL;
n->fd=NULL;
n->equilibre=0;
return n;
}

Ptrajet rotationGauche(Ptrajet t){
  if(t==NULL){
  exit(5);
  }
  Ptrajet pivot;
  int eq_a,eq_p;
  pivot=t->fd;
  t->fd=pivot->fg;
  pivot->fg=t;
  eq_a=t->equilibre;
  eq_p=pivot->equilibre;
  t->equilibre=eq_a-fmax(eq_p,0)-1;
  int min1=fmin(eq_a-2,eq_a+eq_p-2);
  pivot->equilibre=fmin(min1,eq_p-1);
  t=pivot;
  return t;
}

Ptrajet rotationDroite(Ptrajet t){
  if(t==NULL){
  exit(6);
  }
  Ptrajet pivot;
  int eq_a,eq_p;
  pivot=t->fg;
  t->fg=pivot->fd;
  pivot->fd=t;
  eq_a=t->equilibre;
  eq_p=pivot->equilibre;
  t->equilibre=eq_a-fmin(eq_p,0)+1;
  int max1=fmax(eq_a+2,eq_a+eq_p+2);
  pivot->equilibre=fmax(max1,eq_p+1);
  t=pivot;
  return t;
}

Ptrajet doubleRotationGauche(Ptrajet t){
  if(t==NULL){
    exit(1);
  }
  t->fd=rotationDroite(t->fd);
  return rotationGauche(t);
}

Ptrajet doubleRotationDroite(Ptrajet t){
  if(t==NULL){
    exit(2);
  }
  t->fg=rotationGauche(t->fg);
  return rotationDroite(t);
}

Ptrajet equilibrageAVL(Ptrajet t){
if(t==NULL){
exit(10);
}
if(t->equilibre >= 2){
  if(t->fd->equilibre >= 0){
    return rotationGauche(t);
  }
  else{
    return doubleRotationGauche(t);
  }
}
else if(t->equilibre <= -2){
  if(t->fg->equilibre <= 0){
    return rotationDroite(t);
  }
  else{
    return doubleRotationDroite(t);
  }
}
return t;
}

Ptrajet insertAvl( Ptrajet t, int NumId, float NewDistance, int *h ){
  if(t==NULL){
  *h=1;
  return creerNoeud(NumId,NewDistance);
  }
  else if(NumId < t->Id){
  t->fg=insertAvl(t->fg, NumId, NewDistance, h);
  *h=-*h;
  }
  else if(NumId > t->Id){
  t->fd=insertAvl(t->fd,NumId,NewDistance, h);
  }
  else{
  *h=0;
  if(NewDistance > t->max){
  t->max=NewDistance;
  }
  else if(NewDistance < t->min){
  t->min=NewDistance;
  }
  t->max_min= (t->max)-(t->min);
  t->somme+=NewDistance;
  t->count=t->count+1;
  t->moyenne=t->somme/t->count;
  return t;
  }

if(*h!=0){
t->equilibre+=*h;
t=equilibrageAVL(t);
if(t->equilibre==0){
*h=0;
}
else{
*h=1;
}
}
return t;
}

//a=nouveau AVL
//b=Ancien AVL

Ptrajet insertAvlSecond(Ptrajet a, Ptrajet b, int *h){
  if(a==NULL){
    return creerNoeudSecond(b->Id, b->max, b->min, b->max_min, b->somme, b->count, b->moyenne);
  }
  else if(b->max_min < a->max_min){
    a->fg=insertAvlSecond(a->fg,b,h);
    *h=-*h;
  }
  else if(b->max_min > a->max_min){
    a->fd=insertAvlSecond(a->fd,b,h);
  }
  else{
  *h=0;
  return a;
  }
  
  if(*h!=0){
  a->equilibre = a->equilibre + *h;
  a=equilibrageAVL(a);
  
  if(a->equilibre==0){
  *h=0;
  }
  else{
  *h=1;
  }
  }
  return a;
  
}

Ptrajet premierAvl(Ptrajet t, int N){
FILE * f=fopen("fichierstemporaires/data_s.txt","r");
if(f==NULL){
printf("Erreur d'ouverture du fichier. Fin du programme.");
exit(7);
}
int i=0;
int TmpId=0;
float TmpDistance=0;


fscanf(f,"%d %f", &TmpId, &TmpDistance);
t=creerNoeud(TmpId,TmpDistance);
i=1;
int eq=t->equilibre;

while(i!=N){
fscanf(f,"%d %f", &TmpId, &TmpDistance);
t=insertAvl(t,TmpId,TmpDistance,&eq);

i++;
}
fclose(f);
return t;printf("%d",t->Id);
}
 
void enfiler(File * f, Ptrajet t){
if(t==NULL){
printf("Erreur dans l'enfilement. Fin du programme");
exit(8);
}
chainon * n=malloc(sizeof(chainon));
if(n==NULL){
printf("Erreur d'allocation mémoire. Fin du programme.");
exit(2);
}
n->tr=t;
n->suivant=NULL;

if(f->tete==NULL){
f->tete=n;
f->queue=n;
}
else{
f->queue->suivant=n;
f->queue=f->queue->suivant;
}
}

void defiler(File *f, Ptrajet * tra){
if(f==NULL){
printf("Erreur de file. Fin du programme.");
exit(11);
}

if(f->tete==f->queue){
*tra=f->tete->tr;
f->tete=NULL;
f->queue=NULL;
}
else{
*tra=f->tete->tr;
chainon * temp=f->tete;
f->tete=f->tete->suivant;
free(temp);
}
}

void enfilerArbre(Ptrajet t, File *f){
if(t!=NULL){
enfiler(f,t);
enfilerArbre(t->fg,f);
enfilerArbre(t->fd,f);
}
}

Ptrajet secondAvl(Ptrajet t, File * f){
  if(f==NULL){
  printf("Erreur de file. Fin du programme");
  exit(12);
  }
  Ptrajet temp;
  defiler(f,&temp);
  t=creerNoeudSecond(temp->Id,temp->max,temp->min,temp->max_min,temp->somme,temp->count,temp->moyenne);
  int h;
  
  while(f->tete!=NULL){
  defiler(f,&temp);
  h=t->equilibre;
  t=insertAvlSecond(t,temp,&h);
  }
return t;
}
  
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


void affichefile(File f){
if(f.tete==f.queue){
printf("problème");
exit(100);
}
chainon * tmp=f.tete;
while(tmp!=NULL){
printf("%d %f %f %f %f %d \n",tmp->tr->Id,tmp->tr->max,tmp->tr->min,tmp->tr->max_min,tmp->tr->moyenne, tmp->tr->count);
tmp=tmp->suivant;
}
}

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





