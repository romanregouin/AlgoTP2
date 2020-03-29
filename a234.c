#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "pile.h"
#include "file.h"
#include "pile.h"

#define max(a, b) ((a) > (b) ? (a) : (b))


// 1 -> est feuille 0 sinon
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
    if(a==NULL || a->t==0)return 0;
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
    if(a->t!=4)return CleMax(a->fils[2]);
    return CleMax(a->fils[3]);
}

int CleMin(Arbre234 a)
{
    if(a==NULL || a->t==0)return -1;
    if(feuille(a)){
        if(a->t!=2)return a->cles[0];
        return a->cles[1];
    }
    if(a->t!=2)return CleMin(a->fils[0]);
    return CleMin(a->fils[1]);
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
    if(a==NULL || a->t==0)return NULL;
    int j=0;
    int i=0;
    if(a->t==2)j=1;
    for(;i<a->t-1 && a->cles[i+j]<=cle;i++)if(cle==a->cles[i+j])return a;
    return RechercherCle(a->fils[i+j],cle);     
}

Arbre234 RechercherCle2(Arbre234 a, int cle)
{
	if(a==NULL || a->t==0)return NULL;
	if(a->t==2){
		if(cle==a->cles[1])return a;
		else if(cle < a->cles[1]) return RechercherCle2(a->fils[1],cle);
		else return RechercherCle2(a->fils[2],cle);
	}
	if(a->t==3){
		if(cle==a->cles[0] || cle==a->cles[1])return a;
		else if(cle < a->cles[0]) return RechercherCle2(a->fils[0],cle);
		else if(cle < a->cles[1]) return RechercherCle2(a->fils[1],cle);
		else{
			return RechercherCle2(a->fils[2],cle);
		}
	}
	else{ //a->t ==4
		if(cle==a->cles[0] || cle==a->cles[1] || cle==a->cles[2])return a;
		else if(cle < a->cles[0]) return RechercherCle2(a->fils[0],cle);
		else if(cle < a->cles[1]) return RechercherCle2(a->fils[1],cle);
		else if(cle < a->cles[2]) return RechercherCle2(a->fils[2],cle);
		else {
			return RechercherCle2(a->fils[3],cle);
		}
	}
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
    return res+somme_cles(a->fils[i+j]);
}



int somme_cles2(Arbre234 a)
{
    if(a==NULL || a->t==0)return 0;
    if(a->t==2)return a->s+somme_cles2(a->fils[1])+somme_cles2(a->fils[2]);
    else{
        int res=0;
        for(int i=0;i<a->t;i++){
            res+=somme_cles2(a->fils[i]);
        }
        return res+a->s;
    }
}


void noeud_max(Arbre234 a,Arbre234* res)
{
    if(a==NULL)return;
    if(*res==NULL)*res=a;
    else if(a->s>(*res)->s)*res=a;
    noeud_max(a->fils[0],res);
    noeud_max(a->fils[1],res);
    noeud_max(a->fils[2],res);
    noeud_max(a->fils[3],res);
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



void afficher_cles_noeud(Arbre234 a){
    if(a->t==2)printf("%d ",a->cles[1]);
    else{
        for(int i=0;i<a->t-1;i++){
            printf("%d ",a->cles[i]);
        }
    }
}


void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
	ppile_t p=creer_pile();
    empiler(p,a);
    Arbre234 courant,tmp;
    while(!pile_vide(p)){
        courant=depiler(p);
        if(courant->c==0){
            while(!feuille(courant)){
                if(courant->t==2){
                    tmp=courant->fils[1];
                    courant->c=1;
                }
                else {
                    tmp=courant->fils[0];
                    courant->c=1;
                }
                empiler(p,courant);
                courant=tmp;
            }
        }
        if(feuille(courant))afficher_cles_noeud(courant);
        else if(courant->t==2 ){
            if(courant->c<2){
                printf("%d ",courant->cles[1]);
                tmp=courant->fils[2];
                courant->c++;
                empiler(p,courant);
                empiler(p,tmp);
            }else courant->c=0;
        }else{
            if(courant->c<courant->t){
                printf("%d ",courant->cles[courant->c-1]);
                tmp=courant->fils[courant->c];
                courant->c++;
                empiler(p,courant);
                empiler(p,tmp);
            }else courant->c=0;
        }
        
    }
}

