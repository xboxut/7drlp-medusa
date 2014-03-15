
/***************************************************************
*********            joueur.h                        ***********
*********                                            ***********									
****************************************************************
* SOURCE ECRITE POUR LE 7D ROGUELIKE DE 2014 
* AUTEUR: G. DE IZARRA
**************************************
* SOURCE LIBREMENT REUTILISABLE ET MODIFIABLE!!
*
* CONTIENT LA DEFINITION DES DONNES DU JOUEUR, AINSI QUE LES 
* DEFINITION DE QUELQUES FONCTION DE GESTION ET DE CALCUL CON
* CERNANT LE JOUEUR. 
* NOTAMMENT:
* - CALCUL DE LA DEGRADATION DES OBJETS DE PROTECT DU JOUEUR
* - CALCUL DE LA PROTECTION TOTALE DU JOUEUR
***************************************************************/




class joueur
{
	public:
		
	char nom[32];
	int bmp_index;
	int x,y;
	
	int vie;
	int vie_max;
	
	int adrenaline;
	int adrenaline_max;
	int tic_adrenaline;
	
	int coup_critique;//sur 1000
	
	int furie;
	bool enfurie;
	int tic_furie;
	
	//pour gerer les blessure
	bool hemorragie;
	int tic_hemorragie;
	
	
	//pour gerer les implants.
	bool implant_vitesse;
	bool implant_force;
	bool implant_dexterite;
	
	//Caractéristique du joueur
	int force;
	int dexterite;
	int vitesse;
	
	objet *equipement[MAX_EQUIPMNT];
	
	//gestion du sac a dos si le joueur à un sac d'équipé
	bool sac;
	objet *sac_contenu[MAX_SAC_EMPLACEMNT];
	
	
	// HANDICAP/BENEFICE 
	bool manchot;// bonus utilisation pistolet (vitesse +1/4 meilleur vise )/ malus vitesse rechargement, slot inventaire, (utilisation fusil -1/4 moins bonne vise), equipement
	bool combat_cac; // Bonus qui vient s'ajouter au degat cac + rand(1/2 degat initials)  vitesse d execution augmente de 1/4 
	bool deplacement_rapide; //vitesse de deplacement augmenté de 1/4 .
	bool lambin;//vitesset de déplacement reduit de 1/4
	bool mauvaise_vue;// probleme pour viser au dela de 4 case de distance
	bool maudit;// plus de chance de faire de reussite critique * 5 , bcp plus de chance de foirer de maniere critique (8% de chance)
	bool hemophile;// impossibilite d arreter une hémorragie
	bool tireur_sang_froid;//1/3 chance en plus de toucher sa cible au tir, 1/3 e temps en plus pour viser bonus rechargement
	
	// reserve de point d action
	int point_action_restant;
	
	joueur();
	~joueur();
	
};



/************************************************************************
*********************FONCTION DE CALCUL EN RAPPORT AVEC L EQUIPEMENT****/

//int calcul_protec(joueur *jr);
//fonction qui calcule la somme totale de protection due aux vetements equipes
//
// retourne le score protection total
int calcul_protec(joueur *jr);

//int degradation_equip_protec(joueur *jr);
//Fonction qui calcule la degradation des vetements equipes.
//
//Si le joueur est touche et que les protections font leur job,
//on selectionne un equipement de protection aleatoire et on le dégrade d'un point
//Si l'etat d'un objet tombe a zero, il est détruit et on le supprime.
//
//retourne le nombre d'equipement detruit
int degradation_equip_protec(joueur *jr);


//int calcul_bonus_vit_deplacement(joeur *jr);
// Retourne le bonus de vitesse de déplacement du à l'equipement 
int calcul_bonus_equip_vitdeplace(joueur *jr);


/***********************************************************************
********************FONCTIONS DE GESTION DES DIFFERENTES JAUGES *******/

//int maj_furie(joueur *jr);
// fonction de mise a jour de la furie
// Si le bool furie est déclenché-> suppression d'un point tout les n tics
// si furie atteint 0 -> mode furie desenclenché.
//
// retourne 1 si la furie est enclenche sinon 0
int maj_furie(joueur *jr);

//int maj_adrenaline(joueur *jr);
// Fonction de mise a jour de ladrenaline
// Supprime un point d adrenaline tout le n tics.
// Si adrenaline atteint 0, la fonction retourne 0 sinon 1;
int maj_adrenaline(joueur *jr);

//int maj_hemorragie
//fonction de mise a jour de l etat de sante du joueur 
// en relation ac l hemorragie
// retourne 0 si la sante atteint 0 
// retourne 1 si il y a hemoragie
// retourne 2 si il n y a pas hemoragie
int maj_hemorragie(joueur *jr);


int ajout_adrenaline(joueur *jr,int prise_degat,int don_degat,bool mort_ennemi);

/***********************************************************************
********************FONCTION DE L'utilisation de l'équipement**********/


//fonction pour savoir si le joueur possède un stockage de libre ou non.
// retourne le numéro d l emplacement libre
int stockage_libre(joueur *jr,bool *sac=NULL);


//bool arme_rechargeable(joueur *jr, int emplacement=EQUIPMNT_MAIN_D,bool sac=false);
//
//Fonction pour savoir si une arme à un emplacement donné est rechargeable ou non.
//
// jr est un pointeur sur le joueur, emplacement l'emplacement où chercher l'arme et 
// sac un booleen qui permet de selectionner la bonne liste d'objet 
//
//RETOURNE vrai si l'arme est rechargeable sinon faux
bool arme_rechargeable(joueur *jr, int emplacement=EQUIPMNT_MAIN_D,bool sac=false);

//bool munition_arme_dans_inv(joueur *jr,int emplace_arme=EQUIPMENT_MAIN_D);
//
//Fonction pour savoir si le joueur possède des munitions pour l'arme à l'emplacement emplace_arme.
//
// RETOURNE vrai si le joueur possede des munitions pour l'arme place a emplace_arme
bool munition_arme_dans_inv(joueur *jr,int emplace_arme,bool sac);
bool munition_arme_dans_inv(joueur *jr,int emplace_arme);

//Fonction pour savoir si l'arme correspondant aux munitions choisis sont dans l'inventaire
bool arme_de_ces_muni_ds_inv(joueur *jr,int emplace_munit,bool sac);
bool arme_de_ces_muni_ds_inv(joueur *jr,int emplace_munit);

// Fonction pour obtenir l'inde de munitions dans l'inventaire en fonction
// de l arme choisie.
int indice_munition_de_arme(joueur *jr,int inv,bool adanssac ,bool* sac);

//Fonction pour savoir si l'implant est deja mis en place
bool implant_deja_installe(joueur *jr,objet *obj);

//int recharger_arme(joueur *jr,int emplacement=EQUIPMNT_MAIN_D,bool sac=false);
//
// Fonction pour recharger l'arme du joueur.
//
// RETOURNE 0 si le joueur a depense toutes ses munitions sinon 1
int recharger_arme(joueur *jr,int emplacement=EQUIPMNT_MAIN_D,bool sac=false);



