#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// --------------------- Testing purposes ---------------------------------
/*int main(){



	DicoABR *dictionnaire = initdico();
	ajoutMot("final", dictionnaire);
	ajoutMot("final", dictionnaire);
	ajoutMot("ou", dictionnaire);
	ajoutMot("fin", dictionnaire);
	ajoutMot("as", dictionnaire);
	NodeABR *node = ajoutMot("finaux", dictionnaire);

	printf("test : %d \n", compare_souschaine(node, "firoule"));

	rechercheMot("finar", dictionnaire);
	rechercheMot("ou", dictionnaire);
	afficherDico(dictionnaire->root, 0);
	supprimeMot("finar", dictionnaire);
	supprimeMot("fin", dictionnaire);
	afficherDico(dictionnaire->root, 0);
	
	DicoABR *dico2 = initdico();
	ajoutMot("c", dico2);
	ajoutMot("f", dico2);
	ajoutMot("b", dico2);
	ajoutMot("a", dico2);
	ajoutMot("d", dico2);
	afficherDico(dico2->root, 0);
	supprimeMot("f", dico2);
	afficherDico(dico2->root, 0);
	ajoutMot("g", dico2);
	afficherDico(dico2->root, 0);
	ajoutMot("e", dico2);
	afficherDico(dico2->root, 0);
	supprimeMot("c", dico2);
	afficherDico(dico2->root, 0);

	printf("----------------------------------------------------------\n");
	//suggestionMots(3, dictionnaire, "fi");

	return 0;
}*/

//----------------------------------------------------------------------



DicoABR *initdico ()
//Initialise le dictionnaire
{
	printf("Création du dictionnaire\n");	
	DicoABR *new = malloc(sizeof(DicoABR));
	new->root = NULL;
	new->nb = 0;
	return new;
}