//retourne d'indice de la clé max du noeud
int IndiceKeyMaxFromNode(Arbre234* node){
    int max1 = max((*node)->cles[0],(*node)->cles[1]);
    int max2 = max(max1,(*node)->cles[2]);
    switch((*node)->t){
        case 0 :
            return -1;
            break;
        case 2 :
            return 1;
            break;
        case 3 :
            if(max1==(*node)->cles[0]){
                return 0;
            }else{
                return 1;
            }
            break;
        case 4 :
            if(max2==(*node)->cles[0]){
                return 0;
            }else if(max2==(*node)->cles[1]){
                return 1;
            }else{
                return 2;
            }
            break;
        default : //ne doit jamais arriver !
            return -2;
            break;
    }
    return -2; //le switch doit déjà gérer tout les cas!
}

void RemoveKeyFromNode(Arbre234* a, Arbre234* parent, int cle){
    if((*a)->t==0){
        return;
    }
    for(int i=0;i<(*a)->t;i++){
        if((*a)->t==4){
            if((*a)->cles[i]==cle){
                if(!i){
                    (*a)->cles[0] = (*a)->cles[1];
                    (*a)->cles[1] = (*a)->cles[2];
                }else if(i==1){
                    (*a)->cles[1] = (*a)->cles[2];
                }
                (*a)->t--;
                return;
            }
        }else if((*a)->t==3){
            if(((*a)->cles[i]==cle)&&(i!=2)){
                if(i==1){
                    (*a)->cles[1] = (*a)->cles[0];
                }
                (*a)->t--;
                return;
            }
        }else{ //cas ou t=2 si pas de bug
            if(((*a)->cles[i]==cle)&&(i==1)){
                if(((*parent)->fils[1])->t==4){ //prend que le cas de la clef la plus grande

                }else if(((*parent)->fils[1])->t==3){
                    //(*parent)->cles[2] = (*parent)->fils[1]->cles[IndiceKeyMaxFromNode((*parent)->fils[1])]//diapo 9 du cours detruire arbre
                }else if(((*parent)->fils[1])->t==2){

                }
                (*a)->t = 0;
                return;
            }
        }
    }
    return;
}

void Detruire_Cle(Arbre234 *a,Arbre234 *parent, int cle){

    if((*a)!=NULL){
        if((*a)->t!=0){
            if(feuille(*a)){
                RemoveKeyFromNode(a,parent,cle);
                return;
            }
            if((*a)->t==0){
                return;
            }else if((*a)->t==2){
                Detruire_Cle(&((*a)->fils[1]),a,cle);
                Detruire_Cle(&((*a)->fils[2]),a,cle);
            }else if(((*a)->t==3)||((*a)->t==4)){
                for(int i=0;i<(*a)->t;i++){
                    Detruire_Cle(&((*a)->fils[i]),a,cle);
                }
            }
        }
    }
    return;
}



void detruire_clef_feuille(Arbre234* a, Arbre234* parent, int pos1,int pos2){
    switch ((*a)->t){
        case 0:return;
        case 2:
            if(parent==NULL){
                (*a)->t=0;
                return;
            }
            if((*parent)->t==2){
                if(pos2==1){
                    (*a)->cles[1]=(*parent)->cles[1];
                    (*parent)->cles[1]=(*parent)->fils[2]->cles[0];
                    if((*parent)->fils[2]->t==4){
                        (*parent)->fils[2]->cles[0]=(*parent)->fils[2]->cles[1];
                        (*parent)->fils[2]->cles[1]=(*parent)->fils[2]->cles[2];
                    }
                    (*parent)->fils[pos2+1]->t--;
                }else{
                    (*a)->cles[1]=(*parent)->cles[1];
                    (*parent)->cles[0]=(*parent)->fils[1]->cles[(*parent)->fils[1]->t-1];
                    if((*parent)->fils[1]->t==3)(*parent)->fils[1]->cles[1]=(*parent)->fils[1]->cles[0];
                }
            }else{
                if(pos2==(*parent)->t-1){
                    (*a)->cles[1]=(*parent)->cles[pos2-1];
                    (*parent)->cles[pos2-1]=(*parent)->fils[pos2-1]->cles[(*parent)->fils[pos2-1]->t-1];
                    (*parent)->fils[pos2-1]->t--;
                    if((*parent)->fils[pos2-1]->t==3)(*parent)->fils[pos2-1]->cles[1]=(*parent)->fils[pos2-1]->cles[0];
                }else{
                    (*a)->cles[1]=(*parent)->cles[pos2];
                    (*parent)->cles[pos2]=(*parent)->fils[pos2+1]->cles[0];
                    if((*parent)->fils[pos2+1]->t==4){
                        (*parent)->fils[pos2+1]->cles[0]=(*parent)->fils[pos2+1]->cles[1];
                        (*parent)->fils[pos2+1]->cles[1]=(*parent)->fils[pos2+1]->cles[2];
                    }
                    (*parent)->fils[pos2+1]->t--;
                }
            }
        break;
        case 3:
            if(pos1==1)(*a)->cles[1]=(*a)->cles[0];
        default:
            for(int i=pos1;i<(*a)->t-2;i++){
                (*a)->cles[i]=(*a)->cles[i+1];
            }
            (*a)->t--;
        break;
    }
    return;
}

