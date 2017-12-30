#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TMAX 50
#define DEBUG 1
#define MAX_STRING_LENGTH 80
#define MAX_LINES 80

//	PARTIE I
//
// --- Structures ---
typedef struct NodeABR {
	char cle[TMAX];
	struct NodeABR *parent;
	struct NodeABR *left;
	struct NodeABR *right;
} NodeABR;


typedef struct DicoABR {
	NodeABR *root;
	int nb; // le nombre de mots dans le dictionnaire
}DicoABR;


// --- Déclarations des fonctions ---
DicoABR *initdico ();
NodeABR *initNode(char *value);
void afficherNode(NodeABR *node);
void afficherNodeTab(NodeABR **nodeTab);
void afficherDico(NodeABR *root, int nb_tab);

NodeABR *rechercheMot(char *mot, DicoABR *dico);
NodeABR *ajoutMot(char *value, DicoABR *dico);
void supprimeMot(char *mot, DicoABR *dico);
int supprimerNode1(NodeABR *node, DicoABR *dico);
int supprimerNode2(NodeABR *node, DicoABR *dico);
void echangerNodes(NodeABR *n1, NodeABR *n2);
NodeABR *successeur_plus_proche(NodeABR *node);

NodeABR **suggestionMots (int k, DicoABR *dico, char *souschaine);
int compare_souschaine(NodeABR *node, char *souschaine);
NodeABR **compare_k(NodeABR *root, int k, char *souschaine);
int max (int a, int b, int c);


//	PARTIE II
//
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

Dico initpDico(Dico dico, Mot mot);
void afficheMot(Mot mot);
Mot initMot(char *string);
Dico searchBeginCell(Dico dico, Mot mot);
Dico prefixeMot(Dico dico, Mot mot);
int rechercheMot2(Dico dico, Mot mot);
Dico ajoutMot2(Mot mot, Dico dico);
Mot idprefixeMot(Dico dico, Mot mot);
Dico supprimeMot2(Mot mot, Dico dico);


//	PARTIE III
//
//----------Def fonctions-------------------
DicoABR *charger_dico_ABR();
Dico charger_dico_AL();
int suite1();
int suite2();
