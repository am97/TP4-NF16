#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//----------Def fonctions-------------------
DicoABR * charger_dico_ABR(){
	FILE * f_dico;
	DicoABR *dico=initdico();

	char *buf = malloc((MAX_STRING_LENGTH+1)*sizeof(char));
	char buf2[MAX_LINES+1][MAX_STRING_LENGTH+1];
	
	int n, i=0;
	f_dico = fopen("dictionnaire.txt","a+");
	if (f_dico==NULL) {
		perror("fop erreur :");
		exit(0);
	}
	buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
	while (buf != NULL) {
		printf("buf=%s",buf);
		ajoutMot(buf, dico);
		//strcpy(buf2[i], buf);
		buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
		i++;
	}
	return dico;
}

Dico charger_dico_AL(){
	FILE * f_dico;
	Dico dico = malloc(sizeof(Dico));
	Mot mot;

	char *buf = malloc((MAX_STRING_LENGTH+1)*sizeof(char));
	char buf2[MAX_LINES+1][MAX_STRING_LENGTH+1];
	
	int n, i=0;
	f_dico = fopen("dictionnaire.txt","a+");
	if (f_dico==NULL) {
		perror("fop erreur :");
		exit(0);
	}
	buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
	while (buf != NULL) {
		printf("buf=%s",buf);
		mot=initMot(buf);
		dico=ajoutMot2(mot, dico);
		//strcpy(buf2[i], buf);
		buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
		i++;
	}
	return dico;
}

int verimot_ABR(DicoABR * dico){
	printf("VERIMOT: debut\n");
	FILE * f_dico;

	char *buf = malloc((MAX_STRING_LENGTH+1)*sizeof(char));
	char buf2[MAX_LINES+1][MAX_STRING_LENGTH+1];
	
	int n, i=0;
	f_dico = fopen("file.txt","a+");
	if (f_dico==NULL) {
		perror("fop erreur :");
		exit(0);
	}
	buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
	while (buf != NULL) {
		printf("VERIMOT: mot[%d]=%s",i,buf);
		if(rechercheMot(buf, dico)!= NULL){
			printf("VERIMOT: Ce mot est déjà présent dans le dictionnaire. \n");
			return -1;
		} else {
			printf("VERIMOT: Ce mot n'est pas encore présent dans le dictionnaire. Voulez vous...\n 1/ Le remplacer avec une suggestion?\n 2/ L'ajouter au dictionnaire?\n");
			int choix = -1, k=3;
			char * correction;
			scanf("%d", &choix);
			switch(choix){
				case 0:
					exit(0);
					break;
				case 1:
					suggestionMots(k, dico, buf);
					printf("Veuillez recopier celle que vous souhaitez utiliser:");
					scanf("%s", &correction);
					
					break;
				case 2:
					ajoutMot(buf, dico);
					break;
			}
		}
		//strcpy(buf2[i], buf);
		buf = fgets(buf,MAX_STRING_LENGTH,f_dico);
		i++;
	}
}

int suite1(DicoABR * dico){
	int choix = -1;
	printf("### Dico ABR chargé ###:\n 1/ verimot\n 2/ veridico\n 0/ si vous préférez quitter\n");
	scanf("%d", &choix);

	switch(choix){
		case 0:
			exit(0);
			break;
		case 1:
			verimot_ABR(dico);
			break;
		case 2:
			printf("pas encore implementé");
			break;
	}

	return 0;
	
}
