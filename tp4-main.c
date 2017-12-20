#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions_library_dico.h"

int Partie1();
int Partie2();

int main(){

	int choix = -1;

	while (choix != 0){
		printf("Voulez-vous utiliser:\n 1/ les ABR\n 2/ les AL\n 0/ si vous préférez quitter\n");
		scanf("%d", choix);
	}

	switch(choix){
		case 0:
			exit(0);
			break;
		case 1:
			choix=Partie1();
			break;
		case 2:
			choix=Partie2();
	}

	return 0;
}


int Partie1()
{
	int choix = -1, k;
	char *str;
	NodeABR node;
	DicoABR dico=initdico();
	printf("\n\n\nNous avons un dictionnaire vide. Que voulez-vous faire ?\n", );
	while (choix != 0){
		printf("1/ ajouter un mot\n");
		printf("2/ Rechercher un mot\n");
		printf("3/ Afficher les mots contenus dans le dictionnaire\n");
		printf("4/ Trouver les mots suggérés pour une recherche vague\n");
		printf("0/ toujours pour quitter\n");
		scanf("%d", choix);

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
				afficherdico(dico.root, 3);
				break;

			case 4:
				printf("Que chercher ?\n");
				scanf("%s", str);
				printf("Combien de mots à trouver ?");
				scanf("%d", k);
				suggestionMots(k, dico, str);
				break;
			
		}

	}
}


int Partie2()
{
	int choix = -1, k;
	char *str;
	Dico dico;
	Mot mot;
	printf("\n\n\nNous avons un dictionnaire vide. Que voulez-vous faire ?\n", );
	while (choix != 0){
		printf("1/ ajouter un mot\n");
		printf("2/ Rechercher un mot\n");
		printf("3/ Afficher les mots contenus dans le dictionnaire\n");
		printf("4/ Trouver les mots suggérés pour une recherche vague\n");
		printf("0/ toujours pour quitter\n");
		scanf("%d", choix);

		switch(choix){
			case 0:
				return -1;

			case 1://ajout
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				dico=ajoutMot2(str, dico);
				printf("Done !\n");
				break;

			case 2://recherche
				printf("Quel mot ?\n");
				scanf("%s", str);
				mot=initMot(str);
				rechercheMot2(str, dico);
				break;

			case 3:
				
				break;

			case 4:

				break;
			
		}

	}
}
