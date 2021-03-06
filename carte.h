
#define NB_MAX_CARTES	30	

#define NB_MAX_OBJET	1024
#define NB_MAX_ACTEUR	512


class carte
{
public:

tile **donnee_carte;

int x,y;

bool cle_acquise;

objet *objet_tab[NB_MAX_OBJET];
acteur *acteur_tab[NB_MAX_ACTEUR];
	
	
	carte();
	~carte();
};

/**********************************************************************
***********************DONNE POUR LA CREATION DES CARTES *************
**********************************************************************/

//taille des cartes de jeu
// -> tirage nb aleatoire autour de ces valeur slon la loi normale
extern int carte_taille[NB_MAX_CARTES*2];
extern int ecart_type_ctaille[NB_MAX_CARTES];
//nombre d'ennemi a placer sur les cartes
// -> tirage nb aleatoire autour de ces valeurs selon loi normale 
extern int carte_nb_ennemi[NB_MAX_CARTES];
extern int ecart_type_ennemi;

/**********************************************************************
***************************FONCTIONS DE CREATION DES CARTES*************
**********************************************************************/

/************************************** gestion de l'arbre binaire****
class branche
{
	branche *preced;
	
	int niveau;
	bool separation_dg;
	int pos;
	
	int x,int y;
	int h,int w;
	
	branche *g;
	branche *d;

branche()
	{
	 preced=NULL;
	 g=NULL;
	 d=NULL;
	};
};

int ajout_branche(branche * preced,bool d,int decoup_limitalea,int long_min);

int recherche_taille_min_salle(int *x,int *y);

int ajout_niveau_branche(branche *tronc);

int transformer_en_coordonnee(branche *tronc)


*********************************************************************/


//int recuperer_pos_porte(int x,int y,int w,int h,int *xresult,int yresult);

//Fonction pour r�cupere une porte sans issue sur le morceau x1,y1,x2,y2
int recuperer_pos_porte_sans_issue(carte *crte,int x1,int y1,int x2,int y2,int *xresult,int *yresult);

//Fonction pour r�cuperer les coordonn�es d'une porte de maniere al�atoire
int recuperer_pos_porte_aleatoire(carte *crte,int x1,int y1,int x2,int y2,int *xresult,int *yresult);



// Fonction pour tester si une porte existe au nord sud est ouest
bool pas_de_porte_autour(carte *crte, int x,int y);

//Fonction pour tester si du mobilier existe autour de la position.
bool pas_de_mobilier_autour(carte *carte, int x,int y);

//Fonction pour tester si endroit choisi est un coin de salle.
bool coin_de_salle(carte *carte, int x,int y);
 

carte *creer_carte(int profondeur,int taille_piece, int occupation);
int detruire_carte(carte * crte);

int creer_salle(carte*crte,int x1,int y1,int x2,int y2);

