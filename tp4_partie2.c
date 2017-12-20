#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 25

//----------Structures*--------------------
typedef struct Car
{
	char c;
	struct Car *suiv;
}Car;

typedef struct Cellule
{
	char c;
	struct Cellule *suiv;
	struct Cellule *alt;
}Cell;

typedef Car *Mot;
typedef Cell *Dico;


//--------------Fonctions--------------------

Dico initDico2(Dico dico, Mot mot);
void afficheMot(Mot mot);
Mot initMot(char *string);
Dico searchBeginCell(Dico dico, Mot mot);
Dico prefixeMot(Dico dico, Mot mot);
int rechercheMot(Dico dico, Mot mot);
Dico ajoutMot2(Mot mot, Dico dico);
Mot idprefixeMot(Dico dico, Mot mot);
Dico supprimeMot(Mot mot, Dico dico);


//----------Main: testing--------------------
int main() {

	Dico dico = malloc(sizeof(Dico));
	Mot mot2 = initMot("fin");
	Mot mot = initMot("final");
	Mot mot3 = initMot("avoir");
	Mot mot4 = initMot("avare");
	printf("---------------------------------------------\n");
	dico = initpDico(dico, mot);
	rechercheMot(dico, mot);

	prefixeMot(dico, mot3);
	rechercheMot(dico, mot);
	dico=ajoutMot2(mot2, dico);
	rechercheMot(dico, mot2);

	dico=ajoutMot2(mot3, dico);
	rechercheMot(dico, mot3);
	dico=ajoutMot2(mot4, dico);
	rechercheMot(dico, mot4);
	printf("---------------------------------------------\n");
	dico=supprimeMot(mot3, dico);
	printf("---------------------------------------------\n");
	rechercheMot(dico, mot3);


	return 0;
}

//----------Def fonctions-------------------
Mot initMot(char *string)
{
	printf("INITMOT: mot '%s'\n", string);

	int i=0;
	Mot new;

	Car *car = malloc(sizeof(Car));
	Car *suivant = malloc(sizeof(Car));
	car->c = string[0];
	new=car;

	while(string[i] != '\0'){
		printf("INITMOT: lettre %c\n", string[i]);
		printf("INITMOT: lettre suivante %c\n", string[i+1]);
		suivant->c = string[i+1];
		car->suiv = suivant;
		car = suivant;
		suivant = NULL;
		suivant = malloc(sizeof(Car));
		i++;
	}

	suivant->c = '$';
	car->suiv=suivant;

	printf("INITMOT: fin\n");
	return new;
}


Dico initDico2(Dico dico, Mot mot)
{
	//Allouer l'espace pour le dico
	dico = malloc(sizeof(Dico));
	//créer la première cell
	Cell *new = malloc(sizeof(Cell));
	Car *parcours = mot;
	//dico pointera sur la première cellule
	dico=new;

	while (parcours->suiv!=NULL){
	//initialiser toutes les cellules pour le mot
	new->c = parcours->c;
	new->alt = NULL;
	new->suiv = malloc(sizeof (Cell));
	new= new->suiv;
	parcours=parcours->suiv;
	}

	new->c = '$';
	new->alt = NULL;
	new->suiv = NULL;

	return dico;
}



void afficheMot(Mot mot)
{
	
	Mot parcours = mot;

	while (parcours->suiv != NULL){
		printf("%c  ", parcours->c);
		parcours = parcours->suiv;
	}
	printf("\n");
}

int rechercheMot(Dico dico, Mot mot)
{
	printf("RECHERCHE Mot : ");
	afficheMot(mot);
	Cell *prefixe = prefixeMot(dico, mot);
	if (prefixe != NULL){
		if (prefixe->c == '$'){
			printf("RECHERCHE: Mot trouvé !\n");
			return 1;
		}
	}

	else{
		printf("RECHERCHE: Mot non trouvé !\n");
		return 0;
	}

}


Dico ajoutMot2(Mot mot, Dico dico)
{
	printf("\nAJOUT: début\n");
	afficheMot(mot);

	if (mot== NULL){
		printf("AJOUT: mot NULL\n");
		printf("AJOUT: fin\n\n");
		return NULL;
	} 

	if (dico == NULL){
		dico = initDico2(dico, mot);
		printf("AJOUT: retourne %c\n\n", dico->c);
		return dico;
	}

	if (rechercheMot(dico, mot) == 1){
		printf("AJOUT: mot déjà présent.\n");
		printf("AJOUT: retourne %c\n\n", dico->c);
		return dico;
	}

	Cell *pDico = prefixeMot(dico, mot);
	Cell * temp;
	Car *pMot = idprefixeMot(dico, mot);


	if (pDico == NULL){
		printf("AJOUT: Pas de mot commençant par cette lettre.\n");
		pDico = dico;
		dico = initDico2(dico, mot);
		dico->alt = pDico;
		printf("AJOUT: retourne %c\n\n", dico->c);
		return dico;
	} else { 
		printf("AJOUT: le mot possède un préfixe en commun avec un autre!\n");
		if (pDico->suiv != NULL){
			pDico=pDico->suiv;
		}
	}
	//normalement ce n'est pas possible que pDico->suiv soit égal à NULL si le mot n'est pas déjà présent dans le dico.
		

		if (pDico->c != '$'){
			printf("AJOUT: mot placé sous une autre lettre\n");
			while (pDico->c < pMot->c && pDico->alt != NULL){
				pDico=pDico->alt;
			}
		} else
			printf("AJOUT: mot placé sous un $\n");
		

		printf("AJOUT: pDico = %c.\n", pDico->c);

		if (pDico->alt == NULL){ 
			printf("AJOUT: le mot doit être placé à la fin de la série de alt.\n");
			pDico->alt=initDico2(pDico->alt, pMot);
			printf("AJOUT: retourne %c\n\n", pDico->alt->c);
			return dico;
		} else { 
			printf("AJOUT: on place le mot à sa place.\n");
			temp = pDico->alt;
			pDico->alt=initDico2(pDico->alt, pMot);
			pDico->alt->alt = temp;
			printf("AJOUT: retourne %c\n\n", dico->c);
			return dico;
		}

}

