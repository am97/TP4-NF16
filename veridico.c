DicoABR veridico(DicoABR *dico)
{
	Dico *tab;
	tab = print_ABR(dico);
	char *str;
	int choice;
	NodeABR *node;
	NodeABR *mot;
	printf("quel mot choisissez-vous ?\n");
	scanf("%s", &str);
	int i=0;
	while (tab[i]!=NULL && tab[i]->cle!=str){
		i++;
	}
	if (tab[i]->cle==str){
		mot=tab[i];
		while (choice < 1 || choice > 3){
			printf("1/ Corriger ce mot\n");
			printf("2/Supprimer ce mot\n");
			printf("3/Valider ce mot\n");
			scanf("%d", &choice);
		}

		switch(choice){
			case 1:
				choice = -1;
				while (choice != 1 && choice != 0){
					printf("Corriger le mot %s ? (0/ non ; 1/oui)\n", mot->cle);
					scanf("%d", &choice);
				}
				if (choice == 0){
					break;
				} else if (choice == 1){
					printf("entrez le mot corrigé :\n");
					scanf("%s", str);
					ajoutMot(str, dico);
					supprimeMot(str, dico);
					
				}
				break;

			case 2:
				choice = -1;
				while (choice != 1 && choice != 0){
					printf("Supprimer le mot %s ? (0/ non ; 1/oui)\n", mot->cle);
					scanf("%d", &choice);
				}
				if (choice == 0){
					break;
				} else {
					supprimeMot(str, dico);
				}
				break;

			case 3:
				printf("Ce mot est-il valide ? (0/non ; 1/oui)\n");
				choice = -1;
				while (choice != 1 && choice != 0){
					printf("Le mot %s est-il valide ? (0/ non ; 1/oui)\n", mot->cle);
					scanf("%d", &choice);
				}
				if(choice == 1){
					printf("Très bien, nous allons l'enlever de la liste.\n");
					int j =i;
					while (tab[j+1] != NULL){
						tab[j] = tab[j+1];
						j++
					}
					tab[j]=NULL;
				}

				break;
		}

	} else if (tab[i] == NULL) {
		printf("Le mot selectionné n'est pas dans la liste.\n");
		return NULL;
	}
}