void Detruire_Cle_Noeud(Arbre234 a,int pos){
    if(a->t==0)return;
    if(a->fils[pos]!=NULL && a->fils[pos]->t!=2){
        a->cles[pos]=a->fils[pos]->cles[a->fils[pos]->t-2];
        detruire_clef_feuille(&(a->fils[pos]),&a,a->fils[pos]->t-2,pos);
    }else if(a->fils[pos+1]!=NULL && a->fils[pos+1]->t==2){
        a->fils[pos]->cles[0]=a->fils[pos]->cles[1];
        a->fils[pos]->cles[1]=a->fils[pos+1]->cles[1];
        for(int i=pos;i<a->t-2;i++){
                a->cles[i]=a->cles[i+1];
                a->fils[i+1]=a->fils[i+2];
            }
            a->t--;
    }else{
        a->cles[pos]=a->fils[pos+1]->cles[0];
        detruire_clef_feuille(&(a->fils[pos+1]),&a,0,pos+1);
    }
}

void doit_fusionner(Arbre234 a){
    if(a==NULL || a->t==0)return;
    if(a->t==2 && a->fils[1]->t==2 && a->fils[2]->t==2){
        a->t=4;
        a->cles[0]=a->fils[1]->cles[1];
        a->cles[2]=a->fils[2]->cles[1];
        a->fils[0]=a->fils[1]->fils[1];
        a->fils[1]=a->fils[1]->fils[2];
        a->fils[3]=a->fils[2]->fils[2];
        a->fils[2]=a->fils[2]->fils[1]; 
    }else if(a->t!=2){
        for(int i=0;i<a->t-1;i++){
            if(a->fils[i]->t==2 && a->fils[i+1]->t==2){
                if(a->t==3){
                    if(i==0){
                        a->t=2;
                        a->fils[1]->t=4;
                        a->fils[1]->cles[2]=a->fils[1]->cles[1];
                        a->fils[1]->cles[1]=a->cles[0];
                        a->fils[1]->cles[0]=a->fils[0]->cles[1];
                        a->fils[1]->fils[3]=a->fils[1]->fils[2];
                        a->fils[1]->fils[2]=a->fils[1]->fils[1];  
                        a->fils[1]->fils[0]=a->fils[0]->fils[1];
                        a->fils[1]->fils[1]=a->fils[0]->fils[2];
                    }else{
                        a->t=2;
                        a->fils[2]->t=4;
                        a->fils[2]->cles[2]=a->fils[2]->cles[1];
                        a->fils[2]->cles[1]=a->cles[1];
                        a->fils[2]->cles[0]=a->fils[1]->cles[1];
                        a->cles[1]=a->cles[0];
                        a->fils[1]=a->fils[0];
                        a->fils[2]->fils[3]=a->fils[2]->fils[2];
                        a->fils[2]->fils[2]=a->fils[2]->fils[1];  
                        a->fils[2]->fils[0]=a->fils[1]->fils[1];
                        a->fils[2]->fils[1]=a->fils[1]->fils[2];

                    }
                }else{
                    a->fils[i]->t=4;
                    a->fils[i]->cles[0]=a->fils[i]->cles[1];
                    a->fils[i]->cles[1]=a->cles[i];
                    a->fils[i]->cles[2]=a->fils[i+1]->cles[1];
                    for(int j=i;j<a->t-2;j++){
                        a->cles[j]=a->cles[j+1];
                        a->fils[j+1]=a->fils[j+2];
                    }
                    a->t--;
                }
            }
        }
    }
    return;
}