Dico searchBeginCell(Dico dico, Mot mot)
{
	Dico temp;

    if(dico == NULL || mot == NULL){
    	printf("BEGINCELL: dico ou mo NULL\n");
        return NULL;
    }

    if(dico->c == mot->c){
    	printf("BEGINCELL: première lettre : %c\n", dico->c);
        return dico;

    }else{
        if(dico->alt == NULL){
        	printf("BEGINCELL: pas d'alternative à %c. Mot %c\n", dico->c, mot->c);
            return NULL;

        }else{
        	temp = searchBeginCell(dico->alt, mot);
        	if (temp != NULL)
        		printf("BEGINCELL: renvoie %c\n", temp->c);
        	else
        		printf("BEGINCELL: pas de lettre en commun.");
            return temp;
        }
    }
}

Dico prefixeMot(Dico dico, Mot mot){

	if (mot == NULL || dico == NULL){
		printf("PREFIXE: mot ou dico null.\n");
		return NULL;
	}

	Cell *pDico = dico;
	Cell *temp = searchBeginCell(dico, mot);
	if (mot->suiv == NULL){
		printf("PREFIXE: mot à une seule lettre: %c\n", mot->c);
		return temp;
	}
	if (dico->suiv == NULL){
		printf("PREFIXE: dictionnaire une seule cellule.\n");
		return temp;
	}
	if (temp == NULL){
		return NULL;
	}

	Car *pMot = mot;
	//pDico = pDico->suiv;

	while (temp != NULL){
		printf("PREFIXE: temp debut =  %c\n", temp->c);
		if (temp->suiv != NULL){
			pDico = temp;
			pMot = pMot->suiv;
			temp = searchBeginCell(temp->suiv, pMot);
			//printf("PREFIXE: temp fin =  %c\n", temp->c);
		} else {
			pDico = temp;
			temp = NULL;
		}
		
	}
	printf("PREFIXE: return %c\n", pDico->c);
	return pDico;

}

Mot idprefixeMot(Dico dico, Mot mot)
{

	if (mot == NULL || dico == NULL){
		return NULL;
	}

	Cell *pDico = dico;
	Cell *temp = searchBeginCell(dico, mot);
	if (mot->suiv == NULL){
		if (temp != NULL)
			return mot;
		else
			return NULL;
	}
	if (dico->suiv == NULL){
		if (temp != NULL)
			return mot;
		else
			return NULL;
	}

	Car *pMot = mot;
	//pDico = pDico->suiv;

	while (temp != NULL){
		if (temp->suiv != NULL){
			pDico = temp;
			pMot = pMot->suiv;
			temp = searchBeginCell(temp->suiv, pMot);
			//printf("PREFIXE: temp fin =  %c\n", temp->c);
		} else {
			pDico = temp;
			temp = NULL;
		}
		
	}
	return pMot;

}


Dico supprimeMot(Mot mot, Dico dico)
{
	printf("SUPPRIME: Début\n");
	if (rechercheMot(dico, mot) == 0){
		printf("SUPPRIME: le mot n'est pas dans le dico, impossible de le supprimer!\n");
		return dico;
	}

	Cell *pDico = dico;
	Cell *alt;
	Cell *prec;
	Car *pMot = mot;

	pDico = searchBeginCell(dico, mot);
	alt=pDico;

	while (pDico->c != '$'){
		printf("SUPPRIME: pDico = %c\n", pDico->c);
		if (pDico->suiv->alt != NULL){
			printf("SUPPRIME: pDico -> suiv -> alt != NULL\n");
			prec=pDico;
			alt=pDico->suiv;
		}
		pDico = pDico->suiv;
		pMot = pMot->suiv;
		if (pDico->c != pMot->c){
			pDico=searchBeginCell(pDico, pMot);
			//searchbegincell n'est pas censé pouvoir renvoyer 0 vu que le mot existe!
		}

	}
	printf("SUPPRIME: alt = %c\n", alt->c);
	prec->suiv = alt->alt;
	while (pDico->c != '$'){
		pDico = alt->suiv;
		free(alt);
		alt=pDico;
	}
	free(pDico);
	printf("SUPPRIME: fin\n");
	return dico;
}
