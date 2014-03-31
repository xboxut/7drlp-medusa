#define ACTEUR_BUREAU						0
#define ACTEUR_ETAGERE						1
#define ACTEUR_TABLE_OPERATION				2
#define ACTEUR_TABLE						3
#define ACTEUR_RACK_ARME					4
#define ACTEUR_ARMOIRE_MEDIC				5    //limite acteur conteneur
#define ACTEUR_CONSOLE_INFO					6
#define ACTEUR_BOUTEILLE_GAZ				7
#define ACTEUR_CONTENEUR_ACIDE				8
#define ACTEUR_LAVABO						9
#define ACTEUR_TOILETTES					10
#define ACTEUR_LIT							11

// DEFINITION DES PERSONNAGES
#define ACTEUR_SCIENTIFIQUE_BASE			12  //limite acteur pnj
#define ACTEUR_SCIENTIFIQUE_PEUREUX			13
#define ACTEUR_SCIENTIFIQUE_FOU				14
#define ACTEUR_INFIRMIER 					15
#define ACTEUR_INFIRMIER_FOU				16
#define ACTEUR_CHIMPANZE					17
#define ACTEUR_GORILLE						18
#define ACTEUR_SINGE_MUTANT					19

#define ACTEUR_CHIEN						20
#define ACTEUR_CHIEN_MUTANT					21
#define ACTEUR_AGENT_SECURITE				22
#define ACTEUR_AGENT_SECURITE_ARME			23
#define ACTEUR_AGENT_SECURITE_ARME_L		24


#define ACTEUR_SOLDAT						25

#define ACTEUR_H_COBAYE						26
#define ACTEUR_H_COBAYE_FOU					27
#define ACTEUR_H_COBAYE_MUTANT				28
#define ACTEUR_H_COBAYE_TANK				29
#define ACTEUR_H_COBAYE_MUT_COUREUR			30

#define ACTEUR_CADAVRE						31

#define MAX_ACTEUR							32


#define RAYON_EXPLOSION						3
#define DEGAT_EXPLOSION						100

/*
//Constantes pour la définition des comportement
#define CMPRTMNT_RIEN						0
#define CMPRTMNT_NON_AGRESSIF				1
#define CMPRTMNT_FUYARD						2
#define CMPRTMNT_AGRESSIF_NO_LIMIT			3
#define CMPRTMNT_AGRESSIF_LIMIT				4
#define CMPRTMNT_AGRESSIF_FUYARD			5
#define CMPRTMNT_AGRESSIF_SNIPER			6
*/

class acteur
{
public:	
	int acteur_type;
	
	char *acteur_nom;
	char *description;
	
	int bmp_index;
	int bmp_index_detruit;
	
	int x,y;
	
	bool bloquant;
	
	int frce;
	int dxtrt;
	int vitesse;
	
	int vie;
	int vie_max;
	
	int coup_critique;//sur 1000
	
	bool hemorragie;
	int tic_hemorragie;
	//type de comportement
	int comportement_type;
	bool fuite;//savoir si le personnage doit fuir ou non
			   // utile pour les comportement mitigé agresseur/ fuite	
	int effet_memoire;//savoir combien e temps le perso s'echappe
	
	
	// reserve de point d action
	int point_action_restant;
	
	objet *equipement[MAX_EQUIPMNT];
	
	int ajout_score;
	
	acteur();
	~acteur();
};


extern	acteur prefab_acteur[MAX_ACTEUR];
extern char *nom_acteur[MAX_ACTEUR];
extern char *description_acteur[MAX_ACTEUR];

//Fonction pour creer les ressources de base du jeu
// Ici, on creer les objets de base
//
// IL EST POSSIBLE DE MODIFIER LES PROPRIETES DES ACTEURS 
// EN MODIFIANT LA FONCTION creer_prefab_acteurs
int creer_prefab_acteurs();
int supprimer_prefab_acteurs();
/////////////////////////////////////////////////


/**************** FONCTION DE GESTION DES ACTEURS 
******************************************************/

bool est_vivant(acteur* act);