void Detruire_Cle_Liam(Arbre234 *a,Arbre234 *parent, int cle,int num_f){
    if((*a)==NULL || (*a)->t==0)return;
    int j=0;
    int i=0;
    if((*a)->t==2)j=1;
    for(;i<(*a)->t-1 && (*a)->cles[i+j]<cle;i++);
    if(i+j<(*a)->t && cle==(*a)->cles[i+j]){
        if(feuille(*a)){
            detruire_clef_feuille(a,parent,i,num_f);
        }else{
            Detruire_Cle_Noeud(*a,i+j);
        }
    }else Detruire_Cle_Liam(&((*a)->fils[i+j]),a,cle,i+j);
    doit_fusionner(*a);
    return;
}



int main(int argc, char **argv)
{
    Arbre234 a;
    //int suppr = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Usage : %s <nom fichier> <keytoremove>\n", argv[0]);
        exit(-1);
    }

    a = lire_arbre(argv[1]);

    printf("==== Afficher arbre ====\n");

    afficher_arbre(a, 0);
    
    printf("\nNombre de cles = %d\n",NombreCles(a));
    printf("\nCle max = %d\n",CleMax(a));
    printf("\nCle min = %d\n",CleMin(a));
    
    printf("\nTests de recherche:\n");
    Arbre234 res;
    int cles[20]={50,2,3,10,7,1,280,80,500,301,200,12,375,13,11,252,1000,82,40,6};
    for (int i=0;i<20;i++){
		res=RechercherCle2(a, cles[i]);
		if (res==NULL){printf("res recherche cle %d = null\n",cles[i]);}
		else{printf("res recherche cle %d = %d\n",cles[i],res->cles[1]);}
	}
    
    int nb_feuilles=0,nb_2n=0,nb_3n=0,nb_4n=0;
    AnalyseStructureArbre(a,&nb_feuilles,&nb_2n,&nb_3n,&nb_4n);
    printf("\nAnalyse structure de l'arbre :\nfeuilles = %d, 2-noeuds = %d, 3-noeuds = %d, 4-noeuds = %d\n",nb_feuilles, nb_2n, nb_3n, nb_4n);
    
    printf("\nAffichage clés largeur :\n");
    Afficher_Cles_Largeur(a);
    printf("\n");
    
    printf("\nAffichage clés triées récursive :\n");
    Affichage_Cles_Triees_Recursive(a);
    printf("\n");

    printf("\nAffichage clés triées non récursive :\n");
    Affichage_Cles_Triees_NonRecursive(a);

    printf("\nAffichage clés triées non récursive :\n");
    Affichage_Cles_Triees_NonRecursive(a);

    printf("\n");
    printf("\nAffichage du noeud Max :\n");
    Arbre234 res2;
    noeud_max(a,&res2);
    printf("\n");
    printf("Noeud max: %d \n",res2->cles[1]);

    int res3;
    res3=NombreCles(a);
    printf("Il y a %d Cles \n",res3);
    res3=CleMax(a);

    printf("La Cle Max est %d \n",res3);

    res3=CleMin(a);

    printf("La Cle Min est %d \n",res3);

    Arbre234 TestRemovekeyNode = lire_arbre(argv[1]);
    int keytoremove = atoi(argv[2]);
    printf("Arbre :\n");
    afficher_arbre(TestRemovekeyNode,0);
    //int indice = IndiceKeyMaxFromNode(&(TestRemovekeyNode->fils[2]));
    //printf("indice clef max test truc bidule : %d (%d)\n",indice,TestRemovekeyNode->fils[2]->cles[indice]);
    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,keytoremove,0);
    printf("Arbre avec clé %d supprimé :\n",keytoremove);
    afficher_arbre(TestRemovekeyNode,0);

    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,30,0);
    printf("Arbre avec clé %d supprimé :\n",30);
    afficher_arbre(TestRemovekeyNode,0);

    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,80,0);
    printf("Arbre avec clé %d supprimé :\n",80);
    afficher_arbre(TestRemovekeyNode,0);

    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,10,0);
    printf("Arbre avec clé %d supprimé :\n",10);
    afficher_arbre(TestRemovekeyNode,0);

    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,20,0);
    printf("Arbre avec clé %d supprimé :\n",20);
    afficher_arbre(TestRemovekeyNode,0);


    Detruire_Cle_Liam(&TestRemovekeyNode,NULL,200,0);
    printf("Arbre avec clé %d supprimé :\n",200);
    afficher_arbre(TestRemovekeyNode,0);


    res3=somme_cles(a);

    printf("La somme des clefs de l'arbre est %d \n",res3);

    res3=somme_cles2(a);

    printf("La somme2 des clefs de l'arbre est %d \n",res3);

    return 0;
}
