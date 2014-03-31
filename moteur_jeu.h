
/***************************************************************
*********            moteur_jeu.h                    ***********
*********                                            ***********									
****************************************************************
* SOURCE ECRITE POUR LE 7D ROGUELIKE DE 2014 
* AUTEUR: G. DE IZARRA
**************************************
* SOURCE LIBREMENT REUTILISABLE ET MODIFIABLE!!
*
*CONTIENT LA DEFINITION DE TOUTES LES DONNEES UTILISEE DANS LE JEU
* AINSI QUE TOUTES LES FONCTIONS D AFFICHAGE DE LOGIQUE ETC...
*
* - BOUCLE PRINCIPALE
* - INITIALISATION DE TOUTES LES DONNES DU JEU
* 
* - FONCTION D AFFICHAGE DE LA CARTE
* - CALCUL DU CHAMP DE VISION
* - PROCESS DES ACTIONS
* - MENU ETC
***************************************************************/


#define MAX_SON 10// definition faute de fichier dedié


class action;

class moteur_jeu
{
	public:
//DEFINITION DU MODE GRAPHIQUE	
	static int ecranX,ecranY;
	static bool plein_ecran;
	
	static int vue_jeuX,vue_jeuY;//taille de la fenetre de jeu
	static int cameraX,cameraY; 

	static int tile_res;
	static int tile_nbX,tile_nbY;
	
	static int frequence_affichage;
	static ALLEGRO_TIMER *timer_affichage;
//////////////////////////////	

//DEFINITION DES DONNES GRAPHIQUES ET SONORES

static ALLEGRO_BITMAP *bitmap_index[MAX_BMP];
static ALLEGRO_SAMPLE *son_index[MAX_SON];
static ALLEGRO_EVENT_QUEUE *queue;
//////////////////////////////

//DEFINITION DES DONNEE PROPRE AU MOTEUR DE JEU
	//définition du joueur
	static joueur ply1;
	
	//définition du monde de jeu
	static carte * monde[NB_MAX_CARTES];
	static int carte_active;

	//nombre d'action maximale
    static action action_tab[NB_MAX_ACTION];
    static int   actions_finies[NB_MAX_ACTION];
    static int nombre_action_finies;
    
   //gestion de la boucle de jeu et du statut du joueur en fin de partie
   static bool sortie_boucle_jeu; //booleen pour savoir si l on doit sortir de la boucle de jeu -> mort de joueur ou quitter
   static bool mort_joueur;// booleen pour savoir si le joueur quitte la partie en vie

   static bool entree_nouv_carte;	
   //static bool 
/////////////////////////////

/****FONCTION D'AFFICHAGE DES CARTES DE JEU + INTERFACE ET INVENTAIRE******/

static int affiche_tuiles( );
static int affiche_objets( );
static int affiche_acteurs( );

static int affiche_joueur();
	
//static int deplacer_camera(int x,int y);
//
// fonction pour déplacer la camera de jeu	
//retourne 1 si la camera est deplacable, sinon 0
static int deplacer_camera(int x,int y);

//static int centrer_camera_joueur();
//
//fonction pour centrer la camera sur le joueur.
static int centrer_camera_joueur();
/***********************************************************/

static int affiche_interface();


// int affiche_inventaire();
//
// FOnction pour afficher l'inventaire
// Utilise un fond en bitmap d'indice BMP_INVENTAIRE_MENU
static int affiche_inventaire();


// AFFICHAGE DES MESSAGES DE LA CONSOLE
// ENCAPSULE DANS la fonction du moteur de jeu ajout message_console. 
// CETTE ENCAPSULATION PERMET D'OPTIMISER LE REAFFICHAGE DES TEXTE-> 
//Alleg est buggé, il est lent a redessiner les textes
static int affiche_boite_message();
	
/****FONCTION GESTION MOTEUR DE JEU  ****/

// Initialisation du jeu


