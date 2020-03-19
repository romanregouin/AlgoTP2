#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "pile.h"
#include "file.h"

#define max(a, b) ((a) > (b) ? (a) : (b))



int feuille(Arbre234 a){
    if(a==NULL || a->t==0)return 0;
    if(a->t==2 && (a->fils[1]->t==0 ||a->fils[1]==NULL) && (a->fils[2]->t==0 ||a->fils[2]==NULL))return 1;
    else if(a->t!=2){
        for(int i=0;i<a->t;i++){
            if(a->fils[i]!=NULL && a->fils[i]->t!=0)return 0;
        }
        return 1;
    }
    return 0;
}

int hauteur(Arbre234 a)
{
    int h0, h1, h2, h3;

    if (a == NULL)
        return 0;

    if (a->t == 0)
        return 0;

    h0 = hauteur(a->fils[0]);
    h1 = hauteur(a->fils[1]);
    h2 = hauteur(a->fils[2]);
    h3 = hauteur(a->fils[3]);

    return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a)
{
    if(a->t==0)return 0;
    int res=a->t-1;
    if (a->t==2){
		res+=NombreCles(a->fils[1]);
		res+=NombreCles(a->fils[2]);
	}
	else{
		for(int i=0;i<a->t;i++){
			res+=NombreCles(a->fils[i]);
		}
	}
    return res;
}

int CleMax(Arbre234 a)
{
    if(a==NULL || a->t==0)return -1;
    if(feuille(a)){
        if(a->t!=4)return a->cles[1];
        return a->cles[2];
    }
    if(a->t!=4)return CleMax(a->fils[1]);
    return CleMax(a->fils[2]);
}

int CleMin(Arbre234 a)
{
    if(a==NULL || a->t==0)return -1;
    if(feuille(a)){
        if(a->t!=2)return a->cles[0];
        return a->cles[1];
    }
    if(a->t!=2)return CleMax(a->fils[0]);
    return CleMax(a->fils[0]);
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
    if(a==NULL || a->t==0)return NULL;
    int i=0;
    if(a->t==2)i=1;
    for(;a->cles[i]<cle && i<a->t-1;i++)
    if(cle==a->cles[i])return a;
    if(cle>a->cles[i])return RechercherCle(a->fils[i+1],cle);
    return RechercherCle(a->fils[i],cle);     
}

void AnalyseStructureArbre(Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
    if(a->t==0)return;
    if(feuille(a))(*feuilles)++;
    if(a->t==2)(*noeud2)++;
    if(a->t==3)(*noeud3)++;
    if(a->t==4)(*noeud4)++;
    int j=0;
    if(a->t==2)j=1;
    for(int i=0;i<a->t;i++){
        AnalyseStructureArbre(a->fils[i+j],feuilles,noeud2,noeud3,noeud4);
    }
}

int somme_cles(Arbre234 a)
{
    if(a==NULL || a->t==0)return 0;
    int res=0;
    int i;
    int j=0;
    if(a->t==2)j=1;
    for(i=0;i<a->t-1;i++){
        res+=somme_cles(a->fils[i+j]);
        res+=a->cles[i+j];
    }
    return res+somme_cles(a->fils[i+1+j]);
}

Arbre234 noeud_max(Arbre234 a)
{
    /*if(a->t==0)return a;
    Arbre234 b=noeud_max(a->t-1);
    for(int i=0;i<a->t-1;i++){
        if()
    }*/

}

void Afficher_Cles_Largeur(Arbre234 a)
{
	if(a==NULL || a->t==0){
		printf("L'arbre est vide");
	}
	pfile_t f=creer_file();
	Arbre234 c;
	enfiler(f,a);
	while(!file_vide(f)){
		c = defiler(f);
		if(c->t == 0){}
		else if(c->t==2){
			printf("%d ",c->cles[1]);
			enfiler(f,c->fils[1]);
			enfiler(f,c->fils[2]);
		}
		else {
			for(int i=0;i<c->t-1;i++){
				printf("%d ",c->cles[i]);
			}
			for(int i=0;i<c->t;i++){
				enfiler(f,c->fils[i]);
			}
		}
		
	}
}

void Affichage_Cles_Triees_Recursive(Arbre234 a)
{
	if(a==NULL){
		printf("L'arbre est vide");
	}
	
	if(a->t == 0){}
	else if(a->t==2){
		Affichage_Cles_Triees_Recursive(a->fils[1]);
		printf("%d ",a->cles[1]);
		Affichage_Cles_Triees_Recursive(a->fils[2]);
	}
	else {
		for(int i=0;i<a->t-1;i++){
			Affichage_Cles_Triees_Recursive(a->fils[i]);
			printf("%d ",a->cles[i]);
		}
		Affichage_Cles_Triees_Recursive(a->fils[a->t-1]);
	}

}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
	
}

Arbre234 RechercherPere(Arbre234 a, Arbre234 pere, int cle)
{
	return NULL;
}

void Detruire_Cle(Arbre234 *a, int cle)
{
}

int main(int argc, char **argv)
{
    Arbre234 a;
    //int suppr = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <nom fichier>\n", argv[0]);
        exit(-1);
    }

    a = lire_arbre(argv[1]);

    printf("==== Afficher arbre ====\n");

    afficher_arbre(a, 0);
    
    printf("\nNombre de cles = %d\n",NombreCles(a));
    
    int nb_feuilles=0,nb_2n=0,nb_3n=0,nb_4n=0;
    AnalyseStructureArbre(a,&nb_feuilles,&nb_2n,&nb_3n,&nb_4n);
    printf("\nAnalyse structure de l'arbre :\nfeuilles = %d, 2-noeuds = %d, 3-noeuds = %d, 4-noeuds = %d\n",nb_feuilles, nb_2n, nb_3n, nb_4n);
    
    printf("\nAffichage clés largeur :\n");
    Afficher_Cles_Largeur(a);
    printf("\n");
    
    printf("\nAffichage clés triées récursive :\n");
    Affichage_Cles_Triees_Recursive(a);
    printf("\n");

    return 0;
}
