#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 25

typedef struct NodeABR {
	char* cle;
	struct NodeABR *parent;
	struct NodeABR *left;
	struct NodeABR *right;
} NodeABR;


typedef struct DicoABR {
	NodeABR *root;
	int nb; // le nombre de mots dans le dictionnaire
}DicoABR;




NodeABR *rechercheMot(char *mot, DicoABR *dico);
DicoABR *initdico ();
void afficherNode(NodeABR *node);
NodeABR *initNode(char *value);
NodeABR *ajoutMot(char *value, DicoABR *dico);
NodeABR **suggestionMots (int k, DicoABR *dico, char *souschaine);
int compare_souschaine(NodeABR *node, char *souschaine);
//void insertion_tri (int tab[], int value, int i, int length);
//int indice_tri (int tab[], int value);
void displayDico (NodeABR *node);
NodeABR **compare_k(NodeABR *root, int k, char *souschaine);
void afficherNodeTab(NodeABR **nodeTab);
int max (int a, int b, int c);

void supprimeMot(char *mot, DicoABR *dico);
void supprimerNode(NodeABR *node);
NodeABR *successeur_plus_proche(NodeABR *node);


// --------------------- Testing purposes ---------------------------------
int main(){



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
	supprimeMot("finar", dictionnaire);
	supprimeMot("fin", dictionnaire);

	displayDico(dictionnaire->root);
	printf("----------------------------------------------------------\n");
	suggestionMots(3, dictionnaire, "fi");

	return 0;
}

//----------------------------------------------------------------------



DicoABR *initdico ()
//Initialise le dictionnaire
{
	DicoABR new = malloc(sizeof(DicoABR));
	new->root = NULL;
	new->nb = 0;
	printf("Création de dictionnaire\n");
	return new;
}