/************************************************************************
*********************FONCTION DE CALCUL EN RAPPORT AVEC L EQUIPEMENT****/

//int calcul_protec(acteur *act);
//fonction qui calcule la somme totale de protection due aux vetements equipes
//
// retourne le score protection total
int calcul_protec(acteur *act);

//int degradation_equip_protec(acteur *act);
//Fonction qui calcule la degradation des vetements equipes.
//
//Si l acteur est touche et que les protections font leur job,
//on selectionne un equipement de protection aleatoire et on le dégrade d'un point
//Si l'etat d'un objet tombe a zero, il est détruit et on le supprime.
//
//retourne le nombre d'equipement detruit
int degradation_equip_protec(acteur *act);

// Fonction qui calcule la dégradation de l arme equipee
//
// Si le joueur frappe avec son arme ou l'utilise, 
// on enleve 1 a l etat général de cette derniere.
int degradation_equip_arme(acteur *act);

//int calcul_bonus_vit_deplacement(joeur *jr);
// Retourne le bonus de vitesse de déplacement du à l'equipement 
int calcul_bonus_equip_vitdeplace(acteur *act);


//int degradation_equip_protec(acteur *act);
//Fonction qui calcule la degradation des vetements equipes.
//
//Si l'acteur est touche et que les protections font leur job,
//on selectionne un equipement de protection aleatoire et on le dégrade d'un point
//Si l'etat d'un objet tombe a zero, il est détruit et on le supprime.
//
//retourne le nombre d'equipement detruit
int degradation_equip_protec(acteur *act);



/***********************************************************************
********************FONCTIONS DE GESTION DES DIFFERENTES JAUGES *******/

//int transformer_en_cadavre(acteur *act);
//
//Fonction pour transformer un acteur mort en cadavre.
int transformer_en_cadavre(acteur *act);

//int faire_saigner(acteur *act);
//
// Fonction pour initier une hémorragie chez l'acteur.
// met le booleen hemorragie sur vraie et retourne 1 
// (10% de chance).
// Sinon retourne 0
int faire_saigner(acteur *act);


//int maj_hemorragie
//fonction de mise a jour de l etat de sante du joueur 
// en relation ac l hemorragie
// retourne 0 si la sante atteint 0 
// retourne 1 si il y a hemoragie
// retourne 2 si il n y a pas hemoragie
int maj_hemorragie(acteur  *act);

/*********************************************************************
*********************************************************************/




// Fonction pour savoir si un sotckage est
// libre chez les perso non joueur et 'lindice de celui
// ci. Si pas de Stockage libre, retourne -1
int stockage_libre(acteur *act);

// Fonction pour obtenir l'inde de munitions dans l'inventaire en fonction
// de l arme choisie.
int indice_munition_de_arme(acteur *act,int inv);
/******************************************************************/
/*******RECOPIE ET CREATION D ACTEURS *****************************/
/******************************************************************/



//Fonction pour placer le mobilier sur les cartes en x, y
//
// Gestion de l'inventaire dans le mobilier.
// MODIFIER CETTE FONCTION POUR CHANGER LES PROBA DE LOOT
acteur * placer_mobilier(int x, int  y,int acteur_type);

//Fonction pour placer les personnages sur la carte.
// 
//Elle permet de tirer l inventaire des perso  
acteur * placer_personnage(int x,int y,int acteur_type);



/********************************************************************
************ GESTION DU COMPORTEMENT DES ACTEURS ********************
********************************************************************/

//fonction pour savoir si le champ de vision entre le joueur et l'acteur
// Choisi est libre ou non!
// c'est l'algo de champ de vision du joueur simplifié (plus rapide)
int acteur_voit_joueur(carte *crte, acteur *act, joueur *jr);

// int acteur_doit_fuir(carte *crte, acteur *act, joueur *jr);
// Fonction pour savoir si l'acteur doit fuir ou non!
// dépend du type de comportement ainsi que du nombre de points
// de vie de l'acteur et de l'armement du joueur

int acteur_doit_fuir(carte *crte, acteur *act, joueur *jr);
