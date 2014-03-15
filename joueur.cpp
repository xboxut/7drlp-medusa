
/***************************************************************
*********            joueur.cpp                      ***********
*********                                            ***********									
****************************************************************
* SOURCE ECRITE POUR LE 7D ROGUELIKE DE 2014 
* AUTEUR: G. DE IZARRA
**************************************
* SOURCE LIBREMENT REUTILISABLE ET MODIFIABLE!!
*
* CONTIENT LA PLUPART DES FONCTIONS DE GESTION DU JOUEUR
*  
***************************************************************/

#include <stdlib.h>

#include "mt19937ar.h"

#include "const_bmp_index.h"
#include "const_act_joueur.h"


#include "objet.h"
#include "joueur.h"
#include "acteur.h"

#include "action.h"


//constructeur pour le joueur
joueur::joueur()
{
	
	nom[0]='\0';
	bmp_index=1;
	
	x=-1;
	y=-1;
	
	vie=0;
	vie_max=0;
	
	adrenaline=0;
	adrenaline_max=0;
	tic_adrenaline=0;
	
	coup_critique=0;//sur 1000
	
	furie=0;
	enfurie=false;
	tic_furie=0;
	//pour gerer les blessure
	hemorragie=false;
	tic_hemorragie=0;
	
	//pour gerer les implants.
	implant_vitesse=false;
	implant_force=false;
	implant_dexterite=false;
	//Caractéristique du joueur
	force=0;
	dexterite=0;
	vitesse=0;
	
	// HANDICAP/BENEFICE 
	manchot=false;
	combat_cac=false;  
	deplacement_rapide=false;
	lambin=false;
	mauvaise_vue=false;
	maudit=false;
	hemophile=false;
	tireur_sang_froid=false;
	
	// reserve de point d action
	point_action_restant=0;
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	equipement[i]=NULL;
	
	sac=false;
	for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
	sac_contenu[i]=NULL;
	
}


