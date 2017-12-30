#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions_library_dico.h"

#include "tp4_partie1.c"
#include "tp4_partie2.c"
#include "tp4_partie3.c"

int Partie1();
int Partie2();
int Partie3();

int main(){

	int choix = -1;

	//while (choix != 0){
		printf("### NF16 - TP4 ###:\n 1/ Partie 1: les ABR\n 2/ Partie 2: les AL\n 3/ Partie 3: ABR et AL\n 0/ si vous préférez quitter\n");
		scanf("%d", &choix);
	//}

	switch(choix){
		case 0:
			exit(0);
			break;
		case 1:
			choix=Partie1();
			break;
		case 2:
			choix=Partie2();
			break;
		case 3:
			choix=Partie3();
			break;
	}

	return 0;
}


int Partie1()
{
	int choix = -1, k;
	char str[TMAX];
	NodeABR node;
	DicoABR *dico=initdico();
	printf("--------------------------------------------------------\n");
	printf("Nous avons un dictionnaire vide. Que voulez-vous faire ?\n");
	while (choix != 0){
		printf("\n1/ ajouter un mot\n");
		printf("2/ Rechercher un mot\n");
		printf("3/ Supprimer un mot\n");
		printf("4/ Afficher les mots contenus dans le dictionnaire\n");
		printf("5/ Trouver les mots suggérés pour une recherche vague\n");
		printf("0/ toujours pour quitter\n");
		scanf("%d", &choix);

		switch(choix){
			case 0:
				return -1;

			case 1:
				printf("Quel mot ?\n");
				scanf("%s", str);
				ajoutMot(str, dico);
				printf("Done !\n");
				break;

			case 2:
				printf("Quel mot ?\n");
				scanf("%s", str);
				rechercheMot(str, dico);
				break;

			case 3:
				printf("Quel mot ?\n");
				scanf("%s", str);
				supprimeMot(str, dico);
				break;

			case 4:
				afficherDico(dico->root, 0);
				break;

			case 5:
				printf("Que chercher ?\n");
				scanf("%s", str);
				printf("Combien de mots à trouver ?");
				scanf( "%d", &k);
				suggestionMots(k, dico, str);
				break;
			
		}

	}
}


int Partie2()
{
	int choix = -1, k;
	char str[TMAX];
	Dico dico = malloc(sizeof(Dico));
	Mot mot;
	printf("--------------------------------------------------------\n");
	printf("Nous avons un dictionnaire vide. Que voulez-vous faire ?\n");
	while (choix != 0){
		printf("\n1/ ajouter un mot\n");
		printf("2/ Préfixe mot\n");
		printf("3/ Rechercher un mot\n");
		printf("4/ Supprimer un mot\n");
		printf("5/ Afficher les mots contenus dans le dictionnaire\n");
		printf("6/ Trouver les mots suggérés pour une recherche vague\n");
		printf("0/ toujours pour quitter\n");
		scanf("%d", &choix);

		switch(choix){
			case 0:
				return -1;

			case 1://ajout
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				dico=ajoutMot2(mot, dico);
				printf("Done !\n");
				break;

			case 2://prefixe
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				prefixeMot(dico, mot);
				break;

			case 3://recherche
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				rechercheMot2(dico, mot);
				break;

			case 4:
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				supprimeMot2(mot, dico);
				break;

			case 5:
				afficheMot(mot);
				break;
			case 6:
				
				break;
			
		}

	}
}


int Partie3(){
	
	int choix = -1;
	DicoABR *d1;
	Dico d2;

	printf("### Partie 3 ###:\n 1/ Charger dico dans un ABR\n 2/ Charger dico dans un AL\n 0/ si vous préférez quitter\n");
	scanf("%d", &choix);

	switch(choix){
		case 0:
			exit(0);
			break;
		case 1:
			d1=charger_dico_ABR();
			suite1(d1);
			break;
		case 2:
			d2=charger_dico_AL();
			break;
	}

	return 0;
}
