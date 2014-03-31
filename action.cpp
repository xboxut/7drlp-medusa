

#include <stdlib.h>

#include "mt19937ar.h"

#include "const_bmp_index.h"
#include "const_act_joueur.h"

#include "objet.h"
#include "joueur.h"
#include "acteur.h"

#include "action.h"


// CONSTRUCTEUR DESTRUCTEUR
action::action()
{
   active=false;	

// Initiateur de l'action	
initj=NULL;
initc=NULL;
/////////////////////////
	
// cible de l'action 
 x=-1;
 y=-1;
ciblec=NULL;
ciblej=NULL;
////////////////////////	

//objet pour ramassage eventuel sur la carte
obj=NULL;	

// type d'action
action_type=-1;
///////////////

// point d'action
point_action=0;
point_bonus=0; // les points bonus sont spécifique a une action et ne peuvent
				 // etre reporté dans la reserve de point d action de l acteur.
////////////////


//informations complémentaires sur l'action
// Pour les mouvements d'objets dans l'inventaire 
// ou autre
 nb1=0;
 bool1=false;

 nb2=0;
 bool2=false;

}

action::~action()
{
	
}



// Tableau contenant les durées de chaque action
//		

//vitesse moyenne 100 -> 4 tic de 100 par secondes

						//attente   marche   prise_obj cmbt_cac cmbt_lanc cmbtlent 
 int action_d[MAX_ACTION]={400,	    400,	 800,		500	,	 800,	   800,		
                        /*cmbtrapid rechar p_medic  habillmnt equmain  mdifcorpo 	lache_obj,	fermer_porte*/
 							500,	700,	5000,	   8000	,	800,		10000,		600		,	400		};
 


 //duree en tics		perte_adrena	perte_sang		perte_furie
 int duree[MAX_DUREE]={4,				8,				2		};
////////////////////////////////////////////////
//////////////////



/* ********FONCTION UTILES POUR L EMISSION DES ACTIONS***
********************************************************/

// Fonction pour rechercher une action vide
//
// Renvoie l'indice de l'action si trouvé, 
// sinon -1;
int recherche_action_vide(action *act,int taille_tab)
{
	
	
	for(register int i=0;i<taille_tab;i++)
	{
		if(act[i].active==false)return i;
	}
	
	return -1;
}

//int transfert_pointact_vers_action(action *act)
//
// Fonction pour trnasferer les point d'action restant des
// acteurs et du joueur vers l'action en cours.
int transfert_pointact_vers_action(action *act)
{
	if(act->initj!=NULL)
	{
		act->point_action=act->initj->point_action_restant;
		act->initj->point_action_restant=0;
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action=act->initc->point_action_restant;
		act->initc->point_action_restant=0;
		return 2;
	
	}	
		
return 0;		
}

//int transfert_pointact_vers_emetteur(action *act)
//
//Fonction pour transfere les points d'action restants dans 
// l'action vers la variable de stockage du joueur ou du pnj 
int transfert_pointact_vers_emetteur(action *act)
{
	
	if(act->initj!=NULL)
	{
		
		act->initj->point_action_restant=act->point_action;
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->initc->point_action_restant=act->point_action;
		return 2;
	
	}	
		
return 0;	
	
}


// Fonction pour remettre a zero une action donnee.
//
//
int vider_action(action *act)
{
	
	  act->active=false;	

// Initiateur de l'action	
act->initj=NULL;
act->initc=NULL;
/////////////////////////
	
// cible de l'action 
 act->x=-1;
 act->y=-1;
act->ciblec=NULL;
act->ciblej=NULL;
////////////////////////	

//objet pour ramassage eventuel sur la carte
act->obj=NULL;	

// type d'action
act->action_type=-1;
///////////////

// point d'action
act->point_action=0;
act->point_bonus=0; // les points bonus sont spécifique a une action et ne peuvent
				 // etre reporté dans la reserve de point d action de l acteur.
////////////////


//informations complémentaires sur l'action
// Pour les mouvements d'objets dans l'inventaire 
// ou autre
 act->nb1=0;
 act->bool1=false;

 act->nb2=0;
 act->bool2=false;
	
	
}


//bool action_terminee(action *act);
// Fonction pour savoir si une action est terminee ou pas
//
bool action_terminee(action *act)
{
	if(act->active==false)return false;
	if((act->point_action+act->point_bonus)>= action_d[act->action_type])
	return true;
	
	//point_action;
	//int point_bonus;
	//
	return false;
}


/****************************************************************
****FONCTION D AJOUT DE TICS DES ACTIONS *******************************/

/******************************************
Les fonctions d'ajout de tic permettent de gerer les bonus de déplacement ou autre

Leur but est SIMPLEMENT D'AJOUTER LE NOMBRE DE POINT D ACTION CORRECT A CHAQUE ACTION

*******************************************/
int ajout_tic_action_attente(action *act)
{

	if(act->initj!=NULL)
	{
		act->point_action+=act->initj->vitesse;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;

	}
	return 0;
	
}