joueur::~joueur()
{
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	if(equipement[i]!=NULL)delete equipement[i];
	
	for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
	if(sac_contenu[i]!=NULL)delete sac_contenu[i];
	
	
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/*
#define EQUIPMNT_CHAUSSURE	0
#define EQUIPMNT_PANTALON	1
#define EQUIPMNT_TORSE		2
#define EQUIPMNT_GANT		3
#define EQUIPMNT_MAIN_D		4
#define EQUIPMNT_MAIN_G		5
#define EQUIPMNT_DOS		6
#define EQUIPMNT_TETE		7
*/


//int calcul_protec(joueur *jr);
//fonction qui calcule la somme totale de protection due aux vetements equipes
//
// retourne le score protection total
int calcul_protec(joueur *jr)
{
	int prot=0;
	
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	if(jr->equipement[i]!=NULL)prot+=jr->equipement[i]->protection;
	
	if(jr->equipement[EQUIPMNT_TETE]!=NULL)prot+=jr->equipement[EQUIPMNT_TETE]->protection;
	
	
	return prot;
}



//int degradation_equip_protec(joueur *jr);
//Fonction qui calcule la degradation des vetements equipes.
//
//Si le joueur est touche et que les protections font leur job,
//on selectionne un equipement de protection aleatoire et on le dégrade d'un point
//Si l'etat d'un objet tombe a zero, il est détruit et on le supprime.
//
//retourne le nombre d'equipement detruit
int degradation_equip_protec(joueur *jr)
{
	int equip[MAX_EQUIPMNT];
	int nb_equip;
	
	//recup de l'ensemble des équipement de protection
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	{
		if(jr->equipement[i]!=NULL)
		{
			equip[nb_equip]=i;
			nb_equip++;
		}
	}
	
	if(jr->equipement[EQUIPMNT_TETE]!=NULL)
	{
		equip[nb_equip]=EQUIPMNT_TETE;
		nb_equip++;
	}
	
	//choix aleatoire de l objet.
	nb_equip=genrand_int32()%nb_equip;
	
	//degradation de l objet
	jr->equipement[nb_equip]->etat_obj--;
	
	//suppression de l'objet si celui-ci est casse
	if(jr->equipement[nb_equip]->etat_obj<=0)
	{
		delete jr->equipement[nb_equip];
		jr->equipement[nb_equip]=NULL;
		return 1;
		
	}
	
	return 0;
}


int calcul_bonus_equip_vitdeplace(joueur *jr)
{
	int vit=0;
	
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	if(jr->equipement[i]!=NULL)vit+=jr->equipement[i]->modif_vit_dplcment;
	
	if(jr->equipement[EQUIPMNT_TETE]!=NULL)vit+=jr->equipement[EQUIPMNT_TETE]->modif_vit_dplcment;
	
	
	return vit;
}



//int maj_furie(joueur *jr);
// fonction de mise a jour de la furie
// Si le bool furie est déclenché-> suppression d'un point tout les n tics
// si furie atteint 0 -> mode furie desenclenché.
//
// retourne 1 si la furie est enclenche sinon 0
int maj_furie(joueur *jr)
{
	if(jr->enfurie==false)return 0;
	
	jr->tic_furie++;
	if(jr->tic_furie>=duree[DUREE_PERTE_FURIE])
	{
		jr->tic_furie=0;
		jr->furie--;
		
		if(jr->furie<=0)
		{
			jr->enfurie=false;
			return 0;
		}
		
	}
	return 1;
}

//int maj_adrenaline(joueur *jr);
// Fonction de mise a jour de ladrenaline
// Supprime un point d adrenaline tout le n tics.
// Si adrenaline atteint 0, la fonction retourne 0 sinon 1;
int maj_adrenaline(joueur *jr)
{
	
	jr->tic_adrenaline++;
	if(jr->tic_adrenaline>=duree[DUREE_PERTE_ADRENALINE])
	{
		jr->tic_adrenaline=0;
		jr->adrenaline--;
		if(jr->adrenaline<=0)
		return 0;
	}
	
	return 1;
}

//int maj_hemorragie
//fonction de mise a jour de l etat de sante du joueur 
// en relation ac l hemorragie
// retourne 0 si la sante atteint 0 
// retourne 1 si il y a hemoragie
// retourne 2 si il n y a pas hemoragie
int maj_hemorragie(joueur *jr)
{
	if(jr->hemorragie==false)return 2;
	
	jr->tic_hemorragie++;
	
	if(jr->tic_hemorragie>=duree[DUREE_PERTE_SANG])
	{
		jr->tic_hemorragie=0;
		jr->vie--;
		
		if(jr->vie<=0)
		return 0;
	}
	return 1;
}



int ajout_adrenaline(joueur *jr,int prise_degat,int don_degat,bool mort_ennemi)
{
	
	jr->adrenaline+=prise_degat;
	
	jr->adrenaline+=don_degat/2;// a REGLER
	
	if(mort_ennemi)
	jr->adrenaline+=jr->adrenaline_max/10;
	
	if(jr->adrenaline>jr->adrenaline_max)
	jr->adrenaline=jr->adrenaline_max;
	
	return 0;
}


/***********************************************************************
********************FONCTION DE L'utilisation de l'équipement**********/



int stockage_libre(joueur *jr,bool *sac)
{
	
	
	if(jr->equipement[EQUIPMNT_MAIN_D]==NULL)
	{
	if(sac!=NULL)*sac=false;
	return EQUIPMNT_MAIN_D;
	}	
	if(jr->manchot==false && jr->equipement[EQUIPMNT_MAIN_G]==NULL)
	{
	if(sac!=NULL)*sac=false;
	return EQUIPMNT_MAIN_G;		
	}
	
	if(jr->sac)
	{
		for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
		
		if(jr->sac_contenu[i]==NULL)
		{
		
		if(sac!=NULL)*sac=true;
		return i;
		}
	}
	
	return -1;
}


//bool arme_rechargeable(joueur *jr, int emplacement=EQUIPMNT_MAIN_D,bool sac=false);
//
//Fonction pour savoir si une arme à un emplacement donné est rechargeable ou non.
//
// jr est un pointeur sur le joueur, emplacement l'emplacement où chercher l'arme et 
// sac un booleen qui permet de selectionner la bonne liste d'objet 
//
//RETOURNE vrai si l'arme est rechargeable sinon faux
bool arme_rechargeable(joueur *jr, int emplacement,bool sac)
{
	if(sac==false)
	{
		if(jr->equipement[emplacement]==NULL)return false;
		
		if(jr->equipement[emplacement]->objet_type==OBJ_PISTOLET
		   ||jr->equipement[emplacement]->objet_type==OBJ_FUSIL_POMPE
		   ||jr->equipement[emplacement]->objet_type==OBJ_MITRAILLETTE)
		return true;
	}
	else
	{
		if(jr->sac==false)return false;//si le sac n'existe pas
		if(jr->sac_contenu[emplacement]==NULL)return false;//si l'objet n'existe pas

		if(jr->sac_contenu[emplacement]->objet_type==OBJ_PISTOLET
		   ||jr->sac_contenu[emplacement]->objet_type==OBJ_FUSIL_POMPE
		   ||jr->sac_contenu[emplacement]->objet_type==OBJ_MITRAILLETTE)
		return true;

	
	}
	return false;
}

//bool munition_arme_dans_inv(joueur *jr,int emplace_arme=EQUIPMENT_MAIN_D);
//
//Fonction pour savoir si le joueur possède des munitions pour l'arme à l'emplacement emplace_arme.
//
// RETOURNE vrai si le joueur possède des munitions pour l'arme place a emplace_arme
bool munition_arme_dans_inv(joueur *jr,int emplace_arme,bool sac)
{
	int arme_type;
   if(sac==true)
   {
   	arme_type=jr->sac_contenu[emplace_arme]->objet_type;
   	
   }
   else
   {
   	arme_type=jr->equipement[emplace_arme]->objet_type;
   }	
	
//choix du type de munition a rechercher
   switch(arme_type)
   {
   	case OBJ_PISTOLET:
   	arme_type=OBJ_MUNITION_PISTO;	
   	break;
   	
   	case OBJ_FUSIL_POMPE:
	arme_type=OBJ_MUNITION_FUSIL;	
   	break;
   	   	
	break;
   	case OBJ_MITRAILLETTE:
   	arme_type=OBJ_MUNITION_MITRA;	
   	break;
   	
   }

   for(int i=EQUIPMNT_MAIN_D;i<=EQUIPMNT_MAIN_G;i++)
   {
   		if(jr->equipement[i]!=NULL)
   		{
   		
				if(arme_type==jr->equipement[i]->objet_type)
				{
					return true;
				}   	
		   
   		}
   }
	
	if(sac==true)
	{
	
	   for(int i=0;i<=MAX_SAC_EMPLACEMNT;i++)
	   {
	   		if(jr->sac_contenu[i]!=NULL)
	   		{
	   		
					if(arme_type==jr->sac_contenu[i]->objet_type)
					{
						return true;
					}   	
			   
	   		}
	   }	
			
	}
	
	return false;
}



bool munition_arme_dans_inv(joueur *jr,int emplace_arme)
{
	int type_arme;
	
	if(jr->sac==false && emplace_arme>=MAX_EQUIPMNT)return false;
	
	
	if(emplace_arme>=MAX_EQUIPMNT)
	type_arme=jr->sac_contenu[emplace_arme-MAX_EQUIPMNT]->objet_type;
	else
	type_arme=jr->equipement[emplace_arme]->objet_type;
	
	switch(type_arme)
	{
		case OBJ_PISTOLET:
		type_arme=OBJ_MUNITION_PISTO;
		break;
		case OBJ_FUSIL_POMPE:
		type_arme=OBJ_MUNITION_FUSIL;
		break;
		case OBJ_MITRAILLETTE:
		type_arme=OBJ_MUNITION_MITRA;
		
		break;	
	}
	
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	{
		if(jr->equipement[i]!=NULL && jr->equipement[i]->objet_type==type_arme)
		return true;
		
	}
	
	if(jr->sac)
	{
	
			for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
			{
				if(jr->sac_contenu[i]!=NULL && jr->sac_contenu[i]->objet_type==type_arme)
				return true;
		
				
			}
	}
	return false;
}

//Fonction pour savoir si l'arme correspondant aux munitions choisis sont dans l'inventaire
bool arme_de_ces_muni_ds_inv(joueur *jr,int emplace_munit,bool sac)
{
	int arme_type;
	
	if(sac)
	
		arme_type=jr->sac_contenu[emplace_munit]->objet_type;
	else
		arme_type=jr->equipement[emplace_munit]->objet_type;
		
		
	switch(arme_type)
	{
		
	case OBJ_MUNITION_PISTO:
	arme_type=OBJ_PISTOLET;
	break;
	case OBJ_MUNITION_FUSIL:
	arme_type=OBJ_FUSIL_POMPE;
	break;
	case OBJ_MUNITION_MITRA:
	arme_type=OBJ_MITRAILLETTE;
	break;	
	}
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	{
		if(jr->equipement[i]!=NULL && jr->equipement[i]->objet_type==arme_type)return true;
	}
	
	
	if(sac)
	{
		for(int i=0;i<MAX_EQUIPMNT;i++)
		{
		if(jr->sac_contenu[i]!=NULL &&jr->sac_contenu[i]->objet_type==arme_type)return true;
		}
	}


return false;
}


bool arme_de_ces_muni_ds_inv(joueur *jr,int emplace_munit)
{
	
	int type_arme;
	
	if(jr->sac==false && emplace_munit>=MAX_EQUIPMNT)return false;
	
	
	if(emplace_munit>=MAX_EQUIPMNT)
	type_arme=jr->sac_contenu[emplace_munit-MAX_EQUIPMNT]->objet_type;
	else
	type_arme=jr->equipement[emplace_munit]->objet_type;
	
	switch(type_arme)
	{
		case OBJ_MUNITION_PISTO:
		type_arme=OBJ_PISTOLET;
		break;
		case OBJ_MUNITION_FUSIL:
		type_arme=OBJ_FUSIL_POMPE;
		break;
		case OBJ_MUNITION_MITRA:
		type_arme=OBJ_MITRAILLETTE;
		
		break;	
	}
	
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	{
		if(jr->equipement[i]!=NULL && jr->equipement[i]->objet_type==type_arme)
		return true;
		
	}
	
	if(jr->sac)
	{
	
			for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
			{
				if(jr->sac_contenu[i]!=NULL && jr->sac_contenu[i]->objet_type==type_arme)
				return true;
		
				
			}
	}

	return false;
}

// Fonction pour obtenir l'inde de munitions dans l'inventaire en fonction
// de l arme choisie.
int indice_munition_de_arme(joueur *jr,int inv,bool adanssac ,bool* sac)
{
	int munitype=0;
	
	if(adanssac)
	{
		switch(jr->sac_contenu[inv]->objet_type)
		{
			case OBJ_PISTOLET:
			munitype=OBJ_MUNITION_PISTO;	
			break;
			//
			case OBJ_FUSIL_POMPE:
			munitype=OBJ_MUNITION_FUSIL;	
		    break;
		    //
			case OBJ_MITRAILLETTE:
		    munitype=OBJ_MUNITION_MITRA;	
		    break;
		    
		}
		
	}
	else
	{
		switch(jr->equipement[inv]->objet_type)
		{
			case OBJ_PISTOLET:
			munitype=OBJ_MUNITION_PISTO;	
			break;
			//
			case OBJ_FUSIL_POMPE:
			munitype=OBJ_MUNITION_FUSIL;	
		    break;
		    //
			case OBJ_MITRAILLETTE:
		    munitype=OBJ_MUNITION_MITRA;	
		    break;
		    
		}
		
	}
	
	for(int i=0;i<MAX_EQUIPMNT;i++)
	{
		if(jr->equipement[i]!=NULL)
		{
			if(munitype==jr->equipement[i]->objet_type)
			{
				*sac=false;
				return i;
			}
		}
	}
	
	
	if(jr->sac)
	{
		for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
		{
			if(jr->sac_contenu[i]!=NULL)
			{
				if(munitype==jr->sac_contenu[i]->objet_type)
				{	*sac=true;
					return i;
				}
			}
		}
	}
	
	return -1;
}

//Fonction pour savoir si l'implant est deja mis en place
bool implant_deja_installe(joueur *jr,objet *obj)
{
	
		bool implant_vitesse;
	bool implant_force;
	bool implant_dexterite;
	

	switch(obj->objet_type)
	{
		case OBJ_IMPLANT_FORCE:
		if(jr->implant_force==true)return true;
		return false;
		case OBJ_IMPLANT_VITESSE:
		if(jr->implant_vitesse==true)return true;
		return false;	
		case OBJ_IMPLANT_DXTRT:
		if(jr->implant_dexterite==true)return true;
		return false;	
	}	
	
	
	return false;
}


//int recharger_arme(joueur *jr,int emplacement=EQUIPMNT_MAIN_D,bool sac=false);
//
// Fonction pour recharger l'arme du joueur.
//
// RETOURNE 0 si le joueur a dépensé toutes ses munitions sinon 1
int recharger_arme(joueur *jr,int emplacement,bool sac)
{
	objet *ar;
	int arme_type;
   if(sac==true)
   {
   	arme_type=jr->sac_contenu[emplacement]->objet_type;
   	ar=jr->sac_contenu[emplacement];
   }
   else
   {
   	arme_type=jr->equipement[emplacement]->objet_type;
   	ar=jr->equipement[emplacement];
   	
   }	

/////////////////////////////////////////////////////////////
//choix du type de munition a rechercher
   switch(arme_type)
   {
   	case OBJ_PISTOLET:
   	arme_type=OBJ_MUNITION_PISTO;	
   	break;
   	
   	case OBJ_FUSIL_POMPE:
	arme_type=OBJ_MUNITION_FUSIL;	
   	break;
   	   	
	break;
   	case OBJ_MITRAILLETTE:
   	arme_type=OBJ_MUNITION_MITRA;	
   	break;
   	
   }

//recherche de la munition
   for(int i=EQUIPMNT_MAIN_D;i<=EQUIPMNT_MAIN_G;i++)
   {
   		if(jr->equipement[i]!=NULL)
   		{
   				//munition trouvee -> chargement de la munition dans l'arme.
				if(arme_type==jr->equipement[i]->objet_type)
				{
					
					jr->equipement[i]->munition-=ar->max_munition;
					ar->munition=ar->max_munition;
					// si il n'y a plus de munitions -> suppression de l objet
					if(jr->equipement[i]->munition<=0)
					{
						delete jr->equipement[i];
						jr->equipement[i]=NULL;
						return 0;
					}
				
				 	return 1;
				}   	
		   
   		}
   }
	
	if(sac==true)
	{
	
	   for(int i=0;i<=MAX_SAC_EMPLACEMNT;i++)
	   {
	   		if(jr->sac_contenu[i]!=NULL)
	   		{
	   				//munition trouvee -> chargement de la munition
					if(arme_type==jr->sac_contenu[i]->objet_type)
					{
						
						jr->sac_contenu[i]->munition-=ar->max_munition;
						ar->munition=ar->max_munition;
						// si il n'y a plus de munitions -> suppression de l objet
						if(jr->sac_contenu[i]->munition<=0)
						{
							delete jr->sac_contenu[i];
							jr->sac_contenu[i]=NULL;
							return 0;
						}
					
					 	return 1;
						
					}   	
			   
	   		}
	   }	
			
	}
	
	return 0;		
}