NodeABR *initNode(char *value)
//Initialise un node
{
	NodeABR *new = malloc(sizeof(NodeABR));
	
	int i =0;
	while(*(value+i) != '\0'){
		new->cle[i] = value[i];
		i++;
	}

	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

NodeABR *ajoutMot(char *value, DicoABR *dico)
//Ajoute un mot au dictionnaire = un node à l'ABR
{
	printf("AJOUT: On cherche à insérer %s. \n", value);
	NodeABR *new = initNode(value);

	if (dico->root == NULL){
		printf("AJOUT: L'abre est vide, nous ajoutons sa racine: '%s'\n", value);
		dico->root = new;
		dico->nb++;
		return new;
	} else {
		
		if (rechercheMot(value, dico) != NULL){
			printf("AJOUT: Ce mot est déjà présent dans le dictionnaire. \n");
			return NULL;
		} else {
			printf("AJOUT: Insertion de %s. \n", value);
			NodeABR *parcours = dico->root;
			int compare = -1;

			while (compare != 0){
				if (DEBUG == 1) afficherNode(parcours);
				compare = strcasecmp(value, parcours->cle);
				if (DEBUG == 1) printf("AJOUT : compare %d\n", compare);
				if (compare < 0){
					//Si compare < 0 il faut que la node soit à gauche
					if (parcours->left == NULL){
						parcours->left = new;
						new->parent = parcours;
						printf("AJOUT: node '%s', parent '%s'\n", new->cle, new->parent->cle);
						dico->nb++;
						return new;
						break;
					} else {
						parcours = parcours->left;
					}
				} else if (compare > 0){
					if (parcours->right == NULL){
						parcours->right = new;
						new->parent = parcours;
						printf("AJOUT: node '%s', parent '%s'\n", new->cle, new->parent->cle);
						dico->nb++;
						return new;
						break;
					} else {
						parcours = parcours->right;
					}
				}
			}
		}
	}
}



NodeABR *rechercheMot(char *mot, DicoABR *dico)
{
	if (dico->root == NULL){
		printf("RECHERCHE : L'arbre est vide, il n'y a rien à chercher.");
		return NULL;
	}
	printf("RECHERCHE : on recherche : %s\n", mot);
	NodeABR *parcours = dico->root;
	if (DEBUG == 1) printf("RECHERCHE : parcours '%s'\n", parcours->cle);
	int compare = -1;

	//while (compare != 0 && parcours != NULL){
	while (parcours != NULL){
		if (DEBUG == 1) printf("RECHERCHE : while\n");
		compare = strcasecmp(mot, parcours->cle);
		if (DEBUG == 1) printf("RECHERCHE : parcours '%s'\n", parcours->cle);
		if (DEBUG == 1) printf("RECHERCHE : compare %d\n", compare);
		if (compare > 0){
			parcours = parcours->right;
		} else if (compare < 0){
			parcours = parcours->left;
		} else if (compare == 0){
			if (DEBUG == 1) printf("RECHERCHE : cond compare is 0\n");
			break;
		}
	}

	if (parcours != NULL){
		afficherNode(parcours);
		return parcours;
	} else {
		printf("RECHERCHE : mot non trouvé. \n");
		return NULL;
	}
}


void supprimeMot(char *mot, DicoABR *dico)
{
        //check for errors
        if (dico->root == NULL){
                printf("RECHERCHE : L'arbre est vide, il n'y a rien à chercher.");
                return;
	}

       // printf("supprimeMot: mot=%s dico->root->cle=%s\n",mot,dico->root->cle);
	printf("supprimeMot: On cherche à supprimer %s\n",mot);
        NodeABR *node = rechercheMot(mot, dico);
        if (node!=NULL){
		supprimerNode1(node, dico);
	}
        else{
                printf("supprimeMot: Erreur: Valeur \"%s\" non trouvée\n", mot);
        }
}

//La fonction suivante retourne 0 si la suppression a été effectuée avec succès, -1 sinon.
int supprimerNode1(NodeABR *node, DicoABR *dico){
	printf("supprimeNode1: node->cle=%s dico->root->cle=%s\n",node->cle,dico->root->cle);
	if (DEBUG == 1) afficherDico(dico->root, 0);
	int compare=0, pas_de_parent=0, pas_de_fils=0, juste_un_fils_gauche=0, juste_un_fils_droit=0, deux_fils=0;
	if(node->parent==NULL) pas_de_parent=1;
        if(node->left==NULL && node->right==NULL) pas_de_fils=1;
        else if(node->left==NULL) juste_un_fils_droit=1;
        else if(node->right==NULL) juste_un_fils_gauche=1;
        else deux_fils=1;
	printf("pas_de_parent=%d pas_de_fils=%d juste_un_fils_droit=%d juste_un_fils_gauche=%d deux_fils=%d\n",pas_de_parent, pas_de_fils, juste_un_fils_droit, juste_un_fils_gauche, deux_fils);

        if(deux_fils == 1){
		NodeABR *s=successeur_plus_proche(node);
		echangerNodes(s, node);
		if (DEBUG == 1) printf("s->cle=%s\n", s->cle);
		if (DEBUG == 1) printf("s->parent=%s\n", s->parent->cle);
		return supprimerNode1(s, dico);
	}
	else{
		if(pas_de_parent == 0){    // Si le node à supprimer n'est pas la racine	        
			if(node->parent->left != NULL && node->parent->left == node){
				if (DEBUG == 1) printf("c'est le fils gauche\n");
				if(pas_de_fils == 1) node->parent->left = NULL;
				if(juste_un_fils_droit == 1) { node->parent->left=node->right; node->right->parent=node->parent; }
				if(juste_un_fils_gauche == 1) { node->parent->left=node->left; node->left->parent=node->parent; }			
			}
			else if(node->parent->right != NULL && node->parent->right == node){
			        if (DEBUG == 1) printf("c'est le fils droit\n");
				if(pas_de_fils == 1) node->parent->right = NULL;
			        if(juste_un_fils_droit == 1) { node->parent->right=node->right; node->right->parent=node->parent; }
			        if(juste_un_fils_gauche == 1) { node->parent->right=node->left; node->left->parent=node->parent; }
			}
			else{
			        printf("Erreur dans l'arbre\n");
				return -1;
			}
		}
		else if (pas_de_parent == 1){	// Si le node à supprimer est la racine
		        if(juste_un_fils_droit == 1) dico->root=node->right;
		        if(juste_un_fils_gauche == 1) dico->root=node->left;
			if(pas_de_fils == 1) dico->root=NULL;
		}
        	return supprimerNode2(node, dico);
	}
}

//La fonction suivante retourne 0 si la suppression a été effectuée avec succès.
int supprimerNode2(NodeABR *node, DicoABR *dico){
	if (DEBUG == 1) printf("supprimeNode2: node->cle=%s\n",node->cle);
	//node->cle = NULL;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	free(node);
	dico->nb--;
	return 0;
}

void echangerNodes(NodeABR *n1, NodeABR *n2){
	if (DEBUG == 1) printf("echangerNodes: n1->cle=%s n2->cle=%s \n",n1->cle , n2->cle);
	char temp[50];
	strcpy(temp, n1->cle);
	strcpy(n1 -> cle, n2 -> cle);
	strcpy(n2 -> cle, temp);
	if (DEBUG == 1) printf("echangerNodes: FIN: n1->cle=%s n2->cle=%s temp=%s\n",n1->cle , n2->cle, temp);
}

NodeABR *successeur_plus_proche(NodeABR *node){
    printf("successeur_plus_proche(%s)",node->cle);
        NodeABR *s=node->right;
    while (s->left != NULL){
	s=s->left;
    }
    printf("= %s\n",s->cle);
    return s;
}

void afficherNode(NodeABR *node)
{
	if(node == NULL){
		printf("NODE: Pas de node à afficher.\n");
	} else {
		printf("\nnode '%s'\n", node->cle);

		if (node->parent != NULL)
			printf("parent '%s'\n", node->parent->cle);
		else
			printf("Pas de parent\n");

		if (node->left != NULL)
			printf("fils gauche '%s'\n", node->left->cle);
		else
			printf("Pas de fils gauche.\n");

		if (node->right != NULL)
			printf("fils droit '%s'\n\n", node->right->cle);
		else
			printf("Pas de fils droit\n\n");
	}
	
}

void afficherDico(NodeABR *root, int nb_tab)
{
	int i = 0;
	for (i=0; i<nb_tab; i++){
		printf("    ");
	}
	printf("├── ");
	printf("%s\n", root->cle);
	if(root->left != NULL) afficherDico(root->left, nb_tab + 1);
	if(root->right != NULL) afficherDico(root->right, nb_tab + 1);
}

//--------------------------------Suggestion mots ---------------------------------

int compare_souschaine(NodeABR *node, char *souschaine)
//renvoie le nombre de char dans la sous chaine identique au mot
{
	char *nodecle = node->cle;
	int i = 0;
	int count = 0;

	while (nodecle[i] != '\0' && souschaine[i] != '\0'){
		if (nodecle[i] == souschaine[i]){
			count++;
			i++;
		} else break;
		
	}

	return count;
}//Elle fonctionne



NodeABR **suggestionMots (int k, DicoABR *dico, char *souschaine)
{
	if (DEBUG == 1) printf("suggestionMots(%d,%s,%s):\n",k,dico->root->cle,souschaine);
	NodeABR **nodeTab = compare_k(dico->root, k, souschaine);

	return nodeTab;

}

void afficherNodeTab(NodeABR **nodeTab)
{
	if (DEBUG == 1) printf("NODETAB\n");
 	int	i=0;
	while(nodeTab[i+1]!=NULL) {
		printf(" - %s",nodeTab[i]);
		if (DEBUG == 1) afficherNode(nodeTab[i]);
		i++;
	}
	if (DEBUG == 1) printf("NODETAB FIN\n");
}

NodeABR **compare_k(NodeABR *root, int k, char *souschaine)
{
	if (DEBUG == 1) printf("SUGGESTION: Entrée\n");
	NodeABR **nodeTab = malloc (sizeof (nodeTab));

	if (root == NULL ){
		//Si l'arbre est vide
		printf("SUGGESTION: L'arbre est vide.\n");
		return NULL;
	}

	if (root->left == NULL && root->right == NULL){
		//Si l'arbre ne possède qu'un élément
		if (DEBUG == 1) printf("SUGGESTION: L'arbre n'a qu'un élément.\n");
		nodeTab[0] = root;
		if (DEBUG == 1) afficherNodeTab(nodeTab);
		if (DEBUG == 1) printf("SUGGESTION: Retour\n");
		return nodeTab;
	}

	//Dans tous les autres cas l'idée est de récupérer les k mots sur le sag et le sad pour les rassembler dans la table finale
	NodeABR **tabGauche;
	NodeABR **tabDroit;


	//si l'un des deux sous-arbres est vide, alors le tableau final sera celui de l'autre arbre
	if (root->left == NULL){
		nodeTab = compare_k(root->right, k, souschaine);
		if (DEBUG == 1) printf("SUGGESTION: On retourne l'arbre droit (gauche vide).\n");
		if (DEBUG == 1) afficherNodeTab(nodeTab);
		if (DEBUG == 1) printf("SUGGESTION: Retour\n");
		return nodeTab;
	}


	if (root->right == NULL){
		nodeTab = compare_k(root->left, k, souschaine);
		if (DEBUG == 1) printf("SUGGESTION: On retourne l'arbre gauche (droit vide).\n");
		if (DEBUG == 1) afficherNodeTab(nodeTab);
		if (DEBUG == 1) printf("SUGGESTION: Retour\n");
		return nodeTab;
	}


	tabGauche = compare_k(root->left, k, souschaine);
	if (DEBUG == 1) afficherNodeTab(tabGauche);

	tabDroit = compare_k(root->right, k, souschaine);
	if (DEBUG == 1) afficherNodeTab(tabDroit);


	int i=0, j=0, fin=0;
	int gauche, droit;
	//on met la racine dans le tableau (finir d'inclure la racine !)
	//nodeTab[0] = root;
	int c_root = compare_souschaine(root, souschaine);
	int temp;

	while (tabGauche[i]!=NULL && tabDroit[j]!= NULL && fin<k){

		gauche = compare_souschaine(tabGauche[i], souschaine);
		droit = compare_souschaine(tabDroit[j], souschaine);

		if (c_root != -1){
			temp=max(c_root, gauche, droit);
			if(temp==c_root){
				nodeTab[fin] = root;
				c_root = -1;
				fin++;
			}
			if (temp == gauche){
				nodeTab[fin] = tabGauche[i];
				i++;
				fin++;
			}
			if(temp==droit){
				nodeTab[fin]=tabDroit[j];
				j++;
				fin++;
			}
		} else {
			if(gauche > droit){
				nodeTab[fin] = tabGauche[i];
				fin++;
				i++;
			} else if (gauche < droit){
				nodeTab[fin] = tabDroit[j];
				fin++;
				j++;
			} else { //if gauche == droit
				int comp = strcasecmp(tabGauche[i]->cle, tabDroit[j]->cle);
				if (comp < 0){
					nodeTab[fin] = tabGauche[i];
					i++;
					fin++;
				} else if (comp > 0){
					nodeTab[fin] = tabDroit[j];
					j++;
					fin++;
				}// Le cas ou les deux mots sont identiques n'est pas traité (contrainte d'insertion)
			}
		}

		
	}

	if (tabGauche[i] == NULL && fin<k){
		//nodeTab n'est pas plein et fin de tabGauche > complétion avec tabDroit
		while (fin<k && tabDroit[j] != NULL){
			nodeTab[fin]=tabDroit[j];
			fin++;
			j++;
		}
	} else if (fin<k && tabGauche[j] != NULL){
		while (fin<k && tabGauche[i] != NULL){
			nodeTab[fin]=tabGauche[i];
			fin++;
			i++;
		}
		//nodeTab n'est pas plein et fin de tabDroit > complétion avec tabGauche
	}



	//quand on a fini avec les tableaux temporaires on les supprime
	for (i=0; i<k; i++){
		tabDroit[i] = NULL;
		tabGauche[i] = NULL;
		//free(tabDroit);
		//free(tabGauche);
	}

	if (DEBUG == 1) printf("SUGGESTION: return nodeTab.\n");
	printf("SUGGESTION: Voici les %d suggestions que nous avons trouvé:\n",k);
	afficherNodeTab(nodeTab);
	if (DEBUG == 1) printf("SUGGESTION: Retour\n");
	return nodeTab;

}

int max (int a, int b, int c){
	if (a<b){
		if (b<c)
			return c;
		else
			return b;
	} else { // si a>b
		if (a<c)
			return c;
		else
			return a;

	}
}

