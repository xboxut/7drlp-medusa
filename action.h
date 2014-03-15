

#define TICS_PAR_SECONDES				4


#define ACTION_ATTENTE					0
#define ACTION_MARCHE					1
#define ACTION_PRISE_OBJET				2

#define ACTION_COMBAT_CAC				3
#define ACTION_COMBAT_LANCE				4
#define ACTION_COMBAT_AFEU_VISEE		5
#define ACTION_COMBAT_AFEU_RAPID		6
#define ACTION_RECHARGEMENT				7
#define ACTION_PRISE_MEDIC				8
#define ACTION_HABILLEMENT				9
#define ACTION_EQUIP_MAIN				10
#define ACTION_MODIF_CORPO				11
#define ACTION_LACHE_OBJET				12 // a decrire
#define ACTION_OUVRIR_FERMER_PORTE		13 //A DECRIRE

#define MAX_ACTION						14

#define DUREE_PERTE_ADRENALINE			0
#define DUREE_PERTE_SANG				1
#define DUREE_PERTE_FURIE 				2
		
#define MAX_DUREE						3

//Taille de tableau d'action du moteur de jeu		
#define NB_MAX_ACTION	768 // IL EST NECESSAIRE D AVOIR UN PEU PLUS D ACTION QUE D ACTEUR MAX PAR CARTE POUR EVITER LES PROBLEMES


class action
{
public:
//si l action est activee
bool active;	

// Initiateur de l'action	
joueur *initj;
acteur *initc;
/////////////////////////
	
// cible de l'action 
int x,y;
acteur *ciblec;
joueur *ciblej;
////////////////////////	
	
//objet pour ramassage eventuel sur la carte
objet *obj;

	
// type d'action
int action_type;
///////////////

// point d'action
int point_action;
int point_bonus; // les points bonus sont spécifique a une action et ne peuvent
				 // etre reporté dans la reserve de point d action de l acteur.
////////////////


//informations complémentaires sur l'action
// Pour les mouvements d'objets dans l'inventaire 
// ou autre
int nb1;
bool bool1;

int nb2;
bool bool2;
//////////////////////////////////////////

action();
~action();

};

		
		
// Tableau contenant les durées de chaque action
//		
// la duree de ces actions est definie dans action.cpp
extern int action_d[MAX_ACTION];
extern int duree[MAX_DUREE];
////////////////////////////////////////////////
//////////////////

/* ********FONCTION UTILES POUR L EMISSION DES ACTIONS***
********************************************************/

// Fonction pour rechercher une action vide
//
// Renvoie l'indice de l'action si trouvé, 
// sinon -1;
int recherche_action_vide(action *act,int taille_tab);


//int transfert_pointact_vers_action(action *act)
//
// Fonction pour trnasferer les point d'action restant des
// acteurs et du joueur vers l'action en cours.
int transfert_pointact_vers_action(action *act);


//int transfert_pointact_vers_emetteur(action *act)
//
//Fonction pour transfere les points d'action restants dans 
// l'action vers la variable de stockage du joueur ou du pnj 
int transfert_pointact_vers_emetteur(action *act);


// Fonction pour remettre a zero une action donnee.
//
//
int vider_action(action *act);


//bool action_terminee(action *act);
// Fonction pour savoir si une action est terminee ou pas
//
bool action_terminee(action *act);

/****************************************************************
****FONCTION D AJOUT DE TICS DES ACTIONS *******************************/

/******************************************
Les fonctions d'ajout de tic permettent de gerer les bonus de déplacement ou autre

Leur but est SIMPLEMENT D'AJOUTER LE NOMBRE DE POINT D ACTION CORRECT A CHAQUE ACTION

*******************************************/

int ajout_tic_action_attente(action *act);

int ajout_tic_action_deplacement(action *act);

int ajout_tic_action_prise_objet(action *act);
int ajout_tic_action_lacher_objet(action *act);
int ajout_tic_action_cac(action *act);
int ajout_tic_action_clancer(action *act);
int ajout_tic_action_cafeur(action *act);
int ajout_tic_action_cafeul(action *act);

int ajout_tic_action_rechargement(action *act);
int ajout_tic_action_utilisation_medic(action *act);
int ajout_tic_action_habillement(action *act);
int ajout_tic_action_equipement_main(action *act);

int ajout_tic_action_modif_corpo(action *act);

int ajout_tic_action_ouvrir_fermer_porte(action *act);




/**********FONCTIONS D EMISSION******************
***********DES ACTIONS *************************/

int emission_action_attente(action *ac,int taille_tab,joueur *jr,acteur *act);

int emission_action_deplacement(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y,bool hautbas);

int emission_action_prise_objet(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *act_dest,int emplacement, int x,int y);

int emission_action_lacher_objet(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement,bool sac, int x,int y);

int emission_action_cac(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *cible,int x,int y,bool emplacement_strict);

int emission_action_clancer(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y,bool emplacement_strict);

int emission_action_cafeur(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y,bool emplacement_strict,bool direction);

int emission_action_cafeurl(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y,bool emplacement_strict,bool direction);

int emission_action_rechargement_arme(action *ac,int taille_tab,joueur *jr, acteur *act,int emplacement,bool sac,bool sol);

int emission_action_utilisation_medic(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement, bool sac, bool sol);

//Emission d action pour l habillement et le deshabillement.
int emission_action_habillement(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement, bool sac,bool sol);

//emmission d action pour l equipement et le desequipement de la main
int emission_action_equipement_main(action *ac,int taille_tab,joueur *jr, acteur *act, int emplacement, bool sac,bool sol);

int emission_action_modif_corpo(action *ac,int taille_tab,joueur *jr, acteur *act, int emplacement, bool sac,bool sol);


int emission_action_ouvrir_fermer_porte(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y);