int ajout_tic_action_deplacement(action *act)
{
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->lambin)
		{
		vitesse=vitesse*3/4; // 3/4 de la vitesse normale
		}
		 if(act->initj->deplacement_rapide) //5/4 de vitesse normale
		{
		vitesse=vitesse*5/4;
		}
	
	
		act->point_action+=vitesse;
		
		act->point_bonus+=calcul_bonus_equip_vitdeplace(act->initj);

		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		act->point_bonus+=calcul_bonus_equip_vitdeplace(act->initc);
		return 2;

	}
	return 0;
}

int ajout_tic_action_prise_objet(action *act)
{
	
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		vitesse=vitesse*7/10; // 6/10 de la vitesse normale
		}
		
		
		act->point_action+=act->initj->vitesse;
		

		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
}

int ajout_tic_action_lacher_objet(action *act)
{
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		vitesse=vitesse*7/10; // 6/10 de la vitesse normale
		}
	
	
		act->point_action+=vitesse;
		

		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
}

int ajout_tic_action_cac(action *act)
{
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->combat_cac)
		{
		 vitesse=vitesse*5/4; // 4/5 de la vitesse normale
		}
		
		
		act->point_action+=vitesse;
		

		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
}

int ajout_tic_action_clancer(action *act)
{
	if(act->initj!=NULL)
	{

		act->point_action+=act->initj->vitesse;
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
}


int ajout_tic_action_cafeur(action *act)
{
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		 {
		   if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_PISTOLET)
				vitesse=vitesse*5/4;
		
			else if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_FUSIL_POMPE)
				vitesse=vitesse*3/4;
			else if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE)
				vitesse=vitesse*6/5;
		
				
		}
		 if(act->initj->tireur_sang_froid)
		{
				vitesse=vitesse*2/3;
		}
		
		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
	
}


int ajout_tic_action_cafeul(action *act)
{
	
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		 {
		   if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_PISTOLET)
				vitesse=vitesse*5/4;
		
			else if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_FUSIL_POMPE)
				vitesse=vitesse*3/4;
			else if( act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE)
				vitesse=vitesse*6/5;
		
				
		}
		if(act->initj->tireur_sang_froid)
		{
				vitesse=vitesse*2/3;
		}
		
		
		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
}

int ajout_tic_action_rechargement(action *act)
{
	
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot )
		 {
		    
		  		vitesse=vitesse*3/5;
					
		}
	    if(act->initj->tireur_sang_froid )
		{
				vitesse=vitesse*4/3;
		}
		 
		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
	
	
}

int ajout_tic_action_utilisation_medic(action *act)
{
	
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		   	vitesse=vitesse*7/5;
		}

		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;
	
	
}

int ajout_tic_action_habillement(action *act)
{
	if(act->initj!=NULL)
	{
	int vitesse=act->initj->vitesse;
	
		if(act->initj->manchot)
		{
		   	vitesse=vitesse*8/5;
		}

		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;

	
}

int ajout_tic_action_equipement_main(action *act)
{
	
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		   	vitesse=vitesse*8/5;
		}

		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;

	
}

int ajout_tic_action_modif_corpo(action *act)
{
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		   	vitesse=vitesse*10/5;
		}

		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;

	
}

int ajout_tic_action_ouvrir_fermer_porte(action *act)
{
	if(act->initj!=NULL)
	{
		int vitesse=act->initj->vitesse;
		if(act->initj->manchot)
		{
		   	vitesse=vitesse*6/5;
		}

		act->point_action+=vitesse;
		
		return 1;
	}
	if(act->initc!=NULL)
	{
		act->point_action+=act->initc->vitesse;
		return 2;
	}
	
	return 0;

}



/**********FONCTIONS D EMISSION******************
***********DES ACTIONS *************************/

int emission_action_attente(action *ac,int taille_tab,joueur *jr,acteur *act)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:


// Initiateur de l'action	
ac[nouv].initj=jr;
ac[nouv].initc=act;
/////////////////////////
	
	
// type d'action
ac[nouv].action_type=ACTION_ATTENTE;
///////////////

	return 0;
}

int emission_action_deplacement(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y,bool hautbas)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:

// type d'action
ac[nouv].action_type=ACTION_MARCHE;
	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	ac[nouv].x=x;
	ac[nouv].y=y;
	
	ac[nouv].bool1 =hautbas;
	
	return 0;
}

int emission_action_prise_objet(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *act_dest,int emplacement, int x,int y)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:

	// type d'action
ac[nouv].action_type=ACTION_PRISE_OBJET;
///////////////

	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	
	ac[nouv].x=x;
	ac[nouv].y=y;
	
	//cible eventuelle du ramassage
	ac[nouv].ciblec=act_dest;
	
	//emplacement -> indice de l'objet a recuperer
	ac[nouv].nb1=emplacement;