	//static int creation_contenu();
	//
	// Fonction pour charger et produire
	// l'ensemble du contenu de base du jeu. 
	// Bitmap, prefab etc.
	// Cette fonction utilise chargement_bitmap et 
	// creer_prefab_objets, creer_prefab_acteurs
	// creer_prefab_tiles
	static int creation_contenu();
	static int init_alleg_objects(ALLEGRO_DISPLAY *display);
	// 
	static int chargement_bitmap();
	
// Suppression des données creer
 	static int supprimer_bitmap();	
	
// MENU DE CREATION DE PERSONNAGE.	
//	static int
	
	
// *****************************************************
// ************* Gestion de la CONSOLE de jeu **********
// *****************************************************
	
// Fonction pour ajouter un message dans la console
// et updater son affichage.
static int ajouter_mess_console(const char *message, ALLEGRO_COLOR COL);	



//Fonction pour vider les messages de la console
// de la mémoire.
static int vider_console();
// *****************************************************
// ************* Gestion de la boucle de jeu ***********
// *****************************************************

//-------Gestion des actions
		//boucle principale de jeu
		static int jeu();

		static int vider_actions();

        // int ajout_tic();
        //
        // Fonction pour ajouter un tic et incrémenter les points d'action de chacune des
		// actions actives.
		// Retourne 0 si le joueur ne meurt pas.
		// retourne 2 si le joueur meurt. 
		static int ajout_tic();
		
		//int recherche_actions_finies();
		//
		// Fonction pour rechercher les action finies et les stocker
		// dans actions_finies
		static int recherche_actions_finies();
		
		static int calcul_pa_et_tri_action_finies();
		
		// Execution des action finies, 
		// Stoppe tout et
		// retourne 1 si le joueur change de carte.
		static int execution_action_finies();
		
		static int remplacement_action_finies();

		static int premier_remplissage_action();
		
//-------FONCTION D EXECUTION DES ACTIONS

		static int execute_action_attente(action *act);

//		static int execute_action_deplacement(action *act);
//
//     Fonction executer les déplacement du joueur ou des pnj.
// Si le joueur change de carte RETOURNE 1
// Si déplacement standard RETOURNE 0
		static int execute_action_deplacement(action *act);
		static int execute_action_prise_objet(action *act);
		static int execute_action_lacher_objet(action *act);
// 		static int execute_action_cac(action *act);
// 
//Fontion pour exexuter les combats au CaC.
// retourne 1 si le Joeur est mort, sinon 0
		static int execute_action_cac(action *act);
		static int execute_action_clancer(action *act);
		static int execute_action_cafeur(action *act);
		static int execute_action_cafeul(action *act);
		static int execute_action_rechargement(action *act);
		static int execute_action_utilisation_medic(action *act);
		static int execute_action_habillement(action *act);
		static int execute_action_equipement_main(action *act);
		static int execute_action_modif_corpo(action *act);
		static int execute_action_ouvrir_fermer_porte(action *act);
		

// ************************************************************
// ********************FONCTION UTILE POUR LA GESTION DES COMBATS *****
// ************************************************************

// Fonction pour gerer l'interaction entre les tiles et
// les balles lors des calculs des trajectoire e tir.
// retourne 0 si la balle n'est pas arrete
// Sinon retourne 1