NodeABR *initNode(char *value)
//Initialise un node
{
	NodeABR *new = malloc(sizeof(NodeABR));
	new->cle = value;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

NodeABR *ajoutMot(char *value, DicoABR *dico)
//Ajoute un mot au dictionnaire = un node à l'ABR
{
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
				afficherNode(parcours);
				compare = strcasecmp(value, parcours->cle);
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
	printf("RECHERCHE : parcours '%s'\n", parcours->cle);
	int compare = -1;

	//while (compare != 0 && parcours != NULL){
	while (parcours != NULL){
		printf("RECHERCHE : while\n");
		compare = strcasecmp(mot, parcours->cle);
		printf("RECHERCHE : parcours '%s'\n", parcours->cle);
		printf("RECHERCHE : compare %d\n", compare);
		if (compare > 0){
			parcours = parcours->right;
		} else if (compare < 0){
			parcours = parcours->left;
		} else if (compare == 0){
			printf("RECHERCHE : cond compare is 0\n");
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

        printf("supprimeMot: mot=%s dico->root->cle=%s\n",mot,dico->root->cle);
        NodeABR *node = rechercheMot(mot, dico);
        NodeABR *parent, *fils_gauche, *fils_droit;
        int compare=0, pas_de_fils=0, juste_un_fils_gauche=0, juste_un_fils_droit=0, deux_fils=0;

        if (node!=NULL){
                printf("node->cle=%s\n",node->cle);
                if (node->parent != NULL){
                        printf("parent '%s'\n", node->parent->cle);
                        parent=node->parent;
                }
                else{
                        printf("Pas de parent\n");
                        parent=NULL;
                }
                if (node->left != NULL){
                        printf("fils gauche '%s'\n", node->left->cle);
                        fils_gauche=node->left;
                }
                else{
                        printf("Pas de fils gauche.\n");
                        fils_gauche=NULL;
                }
                if (node->right != NULL){
                        printf("fils droit '%s'\n\n", node->right->cle);
                        fils_droit=node->right;
                }
                else{
                        printf("Pas de fils droit\n\n");
                        fils_droit=NULL;
                }

                if(fils_gauche==NULL && fils_droit==NULL) pas_de_fils=1;
                else if(fils_gauche==NULL) juste_un_fils_droit=1;
                else if(fils_droit==NULL) juste_un_fils_gauche=1;
                else deux_fils=1;

        if(pas_de_fils == 0){    // Si le node à supprimer possède au moins un fils
                compare = strcasecmp(node->cle,parent->cle);
                
                if(compare<0){
                        printf("c'est le fils gauche\n");
                if(juste_un_fils_droit == 1) node->parent->left=node->right;
                        if(juste_un_fils_gauche == 1) node->parent->left=node->left;
                        if(deux_fils == 1) node->parent->left=successeur_plus_proche(node);
                }
                else if(compare>0){
                        printf("c'est le fils droit\n");
                        if(juste_un_fils_droit == 1) node->parent->right=node->right;
                        if(juste_un_fils_gauche == 1) node->parent->right=node->left;
                        if(deux_fils == 1) node->parent->right=successeur_plus_proche(node);
                }
                else{
                        printf("Erreur dans l'arbre: node->cle=parent->cle\n");
                }
        }
                supprimerNode(node);
                        
        }
        else{
                printf("supprimeMot: Erreur: Valeur \"%s\" non trouvée\n", mot);
        }
}
void supprimerNode(NodeABR *node){
    node->cle = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    free(node);
}

NodeABR *successeur_plus_proche(NodeABR *node){
    printf("successeur_plus_proche(node): node->cle=%s\n",node->cle);
        NodeABR *s=node->right;
    while (s->left != NULL || s->right != NULL){
        if(s->left != NULL) s=s->left;
        else s=s->right;
    }
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


void displayDico (NodeABR *node)
{
	if (node->left != NULL)
		displayDico (node->left);
	if (node->right != NULL)
		displayDico (node->right);
	printf ("     %s\n", node->cle);
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

	NodeABR **nodeTab = compare_k(dico->root, k, souschaine);

	return nodeTab;

}

void afficherNodeTab(NodeABR **nodeTab)
{
	printf("NODETAB\n");
 	int	i=0;
	while(nodeTab[i]!=NULL) {
		afficherNode(nodeTab[i]);
		i++;
	}
	printf("NODETAB FIN\n");
}

NodeABR **compare_k(NodeABR *root, int k, char *souschaine)
{
	printf("SUGGESTION: Entrée\n");
	NodeABR **nodeTab = malloc (sizeof (nodeTab));

	if (root == NULL ){
		//Si l'arbre est vide
		printf("SUGGESTION: L'arbre est vide.\n");
		return NULL;
	}

	if (root->left == NULL && root->right == NULL){
		//Si l'arbre ne possède qu'un élément
		printf("SUGGESTION: L'arbre n'a qu'un élément.\n");
		nodeTab[0] = root;
		afficherNodeTab(nodeTab);
		printf("SUGGESTION: Retour\n");
		return nodeTab;
	}

	//Dans tous les autres cas l'idée est de récupérer les k mots sur le sag et le sad pour les rassembler dans la table finale
	NodeABR **tabGauche;
	NodeABR **tabDroit;


	//si l'un des deux sous-arbres est vide, alors le tableau final sera celui de l'autre arbre
	if (root->left == NULL){
		nodeTab = compare_k(root->right, k, souschaine);
		printf("SUGGESTION: On retourne l'arbre droit (gauche vide).\n");
		afficherNodeTab(nodeTab);
		printf("SUGGESTION: Retour\n");
		return nodeTab;
	}


	if (root->right == NULL){
		nodeTab = compare_k(root->left, k, souschaine);
		printf("SUGGESTION: On retourne l'arbre gauche (droit vide).\n");
		afficherNodeTab(nodeTab);
		printf("SUGGESTION: Retour\n");
		return nodeTab;
	}


	tabGauche = compare_k(root->left, k, souschaine);
	afficherNodeTab(tabGauche);

	tabDroit = compare_k(root->right, k, souschaine);
	afficherNodeTab(tabDroit);


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
		free(tabDroit);
		free(tabGauche);
	}

	printf("SUGGESTION: return nodeTab.\n");

	afficherNodeTab(nodeTab);
	printf("SUGGESTION: Retour\n");
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

