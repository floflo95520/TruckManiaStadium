#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

Avl2 * creerAvlInterieur(int routeId){
  Avl2 * n=malloc(sizeof(Avl2));
  if(n==NULL){
  exit(1);
  }
  n->fg=NULL;
  n->fd=NULL;
  n->equilibre=0;


  n->routeId=routeId;

  return n;

}

Avl * creerAvl(char nom_ville[],int routeId, int Num_etape){
  Avl * n=malloc(sizeof(Avl));
  if(n==NULL){
    exit(1);
  }
  n->fg=NULL;
  n->fd=NULL;
  n->equilibre=0;
  n->count=1;
  strcpy(n->nom,nom_ville);
  if(Num_etape==1){
    n->departCount=1;
  }
  else{
    n->departCount=0;
  }
  n->Avl_interieur=creerAvlInterieur(routeId);

  return n;
}

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

Avl2* rotationGauche2(Avl2* a){
    if (a==NULL){
        printf("hi");
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

Avl* doubleRotationDroite(Avl* a){
    if (a == NULL) {
        exit(2);
    }
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

Avl2* doubleRotationDroite2(Avl2* a){
    if (a == NULL) {
        exit(2);
    }
    a->fg = rotationGauche2(a->fg);
    return rotationDroite2(a);
}

Avl* doubleRotationGauche(Avl* a){
    if (a == NULL) {
        exit(2);
    }
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
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

Avl2 *insertionAvlInterieur(Avl2 *a,int *h, int route_ID, int *v){
  
    
    if(a==NULL){
        *h = 1;
        return creerAvlInterieur(route_ID);
    }
    else if(route_ID < a->routeId){

        a->fg = insertionAvlInterieur(a->fg, h, route_ID, v);
        *h = -*h;
    }
    else if(route_ID > a->routeId){
        a->fd = insertionAvlInterieur(a->fd, h, route_ID, v);
    }
    else{
        *h = 0;
        *v = -1;
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl2(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl *insertionAvl(Avl *a,int *h, int route_ID,int step_ID, char city_name[]){
    if(a==NULL){
        *h = 1;
        return creerAvl(city_name, route_ID, step_ID);
    }
    else if(strcmp(city_name, a->nom) < 0){

        a->fg = insertionAvl(a->fg, h, route_ID, step_ID, city_name);
        *h = -*h;
    }
    else if(strcmp(city_name, a->nom) > 0){
        a->fd = insertionAvl(a->fd, h, route_ID, step_ID, city_name);
    }
    else{ //already in
        *h = 0;
        int x = a->Avl_interieur->equilibre;
        int v = 0;
        a->Avl_interieur = insertionAvlInterieur(a->Avl_interieur,&x, route_ID, &v);
        if(v != -1){
            a->count++;
        }
        if(step_ID==1){
            a->departCount = (a->departCount) + 1;
        }
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl* construireAvl(Avl * a, int taille){

    FILE * fichier = fopen("fichierstemporaires/data_t.txt","r");
    if(fichier==NULL){
        exit(3);
    }
    int i = 0;
    char city_a[TAILLE];
    char city_b[TAILLE];
    int tempNumEtape;
    int tempRouteID;

    fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b);
    a = creerAvl(city_a, tempRouteID, tempNumEtape);
    int equilibre = a->equilibre;
    a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b);


    for(int i = 0; i<taille;i++){
        fscanf(fichier, "%d %d %s %s", &tempRouteID, &tempNumEtape, city_a, city_b);

        a = insertionAvl(a, &equilibre, tempRouteID, tempNumEtape, city_a);
        a = insertionAvl(a, &equilibre, tempRouteID, 0, city_b);
        
    }
    fclose(fichier);
    return a;

}

chainon *creationchainon(Avl *a){
    chainon *n = malloc(sizeof(chainon));
    if(n==NULL){exit(8);}
    n->suivant = NULL;
    n->noeud= a;
    return n;
}

void enfiler(File *f, Avl *a){
    if(a==NULL){exit(5);}
    chainon*n = creationchainon(a);
    if(f->debut==NULL){
        f->debut=n;
        f->fin=n;
    }
    else{
        f->fin->suivant = n;
        f->fin = f->fin->suivant;
    }
}

void defiler(File *f, Avl **b){
    if(f==NULL){exit(9);}
    chainon *n = f->debut;
    if(n==NULL){exit(55);}
    *b = n->noeud;
    f->debut = f->debut->suivant;

    if(f->debut==NULL){
        f->fin=NULL;
    }
    free(n);

}


Avl * creerAvlSecond(char nom_ville[],int departCount,int count) {
    Avl* n = malloc(sizeof(Avl));
    if (n == NULL) {
        exit(3); 
    }
    strcpy(n->nom, nom_ville);
    n->departCount = departCount;
    n->count = count;

    n -> fg = NULL;
    n -> fd = NULL;
    n->equilibre = 0;
    return n;
}

Avl *insertionSecondAvl(Avl *a, Avl *b, int *h){
    //printf("in\n");
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(b->count < a->count){
        //printf("in");
        a->fg = insertionSecondAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(b->count > a->count){
        a->fd = insertionSecondAvl(a->fd,b, h);
    }
    else{ //already in
        *h = 0;
        //printf("b SOL is %d and a SOL is %d\n", b->size, a->size);        
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

Avl *insertionTroisiemeAvl(Avl *a, Avl *b, int * h){
    //printf("in\n");
    if(a==NULL){
        *h = 1;
        return creerAvlSecond(b->nom,b->departCount,b->count);
    }
    else if(strcmp(b->nom,a->nom)<0){
        //printf("in");
        a->fg = insertionTroisiemeAvl(a->fg,b,h);
        *h = -*h;
    }
    else if(strcmp(b->nom,a->nom)>0){
        a->fd = insertionTroisiemeAvl(a->fd,b, h);
    }
    else{ //already in
        *h = 0;
        //printf("b SOL is %d and a SOL is %d\n", b->size, a->size);        
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAvl(a);
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

void enfilerArbre(Avl *a, File *f){
    if(a!=NULL){
        enfiler(f, a);
        enfilerArbre(a->fd, f);
        enfilerArbre(a->fg, f);
    }
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

void avlDansFile(Avl * a, File *f){
    if(a!=NULL){
        avlDansFile(a->fg,f);
        enfiler(f,a);
        avlDansFile(a->fd,f);
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
    Avl * premierAvl;
    premierAvl=construireAvl(premierAvl,nb_lignes);
    //infixe(premierAvl);
    File f={NULL,NULL};
    enfilerArbre(premierAvl,&f);
    Avl * secondAvl;
    secondAvl=SecondAvl(&f);
    //infixe(secondAvl);
    int i=0;
    recup10premieresvaleurs(secondAvl,&f,&i);
    Avl* troisiemeAvl;
    troisiemeAvl=Avl10premieresvilles(troisiemeAvl,&f);
    //infixe(troisiemeAvl);
    avlDansFile(troisiemeAvl,&f);
    fileDansFichier(&f);
    liberermemoire(premierAvl);
    liberermemoire(secondAvl);




    return 0;
}