////////////////////////	
	
	
	return 0;
}


int emission_action_lacher_objet(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement,bool sac, int x,int y)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:

	// type d'action
ac[nouv].action_type=ACTION_LACHE_OBJET;
///////////////


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	
	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	
	ac[nouv].x=x;
	ac[nouv].y=y;
	
	return 0;
}



int emission_action_cac(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *cible,int x,int y,bool emplacement_strict)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:

	// type d'action
ac[nouv].action_type=ACTION_COMBAT_CAC;
///////////////


	// Initiateur de l'action	
	ac[nouv].initc=act;
	
	if(ac[nouv].initc!=NULL)
	{
		ac[nouv].ciblej=jr;
	}
	else
	ac[nouv].initj=jr;

	/////////////////////////
	
	ac[nouv].ciblec=cible;
	ac[nouv].x=x;
	ac[nouv].y=y;
	
	ac[nouv].bool1=emplacement_strict;
	
	return 0;
}

int emission_action_clancer(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *cible,int x,int y,bool emplacement_strict)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:

	// type d'action
ac[nouv].action_type=ACTION_COMBAT_LANCE;
///////////////

	// Initiateur de l'action	
	ac[nouv].initc=act;
	
	if(ac[nouv].initc!=NULL)
	{
		ac[nouv].ciblej=jr;
	}
	else
	ac[nouv].initj=jr;
	/////////////////////////
	
	
	ac[nouv].ciblec=cible;
	ac[nouv].x=x;
	ac[nouv].y=y;
	
	ac[nouv].bool1=emplacement_strict;
	
	
	return 0;
}

int emission_action_cafeur(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *cible,int x,int y,bool emplacement_strict,bool direction)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
	// type d'action
ac[nouv].action_type=ACTION_COMBAT_AFEU_RAPID;
///////////////


// Initiateur de l'action	
	ac[nouv].initc=act;
	
	if(ac[nouv].initc!=NULL)
	{
		ac[nouv].ciblej=jr;
	}
	else
	ac[nouv].initj=jr;
	/////////////////////////

	ac[nouv].ciblec=cible;
	ac[nouv].x=x;
	ac[nouv].y=y;
	ac[nouv].bool1=emplacement_strict;
	ac[nouv].bool2=direction;
	
		
	return 0;
}

int emission_action_cafeurl(action *ac,int taille_tab,joueur *jr,acteur *act,acteur *cible,int x,int y,bool emplacement_strict,bool direction)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_COMBAT_AFEU_VISEE;


// Initiateur de l'action	
	ac[nouv].initc=act;
	
	if(ac[nouv].initc!=NULL)
	{
		ac[nouv].ciblej=jr;
	}
	else
	ac[nouv].initj=jr;
	/////////////////////////

	ac[nouv].ciblec=cible;
	ac[nouv].x=x;
	ac[nouv].y=y;
	ac[nouv].bool1=emplacement_strict;
	ac[nouv].bool2=direction;
	
	return 0;
}

int emission_action_rechargement_arme(action *ac,int taille_tab,joueur *jr, acteur *act,int emplacement,bool sac,bool sol)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_RECHARGEMENT;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	
	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;

	
	return 0;
}

int emission_action_utilisation_medic(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement, bool sac, bool sol)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_PRISE_MEDIC;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////

	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;

	
	return 0;
}

//Emission d action pour l habillement et le deshabillement.
int emission_action_habillement(action *ac,int taille_tab,joueur *jr,acteur *act,int emplacement, bool sac,bool sol)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_HABILLEMENT;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////


	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	
	return 0;
}

//emmission d action pour l equipement et le desequipement de la main
int emission_action_equipement_main(action *ac,int taille_tab,joueur *jr, acteur *act, int emplacement, bool sac,bool sol)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_EQUIP_MAIN;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////

	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	
	return 0;
}

int emission_action_modif_corpo(action *ac,int taille_tab,joueur *jr, acteur *act, int emplacement, bool sac,bool sol)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_MODIF_CORPO;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	
	return 0;
}

int emission_action_ouvrir_fermer_porte(action *ac,int taille_tab,joueur *jr,acteur *act,int x,int y)
{
	//recuperation d'un emplacement pour stocker l'action
	int nouv=recherche_action_vide(ac, taille_tab);

	//vidage de l'action
	vider_action(&ac[nouv]);
	
	//l action est def comme active	
	ac[nouv].active=true;
////////////////////////////////////////////////////:
//type d action
ac[nouv].action_type=ACTION_OUVRIR_FERMER_PORTE;

	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].x=x;
	ac[nouv].y=y;
	ac[nouv].initc=act;
	/////////////////////////
	
	return 0;
}