 static int interaction_balle_tile(acteur *act, joueur *jr, int x, int y);
 
 
 
// proba_toucher_obstacle
// Fonction pour calculer la probabilité de toucher un obstacle
// entre le tireur et la cible.
// x1 y1 sont la position du tireur et
// x2 y2 les position de la cible.
// pctage -> pourcentage de chance de toucher un obstacle au niveau du joueur /100
// pctage_proche -> pourcentage de chance de touche un obstacle lorsque la distance tireur cible est tres reduite
// int distance_reduit -> longueur maximum a dela de laquelle la distance tireur cible n'est plus réduite.
static bool proba_toucher_obstacle(int x1,int y1,int x2,int y2,int x,int y,int prctage,int pctage_proche,int dist_reduit);				


//static bool proba_toucher_obstacle_direction(int xtireur,ytireur, int x, int y, joueur *jr);
//
// Fonction pour calculer la probabilite de toucher un obstacle lorsque
// l'on décide de tirer dans une direction donnee. 
static bool proba_toucher_obstacle_tdirection( int x, int y, joueur *jr);
static bool proba_toucher_obstacle_tdirection( int x, int y, acteur *act);


//fonction pour savoir si un pnj sur le chemin de la balle, la prend 
// dans la mouille. 
static bool proba_toucher_pnj_non_cible(int x, int y, joueur *jr );
//
// Version pour les pnj 
static bool proba_toucher_pnj_non_cible(int x, int y, acteur *act );
		
	
// Fonction pour calculer et apliquer des dégats en fonction de la position d'un obstacle
// Différent de degat cible car on considere deja que l'obstacle a été touché
// grace a la fonction proba toucher obstacle
static int calcappliq_degat_obstacle(joueur *jr,acteur *act,acteur *cible,int nbballe);

// Fonction pour savoir si la cible visée est atteinte ou pas. Différents des fonctions de traitement
// des obstacles.
static bool calcul_cible_atteinte(joueur *jr, acteur *act,acteur *cible);

//--------GESTION DU JOUEUR
	
	//int placer_joueur(int x,int y);
	//
	// FOnction pour placer le joueur sur
	// la carte active en x et y.
	// Si x et y sont en dehors des limites de la carte RETOURNE -1
	// Si le deplacement se fait dans un mur 			RETOURNE 0
	// Si le deplacement est valide et est correctement menée RETOURNE 1 
	static int placer_joueur(int x,int y);
	
	//gestion_action_joueur(ALLEGRO_EVENT_QUEUE *queue)
	//
	// Fonction pour gerer les choix d'action du joueur!
	static int gestion_action_joueur(ALLEGRO_EVENT_QUEUE *queue);
	
	//int choix_cible(ALLEGRO_EVENT_QUEUE *queue);
	//
	// Fonction pour choisir une cible dans l'entourage du joueur
	// 
	// si direction est vrai, cela signifie  que  le joueur désire tirer dans une direction particuliere
	// de vecteur x,y. Sinon c'est la position de la cible qui est indiqué
	//
	// retourne 1 si la cible est choisie, sinon 0
	static int choix_cible(ALLEGRO_EVENT_QUEUE *queue,int *x,int *y,bool *direction,bool *tirlent);
	static int recherche_cible(int *x,int *y);

	
	//INT gestion_inventaire(ALLEGRO_EVENT_QUEUE *queue);
	//
	// fonction pour gerer l'inventaire et envoyer des actions en conséquence
	// retourne 0 si aucune action n'a été envoyé, sinon retourne 1.
	//
	//
	static int gestion_inventaire(ALLEGRO_EVENT_QUEUE *queue);

	
	//int gestion_ramassage(ALLEGRO_EVENT_QUEUE *queue);
	//
	//Fonction pour gerer l'objet a rammasser par terre.
	static int gestion_ramassage(ALLEGRO_EVENT_QUEUE *queue);
	//Fonction pour gerer le ramassage dans des conteneurs tels que les bureaux etagere etc
	static int gestion_loot(ALLEGRO_EVENT_QUEUE *queue);
	
	//fonction pour gerer l ouverture des portes
	static int gestion_ouverturefermeture(ALLEGRO_EVENT_QUEUE *queue);

	//static int calcul_champ_vision();
	//
	// Fonction de calcul du champ de vision du joueur
	static int calcul_champ_vision();
	static int lancer_rayon(int x1,int y1,int x2,int y2);
	static int suppr_artefact_vision();
	//////////////////////////////////////////////////
	
	

};



extern ALLEGRO_FONT *font;


//Fonction d'affichage de texte.
int affichage_texte(int x,int y, int larg, int ligne_h,int char_lar, char *source);


//Fonction de tri des actions

void int_indquicksort(action *act,int *tableauindice, int debut, int fin,bool croissant);

