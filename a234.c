#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "pile.h"
#include "file.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

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
    if(a->t==0)return a->cles[0];
    return CleMax(a->fils[a->t-1]);
}

int CleMin(Arbre234 a)
{
    if(a->t==0)return a->cles[0];
    return CleMin(a->fils[0]);
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
    if(a->t==0){
        if(a->cles[0]==cle)return a;
        return NULL;
    }
    int i;
    for(i=0;a->cles[i]<cle && i<a->t-1;i++)
    if(cle==a->cles[i])return a;
    if(cle>a->cles[i])return RechercherCle(a->fils[i+1],cle);
    return RechercherCle(a->fils[i],cle);     
}

/*void AnalyseStructureArbre(Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
    if(a->t==0)return (*feuilles)++;
    if(a->t==2)return (*noeud2)++;
    if(a->t==3)return (*noeud3)++;
    if(a->t==4)return (*noeud4)++;
    for(int i=0;i<a->t;i++){
        AnalyseStructureArbre(a->fils[i],*feuilles,*noeud2,*noeud3,*noeud4);
    }
}*/

int somme_cles(Arbre234 a)
{
    if(a->t==0)return a->cles[0];
    int res=0;
    int i;
    for(i=0;i<a->t-1;i++){
        res+=somme_cles(a->fils[i]);
        res+=a->cles[i];
    }
    return res+somme_cles(a->fils[i+1]);
}

Arbre234 noeud_max(Arbre234 a)
{
	return NULL;
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
		switch(c->t)
		{
			case 0:
				break;
			case 2:
				printf("%d ",c->cles[1]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				break;
			case 3:
				printf("%d ",c->cles[0]);
				printf("%d ",c->cles[1]);
				enfiler(f,c->fils[0]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				break;
			case 4:
				printf("%d ",c->cles[0]);
				printf("%d ",c->cles[1]);
				printf("%d ",c->cles[2]);
				enfiler(f,c->fils[0]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				enfiler(f,c->fils[3]);
				break;
			default:
				break;
		}
	}

}

void Affichage_Cles_Triees_Recursive(Arbre234 a)
{
	if(a==NULL){
		printf("L'arbre est vide");
	}
	switch(a->t)
	{
		case 0:
			return;
		case 2:
			Affichage_Cles_Triees_Recursive(a->fils[1]);
			printf("%d ",a->cles[1]);
			Affichage_Cles_Triees_Recursive(a->fils[2]);
			break;
		case 3:
			Affichage_Cles_Triees_Recursive(a->fils[0]);
			printf("%d ",a->cles[0]);
			Affichage_Cles_Triees_Recursive(a->fils[1]);
			printf("%d ",a->cles[1]);
			Affichage_Cles_Triees_Recursive(a->fils[2]);
			break;
		case 4:
			Affichage_Cles_Triees_Recursive(a->fils[0]);
			printf("%d ",a->cles[0]);
			Affichage_Cles_Triees_Recursive(a->fils[1]);
			printf("%d ",a->cles[1]);
			Affichage_Cles_Triees_Recursive(a->fils[2]);
			printf("%d ",a->cles[2]);
			Affichage_Cles_Triees_Recursive(a->fils[3]);
			break;
		default:
			return;
	}
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
	if(a==NULL || a->t==0){
		printf("L'arbre est vide");
	}
	ppile_t p=creer_pile();
	Arbre234 c;
	enpiler(p,a);
	while(!pile_vide(p)){
		c = depiler(p);
		switch(c->t)
		{
			case 0:
				break;
			case 2:
				printf("%d ",c->cles[1]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				break;
			case 3:
				printf("%d ",c->cles[0]);
				printf("%d ",c->cles[1]);
				enfiler(f,c->fils[0]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				break;
			case 4:
				printf("%d ",c->cles[0]);
				printf("%d ",c->cles[1]);
				printf("%d ",c->cles[2]);
				enfiler(f,c->fils[0]);
				enfiler(f,c->fils[1]);
				enfiler(f,c->fils[2]);
				enfiler(f,c->fils[3]);
				break;
			default:
				break;
		}
	}
	
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
    
    printf("\nAffichage clés largeur :\n");
    Afficher_Cles_Largeur(a);
    printf("\n");
    
    printf("\nAffichage clés triées récursive :\n");
    Affichage_Cles_Triees_Recursive(a);
    printf("\n");

    return 0;
}