int creer_salle_pcsecu(carte *crte, int x1, int y1, int x2, int y2,int orientation);
int creer_salle_animalerie(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_bloc_operatoire(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_cobayes(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_stocks(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_bureau(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_laboratoire(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_toilettes(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_hall(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_cafeteria(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_dortoir(carte *crte, int x, int y, int w, int h,int orientation);


/***************************************************************************************************************************************
**************************FONCTIONS DIVERSES RECHERCHE ET DEPOT d'OBJET DE TILE POUR DEPLACEMENT COMBAT CONSTRUCTION DE CARTE****************************
****************************************************************************************************************************************/

//int vider_champ_vision_carte(carte *crte);
//
//Fonction pour vider le champ de vision avant
// le calcul du champ de vision.
//
// Prend en param�tre un pointeur sur la carte a traiter
int vider_champ_vision_carte(carte *crte);


//fonction pour lever le bourillard de guerre sur toute la carte.
int decrouvrir_toute_carte(carte *crte);

//int validite_deplacement(carte *crte,int x,int y, int dx,int dy)
//
// Fonction pour tester la validit� d'un d�placement
// RETOURNE 0 SI PAS DE  OBSTACLE
// RETOURNE 1 SI OBSTACLE TILE CASSABLE
// RETOURNE 2 SI OBSTACLE TILE INCASSABLE
// RETOURNE 3 SI OBSTACLE ACTEUR MOBILIER
// RETOURNE 4 SI OBSTACLE ACTEUR PERSONNAGE 
int validite_deplacement(carte *crte,int x,int y, int dx,int dy);


// Fonction pour r�cuperer un pointeur vers l'eventuel
// pnj present en x, y
acteur* obtenir_ennemi(carte *crte,int x, int y);

// Fonction pour recupererun pointeur sur l eventuel
// moilier present en x y
acteur *obtenir_mobilier(carte *crte,int x, int y);

// fonction pour savoir si du mobilier existe en x et y
bool mobilier_present(carte *crte,int x, int  y);

//Fonction pour stocker les acteurs dans la carte.
int ajouter_acteur(carte *crte,acteur *act);

// fonction pour placer un objet deja existant sur la carte
int ajouter_objet(carte *crte,objet *obj);


carte * cree_carte_test();


/*****************************************************************************
*********************** INTERACTION DU MOBILIER AVEC LA CARTE ***************/

//int effectuer_explosion(carte *crte, int x, int y, int rayon, int max_dmg);
//
//Fonction pour faire exploser les grenades ou les bouteilles de gaz
// applique des degats a l'ensemble des acteur autour de l'explosion
// avec un facteur 1/r^2 pour plus de realisme.
// Le degat sont ensuite inflig�s aux tiles comme les portes les vites etc.
int effectuer_explosion(carte *crte, int x, int y, int rayon, int max_dmg);

//int repandre_acide(carte *crte,int x, int y);
//
// Fontion pour remplacer le sol autour de bouteilles d'acide
// par des flaques de liquide corrosif 1 carreau autour de la position x,y
int repandre_acide(carte *crte,int x, int y);



//int detruire_bouteille_gaz(carte *crte,acteur *act);
//
//Fonction pour d�truire une bouteille de gaz.
// transforme l'affichage, la caracteristique passable ou non
// et genere une explosion
//
//
//retourne 0 si ras
// retoune 1 si l'explosion tue le joueur
int detruire_bouteille_gaz(carte *crte,acteur *act,joueur *ply1);
int detruire_bouteille_gaz(carte *crte,int index,joueur *ply1);
 


// int detruire_conteneur_acide(carte *crte,acteur *act);
//
//Fonction pour d�truire un conteneur d'acide.
// transforme l'affichage, la caracteristique passable ou non
// et repand l'acide surle sol
//
int detruire_conteneur_acide(carte *crte,acteur *act);
int detruire_conteneur_acide(carte *crte,int index);

 
 /****************************************************************
 *****************INTERACTION DES ACTEURS AVEC LA CARTE *********/
 
 //int maj_degat_acide(joueur *jr);
//
//Fonction pour ajouter d'eventuels degat du
// a l'acide.
// retourne 0 si la sant� atteint 0
// retourne 1 si il y a d�gat du a l acide
// retourne 2 si il n y a pas de d�gat du a l acide
// LES CHAUSSURES PROTEGENT DE L ACIDE MAIS SE DEGRADENT VITE.
int maj_degat_acide(joueur *jr,carte *crte);
int maj_degat_acide(acteur *act,carte *crte);

//int ajout_degat_verre(joueur *jr);
//
//Fonction pour ajouter d'eventuels degat du
// aux morceaux de verrespar terre si l'acteur ou le joueur
// ne poss�de pas de chaussure
// retourne 0 si la sant� atteint 0
// retourne 1 si il y a d�gat du a verre
// retourne 2 si il le joueur ne prend pas de d�gat 
int ajout_degat_verre(joueur *jr,carte *crte);
int ajout_degat_verre(acteur *act,carte *crte);
