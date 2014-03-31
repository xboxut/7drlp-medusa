/***************************************************************
*********            moteur_jeu.cpp                  ***********
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
* - INITIALISATION D ALLEGRO.
* - FONCTION D AFFICHAGE DE LA CARTE
* - CALCUL DU CHAMP DE VISION
* - PROCESS DES ACTIONS
* - MENU ETC
***************************************************************/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "mt19937ar.h"

#include "gestion_message.h"
#include "const_act_joueur.h"
#include "const_bmp_index.h"

#include "objet.h"
#include "tile.h"
#include "joueur.h"
#include "acteur.h"

#include "action.h"

#include "carte.h"


#include "moteur_jeu.h"




//DEFINITION DU MODE GRAPHIQUE	
int moteur_jeu::ecranX=1024;
int moteur_jeu::ecranY=768;

bool moteur_jeu::plein_ecran=false;
	
int moteur_jeu::vue_jeuX=32*27;
int moteur_jeu::vue_jeuY=32*21; //moteur_jeu::ecranY*4/5;

 int  moteur_jeu::cameraX=0; 
 int moteur_jeu::cameraY=0; 

int moteur_jeu::tile_res=32;
 int moteur_jeu::tile_nbX=moteur_jeu::vue_jeuX/moteur_jeu::tile_res;
 int moteur_jeu::tile_nbY=moteur_jeu::vue_jeuY/moteur_jeu::tile_res;
	
	
int moteur_jeu::frequence_affichage=60;
 ALLEGRO_TIMER *moteur_jeu::timer_affichage=NULL;
//////////////////////////////	

//DEFINITION DES DONNES GRAPHIQUES ET SONORES

ALLEGRO_BITMAP * moteur_jeu::bitmap_index[MAX_BMP];
ALLEGRO_SAMPLE * moteur_jeu::son_index[MAX_SON];
ALLEGRO_EVENT_QUEUE *moteur_jeu::queue=NULL;
//////////////////////////////

//DEFINITION DES DONNEE PROPRE AU MOTEUR DE JEU
	//définition du joueur
 joueur  moteur_jeu::ply1;
	
	//définition du monde de jeu
 carte *  moteur_jeu::monde[NB_MAX_CARTES];
 int  moteur_jeu::carte_active=0;

	//nombre d'action maximale
 action  moteur_jeu::action_tab[NB_MAX_ACTION];
 int    moteur_jeu::actions_finies[NB_MAX_ACTION];
 int 	 moteur_jeu::nombre_action_finies;
    
   //gestion de la boucle de jeu et du statut du joueur en fin de partie
 bool  moteur_jeu::sortie_boucle_jeu=false; //booleen pour savoir si l on doit sortir de la boucle de jeu -> mort de joueur ou quitter
 bool  moteur_jeu::mort_joueur=false;// booleen pour savoir si le joueur quitte la partie en vie

 bool  moteur_jeu::entree_nouv_carte=true;	


/////////////////////////////

ALLEGRO_FONT *font;



/****FONCTION D'AFFICHAGE DES CARTES DE JEU ******/

int moteur_jeu::affiche_tuiles()
{
	int maxX;
	int maxY;	

//limitation de la zone a afficher
	if(cameraX+tile_nbX>= monde[carte_active]->x)maxX=monde[carte_active]->x;
	else maxX=cameraX+tile_nbX;
	if(cameraY+tile_nbY>= monde[carte_active]->y)maxY=monde[carte_active]->y;
	else maxY=cameraY+tile_nbY;
	
	//boucle d'affichage
	for(int i=cameraY;i<maxY;i++)
	{
		
		for(int j=cameraX;j<maxX;j++)
		{
			
			if(monde[carte_active]->donnee_carte[i][j].decouvert==false)
			{
				
				al_draw_bitmap_region(bitmap_index[BMP_INTERIEUR_MUR],
   				0.0, 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);
			}
			else
			{
			
				if(monde[carte_active]->donnee_carte[i][j].champ_vision)
				{
					if(monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_FRAGILE ||
					   monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_NORMALE ||
					   monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_BLINDE)
					{
							if(monde[carte_active]->donnee_carte[i][j].ferme)
							{
								al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index],
   								0.0, 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);	
							}
							else
								al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index2],
			   					0.0, 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);	
							
					}
					else
					al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index],
   					0.0, 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);					
				}
				else
				{	
				
					if(monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_FRAGILE ||
					   monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_NORMALE ||
					   monde[carte_active]->donnee_carte[i][j].type==TILE_PORTE_BLINDE)
					{
							if(monde[carte_active]->donnee_carte[i][j].ferme)
							{
									al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index],
	   								float(tile_res), 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);

							}
							else
								al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index2],
	   							float(tile_res), 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);

					}
					else
					al_draw_bitmap_region(bitmap_index[monde[carte_active]->donnee_carte[i][j].bmp_index],
	   				float(tile_res), 0.0, float(tile_res), float(tile_res), float((j-cameraX)*tile_res), float((i-cameraY)*tile_res), 0);
				}
				
			}
			
			
		}
		
	}
	
	return 0;
}


int moteur_jeu::affiche_objets()
{

	for( register int i=0; i<NB_MAX_OBJET;i++)
	{
		// Si l'objet existe
		if(monde[carte_active]->objet_tab[i]!=NULL)
		{
			//test pour voir si l'objet est dans l'écran
			if(monde[carte_active]->objet_tab[i]->x>= cameraX && 
			   monde[carte_active]->objet_tab[i]->y>= cameraY &&
			   monde[carte_active]->objet_tab[i]->x< cameraX+tile_nbX &&
			   monde[carte_active]->objet_tab[i]->y< cameraY+tile_nbY )
			{
				        //choix du bitmap a afficher
						if(monde[carte_active]->donnee_carte[monde[carte_active]->objet_tab[i]->y][monde[carte_active]->objet_tab[i]->x].decouvert==true)
						{
							
								if(monde[carte_active]->donnee_carte[monde[carte_active]->objet_tab[i]->y][monde[carte_active]->objet_tab[i]->x].champ_vision==true)
								{
									
										al_draw_bitmap_region(bitmap_index[monde[carte_active]->objet_tab[i]->bmp_index],
   										0.0, 0.0, float(tile_res), float(tile_res), float((monde[carte_active]->objet_tab[i]->x-cameraX)*tile_res), float((monde[carte_active]->objet_tab[i]->y-cameraY)*tile_res), 0);					
																			
								}
								else
								{
									
										al_draw_bitmap_region(bitmap_index[monde[carte_active]->objet_tab[i]->bmp_index],
   										float(tile_res), 0.0, float(tile_res), float(tile_res),  float((monde[carte_active]->objet_tab[i]->x-cameraX)*tile_res),float((monde[carte_active]->objet_tab[i]->y-cameraY)*tile_res), 0);													
										
								}
							
							
						}
			}
			
			
		}
	
		
	}
			
	return 0;
}


int moteur_jeu::affiche_acteurs()
{
	

	for( register int i=0; i<NB_MAX_ACTEUR;i++)
	{
 
		// Si l'objet existe
		if(monde[carte_active]->acteur_tab[i]!=NULL)
		{
				//test pour voir si l'objet est dans l'écran
			if(monde[carte_active]->acteur_tab[i]->x>= cameraX && 
			   monde[carte_active]->acteur_tab[i]->y>= cameraY &&
			   monde[carte_active]->acteur_tab[i]->x< cameraX+tile_nbX &&
			   monde[carte_active]->acteur_tab[i]->y< cameraY+tile_nbY )
			{
				
				        //choix du bitmap a afficher
						if(monde[carte_active]->donnee_carte[monde[carte_active]->acteur_tab[i]->y][monde[carte_active]->acteur_tab[i]->x].decouvert==true)
						{
							
								if(monde[carte_active]->donnee_carte[monde[carte_active]->acteur_tab[i]->y][monde[carte_active]->acteur_tab[i]->x].champ_vision==true)
								{
									
										al_draw_bitmap_region(bitmap_index[monde[carte_active]->acteur_tab[i]->bmp_index],
   										0.0, 0.0, float(tile_res), float(tile_res),  float((monde[carte_active]->acteur_tab[i]->x-cameraX)*tile_res),float((monde[carte_active]->acteur_tab[i]->y-cameraY)*tile_res), 0);					
																			
								}
								else
								{
		

								 if(monde[carte_active]->acteur_tab[i]->acteur_type<ACTEUR_SCIENTIFIQUE_BASE)
								 al_draw_bitmap_region(bitmap_index[monde[carte_active]->acteur_tab[i]->bmp_index],
   										float(tile_res), 0.0, float(tile_res), float(tile_res),  float((monde[carte_active]->acteur_tab[i]->x-cameraX)*tile_res),float((monde[carte_active]->acteur_tab[i]->y-cameraY)*tile_res), 0);													
											
								}
							
							
						}
			}
			
			
		}
	
		
	}
			
	return 0;


}

//static int affiche_joueur();
//
//Fonction pour afficher le joueur à l'écran.

int moteur_jeu::affiche_joueur()
{
	
	if(ply1.x>= cameraX && ply1.y>=cameraY && ply1.x < cameraX+tile_nbX && ply1.y < cameraY+tile_nbY)
	{
		
			al_draw_bitmap_region(bitmap_index[BMP_JOUEUR],
   				0.0, 0.0, float(tile_res), float(tile_res), float((ply1.x-cameraX)*tile_res), float((ply1.y-cameraY)*tile_res), 0);													
									
	
		
	}
	
}


int moteur_jeu::affiche_interface()
{
		
		al_draw_bitmap(bitmap_index[BMP_INTERFACE_FOND],float(vue_jeuX), 0.0,  0);													
									
	
		//al_draw_filled_rectangle(float(vue_jeuX)+0.5,float(0.5),float(ecranX)-0.5,float(vue_jeuY)-0.5,al_map_rgb(0,0,0));
	
	  	al_draw_text(font,al_map_rgb(0,0,0), float(vue_jeuX+5),float(5), 0,ply1.nom);
	   			
	// JAUGE DE VIE 
	   // Taille de 20 de large
	   // taille de 150 de haut
	   // debut de la jauge 20
		al_draw_rectangle(float(vue_jeuX+(ecranX-vue_jeuX)/5),float(100),float(vue_jeuX+(ecranX-vue_jeuX)/5+20)+0.5,float(100+150),al_map_rgb(255,0,0),2.0);
		al_draw_filled_rectangle(float(vue_jeuX+(ecranX-vue_jeuX)/5+2),float(100+150-150*ply1.vie/ply1.vie_max+2),float(vue_jeuX+(ecranX-vue_jeuX)/5+20-2)+0.5,float(100+150-2),al_map_rgb(242,40,40));
		
		al_draw_textf(font,al_map_rgb(255,50,0), float(vue_jeuX+(ecranX-vue_jeuX)/5+10),float(100+150+20), ALLEGRO_ALIGN_CENTRE,"%d/%d",ply1.vie,ply1.vie_max);
	   		   		
   		
	//al_draw_filled_rectangle(0.0,float(682),float(vue_jeuX+8)+0.5,float(ecranY),al_map_rgb(0,0,0));
   
	
	// JAUGE D' ADRENALINE
		al_draw_rectangle(float(vue_jeuX+3*(ecranX-vue_jeuX)/5),float(100),float(vue_jeuX+3*(ecranX-vue_jeuX)/5+20)+0.5,float(100+150),al_map_rgb(5,29,192),2.0);
     	al_draw_filled_rectangle(float(vue_jeuX+3*(ecranX-vue_jeuX)/5+2),float(100+150-150*ply1.adrenaline/ply1.adrenaline_max+2),float(vue_jeuX+3*(ecranX-vue_jeuX)/5+20-2)+0.5,float(100+150-2),al_map_rgb(61,84,250));

	    al_draw_textf(font,al_map_rgb(0,50,250), float(vue_jeuX+3*(ecranX-vue_jeuX)/5+10),float(100+150+20), ALLEGRO_ALIGN_CENTRE,"%d/%d",ply1.adrenaline,ply1.adrenaline_max);
	
	// AFFICHAGE DES CARACTERISTIQUES DU JOUEUR
	
	    al_draw_textf(font,al_map_rgb(0,0,0), float(vue_jeuX+5),float(100+150+20+50), 0,"Caracteristiques");
	
		al_draw_textf(font,al_map_rgb(0,0,0), float(vue_jeuX+15),float(100+150+20+70), 0,"Force: %d", ply1.force);
		al_draw_textf(font,al_map_rgb(0,0,0), float(vue_jeuX+15),float(100+150+20+80), 0,"Dexteri: %d", ply1.dexterite);
		al_draw_textf(font,al_map_rgb(0,0,0), float(vue_jeuX+15),float(100+150+20+90), 0,"Vitesse: %d", ply1.vitesse);
		//al_draw_textf(font,al_map_rgb(0,50,250), float(vue_jeuX+40),float(100+150+20+70), 0,"Dxtrt: %d", ply1.dexterite);
		
	// GESTION DE LA FURIE
	 if( ply1.enfurie)
	 {
	 	
	 		al_draw_bitmap(bitmap_index[BMP_INTERFACE_BFURIE],float(vue_jeuX+30), float(100+150+20+115),  0);													
	
	 }
	
	// Affichage du saignement
	 if( ply1.hemorragie)
	 {
	 	
	 		al_draw_bitmap(bitmap_index[BMP_INTERFACE_BHEMORRAGIE],float(vue_jeuX+30), float(100+150+20+155),  0);													
	
	 }
	
	 if( monde[carte_active]->cle_acquise)
	 {
	 	
	 		al_draw_bitmap(bitmap_index[BMP_INTERFACE_BCLE],float(vue_jeuX+30), float(100+150+20+255),  0);													
	
	 }
	
	
	return 0;
}


 int moteur_jeu::affiche_inventaire()
 {
 	
 	
 	//On affiche l'inventaire au milieu de l'écran.
 	// IL y a 5 emplacement dans le sac a dos
 	// et 8 equipements différent sur le joueur.
 	// separation de 2 items entre le sac et le reste si il existe.
 	
 	// speration 1/2 tile res entre le nom de l objet et son image
 	
	 //separation 1 item entre description et reste
	// affichage de la description de l'objet sur 5 lignes de 10 pixels
 	
 	// affichage des objet à 300 pixels du bord gauche de l ecran
 	
 	
 	int y=(ecranY-((8+5+2+1)*tile_res+10*5))/2;
 	
 	  al_draw_bitmap(bitmap_index[BMP_INVENTAIRE_MENU],
		   				  0., float(y), 00);
				
 	
 	for(int i=0;i<MAX_EQUIPMNT;i++)
 	{	
 	   if(ply1.equipement[i]!=NULL)
 	   {
 	   	  al_draw_bitmap_region(bitmap_index[ply1.equipement[i]->bmp_index],
   				0.0, 0.0, float(tile_res), float(tile_res), 400., float(y+i*tile_res), 0);
		
			//affichage des munitions
			if(ply1.equipement[i]->objet_type==OBJ_MUNITION_PISTO ||
				ply1.equipement[i]->objet_type==OBJ_MUNITION_FUSIL ||
				ply1.equipement[i]->objet_type==OBJ_MUNITION_MITRA 	)
				{	
		  			al_draw_textf(font,al_map_rgb(0,0,0), float(400+tile_res+tile_res/2),float(y+i*tile_res+(tile_res-8)/2), 0,"%s  x %d",ply1.equipement[i]->objet_nom,ply1.equipement[i]->munition);
	   													
				}
				else//affichage du reste
				al_draw_textf(font,al_map_rgb(0,0,0), float(400+tile_res+tile_res/2),float(y+i*tile_res+(tile_res-8)/2), 0,"%s (etat: %d)",ply1.equipement[i]->objet_nom,ply1.equipement[i]->etat_obj);
	   				
 	   }
 	}
 	
 	if(ply1.sac)
 	{
 	
		 	for(int i=0;i<MAX_SAC_EMPLACEMNT;i++)
		 	{	
		 	   if(ply1.sac_contenu[i]!=NULL)
		 	   {
		 	   	  al_draw_bitmap_region(bitmap_index[ply1.sac_contenu[i]->bmp_index],
		   				0.0, 0.0, float(tile_res), float(tile_res), 400.+float(tile_res), float((MAX_EQUIPMNT+2)*tile_res +y+i*tile_res), 0);
					
				if(ply1.sac_contenu[i]->objet_type==OBJ_MUNITION_PISTO ||
				   ply1.sac_contenu[i]->objet_type==OBJ_MUNITION_FUSIL ||
				   ply1.sac_contenu[i]->objet_type==OBJ_MUNITION_MITRA 	)
				   {
				   	al_draw_textf(font,al_map_rgb(0,0,0), float(400+tile_res*2+tile_res/2),float((MAX_EQUIPMNT+2)*tile_res+y+i*tile_res+(tile_res-8)/2), 0,"%s  x %d",ply1.sac_contenu[i]->objet_nom,ply1.sac_contenu[i]->munition);
			   		
				   }
				   else	
				  	al_draw_textf(font,al_map_rgb(0,0,0), float(400+tile_res*2+tile_res/2),float((MAX_EQUIPMNT+2)*tile_res+y+i*tile_res+(tile_res-8)/2), 0,"%s (etat: %d)",ply1.sac_contenu[i]->objet_nom,ply1.sac_contenu[i]->etat_obj);
			   													
					
		 	   }
		 	}
 	}
 	
 }
 
 
 
 
int moteur_jeu::affiche_boite_message()// a faire
{

/*
	ALLEGRO_USTR *src= al_ustr_new(source);
	ALLEGRO_USTR *aff=al_ustr_new("");
	
	
	int nb_char_ligne=larg/char_lar;
	int lcnt=0;
	
	
	while(lcnt*nb_char_ligne<al_ustr_size(src))
	{
		al_ustr_assign(aff,src);

		al_ustr_truncate(aff, (lcnt+1)*nb_char_ligne);		
		al_ustr_remove_range(aff, 0,lcnt*nb_char_ligne);
		al_draw_ustr(font,al_map_rgb(0,0,0),float(x),float(y+lcnt*ligne_h),0,aff);
		lcnt++;
	}
	
	al_ustr_free(src);
	al_ustr_free(aff);
*/
	// taille de la boite a message ->
	//y=682 -> jusqu'a 752   ->7 ligne
	message *mess=gestionnaire_message::recup_dernier_message();
	if(mess==NULL)return 0;
	
	
	int ligne_cnt=0;
	int largeur=vue_jeuX;
	int nb_char_pligne=largeur/8;
	
	int message_nbl=0;
	ALLEGRO_USTR *src= al_ustr_new("");
	ALLEGRO_USTR *aff=al_ustr_new("");	
	
	while(1)
	{
		
	 al_ustr_assign_cstr(src,mess->mess);
	 
	 // calcul du nombre de ligne que fait le message.
	 message_nbl=al_ustr_size(src)/nb_char_pligne;
	 if(al_ustr_size(src)%nb_char_pligne!=0)message_nbl++;		
		
	  	
	if(ligne_cnt+message_nbl>7)break;	
		
	ligne_cnt+=message_nbl;
		
	message_nbl=0;
	
		while(message_nbl*nb_char_pligne<al_ustr_size(src))
		{
		al_ustr_assign(aff,src);

		al_ustr_truncate(aff, (message_nbl+1)*nb_char_pligne);		
		al_ustr_remove_range(aff, 0,message_nbl*nb_char_pligne);
		al_draw_ustr(font,mess->col,float(10),float(752-(10*(ligne_cnt))+ message_nbl*10),0,aff);
		message_nbl++;
		}
		
	  mess=mess->precedent;
	  if(mess==NULL)return 0;
	}
	
	
	int ligne_a_virer=ligne_cnt+message_nbl-7;
	ligne_cnt=8;
	message_nbl=ligne_a_virer;
	while(message_nbl*nb_char_pligne<al_ustr_size(src))
	{
		al_ustr_assign(aff,src);

		al_ustr_truncate(aff, (message_nbl+1)*nb_char_pligne);		
		al_ustr_remove_range(aff, 0,message_nbl*nb_char_pligne);
		al_draw_ustr(font,mess->col,float(10),float(752-(10*(ligne_cnt))+ message_nbl*10),0,aff);
		message_nbl++;
	}
	 
	return 1;
}
 
//static int deplacer_camera(int x,int y);
//
// fonction pour déplacer la camera de jeu	
//retourne 1 si la camera est deplacable, sinon 0
int moteur_jeu::deplacer_camera(int x,int y)
{
	
	if(x<0 )cameraX=0;
	else if(x+tile_nbX>=monde[carte_active]->x)cameraX=monde[carte_active]->x-tile_nbX;
	else cameraX=x;
	
	if(y<0) cameraY=0;	
	else if(y+tile_nbY>=monde[carte_active]->y)cameraY=monde[carte_active]->y-tile_nbY;
	else cameraY=y;
	
	return 0;
}

//static int centrer_camera_joueur();
//
//fonction pour centrer la camera sur le joueur.
int moteur_jeu::centrer_camera_joueur()
{
	int x;
	int y;
	
	x=ply1.x-tile_nbX/2;
	y=ply1.y-tile_nbY/2;
	
//	if(x+tile_nbX>monde[carte_active]->x)x=monde[carte_active]->x-tile_nbX;
	if(x<0)x=0;
	
//	if(y+tile_nbY>monde[carte_active]->y)y=monde[carte_active]->y-tile_nbY;
	if(y<0)y=0;	
	
	cameraX=x;
	cameraY=y;
	
	return 0;
}





	
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
int moteur_jeu::creation_contenu()
{
	
	
	chargement_bitmap();
	creation_tile_prefab();
	creer_prefab_objets();
	creer_prefab_acteurs();
	
	return 0;
}

int moteur_jeu::init_alleg_objects(ALLEGRO_DISPLAY *display)
{
	
	
   timer_affichage = al_create_timer(1.0 / float(frequence_affichage));
	al_start_timer(timer_affichage)	;

   queue = al_create_event_queue(); //creation de la queue d'evenement
   al_register_event_source(queue, al_get_display_event_source(display)); // enregistement 
   al_register_event_source(queue, al_get_keyboard_event_source());// des divers fournisseur d evenements
   al_register_event_source(queue, al_get_mouse_event_source());
   al_register_event_source(queue, al_get_timer_event_source(timer_affichage));

	
	return 0;
}

int moteur_jeu::chargement_bitmap()
{
	bitmap_index[BMP_INTERIEUR_MUR]=al_load_bitmap(".\\bitmap\\BMP_INTERIEUR_MUR.bmp");
	bitmap_index[BMP_SOL]=al_load_bitmap(".\\bitmap\\BMP_SOL.bmp");
	bitmap_index[BMP_SOL_BRISE]=al_load_bitmap(".\\bitmap\\BMP_SOL_BRISE.bmp");
	bitmap_index[BMP_SOL_VERRE]=al_load_bitmap(".\\bitmap\\BMP_SOL_VERRE.bmp");
	bitmap_index[BMP_SOL_ACIDE]=al_load_bitmap(".\\bitmap\\BMP_SOL_ACIDE.bmp");
	bitmap_index[BMP_MUR]=al_load_bitmap(".\\bitmap\\BMP_MUR.bmp");
	bitmap_index[BMP_MUR_BRISE]=al_load_bitmap(".\\bitmap\\BMP_MUR_BRISE.bmp");
	bitmap_index[BMP_VITRE]=al_load_bitmap(".\\bitmap\\BMP_VITRE.bmp");
	bitmap_index[BMP_PORTE_FRAGILE]=al_load_bitmap(".\\bitmap\\BMP_PORTE_FRAGILE.bmp");
	bitmap_index[BMP_PORTE_NORMALE]=al_load_bitmap(".\\bitmap\\BMP_PORTE_NORMALE.bmp");
	bitmap_index[BMP_PORTE_BLINDE]=al_load_bitmap(".\\bitmap\\BMP_PORTE_BLINDE.bmp");
	bitmap_index[BMP_BARREAUX]=al_load_bitmap(".\\bitmap\\BMP_BARREAUX.bmp");
	bitmap_index[BMP_ESCALIER_BAS]=al_load_bitmap(".\\bitmap\\BMP_ESCALIER_BAS.bmp");
	bitmap_index[BMP_ESCALIER_HAUT]=al_load_bitmap(".\\bitmap\\BMP_ESCALIER_HAUT.bmp");
	
	bitmap_index[BMP_SERUM_PHYSIO]=al_load_bitmap(".\\bitmap\\BMP_SERUM_PHYSIO.bmp");
	bitmap_index[BMP_BANDAGE]=al_load_bitmap(".\\bitmap\\BMP_BANDAGE.bmp");
	bitmap_index[BMP_MEDIPACK]=al_load_bitmap(".\\bitmap\\BMP_MEDIPACK.bmp");
	bitmap_index[BMP_ADRENALINE]=al_load_bitmap(".\\bitmap\\BMP_ADRENALINE.bmp");
	bitmap_index[BMP_FURIE_PACK]=al_load_bitmap(".\\bitmap\\BMP_FURIE_PACK.bmp");
	bitmap_index[BMP_SCALPEL]=al_load_bitmap(".\\bitmap\\BMP_SCALPEL.bmp");
	bitmap_index[BMP_COUTEAU]=al_load_bitmap(".\\bitmap\\BMP_COUTEAU.bmp");
	bitmap_index[BMP_COUTEAU_CMBT]=al_load_bitmap(".\\bitmap\\BMP_COUTEAU_CMBT.bmp");
	bitmap_index[BMP_PISTOLET]=al_load_bitmap(".\\bitmap\\BMP_PISTOLET.bmp");
	bitmap_index[BMP_FUSIL_POMPE]=al_load_bitmap(".\\bitmap\\BMP_FUSIL_POMPE.bmp");
	bitmap_index[BMP_MITRAILLETTE]=al_load_bitmap(".\\bitmap\\BMP_MITRAILLETTE.bmp");
	
	bitmap_index[BMP_MUNITION_PISTO]=al_load_bitmap(".\\bitmap\\BMP_MUNITION_PISTO.bmp");
	bitmap_index[BMP_MUNITION_FUSIL]=al_load_bitmap(".\\bitmap\\BMP_MUNITION_FUSIL.bmp");
	bitmap_index[BMP_MUNITION_MITRA]=al_load_bitmap(".\\bitmap\\BMP_MUNITION_MITRA.bmp");
	bitmap_index[BMP_CHAUSSURE]=al_load_bitmap(".\\bitmap\\BMP_CHAUSSURE.bmp");
	bitmap_index[BMP_BOTTE_COMBAT]=al_load_bitmap(".\\bitmap\\BMP_BOTTE_COMBAT.bmp");
	bitmap_index[BMP_PANTALON]=al_load_bitmap(".\\bitmap\\BMP_PANTALON.bmp");
	bitmap_index[BMP_BLOUSE]=al_load_bitmap(".\\bitmap\\BMP_BLOUSE.bmp");
	bitmap_index[BMP_GANT]=al_load_bitmap(".\\bitmap\\BMP_GANT.bmp");
	bitmap_index[BMP_PANTALON]=al_load_bitmap(".\\bitmap\\BMP_PANTALON.bmp");
	bitmap_index[BMP_BLOUSON]=al_load_bitmap(".\\bitmap\\BMP_BLOUSON.bmp");
	
	bitmap_index[BMP_GILET_PARE_B]=al_load_bitmap(".\\bitmap\\BMP_GILET_PARE_B.bmp");
	bitmap_index[BMP_IMPLANT_VITESSE]=al_load_bitmap(".\\bitmap\\BMP_IMPLANT_VITESSE.bmp");
	bitmap_index[BMP_IMPLANT_FORCE]=al_load_bitmap(".\\bitmap\\BMP_IMPLANT_FORCE.bmp");
	bitmap_index[BMP_IMPLANT_DXTRT]=al_load_bitmap(".\\bitmap\\BMP_IMPLANT_DXTRT.bmp");
	bitmap_index[BMP_GRENADE]=al_load_bitmap(".\\bitmap\\BMP_GRENADE.bmp");
	bitmap_index[BMP_ANTIDOTE_FINAL]=al_load_bitmap(".\\bitmap\\BMP_ANTIDOTE_FINAL.bmp");
	bitmap_index[BMP_CLE]=al_load_bitmap(".\\bitmap\\BMP_CLE.bmp");
	
	//bitmap pour les acteurs
	bitmap_index[BMP_BUREAU]=al_load_bitmap(".\\bitmap\\BMP_BUREAU.bmp");
	bitmap_index[BMP_ETAGERE]=al_load_bitmap(".\\bitmap\\BMP_ETAGERE.bmp");
	bitmap_index[BMP_TABLE_OPERATION]=al_load_bitmap(".\\bitmap\\BMP_TABLE_OPERATION.bmp");
	bitmap_index[BMP_TABLE]=al_load_bitmap(".\\bitmap\\BMP_TABLE.bmp");
	bitmap_index[BMP_RACK_ARME]=al_load_bitmap(".\\bitmap\\BMP_RACK_ARME.bmp");
	bitmap_index[BMP_ARMOIRE_MEDIC]=al_load_bitmap(".\\bitmap\\BMP_ARMOIRE_MEDIC.bmp");
	bitmap_index[BMP_CONSOLE_INFO]=al_load_bitmap(".\\bitmap\\BMP_CONSOLE_INFO.bmp");
	bitmap_index[BMP_BOUTEILLE_GAZ]=al_load_bitmap(".\\bitmap\\BMP_BOUTEILLE_GAZ.bmp");
	bitmap_index[BMP_CONTENEUR_ACIDE]=al_load_bitmap(".\\bitmap\\BMP_CONTENEUR_ACIDE.bmp");
	bitmap_index[BMP_LAVABO]=al_load_bitmap(".\\bitmap\\BMP_LAVABO.bmp");
	bitmap_index[BMP_TOILETTES]=al_load_bitmap(".\\bitmap\\BMP_TOILETTES.bmp");
	bitmap_index[BMP_LIT]=al_load_bitmap(".\\bitmap\\BMP_LIT.bmp");
	
	//
	bitmap_index[BMP_SCIENTIFIQUE]=al_load_bitmap(".\\bitmap\\BMP_SCIENTIFIQUE.bmp");
	bitmap_index[BMP_INFIRMIER]=al_load_bitmap(".\\bitmap\\BMP_INFIRMIER.bmp");
	bitmap_index[BMP_CHIMPANZE]=al_load_bitmap(".\\bitmap\\BMP_CHIMPANZE.bmp");
	bitmap_index[BMP_GORILLE]=al_load_bitmap(".\\bitmap\\BMP_GORILLE.bmp");
	bitmap_index[BMP_SINGE_MUTANT]=al_load_bitmap(".\\bitmap\\BMP_SINGE_MUTANT.bmp");
	bitmap_index[BMP_CHIEN]=al_load_bitmap(".\\bitmap\\BMP_CHIEN.bmp");
	bitmap_index[BMP_CHIEN_MUTANT]=al_load_bitmap(".\\bitmap\\BMP_CHIEN_MUTANT.bmp");
	bitmap_index[BMP_AGENT_SECU]=al_load_bitmap(".\\bitmap\\BMP_AGENT_SECU.bmp");
	bitmap_index[BMP_AGENT_SECU_ARME]=al_load_bitmap(".\\bitmap\\BMP_AGENT_SECU_ARME.bmp");
	bitmap_index[BMP_AGENT_SECU_ARME_L]=al_load_bitmap(".\\bitmap\\BMP_AGENT_SECU_ARME_L.bmp");
	
	bitmap_index[BMP_SOLDAT]=al_load_bitmap(".\\bitmap\\BMP_SOLDAT.bmp");
	
	bitmap_index[BMP_H_COBAYE]=al_load_bitmap(".\\bitmap\\BMP_H_COBAYE.bmp");
	bitmap_index[BMP_H_COBAYE_FOU]=al_load_bitmap(".\\bitmap\\BMP_H_COBAYE_FOU.bmp");
	bitmap_index[BMP_H_COBAYE_MUTANT]=al_load_bitmap(".\\bitmap\\BMP_H_COBAYE_MUTANT.bmp");
	bitmap_index[BMP_H_COBAYE_TANK]=al_load_bitmap(".\\bitmap\\BMP_H_COBAYE_TANK.bmp");
	bitmap_index[BMP_H_COBAYE_MUT_COUREUR]=al_load_bitmap(".\\bitmap\\BMP_H_COBAYE_MUT_COUREUR.bmp");
	
	bitmap_index[BMP_H_CADAVRE]=al_load_bitmap(".\\bitmap\\BMP_H_CADAVRE.bmp");
	
	bitmap_index[BMP_JOUEUR]=al_load_bitmap(".\\bitmap\\BMP_JOUEUR.bmp");
	
	bitmap_index[BMP_INVENTAIRE_MENU]=al_load_bitmap(".\\bitmap\\BMP_INVENTAIRE_MENU.bmp");
	bitmap_index[BMP_FLECHE_MENU]=al_load_bitmap(".\\bitmap\\BMP_FLECHE_MENU.bmp");
	bitmap_index[BMP_PRENDRE_MENU]=al_load_bitmap(".\\bitmap\\BMP_PRENDRE_MENU.bmp");
	
	// bitmap des objets brises
	bitmap_index[BMP_CONTENEUR_ACIDE_BRISE]=al_load_bitmap(".\\bitmap\\BMP_CONTENEUR_ACIDE_BRISE.bmp");
	bitmap_index[BMP_BOUTEILLE_GAZ_BRISE]=al_load_bitmap(".\\bitmap\\BMP_BOUTEILLE_GAZ_BRISE.bmp");


	// bitmap pour l'interface
	bitmap_index[BMP_INTERFACE_FOND]=al_load_bitmap(".\\bitmap\\BMP_INTERFACE_FOND.bmp");
	bitmap_index[BMP_INTERFACE_BFURIE]=al_load_bitmap(".\\bitmap\\BMP_INTERFACE_BFURIE.bmp");
	bitmap_index[BMP_INTERFACE_BHEMORRAGIE]=al_load_bitmap(".\\bitmap\\BMP_INTERFACE_BHEMORRAGIE.bmp");
	bitmap_index[BMP_INTERFACE_BCLE]=al_load_bitmap(".\\bitmap\\BMP_INTERFACE_BCLE.bmp");
	
	//bitmap pour porte ouverte
	bitmap_index[BMP_PORTE_FRAGILE_OUVERT]=al_load_bitmap(".\\bitmap\\BMP_PORTE_FRAGILE_OUVERT.bmp");
	bitmap_index[BMP_PORTE_NORMALE_OUVERT]=al_load_bitmap(".\\bitmap\\BMP_PORTE_NORMALE_OUVERT.bmp");
	bitmap_index[BMP_PORTE_BLINDE_OUVERT]=al_load_bitmap(".\\bitmap\\BMP_PORTE_BLINDE_OUVERT.bmp");

//	 al_convert_mask_to_alpha(bitmap_index[BMP_FLECHE_MENU], al_map_rgb(255,0,255));
	
	//test de chargement
	for(int i=0;i<MAX_BMP;i++)
	{
	if(bitmap_index[i]==NULL)return i;
	 al_convert_mask_to_alpha(bitmap_index[i], al_map_rgb(255,0,255));
	}
return -1;
}



int moteur_jeu::supprimer_bitmap()
{
	for(int i=0;i<MAX_BMP;i++)
	if(bitmap_index[i]!=NULL)al_destroy_bitmap(bitmap_index[i]);
	
	return 0;
}	



// *****************************************************
// ************* Gestion de la CONSOLE de jeu **********
// *****************************************************
	
// Fonction pour ajouter un message dans la console
// et updater son affichage.
int moteur_jeu::ajouter_mess_console(const char *message, ALLEGRO_COLOR COL)
{
	
	gestionnaire_message::ajout_message( message,COL);
	
	al_draw_filled_rectangle(0.0,float(682),float(vue_jeuX+8)+0.5,float(ecranY),al_map_rgb(0,0,0));
   
	 affiche_boite_message();
}	



//Fonction pour vider les messages de la console
// de la mémoire.
static int vider_console();

	
// *****************************************************
// ************* Gestion de la boucle de jeu ***********
// *****************************************************

//-------Gestion des actions
int moteur_jeu::jeu()
{
	int res=0;
	while(sortie_boucle_jeu==false)
	{
		if(entree_nouv_carte)
		{	
			printf("entree premier remplissage\n");
			premier_remplissage_action();
			printf("premier remplissage\n");
		}
		else
		{
			printf("remplacement action finie\n");
			remplacement_action_finies();	
		}
		
		///////////////////////////
		printf("ajout tics");
		res=ajout_tic();
		if(res==2)
		{
		 	mort_joueur=true;
			sortie_boucle_jeu=true;	
		}
		///////////////////////////
		
		///////////////////////////
		printf("recherche actions finies\n");
		recherche_actions_finies();
		///////////////////////////
		
		
		printf("tri actions finies\n");
		calcul_pa_et_tri_action_finies();
		
		printf("execution actions finies\n");
		res=execution_action_finies();
		if(res==1) //-> SI Execution action finies retourne 1 cela correspond a un changement de carte.
		{
			//GESTION DU CHANGEMENT DE CARTE
			vider_actions();
			nombre_action_finies=0;
			
		}
		if(res==2)
		{
			mort_joueur=true;
			sortie_boucle_jeu=true;
			
		}
		
			
		
	}
	
	return 0;
}

int moteur_jeu::vider_actions()
{
	for(int i=0;i<NB_MAX_ACTION;i++)
	vider_action(&action_tab[i]);
	
	
	return 0;
}

        // int ajout_tic();
        //
        // Fonction pour ajouter un tic et incrémenter les points d'action de chacune des
		// actions actives. 
		// Retourne 0 si le joueur ne meurt pas.
		// retourne 1 si le joueur meurt.
		
int moteur_jeu::ajout_tic()
{
	// ************************
	// ************* MISE A JOUR DES JAUGES DU JOUEUR
	// ***********************
	
	maj_furie(&ply1);

	if(maj_adrenaline(&ply1)==0)return 2;

    if(maj_hemorragie(&ply1)==0)return 2;
    
    if(maj_degat_acide(&ply1,monde[carte_active])==0)return 2;
 
//A FAIRE Gestion de la mort

	// ************************
	// ************* MISE A JOUR DES JAUGES DES ACTEURS
	// ************************
	
	for(register int i=0;i<NB_MAX_ACTEUR;i++)
	{
		
		if(monde[carte_active]->acteur_tab[i]!=NULL &&
		   monde[carte_active]->acteur_tab[i]->acteur_type>=ACTEUR_SCIENTIFIQUE_BASE &&
		   est_vivant(monde[carte_active]->acteur_tab[i]))
		   {
		   	maj_degat_acide(monde[carte_active]->acteur_tab[i],monde[carte_active]);
		   	maj_hemorragie(monde[carte_active]->acteur_tab[i]);
		   }
		
		
		
	}
	

  // **************************
  // **************** 
  // ***************************
	for(register int i=0;i<NB_MAX_ACTION;i++)
	{
		if(action_tab[i].active)
		{
			
			switch(action_tab[i].action_type)
			{
				
				case ACTION_ATTENTE:
				ajout_tic_action_attente(&action_tab[i]);
				break;
				//	
				case ACTION_MARCHE:
				ajout_tic_action_deplacement(&action_tab[i]);
				break;
				//
				case ACTION_PRISE_OBJET:
				ajout_tic_action_prise_objet(&action_tab[i]);
				break;
				//
				case ACTION_COMBAT_CAC:
				ajout_tic_action_cac(&action_tab[i]);
				break;
				//	
				case ACTION_COMBAT_LANCE:
				ajout_tic_action_clancer(&action_tab[i]);	
				break;
				//	
				case ACTION_COMBAT_AFEU_VISEE:
				ajout_tic_action_cafeul(&action_tab[i]);
				break;
				//	
				case ACTION_COMBAT_AFEU_RAPID:
				ajout_tic_action_cafeur(&action_tab[i]);
				break;
				//	
				case ACTION_RECHARGEMENT:	
				ajout_tic_action_rechargement(&action_tab[i]);
				break;
				//	
				case ACTION_PRISE_MEDIC:
				ajout_tic_action_utilisation_medic(&action_tab[i]);
				break;
				//		
				case ACTION_HABILLEMENT:
				ajout_tic_action_habillement(&action_tab[i]);
				break;
				//		
				case ACTION_EQUIP_MAIN:
				ajout_tic_action_equipement_main(&action_tab[i]);
				break;
				//		
				case ACTION_MODIF_CORPO:
				ajout_tic_action_modif_corpo(&action_tab[i]);
				break;
				//		
				case ACTION_LACHE_OBJET:
				ajout_tic_action_lacher_objet(&action_tab[i]);
				break;
				//		
				case ACTION_OUVRIR_FERMER_PORTE:
				ajout_tic_action_ouvrir_fermer_porte(&action_tab[i]);
				break;
				//		
			}
			

			
		}
		
	}
	
	return 0;
}
		
//int recherche_actions_finies();
//
// Fonction pour rechercher les action finies et les stocker
// dans actions_finies
int moteur_jeu::recherche_actions_finies()
{
	int cnt=0;
	for(register int i=0;i<NB_MAX_ACTION;i++)
	{
		
		if(action_terminee(&action_tab[i]))
		{
			
			actions_finies[cnt]=i;
			cnt++;
		}
		
	}
	
	nombre_action_finies=cnt;
	
	return 0;
}
		
int moteur_jeu::calcul_pa_et_tri_action_finies()
{
	int compteur;
	//calcul des points d actions restants
	for(int i=0;i<nombre_action_finies;i++)
	{
		compteur=action_d[action_tab[actions_finies[i]].action_type];
		
		//decompte des points bonus
		compteur-=action_tab[actions_finies[i]].point_bonus;
		action_tab[actions_finies[i]].point_bonus=0;
		
		//calcul des points restant
		action_tab[actions_finies[i]].point_action-=compteur;
	}
	
	
	
	
	
	/*****************************************************************/
	/******************** TRI QSORT DES ACTIONS***********************/
	
	
	//Fonction de tri des actions
	int_indquicksort(action_tab,actions_finies, 0, nombre_action_finies-1,false);

	
	
	
	
	
	return 0;
}
		
		
int moteur_jeu::execution_action_finies()
{
int res=0;	
	for(int i=0;i<nombre_action_finies;i++)
	{
		// EXECUTION DES ACTIONS TRIES PAR POINT D ACTION MAX
		switch(action_tab[actions_finies[i]].action_type)
		{
				
				case ACTION_ATTENTE:
				execute_action_attente(&action_tab[actions_finies[i]]);
				break;
				//	
				case ACTION_MARCHE:
				res=execute_action_deplacement(&action_tab[actions_finies[i]]); // SI L'action deplacement retourne 1-> Changement de carte// On arrete tout les actions en cours
				if(res==1)return 1;
				if(res==2)return 2;
				break;
				//
				case ACTION_PRISE_OBJET:
				execute_action_prise_objet(&action_tab[actions_finies[i]]);
				break;
				//
				case ACTION_COMBAT_CAC:
				res=execute_action_cac(&action_tab[actions_finies[i]]);
				if(res==2)return 2;
				break;
				//	
				case ACTION_COMBAT_LANCE:
				execute_action_clancer(&action_tab[actions_finies[i]]);	
				break;
				//	
				case ACTION_COMBAT_AFEU_VISEE:
				res=execute_action_cafeul(&action_tab[actions_finies[i]]);
				if(res==2)return 2;
				break;
				//	
				case ACTION_COMBAT_AFEU_RAPID:
				res=execute_action_cafeur(&action_tab[actions_finies[i]]);
				break;
				//	
				case ACTION_RECHARGEMENT:	
				execute_action_rechargement(&action_tab[actions_finies[i]]);
				break;
				//	
				case ACTION_PRISE_MEDIC:
				execute_action_utilisation_medic(&action_tab[actions_finies[i]]);
				break;
				//		
				case ACTION_HABILLEMENT:
				execute_action_habillement(&action_tab[actions_finies[i]]);
				break;
				//		
				case ACTION_EQUIP_MAIN:
				execute_action_equipement_main(&action_tab[actions_finies[i]]);
				break;
				//		
				case ACTION_MODIF_CORPO:
				execute_action_modif_corpo(&action_tab[actions_finies[i]]);
				break;
				//		
				case ACTION_LACHE_OBJET:
				execute_action_lacher_objet(&action_tab[actions_finies[i]]);
				break;
				//		
				case ACTION_OUVRIR_FERMER_PORTE:
				execute_action_ouvrir_fermer_porte(&action_tab[actions_finies[i]]);
				break;
			
			
		}
		
		
		
	}
	
	return 0;
}
		
int moteur_jeu::remplacement_action_finies()
{
	
	for(register int i=0;i<nombre_action_finies;i++)
	{
	
	
		action_tab[actions_finies[i]].active=false;	
	    transfert_pointact_vers_emetteur(&action_tab[actions_finies[i]]);
	
	
		// REMPLACEMENT DES ACTIONS DU JOUEUR
		if(action_tab[actions_finies[i]].initj!=NULL)
		{
			if(action_tab[actions_finies[i]].initj->vie>0)
			{
				gestion_action_joueur(queue);
			}
			else
			return 1;
			
		}
		else if(action_tab[actions_finies[i]].initc!=NULL)
		{
			if(est_vivant(action_tab[actions_finies[i]].initc))
			{
				// FONCTION D EMISSION D ACTION DES PNJ A PLACER ICI
			}
			
		}
	}
		
	nombre_action_finies=0;	
	
	return 0;
}

int moteur_jeu::premier_remplissage_action()
{
	
	gestion_action_joueur(queue);
	
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(monde[carte_active]->acteur_tab[i]!=NULL)
		{
			
			if(monde[carte_active]->acteur_tab[i]->acteur_type>=ACTEUR_SCIENTIFIQUE_BASE &&
			  monde[carte_active]->acteur_tab[i]->acteur_type<ACTEUR_CADAVRE	)
			{
					if(est_vivant(monde[carte_active]->acteur_tab[i]))
					{
						
						//FONCTION D EMISSION D ACTION DES PNJ A PLACER ICI
					}		  	
			}
		}
	}
	entree_nouv_carte=false;
	return 0;
}

//-------FONCTION D EXECUTION DES ACTIONS

int moteur_jeu::execute_action_attente(action *act)
{
	
	
	return 0;
}
//////////////
int moteur_jeu::execute_action_deplacement(action *act)
{
  int deplac;	
	if(act->initj!=NULL && act->initj->vie>0)
	{
		// CHANGEMENT DE CARTE -> JOUEUR AU DESSUS D un ESCALIER
		if(act->bool1==true)
		{
			if(monde[carte_active]->donnee_carte[act->initj->y][act->initj->x].type==TILE_ESCALIER_BAS)
			{
			carte_active++;
			entree_nouv_carte=true;
			if(monde[carte_active]==NULL)
			{
					ajout_score_changement_niveau(act->initj,carte_active);
			}
			//Gestion creation nouvelle carte
			// A FAIRE
			return 1;
			}
			else
			{
			carte_active--;
			entree_nouv_carte=true;
			return 1;
			}
			
		}
		
		deplac=validite_deplacement(monde[carte_active],act->initj->x,act->initj->y, act->x,act->y);
		 
		if(deplac==0)
		{
			act->initj->x+=act->x;
			act->initj->y+=act->y;
			ajout_score_deplacement(act->initj);
		//GESTION DE LA CAMERA	
			//deplacement de la camera pour suivre le joueur
			if(act->initj->x-1<cameraX)cameraX=act->initj->x-2;
			if(act->initj->y-1<cameraY)cameraY=act->initj->y-2;
			if(act->initj->x+1>=cameraX+tile_nbX)cameraX+=2;
			if(act->initj->y+1>=cameraY+tile_nbY)cameraY+=2;
			
			//test pour voir si la camera sort pas des clous;
			if(cameraX<=0)cameraX=0;
			if(cameraY<=0)cameraY=0;
			
			/////////////////////////////////	
			if(ajout_degat_verre(act->initj,monde[carte_active])==0) // degat du au verre sous les pieds
			{
				
				return 2;
			/*************** GESTION DE  LA MORT DU PERSO PRINCIPAL***********
			******************************************************************/
			}
			
			vider_champ_vision_carte(monde[carte_active]);
			calcul_champ_vision();
			
		}
		else if(deplac==4)//SI UN ACTEUR EST ARRIVE AVANT SUR LA CASE
		{
			
		}
		
		
	}
	if(act->initc!=NULL && est_vivant(act->initc))
	{
		deplac=validite_deplacement(monde[carte_active],act->initc->x,act->initc->y, act->x,act->y);
		
		// SI LE JOUEUR EST DEJA SUR LA CASE
		if(act->initc->x+act->x==ply1.x && act->initc->y+act->y==ply1.y)
		{
			
		} 
		else if(deplac==0)// SI LA CASE EST VIDE
		{
			act->initc->x+=act->x;
			act->initc->y+=act->y;
			
		}
		
		
	}
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_cac(action *act)
{
	char message[1024];
	int tiragedex1=0;
	int tiragedex2=0;
	int critique=0;
	int coup_critique=0; //coup critique 1 coup normal 0, foirage critique -1
	int degat=0;
	int protection;
	bool mort=false;
	int vdeplacement;
	acteur *mobilier;
	// ATTAQUE DU JOUEUR
	if(act->initj!=NULL && act->initj->vie>0)
	{
		if(act->ciblec!=NULL)// Cible du Joueur déjà définie
		{
				if(est_vivant(act->ciblec))// SI la cible est vivante
				{
				
					if(act->ciblec->x==act->initj->x+act->x &&   //La cible n'a pas bougé depuis le choix de l'action -> attaque possible
					   act->ciblec->y==act->initj->y+act->y)
					{
						
						// COMMMMMMMMMMMMMMMMMMMBBBBBBBATTTTT
						
						if(act->initj->combat_cac)	// BONUS de combat cac	
						 tiragedex1+=1;
						
						tiragedex1+=genrand_int32()%(act->initj->dexterite+1);
						tiragedex2+=genrand_int32()%(act->ciblec->dxtrt+1);
						
						//Si le tirage de dexterite du joueur est superieur a celui du monstre -> touché
						if(tiragedex1>=tiragedex2)
						{
							
								// Tentative de tirage de coup critique
								
								critique=genrand_int32()%1001; //tirage proba coup critique							
								if(act->initj->maudit)
								{
								  if(critique >=920)coup_critique=-1;
								  if(critique<=act->initj->coup_critique*5)coup_critique=1;
								  	
								}
								else
								{	
									// ECHEC CRITIQUE -> FORMULE  1000-100/dexterite au pire 10% de chance de foirer. Au mieux 0.5%
									if(critique>= 1000-100/act->initj->dexterite)coup_critique=-1;
									if(critique<=act->initj->coup_critique)coup_critique=1;
								}
								//////////////////////////////////////
								
								
								//calcul des dégats ///////////////////////
								/////////////////////////////////////
								
								if(act->initj->equipement[EQUIPMNT_MAIN_D]==NULL)
								{
									//degat = degat minimum + tirage nb_aletaoire sur moitie de force
									degat=1+genrand_int32()%(act->initj->force/2+1);
								}
								else if(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_PISTOLET ||
										act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_FUSIL_POMPE ||
										act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
								{
									// Avec arme à feu bonus de frappe de  rand()%3
									degat=1+genrand_int32()%(2+1)+genrand_int32()%(act->initj->force/2+1);
								}
								else 
								{
									degat=1+genrand_int32()%(act->initj->equipement[EQUIPMNT_MAIN_D]->degat+1)+genrand_int32()%(act->initj->force/2+1);
									
								}
								
								// Prise en compte du bonus/malus cac
								if(act->initj->combat_cac)degat=degat+genrand_int32()%(degat/2+1);
																
								////////////////////////////////////
								//////////////////////////////////////////
								switch(coup_critique)
								{
								case 1:
									//Message coup_critique, vous passez au travers des defenses de l'ennemi.

									// diminution de la vie du PNJ
									act->ciblec->vie-=degat*4/3;
									
									degradation_equip_arme(act->initj);
									
									// CALCUL DE L AJOUT D ADRENALINE
									if(act->ciblec->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,degat*4/3,mort);
									
									if(mort) sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi, le tuant sur le coup! Dgt:%d",degat*4/3) ;
									else sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi. Dgt:%d",degat*4/3);
									ajouter_mess_console(message,al_map_rgb(255,0,0));
									
									break;
								case 0:
									
									
									protection=calcul_protec(act->ciblec);
									//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
									act->ciblec->vie-=(degat*(100-protection))/100;
									
									//degradation des equipements de protection/
									degradation_equip_protec(act->ciblec);
									
									degradation_equip_arme(act->initj);// Degradation de l'arme du donneur de coup
									
									// CALCUL DE L AJOUT D ADRENALINE
									if(act->ciblec->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,(degat*(100-protection))/100,mort);
									 if(mort) sprintf(message,"Vous frappez l'ennemi, votre coup lui ecrase la tete. Avec la puree qu'il a entre les oreilles, les seuls mouvements dont il est capable sont nerveux Dgt:%d",(degat*(100-protection))/100) ;
									else sprintf(message,"Vous tapez de toutes vos forces sur l'ennemi. Dgt:%d",degat*4/3);
									ajouter_mess_console(message,al_map_rgb(255,0,0));
									break;
								case -1:
									//Message ratage critique, vous vous blessez en tentant de donner le coup
									degat=genrand_int32()%(degat/2+1);
									act->initj->vie-=degat;
									faire_saigner(act->initj);
									degradation_equip_arme(act->initj);//degradation de l'arme
									
									// AJOUT DE L ADRENALINE
									 ajout_adrenaline(act->initj,degat,0,mort);
									if(act->initj->vie<=0)return 2;
									
									break;
								}
								
								
						}
						else
						{
							//message: vous ratez votre coup
							ajouter_mess_console("Vous ratez votre coup",al_map_rgb(0,255,0));
						}
						
					}
					else
					{
						//Message: vous etes moins rapide que votre cible.
						//			elle a déjà filé lorsque vous frappez
						ajouter_mess_console("Vous etes beaucoup moins rapide que votre cible; elle avait deja file deuis longtemps alors que vous asseniez votre coup",al_map_rgb(255,255,255));
						
					}
				
				}
				else
				{
					//Message : la cible est deja morte, 
					//            vous frappez son cadavre
					ajouter_mess_console("votre cible est deja morte! Qu'importe vous lui donner un dernier coup pour la route!",al_map_rgb(255,0,0));
				}
		}
		else // Sinon cibles diverses mur portes etc...
		{
				//SI LE JOUEUR NE FRAPPE PAS UN EMPLACEMENT CONTENANT DE L IMMOBILIER
			    vdeplacement=validite_deplacement(monde[carte_active],act->initj->x,act->initj->y, act->x,act->y);
			    // Fonction pour tester la validité d'un déplacement
				// RETOURNE 0 SI PAS DE  OBSTACLE
				// RETOURNE 1 SI OBSTACLE TILE CASSABLE
				// RETOURNE 2 SI OBSTACLE TILE INCASSABLE
				// RETOURNE 3 SI OBSTACLE ACTEUR MOBILIER
				// RETOURNE 4 SI OBSTACLE ACTEUR PERSONNAGE 
			    
				switch(vdeplacement)
				{
					case 1: //Tile cassable
							    switch(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].destructible_id)
							    {
							    	case DESTRUC_FACILE:
							    		
							    		if(act->initj->equipement[EQUIPMNT_MAIN_D]==NULL)
							    		{
							    		   if(act->initj->force<=9)
										   {
										   	 ajouter_mess_console("Vous frappez la porte en vain. Vous etes trop faible pour briser cet obstacla a mains nues",al_map_rgb(255,255,255));
									
										   }
										   else
										   {
										   	
										   	 if(genrand_int32()%101+act->initj->force>65)
										   	 {
										   	 	//message: vous brisez l obstacle
										   	 	
										   	 	//si le tile est une porte, suppression de la porte
												if(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].type==TILE_PORTE_FRAGILE)
										   	 	{
										   	 		ajouter_mess_console("La porte se brise sous vos coups.",al_map_rgb(255,255,0));
										   	 		placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL);
										   	 		vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
										   	 	}
										   	 	else //sinon suppression de la vitre et mise en place de morceau de verre par terre
										   	 	{
										   	 		 ajouter_mess_console("La vitre explose en de minuscules morceaux qui se rependent sur le carrelage envirronant",al_map_rgb(255,255,0));
										   	 			placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL_VERRE);	
										   	 			vider_champ_vision_carte(monde[carte_active]);
														calcul_champ_vision();
												}
										   	 }
										   	 else
										   	 {
										   	 	//message: vous n arrivez as a casser l obstacle
										   	 		ajouter_mess_console("Malgre vos effort, l'obstacle ne cede pas.",al_map_rgb(255,255,0));
										   	 }
										   	
										   }	
										
										}
							    		else //si le perso a un equipement en main. 
							    		{
							    			
							    		    switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
											{
												case OBJ_PISTOLET:
												case OBJ_FUSIL_POMPE:
												case OBJ_MITRAILLETTE:
													
													degradation_equip_arme(act->initj);//degradation de l'arme
													 if(genrand_int32()%101+act->initj->force*2>45)
												   	 {
												   	 	//message: vous brisez l obstacle
												   	 
														//si le tile est une porte, suppression de la porte
														if(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].type==TILE_PORTE_FRAGILE)
												   	 	{
												   	 		ajouter_mess_console("La porte se brise sous vos coups.",al_map_rgb(255,255,0));
												   	 		placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL);
												   	 		vider_champ_vision_carte(monde[carte_active]);
															calcul_champ_vision();
												   	 		
												   	 	}
												   	 	else //sinon suppression de la vitre et mise en place de morceau de verre par terre
												   	 	{
												   	 		 ajouter_mess_console("La crosse de votre arme passe au travers de la vitre et la fait exploser en de minuscules morceaux.",al_map_rgb(255,255,0));
												   	 			placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL_VERRE);	
												   	 			vider_champ_vision_carte(monde[carte_active]);
																calcul_champ_vision();
														}
												   	 }
												   	 else
												   	 {
												   	 	 ajouter_mess_console("L'obstacle etait trop solide pour ceder cette fois-ci",al_map_rgb(255,255,0));
												   	 		
												   	 	//message: vous n arrivez as a casser l obstacle
												   	 }
			
												break;
												
												case OBJ_SCALPEL:
												case OBJ_COUTEAU:
												case OBJ_COUTEAU_CMBT:	
													
													degradation_equip_arme(act->initj);//degradation de l'arme
													 if(genrand_int32()%101+act->initj->force*2>60)
												   	 {
												   	 	//message: vous brisez l obstacle
												   	 	
												   	 	//si le tile est une porte, suppression de la porte
														if(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].type==TILE_PORTE_FRAGILE)
												   	 	{
												   	 		ajouter_mess_console("Vous faites exploser le bois autour de la porte a l'aide de votre lame.",al_map_rgb(255,255,255));
		
												   	 		placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL);
												   	 		vider_champ_vision_carte(monde[carte_active]);
															calcul_champ_vision();
												   	 	}
												   	 	else //sinon suppression de la vitre et mise en place de morceau de verre par terre
												   	 	{
											   	 			ajouter_mess_console("La lame traverse la vitre, elle s'effondre en des centaines de morceaux coupants.",al_map_rgb(255,255,255));


											   	 			placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL_VERRE);	
											   	 			vider_champ_vision_carte(monde[carte_active]);
															calcul_champ_vision();
														}
												   	 }
												   	 else
												   	 {
												   	 	//message: vous n arrivez as a casser l obstacle
												   	 	ajouter_mess_console("Vous n'arrivez pas a brisez l'obstacle.",al_map_rgb(255,255,255));

												   	 }
			
												break;
										        default:
												
													if(act->initj->force<=9)
												   {
												   	 //message: vous etes trop faible pour tenter de briser cet obstacle
												   }
												   else
												   {
												   	
												   	 if(genrand_int32()%101+act->initj->force>65)
												   	 {
												   	 	//message: vous brisez l obstacle
												   	 	
												   	 	//si le tile est une porte, suppression de la porte
														if(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].type==TILE_PORTE_FRAGILE)
												   	 	{
												   	 		
												   	 		placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL);
												   	 		vider_champ_vision_carte(monde[carte_active]);
															calcul_champ_vision();
												   	 	}
												   	 	else //sinon suppression de la vitre et mise en place de morceau de verre par terre
												   	 	{
												   	 			placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL_VERRE);	
																vider_champ_vision_carte(monde[carte_active]);
																calcul_champ_vision();
												   	 	}
												   	 }
												   	 else
												   	 {
												   	 	//message: vous n arrivez as a casser l obstacle
												   	 	ajouter_mess_console("Vous n'arrivez pas a briser l'obstacle.",al_map_rgb(255,255,255));
												   	 }
												   	
												   }
														
											}	
							    			
							    		}
							    		
							    		break;
							    		
							    	case DESTRUC_MOYEN:
							    		
							    		if(act->initj->equipement[EQUIPMNT_MAIN_D]!=NULL)
							    		{
							    			if(objet_est_arme(act->initj->equipement[EQUIPMNT_MAIN_D]))
							    			{
							    				degradation_equip_arme(act->initj);//degradation de l'arme
							    				 if(genrand_int32()%101+act->initj->force>85)
												{
												   	placer_tile(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x],TILE_SOL);
													ajouter_mess_console("Vous brisez l'obstacle.",al_map_rgb(255,255,255));
							    			
													vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
												}
												else
												{
													//message vous frapper l'obstacle, mais impossible de le briser
													ajouter_mess_console("Vous frappez l'obstacle de toutes vos forces, en vain!",al_map_rgb(255,255,255));
							    			
												}
							    				
							    			}
							    		}
							    		else
							    		{
							    			ajouter_mess_console("Impossible de briser cela a main nue!",al_map_rgb(255,255,255));
							    			//message: impossible de briser cela a main nue
							    		}
							    		
							    	break;	
							    	case DESTRUC_DUR:
							    	ajouter_mess_console("Vous n'arrivez pas a brisez cet obstacle.",al_map_rgb(255,255,255));
							    		//message Vous n arrivez pas a briser cet obstacle
							    	break;
							    }
					break;
					///////////////////////////////////////////////
					case 2: //tile incassable
					// message: en fonction du tile
							  	switch(monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].type)
							  	{
							  	 case TILE_MUR:
								 case TILE_MUR_BRISE:
								 ajouter_mess_console("Vous frappez le mur, sans resultats ",al_map_rgb(255,255,255));
									
								 break;
								 //
								 case TILE_PORTE_BLINDE:
								 break;
								 //
								 case TILE_BARREAUX:
								 
								 break;
								 //
								   	
							  	}
					break;	
					///////////////////////////////////////	  	
					case 3: //mobilier
					//message: vous frappez le mobilier de toute vos forces -> A VOIR POUR BOUTEILLE GAZ ET CONTENEUR ACIDE
					   
					   mobilier=obtenir_mobilier(monde[carte_active],act->initj->x+act->x, act->initj->y+act->y);

					   if(mobilier->acteur_type==ACTEUR_BOUTEILLE_GAZ || mobilier->acteur_type==ACTEUR_CONTENEUR_ACIDE)
					   {

								   if(act->initj->equipement[EQUIPMNT_MAIN_D]==NULL)
								{
									//degat = degat minimum + tirage nb_aletaoire sur moitie de force
									degat=1+genrand_int32()%(act->initj->force/2+1);
								}
								else if(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_PISTOLET ||
										act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_FUSIL_POMPE ||
										act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
								{
									// Avec arme à feu bonus de frappe de  rand()%3
									degat=1+genrand_int32()%(2+1)+genrand_int32()%(act->initj->force/2+1);
								}
								else 
								{
									degat=1+genrand_int32()%(act->initj->equipement[EQUIPMNT_MAIN_D]->degat+1)+genrand_int32()%(act->initj->force/2+1);
									
								}
								
								// Prise en compte du bonus/malus cac
								if(act->initj->combat_cac)degat=degat+genrand_int32()%(degat/2+1);
								
								mobilier->vie-=degat;
								degradation_equip_arme(act->initj);//degradation de l'arme
												printf("bouteille gaz et co %d\n",mobilier->vie);								
								if(mobilier->vie<=0) // Le conteneur ou la bouteille pète
								{
									
									  if(mobilier->acteur_type==ACTEUR_BOUTEILLE_GAZ)
									  {
									  	
										// Message l'acide vous éclabousse et endommage votre materiel
									  	if(detruire_bouteille_gaz(monde[carte_active],mobilier,act->initj)==1)return 2;
										vider_champ_vision_carte(monde[carte_active]);
										calcul_champ_vision();
									  	   	
									  }
									  else if(mobilier->acteur_type==ACTEUR_CONTENEUR_ACIDE)
									  {
									  	// Message l'acide vous éclabousse et endommage votre materiel
									  	detruire_conteneur_acide(monde[carte_active],mobilier);
										vider_champ_vision_carte(monde[carte_active]);
										calcul_champ_vision();
									  	
									  }
									
								}
								
					   }
					  
					
					break;
					default:	
					break;
				} 
							
		}
		
		
	}
	
	
	//ATTAQUE DES PNJ
	if(act->initc!=NULL && est_vivant(act->initc))
	{
		
		
	}
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_lacher_objet(action *act)
{
	
	if(act->initj!=NULL) // si c'est le joueur qui lache l'objet:
	{
	
	
		if(act->bool1)
		{
				act->initj->sac_contenu[act->nb1]->x=act->x;
				act->initj->sac_contenu[act->nb1]->y=act->y;
				
				ajouter_objet(monde[carte_active],act->initj->sac_contenu[act->nb1]);
				act->initj->sac_contenu[act->nb1]=NULL;
		}
		else
		{
				act->initj->equipement[act->nb1]->x=act->x;
				act->initj->equipement[act->nb1]->y=act->y;
				
			   ajouter_objet(monde[carte_active],act->initj->equipement[act->nb1]);
			   act->initj->equipement[act->nb1]=NULL;
			   
		}	
	
	}
	else if(act->initc)
	{
				act->initc->equipement[act->nb1]->x=act->x;
				act->initc->equipement[act->nb1]->y=act->y;
		ajouter_objet(monde[carte_active],act->initc->equipement[act->nb1]);
		act->initc->equipement[act->nb1]=NULL;
		
	}
		
	return 0;
}
///////////////
int moteur_jeu::execute_action_prise_objet(action *act)
{
	/*
	
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

	
	*/
	int emplacement;
	bool sac;
	if(act->initj!=NULL) // si 'est le joueur l'initiateur
	{
			emplacement=stockage_libre(act->initj,&sac);
		
		if(act->ciblec==NULL)// si pas de cible, l'objet se trouve par terre
		{
			//GESTION DES CLE
			if(monde[carte_active]->objet_tab[act->nb1]->objet_type==OBJ_CLE)
			{
				monde[carte_active]->objet_tab[act->nb1]=NULL;
				monde[carte_active]->cle_acquise=true;
				return 0;
			}
			/////////////
			if(sac)
			{
				
				act->initj->sac_contenu[emplacement]=monde[carte_active]->objet_tab[act->nb1];
				monde[carte_active]->objet_tab[act->nb1]=NULL;
			}
			else
			{
				act->initj->equipement[emplacement]=monde[carte_active]->objet_tab[act->nb1];
				monde[carte_active]->objet_tab[act->nb1]=NULL;
			}
			
		}
		else
		{
			// GESTION DES CLE
			if(act->ciblec->equipement[act->nb1]->objet_type==OBJ_CLE)
			{
				act->ciblec->equipement[act->nb1]=NULL;
				monde[carte_active]->cle_acquise=true;
				return 0;
			}
			/////////////////
			if(sac)
			{
				act->initj->sac_contenu[emplacement]=act->ciblec->equipement[act->nb1];;
				act->ciblec->equipement[act->nb1]=NULL;
			}
			else
			{
				act->initj->equipement[emplacement]=act->ciblec->equipement[act->nb1];
				act->ciblec->equipement[act->nb1]=NULL;
			}
			
			
		}
		
	}
	else if(act->initc!=NULL)
	{
		emplacement=stockage_libre(act->initc);
			
		if(act->ciblec==NULL)// si pas de cible, l'objet se trouve par terre
		{
			
			
			
				act->initc->equipement[emplacement]=monde[carte_active]->objet_tab[act->nb1];
				monde[carte_active]->objet_tab[act->nb1]=NULL;
			
			
		}
		else
		{
		
			
				act->initc->equipement[emplacement]=act->ciblec->equipement[act->nb1];
				act->ciblec->equipement[act->nb1]=NULL;
			
			
			
		}
	}
	return 0;
}
///////////////
int moteur_jeu::execute_action_clancer(action *act)
{
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_cafeur(action *act)
{
   acteur *ac,*mb;	
   int x2,y2;	
   int x1,y1;
   int x,y;
   int bonus_visee_cs=0;// Bonus si l'on vise un point fixe ou une cible
   int nbballe=0;
   int balle_prise;
   
   int degat=0;
   int coup_critique=0;
   int  critique=0;
   bool mort=false;
   int protection=0;
   char message[1024];
   
   int dy;
   int dx;
   int err;
   int e2;
   int signx,signy;
  
   
   int proba=80;// Probabilite de toucher un obstacle 
   				// Modification en fonction des  carac du joeur

	
	if(act->initj!=NULL)
	{
		// ******************CALCUL DU MODIFICATEUR DE PROBA
		// ****************** DE TOUCHER UN OBSTACLE
		if(act->initj->tireur_sang_froid)
		{
			proba=-20; // Bonus -20% sur la proba de toucher un obstacle  
		}
		// ********************************************************
		
		// *****************Gestion d'une arme vide
		if(act->initj->equipement[EQUIPMNT_MAIN_D]->munition<=0)
		{
			ajouter_mess_console("Malgre le clic de la detente, rien ne se produit. L'arme doit etre vide", al_map_rgb(255,0,0));	
			return 0;
		}
		///// CALCUL DU NOMBRE DE BALLES TIRE
		switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
		{
			case OBJ_PISTOLET:
		    case OBJ_FUSIL_POMPE:
		    nbballe=1;	
		    act->initj->equipement[EQUIPMNT_MAIN_D]->munition--;
			break;
			case OBJ_MITRAILLETTE:
			nbballe=3+genrand_int32()%5;
			if(act->initj->equipement[EQUIPMNT_MAIN_D]->munition<nbballe)nbballe=act->initj->equipement[EQUIPMNT_MAIN_D]->munition;
			act->initj->equipement[EQUIPMNT_MAIN_D]->munition-=nbballe;
			break;
		}
		////////////////////////////////////////////
		
		if(act->bool1) //EMPLACEMENT STRICT
		{
			bonus_visee_cs=2;//bonus de visee de cible fixe
			
			/*CALCUL PREMIER CHEMIN DE LA BALLE OU DES BALLES: chemin joueur_ennemi	*/
			//initialisation algo ligne
			x2=act->x;
			y2=act->y;
			
			x1=act->initj->x;
			y1=act->initj->y;
			x=act->initj->x;
			y=act->initj->y;
			
			
			 dx=abs(x2-x1);
			 dy=abs(y2-y1);
			 err=dx-dy;
	
			 signx=-1;
			 signy=-1;
			 if(x2>x1)signx=1;
			 if(y2>y1)signy=1;
			/////////////////////////
			
				//Algo de ligne
						while(1)
						{
 
							//ope sur position x;y si on arrive sur la cible break
							if(x==x2 && y==y2)break;
							
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
 
						
							/***********************************************
							******GESTION DES INTERACTIONS AVEC LES ACTEURS ***
							***********************************************/
							ac=obtenir_ennemi(monde[carte_active],x,y);
							mb=obtenir_mobilier(monde[carte_active],x, y);
							if(ac!=NULL)// SI ENNEMI SURLE CHEMIN
							{
							
								if( proba_toucher_pnj_non_cible(x,y,act->initj )){// SI L'ACTEUR EST TOUCHE
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,ac,balle_prise);
											
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
											ajouter_mess_console("Un dommage collateral stoppe les balles avec sa tete.", al_map_rgb(255,0,0));	
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
											ajouter_mess_console("Une partie des balles est stoppee par un corps qui passait par la! Pas de chance...", al_map_rgb(255,0,0));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,ac,1);
										    ajouter_mess_console("Vous offrez un lifting gratuit a la chevrotine au pauvre here qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,ac,1);
											ajouter_mess_console("La balle s'integre parfaitement dans le corps de la chose qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
									}
									
								}
							}
							else if(mb!=NULL) // SI MOBILIER SUR LE CHEMIN
							{
								printf("toto");
								
								if(proba_toucher_obstacle(x1,y1,x2,y2,x,y,proba,3,4)){
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,mb,balle_prise);
											printf("obstacle chemin %d",mb->vie);
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												  	if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
											 	  	detruire_conteneur_acide(monde[carte_active],mb);
												   	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
													
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
												ajouter_mess_console("Vous arrachez la moitie du mobilier avec votre rafale!", al_map_rgb(255,255,255));
											return 0;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
												ajouter_mess_console("Le mobilier stoppe net une partie de vos balles, ils ne doivent pas etre de marque ichiea!", al_map_rgb(255,255,255));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La charge de chevrotine est stoppee par du mobilier", al_map_rgb(255,255,255));		
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												  	if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La balle se loge dans le mobilier.", al_map_rgb(255,255,255));	
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
													if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			  
												
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												 	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
									}
									
									
								}
							}
							
							/**********************************************
							*** FIN DE GESTION DES INTER AVEC LES ACTEURS*/
												
							e2=2*err;
								if(e2>-dy)
								{
									err-=dy;
									x+=signx;
								}
							
							if(x==x2 && y==y2)
							{
								//ope sur position;
							break;
							}
							if(e2<dx)
							{
								err+=dx;
								y+=signy;
							}
								
							
						}
				///////////////
			
			/******************************************************************
			***********CALCUL DES EVENTUELS DEGATS SUR LA CIBLE EVENTUELLE****************
			******************************************************************/
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
								if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
							/************************************************
							*******FIN DE GESTION DES INTER AC LES TILES ***/
							
			ac=obtenir_ennemi(monde[carte_active],x,y);
			mb=obtenir_mobilier(monde[carte_active],x, y);
			printf("obtenir ennemi %d x %d, y %d\n",obtenir_ennemi(monde[carte_active],x,y),x,y);
			if(ac!=NULL)  // GESTION DE LA CIBLE EVENTUELLE
			{
				printf("Cible ennemi trouvee \n");
			     if(calcul_cible_atteinte(act->initj,NULL,ac))
			     {
			     	
			     	///////////////////////////////////
			     	///////GESTION DES COUPS CRITIQUES
			     	            critique=genrand_int32()%1001; //tirage proba coup critique							
								if(act->initj->maudit)
								{
								  if(critique >=920)coup_critique=-1;
								  if(critique<=act->initj->coup_critique*5)coup_critique=1;
								  	
								}
								else if(act->initj->tireur_sang_froid)// pas d echec critique 
								{
									if(critique<=act->initj->coup_critique)coup_critique=1;
									
								}
								else 
								{	
									// ECHEC CRITIQUE -> FORMULE  1000-100/dexterite au pire 10% de chance de foirer. Au mieux 0.5%
								
									if(critique>= 1000-100/act->initj->dexterite)coup_critique=-1;
									if(critique<=act->initj->coup_critique)coup_critique=1;
								}
				 	////////FIN GESTION DES COUPS CRITIQUES
				 	///////////////////////////////////////
				 	
				 	degat=nbballe*act->initj->equipement[EQUIPMNT_MAIN_D]->degat;
				 	
				 	// Gestion tireur sang froid
					 if(act->initj->tireur_sang_froid)
				 	{
				 		degat*=4/3;
				 	}
				 	
				 	// CALCUL DES DEGATS 
				 	switch(coup_critique)
				 	{
				 		/***************************************************************************************/
				 		case 1:
									//Message coup_critique, vous passez au travers des defenses de l'ennemi.

									// diminution de la vie du PNJ
									ac->vie-=degat*4/3;
									
									// CALCUL DE L AJOUT D ADRENALINE
									if(ac->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,degat*4/3,mort);
									
									if(mort)
									{
									 sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi, le tuant sur le coup! Dgt:%d",degat*4/3) ;
									 ajout_score_mort_monstre(act->initj,ac);
									}
									else
									{
									 sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi. Dgt:%d",degat*4/3);
									}
									
									ajouter_mess_console(message,al_map_rgb(255,0,0));
									// Gestion de la degradation des armes
								 	if(degradation_equip_arme(act->initj)==1)
								  	{
								  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
								  	}
									break;
						/*************************************************************************************/			
						case 0:
									
									
									protection=calcul_protec(ac);
									//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
									ac->vie-=(degat*(100-protection))/100;
									
									//degradation des equipements de protection/
									degradation_equip_protec(ac);
						
									// CALCUL DE L AJOUT D ADRENALINE
									if(ac->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,(degat*(100-protection))/100,mort);
									 if(mort)
									 {
									  sprintf(message,"Vous frappez l'ennemi, votre coup lui ecrase la tete. Avec la puree qu'il a entre les oreilles, les seuls mouvements dont il est capable sont nerveux Dgt:%d",(degat*(100-protection))/100) ;
									 ajout_score_mort_monstre(act->initj,ac);// Calcul du nouveau score du joueur
									  
									 }
									 else 
									 {
									 	sprintf(message,"Vous tapez de toutes vos forces sur l'ennemi. Dgt:%d",degat*4/3);
									 
									 }
									 ajouter_mess_console(message,al_map_rgb(255,0,0));
									 
								 //GESTION DE LA DEGRADATION DES ARMES
								  	if(degradation_equip_arme(act->initj)==1)
								  	{
								  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
								  	}
									break;
						/***********************************************************************************/			
						case -1:
									
								    if(act->initj->equipement[EQUIPMNT_MAIN_D]!=NULL)
									{
										faire_saigner(act->initj);
										delete act->initj->equipement[EQUIPMNT_MAIN_D];
										act->initj->equipement[EQUIPMNT_MAIN_D]=NULL;
										ajouter_mess_console("Echec critique, l'arme se desintegre dans votre main!",al_map_rgb(0,0,255));
									}	 
									// AJOUT DE L ADRENALINE
									 ajout_adrenaline(act->initj,10,0,0);
									break;
				 		/***********************************************************************************/
				 		
				 	}
				 	 
				 return 1;	
			     }
			}
			else if(mb!=NULL ) //GESTION DU MOBILIER EVENTUEL
			{
		 		 if(calcul_cible_atteinte(act->initj,NULL,mb))
			     {
				     	if(mb->acteur_type==ACTEUR_BOUTEILLE_GAZ || mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
						{
					
						 ///////////////////////////////////
			     	    ///////GESTION DES COUPS CRITIQUES
			     	            critique=genrand_int32()%1001; //tirage proba coup critique							
								if(act->initj->maudit)
								{
								  if(critique >=920)coup_critique=-1;
								  if(critique<=act->initj->coup_critique*5)coup_critique=1;
								  	
								}
								else if(act->initj->tireur_sang_froid)// pas d echec critique 
								{
									if(critique<=act->initj->coup_critique)coup_critique=1;
									
								}
								else 
								{	
									// ECHEC CRITIQUE -> FORMULE  1000-100/dexterite au pire 10% de chance de foirer. Au mieux 0.5%
								
									if(critique>= 1000-100/act->initj->dexterite)coup_critique=-1;
									if(critique<=act->initj->coup_critique)coup_critique=1;
								}
							 	////////FIN GESTION DES COUPS CRITIQUES
							 	///////////////////////////////////////
							 	
							 		
							 	degat=nbballe*act->initj->equipement[EQUIPMNT_MAIN_D]->degat;
							 	
							 	// Gestion tireur sang froid
								 if(act->initj->tireur_sang_froid)
							 	{
							 		degat*=4/3;
							 	}
				 	
				 	
							 	// CALCUL DES DEGATS 
							 	switch(coup_critique)
							 	{
							 		/***************************************************************************************/
							 		case 1:
												//Message coup_critique, vous passez au travers des defenses de l'ennemi.
			
												// degat pour coup critique
												degat=degat*4/3;
									/*************************************************************************************/			
									case 0:
												
												mb->vie-=(degat);
									
												// CALCUL DE L AJOUT D ADRENALINE
												if(mb->vie<=0) mort=true;
											//	 ajout_adrenaline(act->initj,0,(degat*(100-protection))/100,mort);
												 if(mort)
												 {
												      if(mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
												      {
												      	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
														if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  		vider_champ_vision_carte(monde[carte_active]);
														calcul_champ_vision();
									  		  
												      }
												      else if(mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
												      {
												      	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
												        detruire_conteneur_acide(monde[carte_active],mb);
												      	vider_champ_vision_carte(monde[carte_active]);
														calcul_champ_vision();
									  	
													  }
												 }
												 else
												 {
												 	
												 }
												
											 //GESTION DE LA DEGRADATION DES ARMES
											  	if(degradation_equip_arme(act->initj)==1)
											  	{
											  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
											  	}
												break;
									/***********************************************************************************/			
									case -1:
												
											    if(act->initj->equipement[EQUIPMNT_MAIN_D]!=NULL)
												{
													delete act->initj->equipement[EQUIPMNT_MAIN_D];
													act->initj->equipement[EQUIPMNT_MAIN_D]=NULL;
													ajouter_mess_console("Echec critique, l'arme se desintegre dans votre main!",al_map_rgb(0,0,255));
												}	 
												// AJOUT DE L ADRENALINE
												 ajout_adrenaline(act->initj,10,0,0);
												break;
							 		/***********************************************************************************/
							 		
							 	}
							 	//fin de calcul des degats
				 				
					    }
					    else// GESTION DU MOBILIER DIFFERENT DE LA BOUTEILLE DE GAZ ET DU CONTENEUR D ACIDE
					    {
					    ajouter_mess_console("Vos munitions s'ecrasent contre le mobilier.",al_map_rgb(0,0,255));								 
					    }
			     
			     	return 1;
			 	}
			 	
			 	
			}
			
			
			/*****************************************************************
			*************FIN DE CALCUL DE DEGAT******************
			*****************************************************************/
			
			/*******************************************************************
			**** CALCUL DU RESTE DE LA TRAJECTION SI LA BALLE N A RIEN TOUCHE**/
			x=(x2-x1)*100;
			y=(y2-y1)*100;
			
			y1=y2;
			x1=x2;
			y2+=y;
			x2+=x;
			x=x1;
			y=y1;
			/*******************************/
			 
			 dx=abs(x2-x1);
			 dy=abs(y2-y1);
			 err=dx-dy;
			 
			//deplacement de une case
			e2=2*err;
			if(e2>-dy)
			{
				err-=dy;
				x+=signx;
			}
			if(e2<dx)
			{
				err+=dx;
				y+=signy;
			}
			///////////////////////					
			
			//Algo de ligne
						while(1)
						{
 
							//ope sur position x;y si on arrive sur la cible break
							if(x==x2 && y==y2)break;
							
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
 
						
							/***********************************************
							******GESTION DES INTERACTIONS AVEC LES ACTEURS ***
							***********************************************/
							ac=obtenir_ennemi(monde[carte_active],x,y);
							mb=obtenir_mobilier(monde[carte_active],x, y);
							if(ac!=NULL)// SI ENNEMI SURLE CHEMIN
							{
							
								if( proba_toucher_pnj_non_cible(x,y,act->initj )){// SI L'ACTEUR EST TOUCHE
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,ac,balle_prise);
											
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
											ajouter_mess_console("Un dommage collateral stoppe les balles avec sa tete.", al_map_rgb(255,0,0));	
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
											ajouter_mess_console("Une partie des balles est stoppee par un corps qui passait par la! Pas de chance...", al_map_rgb(255,0,0));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,ac,1);
										    ajouter_mess_console("Vous offrez un lifting gratuit a la chevrotine au pauvre here qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,ac,1);
											ajouter_mess_console("La balle s'integre parfaitement dans le corps de la chose qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
									}
									
								}
							}
							else if(mb!=NULL) // SI MOBILIER SUR LE CHEMIN
							{
								printf("toto");
								
								if(proba_toucher_obstacle(x1,y1,x2,y2,x,y,proba,3,4)){
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,mb,balle_prise);
											printf("obstacle chemin %d",mb->vie);
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
											 		detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
													
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
												ajouter_mess_console("Vous arrachez la moitie du mobilier avec votre rafale!", al_map_rgb(255,255,255));
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
												ajouter_mess_console("Le mobilier stoppe net une partie de vos balles, ils ne doivent pas etre de marque ichiea!", al_map_rgb(255,255,255));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La charge de chevrotine est stoppee par du mobilier", al_map_rgb(255,255,255));		
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La balle se loge dans le mobilier.", al_map_rgb(255,255,255));	
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
													if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			  
												
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
									}
									
									
								}
							}
							
							/**********************************************
							*** FIN DE GESTION DES INTER AVEC LES ACTEURS*/
												
							e2=2*err;
								if(e2>-dy)
								{
									err-=dy;
									x+=signx;
								}
							
							if(x==x2 && y==y2)
							{
								//ope sur position;
							break;
							}
							if(e2<dx)
							{
								err+=dx;
								y+=signy;
							}
								
							
						}
				///////////////	
		}
		/**********************************************************************************
		************************************************************************************
		***************************************************************************
		***************************GESTION DES EMPLACEMENT NON STRICT **********************
		**********POUR LES CIBLES ET LES DIRECTION*******************/
		else  
		{ 
		   if(act->bool2) // Tir selon une direction
		   {
		   	// Calcul de la ligne de direction   
		   	x1=act->initj->x;
		   	y1=act->initj->y;
		   	x2=act->initj->x+act->x*200;
		   	y2=act->initj->y+act->y*200;
		   	x=x1;
		   	y=y1;
		   	printf("Tir dans une direction donnee x1 %d y1 %d x2 %d y2 %d",x1,y1,x2,y2);
		   	// *******************************
		   	
		   	
		   	//calcul de la trajectoire
			
			 dx=abs(x2-x1);
			 dy=abs(y2-y1);
			 err=dx-dy;
	
			 signx=-1;
			 signy=-1;
			 if(x2>x1)signx=1;
			 if(y2>y1)signy=1;
			/////////////////////////
			
				//Algo de ligne
						while(1)
						{
 
							//ope sur position x;y si on arrive sur la cible break
							if(x==x2 && y==y2)break;
							
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
 
						
							/***********************************************
							******GESTION DES INTERACTIONS AVEC LES ACTEURS ***
							***********************************************/
							ac=obtenir_ennemi(monde[carte_active],x,y);
							mb=obtenir_mobilier(monde[carte_active],x, y);
							if(ac!=NULL)// SI ENNEMI SURLE CHEMIN
							{
							
								if( proba_toucher_pnj_non_cible(x,y,act->initj )){// SI L'ACTEUR EST TOUCHE
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,ac,balle_prise);
											
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
											ajouter_mess_console("Un dommage collateral stoppe les balles avec sa tete.", al_map_rgb(255,0,0));	
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
											ajouter_mess_console("Une partie des balles est stoppee par un corps qui passait par la! Pas de chance...", al_map_rgb(255,0,0));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,ac,1);
										    ajouter_mess_console("Vous offrez un lifting gratuit a la chevrotine au pauvre here qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,ac,1);
											ajouter_mess_console("La balle s'integre parfaitement dans le corps de la chose qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
									}
									
								}
							}
							else if(mb!=NULL) // SI MOBILIER SUR LE CHEMIN
							{
								printf("toto");
								
								if(proba_toucher_obstacle_tdirection( x, y, act->initj)){
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,mb,balle_prise);
											printf("obstacle chemin %d",mb->vie);
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
											 		detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
													
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
												ajouter_mess_console("Vous arrachez la moitie du mobilier avec votre rafale!", al_map_rgb(255,255,255));
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
												ajouter_mess_console("Le mobilier stoppe net une partie de vos balles, ils ne doivent pas etre de marque ichiea!", al_map_rgb(255,255,255));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La charge de chevrotine est stoppee par du mobilier", al_map_rgb(255,255,255));		
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La balle se loge dans le mobilier.", al_map_rgb(255,255,255));	
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
													if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			  
												
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
									}
									
									
								}
							}
							
							/**********************************************
							*** FIN DE GESTION DES INTER AVEC LES ACTEURS*/
												
							e2=2*err;
								if(e2>-dy)
								{
									err-=dy;
									x+=signx;
								}
							
							if(x==x2 && y==y2)
							{
								//ope sur position;
							break;
							}
							if(e2<dx)
							{
								err+=dx;
								y+=signy;
							}
								
							
						}
				///////////////
				   	
		   }
		   else // GESTION DU TIR SUR LA CIBLE 
		   {
		   	    /*CALCUL PREMIER CHEMIN DE LA BALLE OU DES BALLES: chemin joueur_ennemi	*/
			//initialisation algo ligne
			x2=act->ciblec->x;
			y2=act->ciblec->y;
			
			x1=act->initj->x;
			y1=act->initj->y;
			x=act->initj->x;
			y=act->initj->y;
			
			
			 dx=abs(x2-x1);
			 dy=abs(y2-y1);
			 err=dx-dy;
	
			 signx=-1;
			 signy=-1;
			 if(x2>x1)signx=1;
			 if(y2>y1)signy=1;
			/////////////////////////
			
				//Algo de ligne
						while(1)
						{
 
							//ope sur position x;y si on arrive sur la cible break
							if(x==x2 && y==y2)break;
							
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
 
						
							/***********************************************
							******GESTION DES INTERACTIONS AVEC LES ACTEURS ***
							***********************************************/
							ac=obtenir_ennemi(monde[carte_active],x,y);
							mb=obtenir_mobilier(monde[carte_active],x, y);
							if(ac!=NULL)// SI ENNEMI SURLE CHEMIN
							{
							
								if( proba_toucher_pnj_non_cible(x,y,act->initj )){// SI L'ACTEUR EST TOUCHE
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,ac,balle_prise);
											
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
											ajouter_mess_console("Un dommage collateral stoppe les balles avec sa tete.", al_map_rgb(255,0,0));	
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
											ajouter_mess_console("Une partie des balles est stoppee par un corps qui passait par la! Pas de chance...", al_map_rgb(255,0,0));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,ac,1);
										    ajouter_mess_console("Vous offrez un lifting gratuit a la chevrotine au pauvre here qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,ac,1);
											ajouter_mess_console("La balle s'integre parfaitement dans le corps de la chose qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
									}
									
								}
							}
							else if(mb!=NULL) // SI MOBILIER SUR LE CHEMIN
							{
								printf("toto");
								
								if(proba_toucher_obstacle(x1,y1,x2,y2,x,y,proba,3,4)){
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,mb,balle_prise);
											printf("obstacle chemin %d",mb->vie);
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												  	if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
											 	  	detruire_conteneur_acide(monde[carte_active],mb);
												   	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
													
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
												ajouter_mess_console("Vous arrachez la moitie du mobilier avec votre rafale!", al_map_rgb(255,255,255));
											return 0;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
												ajouter_mess_console("Le mobilier stoppe net une partie de vos balles, ils ne doivent pas etre de marque ichiea!", al_map_rgb(255,255,255));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La charge de chevrotine est stoppee par du mobilier", al_map_rgb(255,255,255));		
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												  	if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La balle se loge dans le mobilier.", al_map_rgb(255,255,255));	
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
													if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			  
												
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	    ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												 	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
									}
									
									
								}
							}
							
							/**********************************************
							*** FIN DE GESTION DES INTER AVEC LES ACTEURS*/
												
							e2=2*err;
								if(e2>-dy)
								{
									err-=dy;
									x+=signx;
								}
							
							if(x==x2 && y==y2)
							{
								//ope sur position;
							break;
							}
							if(e2<dx)
							{
								err+=dx;
								y+=signy;
							}
								
							
						}
				///////////////
			
			/******************************************************************
			***********CALCUL DES EVENTUELS DEGATS SUR LA CIBLE EVENTUELLE****************
			******************************************************************/
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
								if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
							/************************************************
							*******FIN DE GESTION DES INTER AC LES TILES ***/
							
			ac=obtenir_ennemi(monde[carte_active],x,y);
			mb=obtenir_mobilier(monde[carte_active],x, y);
			printf("obtenir ennemi %d x %d, y %d\n",obtenir_ennemi(monde[carte_active],x,y),x,y);
			if(ac!=NULL)  // GESTION DE LA CIBLE EVENTUELLE
			{
				printf("Cible ennemi trouvee \n");
			     if(calcul_cible_atteinte(act->initj,NULL,ac))
			     {
			     	
			     	///////////////////////////////////
			     	///////GESTION DES COUPS CRITIQUES
			     	            critique=genrand_int32()%1001; //tirage proba coup critique							
								if(act->initj->maudit)
								{
								  if(critique >=920)coup_critique=-1;
								  if(critique<=act->initj->coup_critique*5)coup_critique=1;
								  	
								}
								else if(act->initj->tireur_sang_froid)// pas d echec critique 
								{
									if(critique<=act->initj->coup_critique)coup_critique=1;
									
								}
								else 
								{	
									// ECHEC CRITIQUE -> FORMULE  1000-100/dexterite au pire 10% de chance de foirer. Au mieux 0.5%
								
									if(critique>= 1000-100/act->initj->dexterite)coup_critique=-1;
									if(critique<=act->initj->coup_critique)coup_critique=1;
								}
				 	////////FIN GESTION DES COUPS CRITIQUES
				 	///////////////////////////////////////
				 	
				 	degat=nbballe*act->initj->equipement[EQUIPMNT_MAIN_D]->degat;
				 	
				 	// Gestion tireur sang froid
					 if(act->initj->tireur_sang_froid)
				 	{
				 		degat*=4/3;
				 	}
				 	
				 	// CALCUL DES DEGATS 
				 	switch(coup_critique)
				 	{
				 		/***************************************************************************************/
				 		case 1:
									//Message coup_critique, vous passez au travers des defenses de l'ennemi.

									// diminution de la vie du PNJ
									ac->vie-=degat*4/3;
									
									// CALCUL DE L AJOUT D ADRENALINE
									if(ac->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,degat*4/3,mort);
									
									if(mort)
									{
									 sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi, le tuant sur le coup! Dgt:%d",degat*4/3) ;
									 ajout_score_mort_monstre(act->initj,ac);
									}
									else
									{
									 sprintf(message,"Coup Critique, vous passez a travers les defenses de l'ennemi. Dgt:%d",degat*4/3);
									}
									
									ajouter_mess_console(message,al_map_rgb(255,0,0));
									// Gestion de la degradation des armes
								 	if(degradation_equip_arme(act->initj)==1)
								  	{
								  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
								  	}
									break;
						/*************************************************************************************/			
						case 0:
									
									
									protection=calcul_protec(ac);
									//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
									ac->vie-=(degat*(100-protection))/100;
									
									//degradation des equipements de protection/
									degradation_equip_protec(ac);
						
									// CALCUL DE L AJOUT D ADRENALINE
									if(ac->vie<=0) mort=true;
									 ajout_adrenaline(act->initj,0,(degat*(100-protection))/100,mort);
									 if(mort)
									 {
									  sprintf(message,"Vous frappez l'ennemi, votre coup lui ecrase la tete. Avec la puree qu'il a entre les oreilles, les seuls mouvements dont il est capable sont nerveux Dgt:%d",(degat*(100-protection))/100) ;
									 ajout_score_mort_monstre(act->initj,ac);// Calcul du nouveau score du joueur
									  
									 }
									 else 
									 {
									 	sprintf(message,"Vous tapez de toutes vos forces sur l'ennemi. Dgt:%d",degat*4/3);
									 
									 }
									 ajouter_mess_console(message,al_map_rgb(255,0,0));
									 
								 //GESTION DE LA DEGRADATION DES ARMES
								  	if(degradation_equip_arme(act->initj)==1)
								  	{
								  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
								  	}
									break;
						/***********************************************************************************/			
						case -1:
									
								    if(act->initj->equipement[EQUIPMNT_MAIN_D]!=NULL)
									{
										faire_saigner(act->initj);
										delete act->initj->equipement[EQUIPMNT_MAIN_D];
										act->initj->equipement[EQUIPMNT_MAIN_D]=NULL;
										ajouter_mess_console("Echec critique, l'arme se desintegre dans votre main!",al_map_rgb(0,0,255));
									}	 
									// AJOUT DE L ADRENALINE
									 ajout_adrenaline(act->initj,10,0,0);
									break;
				 		/***********************************************************************************/
				 		
				 	}
				 	 
				 return 1;	
			     }
			}
			else if(mb!=NULL ) //GESTION DU MOBILIER EVENTUEL
			{
		 		 if(calcul_cible_atteinte(act->initj,NULL,mb))
			     {
				     	if(mb->acteur_type==ACTEUR_BOUTEILLE_GAZ || mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
						{
					
						 ///////////////////////////////////
			     	    ///////GESTION DES COUPS CRITIQUES
			     	            critique=genrand_int32()%1001; //tirage proba coup critique							
								if(act->initj->maudit)
								{
								  if(critique >=920)coup_critique=-1;
								  if(critique<=act->initj->coup_critique*5)coup_critique=1;
								  	
								}
								else if(act->initj->tireur_sang_froid)// pas d echec critique 
								{
									if(critique<=act->initj->coup_critique)coup_critique=1;
									
								}
								else 
								{	
									// ECHEC CRITIQUE -> FORMULE  1000-100/dexterite au pire 10% de chance de foirer. Au mieux 0.5%
								
									if(critique>= 1000-100/act->initj->dexterite)coup_critique=-1;
									if(critique<=act->initj->coup_critique)coup_critique=1;
								}
							 	////////FIN GESTION DES COUPS CRITIQUES
							 	///////////////////////////////////////
							 	
							 		
							 	degat=nbballe*act->initj->equipement[EQUIPMNT_MAIN_D]->degat;
							 	
							 	// Gestion tireur sang froid
								 if(act->initj->tireur_sang_froid)
							 	{
							 		degat*=4/3;
							 	}
				 	
				 	
							 	// CALCUL DES DEGATS 
							 	switch(coup_critique)
							 	{
							 		/***************************************************************************************/
							 		case 1:
												//Message coup_critique, vous passez au travers des defenses de l'ennemi.
			
												// degat pour coup critique
												degat=degat*4/3;
									/*************************************************************************************/			
									case 0:
												
												mb->vie-=(degat);
									
												// CALCUL DE L AJOUT D ADRENALINE
												if(mb->vie<=0) mort=true;
											//	 ajout_adrenaline(act->initj,0,(degat*(100-protection))/100,mort);
												 if(mort)
												 {
												      if(mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
												      {
												      	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
														if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  		vider_champ_vision_carte(monde[carte_active]);
														calcul_champ_vision();
									  		  
												      }
												      else if(mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
												      {
												      	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
												        detruire_conteneur_acide(monde[carte_active],mb);
												      	vider_champ_vision_carte(monde[carte_active]);
														calcul_champ_vision();
									  	
													  }
												 }
												 else
												 {
												 	
												 }
												
											 //GESTION DE LA DEGRADATION DES ARMES
											  	if(degradation_equip_arme(act->initj)==1)
											  	{
											  		ajouter_mess_console("Usee par de nombreux usages, votre arme rend l'ame.",al_map_rgb(0,0,255));
											  	}
												break;
									/***********************************************************************************/			
									case -1:
												
											    if(act->initj->equipement[EQUIPMNT_MAIN_D]!=NULL)
												{
													delete act->initj->equipement[EQUIPMNT_MAIN_D];
													act->initj->equipement[EQUIPMNT_MAIN_D]=NULL;
													ajouter_mess_console("Echec critique, l'arme se desintegre dans votre main!",al_map_rgb(0,0,255));
												}	 
												// AJOUT DE L ADRENALINE
												 ajout_adrenaline(act->initj,10,0,0);
												break;
							 		/***********************************************************************************/
							 		
							 	}
							 	//fin de calcul des degats
				 				
					    }
					    else// GESTION DU MOBILIER DIFFERENT DE LA BOUTEILLE DE GAZ ET DU CONTENEUR D ACIDE
					    {
					    ajouter_mess_console("Vos munitions s'ecrasent contre le mobilier.",al_map_rgb(0,0,255));								 
					    }
			     
			     	return 1;
			 	}
			 	
			 	
			}
			
			
			/*****************************************************************
			*************FIN DE CALCUL DE DEGAT******************
			*****************************************************************/
			
			/*******************************************************************
			**** CALCUL DU RESTE DE LA TRAJECTION SI LA BALLE N A RIEN TOUCHE**/
			x=(x2-x1)*100;
			y=(y2-y1)*100;
			
			y1=y2;
			x1=x2;
			y2+=y;
			x2+=x;
			x=x1;
			y=y1;
			/*******************************/
			 
			 dx=abs(x2-x1);
			 dy=abs(y2-y1);
			 err=dx-dy;
			 
			//deplacement de une case
			e2=2*err;
			if(e2>-dy)
			{
				err-=dy;
				x+=signx;
			}
			if(e2<dx)
			{
				err+=dx;
				y+=signy;
			}
			///////////////////////					
			
			//Algo de ligne
						while(1)
						{
 
							//ope sur position x;y si on arrive sur la cible break
							if(x==x2 && y==y2)break;
							
							
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(interaction_balle_tile(NULL, act->initj,x, y)==1)return 0;
 
						
							/***********************************************
							******GESTION DES INTERACTIONS AVEC LES ACTEURS ***
							***********************************************/
							ac=obtenir_ennemi(monde[carte_active],x,y);
							mb=obtenir_mobilier(monde[carte_active],x, y);
							if(ac!=NULL)// SI ENNEMI SURLE CHEMIN
							{
							
								if( proba_toucher_pnj_non_cible(x,y,act->initj )){// SI L'ACTEUR EST TOUCHE
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,ac,balle_prise);
											
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
											ajouter_mess_console("Un dommage collateral stoppe les balles avec sa tete.", al_map_rgb(255,0,0));	
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
											ajouter_mess_console("Une partie des balles est stoppee par un corps qui passait par la! Pas de chance...", al_map_rgb(255,0,0));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,ac,1);
										    ajouter_mess_console("Vous offrez un lifting gratuit a la chevrotine au pauvre here qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,ac,1);
											ajouter_mess_console("La balle s'integre parfaitement dans le corps de la chose qui passait par la!", al_map_rgb(255,0,0));
											return 0;
										break;
										//
									}
									
								}
							}
							else if(mb!=NULL) // SI MOBILIER SUR LE CHEMIN
							{
								printf("toto");
								
								if(proba_toucher_obstacle(x1,y1,x2,y2,x,y,proba,3,4)){
									
									//Calcul du nombre de balle arreté
									switch(act->initj->equipement[EQUIPMNT_MAIN_D]->objet_type)
									{
										case OBJ_MITRAILLETTE:
											balle_prise=1+genrand_int32()%(nbballe);
											nbballe-=balle_prise;
											// CALCUL DES DEGATS
											calcappliq_degat_obstacle(act->initj,NULL,mb,balle_prise);
											printf("obstacle chemin %d",mb->vie);
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
											 		detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
													
											// SI TOUTES LES BALLES ONT ETE ARRETES
											if(nbballe<=0)
											{
												ajouter_mess_console("Vous arrachez la moitie du mobilier avec votre rafale!", al_map_rgb(255,255,255));
											return 2;
											}
											else //SI QUELQUES BALLES SONT ARRETEE
											{
												ajouter_mess_console("Le mobilier stoppe net une partie de vos balles, ils ne doivent pas etre de marque ichiea!", al_map_rgb(255,255,255));	
											}
										break;
										//
										case OBJ_FUSIL_POMPE:
											calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La charge de chevrotine est stoppee par du mobilier", al_map_rgb(255,255,255));		
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
												    if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
										case OBJ_PISTOLET:
										   	calcappliq_degat_obstacle(act->initj,NULL,mb,1);
											ajouter_mess_console("La balle se loge dans le mobilier.", al_map_rgb(255,255,255));	
											// Gestion des explosions et de l acide.
											 if(mb->vie<=0 && mb->acteur_type==ACTEUR_BOUTEILLE_GAZ)
											 {
											 	 	ajouter_mess_console("La bouteille de gaz explose.",al_map_rgb(0,0,255));
													if(detruire_bouteille_gaz(monde[carte_active],mb,act->initj)==1)return 2;
												  	vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  			  
												
											 }
											 else if(mb->vie<=0 && mb->acteur_type==ACTEUR_CONTENEUR_ACIDE)
											 {
											 	 	ajouter_mess_console("Le conteneur en acide est eventre par vos munitions. De l'acide sulfurique se repand sur le sol.",al_map_rgb(0,0,255));
													detruire_conteneur_acide(monde[carte_active],mb);
												    vider_champ_vision_carte(monde[carte_active]);
													calcul_champ_vision();
									  	
											 }
											
											return 0;
										break;
										//
									}
									
									
								}
							}
							
							/**********************************************
							*** FIN DE GESTION DES INTER AVEC LES ACTEURS*/
												
							e2=2*err;
								if(e2>-dy)
								{
									err-=dy;
									x+=signx;
								}
							
							if(x==x2 && y==y2)
							{
								//ope sur position;
							break;
							}
							if(e2<dx)
							{
								err+=dx;
								y+=signy;
							}
								
							
						}
				///////////////	
		   	
		   }
		
		}
		/***********************************************************************************
		***********************************************************************************/
	}
	else if(act->initc!=NULL)
	{
		
		
	}
	
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_cafeul(action *act)
{
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_rechargement(action *act)
{
	/*
	
	ac[nouv].action_type=ACTION_RECHARGEMENT;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////
	
	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;

	*/
			ajouter_mess_console("Vous rechargez votre arme.", al_map_rgb(255,255,255));
							
	int emplamuni;
	bool sac;
	if(act->initj!=NULL)
	{
		
				emplamuni=indice_munition_de_arme(act->initj,act->nb1,act->bool1, &sac );
						
				if(act->bool1)
				{
				
						if(sac)
						{
							
							act->initj->sac_contenu[act->nb1]->munition=act->initj->sac_contenu[act->nb1]->max_munition;
							act->initj->sac_contenu[emplamuni]->munition-=act->initj->sac_contenu[act->nb1]->max_munition;
							if(act->initj->sac_contenu[emplamuni]->munition<=0)
							{
							
							system("pause");			
							delete  act->initj->sac_contenu[emplamuni];
							act->initj->sac_contenu[emplamuni]=NULL;
							
							}
						}
						else
						{
							act->initj->sac_contenu[act->nb1]->munition=act->initj->sac_contenu[act->nb1]->max_munition;
							act->initj->equipement[emplamuni]->munition-=act->initj->sac_contenu[act->nb1]->max_munition;
							if(act->initj->equipement[emplamuni]->munition<=0)
							{
							
								
							delete  act->initj->equipement[emplamuni];
							act->initj->equipement[emplamuni]=NULL;
							
							}
							
						}
				
				
					
				}
				else
				{
						if(sac)
						{
							
							act->initj->equipement[act->nb1]->munition=act->initj->equipement[act->nb1]->max_munition;
							act->initj->sac_contenu[emplamuni]->munition-=act->initj->equipement[act->nb1]->max_munition;
							if(act->initj->sac_contenu[emplamuni]->munition<=0)
							{
							
							
							delete  act->initj->sac_contenu[emplamuni];
							act->initj->sac_contenu[emplamuni]=NULL;
							
							}
						}
						else
						{
							act->initj->equipement[act->nb1]->munition=act->initj->equipement[act->nb1]->max_munition;
							act->initj->equipement[emplamuni]->munition-=act->initj->equipement[act->nb1]->max_munition;
							if(act->initj->equipement[emplamuni]->munition<=0)
							{
							
								
							delete  act->initj->equipement[emplamuni];
							act->initj->equipement[emplamuni]=NULL;
							
							}
							
						}
				}
			
	}
	else if(act->initc!=NULL)
	{
		//recherche des munitions
		emplamuni=indice_munition_de_arme(act->initc,act->nb1);
		
			//rechargement de l'arme
			act->initc->equipement[act->nb1]->munition=act->initc->equipement[act->nb1]->max_munition;
			// soustraction des munitions utilisés
			act->initc->equipement[emplamuni]->munition-=act->initc->equipement[act->nb1]->max_munition;
			
			// Si les munitions sont inférieures ou = à 0 -> suppression de l objet munition
			if(act->initc->equipement[emplamuni]->munition<=0)
			{
			
				
			delete  act->initc->equipement[emplamuni];
			act->initc->equipement[emplamuni]=NULL;
			}
	}
	return 0;
}
///////////////
int moteur_jeu::execute_action_utilisation_medic(action *act)
{
	/*
	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////

	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	*/
	
	/*
		prefab_objet[OBJ_BANDAGE].ajt_vie=1;          // AJOUT DE VIE 
	prefab_objet[OBJ_BANDAGE].ajt_adrenaline=0;
	prefab_objet[OBJ_BANDAGE].ajt_furie=0;
	*/
	if(act->initj!=NULL)
	{
	     if(act->bool1)// si la medication a prendre est dans le sac.
		 {
		 	 
				
			
				act->initj->vie+=act->initj->sac_contenu[act->nb1]->ajt_vie;          // AJOUT DE VIE 
				if(act->initj->vie>act->initj->vie_max)act->initj->vie=act->initj->vie_max;
				
				act->initj->adrenaline+=act->initj->sac_contenu[act->nb1]->ajt_adrenaline;
				if(act->initj->adrenaline>act->initj->adrenaline_max)act->initj->adrenaline=act->initj->adrenaline_max;
				
				act->initj->furie+=	act->initj->sac_contenu[act->nb1]->ajt_furie;
				
				if(	act->initj->sac_contenu[act->nb1]->stop_sang)
				{
					act->initj->hemorragie=false;
					act->initj->tic_hemorragie=0;
				}
			
		 		delete act->initj->sac_contenu[act->nb1];
		 		act->initj->sac_contenu[act->nb1]=NULL;
		 }
		 else
		 {
				act->initj->vie+=act->initj->equipement[act->nb1]->ajt_vie;          // AJOUT DE VIE 
				if(act->initj->vie>act->initj->vie_max)act->initj->vie=act->initj->vie_max;
				
				act->initj->adrenaline+=act->initj->equipement[act->nb1]->ajt_adrenaline;
				if(act->initj->adrenaline>act->initj->adrenaline_max)act->initj->adrenaline=act->initj->adrenaline_max;
				
				act->initj->furie+=	act->initj->equipement[act->nb1]->ajt_furie;
				
				if(	act->initj->equipement[act->nb1]->stop_sang)
				{
					act->initj->hemorragie=false;
					act->initj->tic_hemorragie=0;
				}
			 	
			 	delete  act->initj->equipement[act->nb1];
			 	act->initj->equipement[act->nb1]=NULL;
		 	
		 	
		 }	
		
	}
	else if(act->initc!=NULL)
	{
				act->initc->vie+=act->initc->equipement[act->nb1]->ajt_vie;          // AJOUT DE VIE 
				if(act->initc->vie>act->initc->vie_max)act->initc->vie=act->initc->vie_max;
				
				
				if(	act->initc->equipement[act->nb1]->stop_sang)
				{
					act->initc->hemorragie=false;
					act->initc->tic_hemorragie=0;
				}
			 	
			 	delete act->initc->equipement[act->nb1];
			 	act->initc->equipement[act->nb1]=NULL; 	
		
	}
	
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_habillement(action *act)
{
	// Gestion de l'habillement -> si le  numero d equipement est une partie du corps
	// cela signifie que l'on enleve un habit.
	// sinon cela signifie que l'on en met un.
	
	/*
	
//type d action
ac[nouv].action_type=ACTION_HABILLEMENT;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////


	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	
	
	*/
	int emplaequip=-1;
	bool sac;
	if(act->initj!=NULL)
	{
		   // Si c'est le sac impossible que ce soit du deshabillage
			if(act->bool1)
			{
				  emplaequip=emplacement_equipe(act->initj->sac_contenu[act->nb1]);
				  
				  act->initj->equipement[emplaequip]=act->initj->sac_contenu[act->nb1];
				  act->initj->sac_contenu[act->nb1]=NULL;
				
			}	
			else //sinon
			{
				 if(act->nb1== EQUIPMNT_CHAUSSURE ||
				 act->nb1==	EQUIPMNT_PANTALON ||
					act->nb1==	EQUIPMNT_TORSE ||
					act->nb1==EQUIPMNT_GANT ||
					act->nb1==EQUIPMNT_DOS||
					act->nb1==EQUIPMNT_TETE)
					{
						// MISE EN PLACE DE CE TEST POUR BRIDER LA POSSIBILITE 
						// DE RAMASSER DES SACS
						if(act->nb1!=EQUIPMNT_DOS)
						{
						
							emplaequip=stockage_libre(act->initj,&sac);
							if(sac) 
							{
								
								act->initj->sac_contenu[emplaequip]=act->initj->equipement[act->nb1];
								act->initj->equipement[act->nb1]=NULL;
								
							}
							else
							{
								act->initj->equipement[emplaequip]=act->initj->equipement[act->nb1];
								act->initj->equipement[act->nb1]=NULL;
							}
							
						
						}
					}
					else
					{
					
						emplaequip=emplacement_equipe(act->initj->equipement[act->nb1]);
						act->initj->equipement[emplaequip]=act->initj->equipement[act->nb1];
				 		act->initj->equipement[act->nb1]=NULL;
					      
					   	
					}	 

				
			}
		
	}
	else if(act->initc!=NULL)
	{
		//dehabillement
			if(act->nb1== EQUIPMNT_CHAUSSURE ||
				 act->nb1==	EQUIPMNT_PANTALON ||
					act->nb1==	EQUIPMNT_TORSE ||
					act->nb1==EQUIPMNT_GANT ||
					act->nb1==EQUIPMNT_DOS||
					act->nb1==EQUIPMNT_TETE)
			{
				
				emplaequip=stockage_libre(act->initc);
				act->initc->equipement[emplaequip]=act->initc->equipement[act->nb1];
				act->initc->equipement[act->nb1]=NULL;
			}
			else//habillement
			{
				emplaequip=emplacement_equipe(act->initc->equipement[act->nb1]);
				act->initj->equipement[emplaequip]=act->initc->equipement[act->nb1];
				act->initc->equipement[act->nb1]=NULL;
			}		
	}
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_equipement_main(action *act)
{
	
	/*
	
	////////////////////////////////////////////////////:
/	/type d action
	ac[nouv].action_type=ACTION_EQUIP_MAIN;


	// Initiateur de l'action	
	ac[nouv].initj=jr;
	ac[nouv].initc=act;
	/////////////////////////

	ac[nouv].nb1=emplacement;
	ac[nouv].bool1=sac;
	ac[nouv].bool2=sol;
	
	*/
	int emplaequip=0;
	bool sac;
	if(act->initj!=NULL)
	{
			if(act->bool1)// SI l'objet a équiper est dans le sac.
			{
				
				act->initj->equipement[EQUIPMNT_MAIN_D]=act->initj->sac_contenu[act->nb1];
				act->initj->sac_contenu[act->nb1]=NULL;
				
			}	
			else// Si objet dans equipement corporel.
			{
				
				if(act->nb1==EQUIPMNT_MAIN_D)// DEsequipement de la main
				{
					
					emplaequip=stockage_libre(act->initj,&sac);
					if(sac) 
					{
					act->initj->sac_contenu[emplaequip]=act->initj->equipement[act->nb1];
					act->initj->equipement[act->nb1]=NULL;
					
					}
					else
					{
					
					act->initj->equipement[emplaequip]=act->initj->equipement[act->nb1];
					act->initj->equipement[act->nb1]=NULL;
						
					}
					
				}
				else
				{
					
					act->initj->equipement[EQUIPMNT_MAIN_D]=act->initj->equipement[act->nb1];
					act->initj->equipement[act->nb1]=NULL;
					
					
				}
				
			}
	}
	else if(act->initc!= NULL)
	{
		
		  	    if(act->nb1==EQUIPMNT_MAIN_D)// DEsequipement de la main
				{
					
					emplaequip=stockage_libre(act->initc);
					
					
					act->initc->equipement[emplaequip]=act->initc->equipement[act->nb1];
					act->initc->equipement[act->nb1]=NULL;
						
					
					
				}
				else
				{
					
					act->initc->equipement[EQUIPMNT_MAIN_D]=act->initc->equipement[act->nb1];
					act->initc->equipement[act->nb1]=NULL;
					
					
				}
		
	}	
	
	return 0;
}
///////////////
int moteur_jeu::execute_action_modif_corpo(action *act)
{
	/*
		bool implant_vitesse;
	bool implant_force;
	bool implant_dexterite;
	
	//Caractéristique du joueur
	int force;
	int dexterite;
	int vitesse;*/
	if(act->initj!=NULL)
	{    
			if(act->bool1)// si l'implant est dans le sac 
			{
				
				switch(act->initj->sac_contenu[act->nb1]->objet_type)
				{
				case OBJ_IMPLANT_FORCE:
					act->initj->implant_force=true;
					act->initj->force+=2;
				break;	
				case OBJ_IMPLANT_VITESSE:
					act->initj->implant_vitesse=true;
					act->initj->vitesse+=40;
				break;
				case OBJ_IMPLANT_DXTRT:
					act->initj->implant_dexterite=true;
					act->initj->dexterite+=2;
				break;
				}
				delete act->initj->sac_contenu[act->nb1];
				act->initj->sac_contenu[act->nb1]=NULL;
			}
			else
			{
				
				switch(act->initj->equipement[act->nb1]->objet_type)
				{
				case OBJ_IMPLANT_FORCE:
					act->initj->implant_force=true;
					act->initj->force+=2;
				break;	
				case OBJ_IMPLANT_VITESSE:
					act->initj->implant_vitesse=true;
					act->initj->vitesse+=40;
				break;
				case OBJ_IMPLANT_DXTRT:
					act->initj->implant_dexterite=true;
					act->initj->dexterite+=2;
				break;
				}
				delete act->initj->equipement[act->nb1];
				act->initj->equipement[act->nb1]=NULL;
					
			}
	
	}
	
	/**********************************************
	****************MODIF CORPO IMPOSSIBLE POUR LES PNJ !!!!!!!!!!!!!!!!!!!
	**********************************************/
	
	return 0;
}
//////////////
int moteur_jeu::execute_action_ouvrir_fermer_porte(action *act)
{
	if(act->initj!=NULL)
	{
		
		if(monde[carte_active]->cle_acquise)
		{
			//monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].verrouille=false;
			//monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].ferme=!monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].ferme;	
		    ouvrir_fermer_porte(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x]);
			
		}
		else
		{
			
			if(	monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].verrouille==true)
			{
				  ajouter_mess_console("La porte est ferme a cle.",al_map_rgb(255,255,255));	
			return 0;
			}
			else
			ouvrir_fermer_porte(&monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x]);
			  //monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].ferme=!monde[carte_active]->donnee_carte[act->initj->y+act->y][act->initj->x+act->x].ferme;				
			
		}
		    ajouter_mess_console("Vous ouvrez la porte.",al_map_rgb(255,255,255));
			vider_champ_vision_carte(monde[carte_active]);
			calcul_champ_vision();
	}
	else if(act->initc!=NULL)
	{
		
		
		
	}
	return 0;
}		

////////////////////////////////////


////////////////////////////////////


// ************************************************************
// ********************FONCTION UTILE POUR LA GESTION DES COMBATS *****
// ************************************************************


int moteur_jeu::interaction_balle_tile(acteur *act, joueur *jr, int x, int y)
{
	if(jr!=NULL)
	{
	
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(monde[carte_active]->donnee_carte[y][x].bloquant)
							{
								
								if(monde[carte_active]->donnee_carte[y][x].type==TILE_BARREAUX)
								{
								 //Barreaux -> la balle traverse	
								}
								else if(monde[carte_active]->donnee_carte[y][x].type==TILE_VITRE)// DESTRUCTION PANNEAU VERRES PAR BALLES
								{
									if(jr->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE)
									ajouter_mess_console("Le panneau de verre est traverse par les munitions. Il s'affaisse et eclate en de milliers de morceaux.", al_map_rgb(255,255,255));
									else 
									ajouter_mess_console("La munition brise le panneau de verre.", al_map_rgb(255,255,255));
									
									placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
									vider_champ_vision_carte(monde[carte_active]);
									calcul_champ_vision();	
								}
								else if(monde[carte_active]->donnee_carte[y][x].type==TILE_PORTE_FRAGILE)//DESTRUCTION DE LA PORTE FRAGILE PAR BALLES
								{
									
									if(jr->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
									{
										if(genrand_int32()%101<95){
										
											ajouter_mess_console("Le frele panneau de bois de la porte est reduis en sciure pour vos balles.", al_map_rgb(255,255,255));
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											ajouter_mess_console("La porte stoppe toutes vos munitions", al_map_rgb(255,255,255));
											return 1;
										}
									}
									else
									{ 
										 if(genrand_int32()%101<70){
										 
											ajouter_mess_console("Le panneau de bois s'ouvre en deux sous l'impact de la balle.", al_map_rgb(255,255,255));
											
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											ajouter_mess_console("La porte arrete votre munition...", al_map_rgb(255,255,255));
											return 1;
										}
									}
								}else if(monde[carte_active]->donnee_carte[y][x].type==TILE_PORTE_NORMALE)//DESTRUCTION DE LA PORTE NORMALE PAR BALLES
								{
									
									if(jr->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
									{
										if(genrand_int32()%101<65){
										
											ajouter_mess_console("Le frele panneau de bois de la porte est reduis en sciure pour vos balles.", al_map_rgb(255,255,255));
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											ajouter_mess_console("La porte stoppe toutes vos munitions", al_map_rgb(255,255,255));
											return 1;
										}
									}
									else
									{ 
										 if(genrand_int32()%101<45){
										 
											ajouter_mess_console("Le panneau de bois s'ouvre en deux sous l'impact de la balle.", al_map_rgb(255,255,255));
											
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											ajouter_mess_console("La porte arrete votre munition...", al_map_rgb(255,255,255));
											return 1;
										}
									}
								}
								else 
								{		
									/***************************************************************
									*************GESTION DES TILES BLOQUANT ET INCASSABLE **********
									***************************************************************/	
								     if(jr->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE)
									ajouter_mess_console("Les balles s'ecrasent avec fracas contre la paroi.", al_map_rgb(255,255,255));
									else 
									ajouter_mess_console("La munition se desintegre contre la paroi.", al_map_rgb(255,255,255));
								
									return 1;
								}
							}
							/************************************************
							*******FIN DE GESTION DES INTER AC LES TILES ***/
		
	}
	else if(act!=NULL)
	{
							/************************************************
							**********GESTION DES INTERACTION AVEC LES TILES*/
							if(monde[carte_active]->donnee_carte[y][x].bloquant)
							{
								
								if(monde[carte_active]->donnee_carte[y][x].type==TILE_BARREAUX)
								{
								 //Barreaux -> la balle traverse	
								}
								else if(monde[carte_active]->donnee_carte[y][x].type==TILE_VITRE)// DESTRUCTION PANNEAU VERRES PAR BALLES
								{
									
									placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
									vider_champ_vision_carte(monde[carte_active]);
									calcul_champ_vision();	
								}
								else if(monde[carte_active]->donnee_carte[y][x].type==TILE_PORTE_FRAGILE)//DESTRUCTION DE LA PORTE FRAGILE PAR BALLES
								{
									
									if(act->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
									{
										if(genrand_int32()%101<95){
										
									
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{										
											return 1;
										}
									}
									else
									{ 
										 if(genrand_int32()%101<70){
										 											
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											return 1;
										}
									}
								}else if(monde[carte_active]->donnee_carte[y][x].type==TILE_PORTE_NORMALE)//DESTRUCTION DE LA PORTE NORMALE PAR BALLES
								{
									
									if(act->equipement[EQUIPMNT_MAIN_D]->objet_type==OBJ_MITRAILLETTE )
									{
										if(genrand_int32()%101<65){
										
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
										
											return 1;
										}
									}
									else
									{ 
										 if(genrand_int32()%101<45){
										 
											
											placer_tile(&monde[carte_active]->donnee_carte[y][x],TILE_SOL_VERRE);
											vider_champ_vision_carte(monde[carte_active]);
											calcul_champ_vision();
										}
										else
										{
											return 1;
										}
									}
								}
								else 
								{		
									/***************************************************************
									*************GESTION DES TILES BLOQUANT ET INCASSABLE **********
									***************************************************************/	
									return 1;
								}
							}
							/************************************************
							*******FIN DE GESTION DES INTER AC LES TILES ***/

		
	}
	return 0;
}



// proba_toucher_obstacle
// Fonction pour calculer la probabilité de toucher un obstacle
// entre le tireur et la cible.
// x1 y1 sont la position du tireur et
// x2 y2 les position de la cible.
// pctage -> pourcentage de chance de toucher un obstacle au niveau du joueur /100
// pctage_proche -> pourcentage de chance de touche un obstacle lorsque la distance tireur cible est tres reduite
// int distance_reduit -> longueur maximum a dela de laquelle la distance tireur cible n'est plus réduite.
bool moteur_jeu::proba_toucher_obstacle(int x1,int y1,int x2,int y2,int x,int y,int prctage,int pctage_proche,int dist_reduit)
{
	
	int distance=int(sqrt(double((x-x1)*(x-x1)+(y-y1)*(y-y1))));
	printf("\n distance  %d\n",distance,dist_reduit);
	if(distance<=dist_reduit)
	{
		if(genrand_int32()%101<pctage_proche)return true;
		return false;
	}	
	
	printf("\n prctage  %d",prctage-prctage/(distance/3+1));
	
	if(genrand_int32()%101<prctage-prctage/(distance/3+1))return true;
	
	return false;
}		


//static bool proba_toucher_obstacle_direction(int xtireur,ytireur, int x, int y, joueur *jr);
//
// Fonction pour calculer la probabilite de toucher un obstacle lorsque
// l'on décide de tirer dans une direction donnee. 
bool moteur_jeu::proba_toucher_obstacle_tdirection( int x, int y, joueur *jr)
{
	
	int distance=int(sqrt(double((x-jr->x)*(x-jr->x)+(y-jr->y)*(y-jr->y))));
	printf("\n distance  %d %d\n",distance,100*jr->dexterite/(19*distance));

	if(genrand_int32()%101<100*jr->dexterite/(17*distance))return true;
	
	return false;
	
}
//version pnj
bool moteur_jeu::proba_toucher_obstacle_tdirection( int x, int y, acteur *act)
{
	
	int distance=int(sqrt(double((x-act->x)*(x-act->x)+(y-act->y)*(y-act->y))));
	printf("\n distance  %d %d\n",distance,100*act->dxtrt/(19*distance));

	if(genrand_int32()%101<100*act->dxtrt/(17*distance))return true;
	
	return false;
	
}


//fonction pour savoir si un pnj sur le chemin de la balle, la prend 
// dans la mouille
bool moteur_jeu::proba_toucher_pnj_non_cible(int x, int y, joueur *jr )
{
	
		int distance=int(sqrt(double((x-jr->x)*(x-jr->x)+(y-jr->y)*(y-jr->y))));
		printf("\n distance  %d %d\n",distance,100*jr->dexterite/(17*distance));

	if(genrand_int32()%101<100*jr->dexterite/(17*distance))return true;
	
	return false;
}
//version pnj
bool moteur_jeu::proba_toucher_pnj_non_cible(int x, int y, acteur *act )
{
	
		int distance=int(sqrt(double((x-act->x)*(x-act->x)+(y-act->y)*(y-act->y))));
		printf("\n distance  %d %d\n",distance,100*act->dxtrt/(17*distance));

	if(genrand_int32()%101<100*act->dxtrt/(17*distance))return true;
	
	return false;
}


// Fonction pour calculer et appliquer des dégats en fonction de la position d'un obstacle
// Différent de degat cible car on considere deja que l'obstacle a été touché
// grace a la fonction proba toucher obstacle
int moteur_jeu::calcappliq_degat_obstacle(joueur *jr,acteur *act,acteur *cible,int nbballe)
{
 	int	degat=0;
 	int protection=0;
	if(jr!=NULL && act==NULL) // Si c'est le joueur qui tire
	{
			
			degat+=nbballe*jr->equipement[EQUIPMNT_MAIN_D]->degat;
			
			degat=1+genrand_int32()%(degat/3);// Calcul du nombre de dégat que prend l'acteur
			
			
			if(cible->acteur_type>=ACTEUR_LIT)// GESTION DES PERSONNAGES
			{
			
			protection=calcul_protec(cible);
			//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
			cible->vie-=(degat*(100-protection))/100;
									
			//degradation des equipements de protection/
			degradation_equip_protec(cible);
			}
			else
			cible->vie-=degat;
			
			
			return degat;
	}
	else// Sinon c'est act qui tire
	{
			
					degat+=nbballe*jr->equipement[EQUIPMNT_MAIN_D]->degat;
			
					degat=1+genrand_int32()%(degat/3);// Calcul du nombre de dégat que prend l'acteur
			
					cible->vie-=degat;
			

			if(jr==NULL)//Si le joueur n'est pas la cible
			{
				if(cible->acteur_type>=ACTEUR_LIT)// GESTION DES PERSONNAGES
				{
				
				protection=calcul_protec(cible);
				//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
				cible->vie-=(degat*(100-protection))/100;
										
				//degradation des equipements de protection/
				degradation_equip_protec(cible);
				}
				else
				{
				
				cible->vie-=degat;
				//ICI GESTION DE L EXPLOSION DES BOUTEILLES DE GAZ, DE LA MORT D'UN PERSO
				}
			}	
			else
			{
				
				protection=calcul_protec(jr);
				//Diminition de la vie du PNJ. Limitation de degat grace aux protection.
				jr->vie-=(degat*(100-protection))/100;
										
				//degradation des equipements de protection/
				degradation_equip_protec(jr);
				
							
			}
			
			
				return degat;
	}
	
	
}



// Fonction pour calculer et apliquer des dégats en fonction de la position d'un obstacle
// Différent de degat cible car on considere deja que l'obstacle a été touché
// grace a la fonction proba toucher obstacle
bool moteur_jeu::calcul_cible_atteinte(joueur *jr, acteur *act,acteur *cible)
{
	
	int dexnb;
	int distance;
	if(jr!=NULL && act==NULL) // Si c'est le joueur qui tire
	{
				distance=int(sqrt(double((jr->x-cible->x)*(jr->x-cible->x)+(jr->y-cible->y)*(jr->y-cible->y))));
				
					// Proba de toucher.
					
					// DISTANCE COURTE ---------------------distance< dxtrt*4/10 -> max 8 cases + 2 case max pour tireur sang froid
					if(distance<=(jr->dexterite*3)/10+int(jr->tireur_sang_froid)*genrand_int32()%3)
					{
						printf("tir sur cible:dis %d distance courte %d prctage %d\n",distance,(jr->dexterite*2)/10+int(jr->tireur_sang_froid)*genrand_int32()%3,95+int(jr->tireur_sang_froid)*3);
								if(genrand_int32()%101<90+int(jr->tireur_sang_froid)*3-distance*distance) // 95% de chance de toucher -> 98 pour tireur de sang froid
								{
									
									return true;
								}
								return false;
					}
					// ----------------------------------------------
					else // Grance distance proba de toucher diminue avec la distance
					{
				         dexnb= jr->dexterite*jr->dexterite*3*3/100;
						
						printf("tir sur cible: distance longue %d\n",dexnb*100/(distance*distance)+int(jr->tireur_sang_froid)*10);
						
						// La chance de toucher un ennemi varie en /d^2 avec un bonus de 10% pour les tireurs de sang froid  
						 if(genrand_int32()%101<dexnb*100/(distance*distance)+int(jr->tireur_sang_froid)*10)
						 {
						 	return true;
						 }		
						
					}
	}
	else// Sinon c'est act qui tire
	{
			
			if(jr==NULL)//Si le joueur n'est pas la cible
			{
					distance=abs(act->x-cible->x)*abs(act->y-cible->y);
				
					// Proba de toucher.
					
					// DISTANCE COURTE ---------------------distance< dxtrt*4/10 -> max 8 cases + 2 case max pour tireur sang froid
					if(distance<=(act->dxtrt*4)/10+1)
					{
								if(genrand_int32()%101<95 ) // 95% de chance de toucher -> 98 pour tireur de sang froid
								{
									
									return true;
								}
								return false;
					}
					// ----------------------------------------------
					else // Grance distance proba de toucher diminue avec la distance
					{
				         dexnb= act->dxtrt*act->dxtrt*4*5/100;
						
						// La chance de toucher un ennemi varie en /d^2 avec un bonus de 10% pour les tireurs de sang froid  
						 if(genrand_int32()%101<dexnb*100/(distance*distance)+5)
						 {
						 	return true;
						 }		
						
					}
			
			}	
			else/////////////// SI LE JOUEUR EST LA CIBLE
			{
				 	distance=abs(act->x-jr->x)*abs(act->y-jr->y);
				
					// Proba de toucher.
					
					// DISTANCE COURTE ---------------------distance< dxtrt*4/10 -> max 8 cases + 2 case max pour tireur sang froid
					if(distance<=(act->dxtrt*4)/10+1)
					{
								if(genrand_int32()%101<95 ) // 95% de chance de toucher -> 98 pour tireur de sang froid
								{
									
									return true;
								}
								return false;
					}
					// ----------------------------------------------
					else // Grance distance proba de toucher diminue avec la distance
					{
				         dexnb= act->dxtrt*act->dxtrt*4*5/100;
						
						// La chance de toucher un ennemi varie en /d^2 avec un bonus de 10% pour les tireurs de sang froid  
						 if(genrand_int32()%101<dexnb*100/(distance*distance)+5)
						 {
						 	return true;
						 }		
						
					}
			
				 			
			}
			
			
			
	}
return false;	
}



//--------GESTION DU JOUEUR
	
	//int placer_joueur(int x,int y);
	//
	// FOnction pour placer le joueur sur
	// la carte active en x et y.
	// Si x et y sont en dehors des limites de la carte RETOURNE -1
	// Si le deplacement se fait dans un mur 			RETOURNE 0
	// Si le deplacement est valide et est correctement menée RETOURNE 1 
int moteur_jeu::placer_joueur(int x,int y)
{
	
	if(x<0 || y<0 || x>=monde[carte_active]->x || y>=monde[carte_active]->y)return -1;
	
	if(monde[carte_active]->donnee_carte[y][x].bloquant==true)return 0;
	
	ply1.x=x;
	ply1.y=y;
	
	return 0;
}


//gestion_action_joueur(ALLEGRO_EVENT_QUEUE *queue)
//
// Fonction pour gerer les choix d'action du joueur!
int moteur_jeu::gestion_action_joueur(ALLEGRO_EVENT_QUEUE *queue)
{
	bool tir_lent;
	bool tir_direction;
	int ciblex,cibley;
	acteur *act;

   ALLEGRO_EVENT event;
   bool affich = false;
   int buff;
   printf("entre gestion action joueur\n");
   
   //forçage de l'affichage du monde de jeu;
        
			affiche_tuiles();
		affiche_objets();
		affiche_acteurs(); 
	 	affiche_joueur();
	 	affiche_interface();
	 	
	 	al_flip_display();
   
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) {
	
		al_draw_filled_rectangle(0.0,0.0,float(vue_jeuX)+0.5,float(vue_jeuY)+0.5,al_map_rgb(0,0,0));
   	
		affiche_tuiles();
		affiche_objets();
		affiche_acteurs(); 
	 	affiche_joueur();
	 	affiche_interface();
	 	
	 	al_flip_display();
	 	affich=false;
	 	//printf("affich");
	 	}
	 	//printf("ssss");
	 	al_wait_for_event(queue, &event);
		
	  //gestion des entrees	
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
	    {	
			
			switch(event.keyboard.keycode)
			{
				
			//DEPLACEMENT ET COMBAT CAC************
			// ************************************
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_PAD_8:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, 0,-1);
			if(buff==0)//chemin libre
			{
				emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,0,-1,false);
				return 0;
			}
			else if(buff==4)//pnj combat cac.
			{
			    emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x,ply1.y-1) ,0,-1,false);			
				return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x,ply1.y-1),0,-1,true);
				return 0;	
				//}
				
			}
			continue;	
			//
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_PAD_2:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, 0,+1);
			if(buff==0)//chemin libre
			{
					emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,0,+1,false);
					return 0;	
			}
			else if(buff==4)//pnj combat cac.
			{
				   emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x,ply1.y+1),0,+1,false);
				   return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x,ply1.y+1),0,+1,true);
				return 0;
					
				//}
				
			}			
			continue;
			//
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_PAD_4:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, -1,0);
			if(buff==0)//chemin libre
			{
				emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,-1,0,false);
				return 0;	
			}
			else if(buff==4)//pnj combat cac.
			{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y),-1,0,false);
				return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y),-1,0,true);	
				return 0;
				//}
				
			}
			break;
			//
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_PAD_6:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, +1,0);
			if(buff==0)//chemin libre
			{
					emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,+1,0,false);
					return 0;		
			}
			else if(buff==4)//pnj combat cac.
			{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y),+1,0,false);
				return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y),+1,0,true);
				return 0;	
				//}
				
			}
			break;
			//
			case ALLEGRO_KEY_PAD_1:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, -1,+1);
			if(buff==0)//chemin libre
			{
					emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,-1,+1,false);
					return 0;
			}
			else if(buff==4)//pnj combat cac.
			{
				   emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y+1),-1,+1,false);
				   return 0;	
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y+1),-1,+1,true);
				return 0;	
				//}
				
			}
			break;
			//
			case ALLEGRO_KEY_PAD_7:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, -1,-1);
			if(buff==0)//chemin libre
			{
					emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,-1,-1,false);
					return 0;
			}
			else if(buff==4)//pnj combat cac.
			{
					emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y-1),-1,-1,false);
					return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x-1,ply1.y-1),-1,-1,true);
				return 0;	
				//}
				
			}
			break;
			//
			case ALLEGRO_KEY_PAD_9:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, +1,-1);	
			
			if(buff==0)//chemin libre
			{
					emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,+1,-1,false);
					return 0;
			}
			else if(buff==4)//pnj combat cac.
			{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y-1),+1,-1,false);
				return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y-1),+1,-1,true);
				return 0;	
				//}
				
			}
			break;
			case ALLEGRO_KEY_PAD_3:
			buff=validite_deplacement(monde[carte_active],ply1.x,ply1.y, +1,+1);	
		
			if(buff==0)//chemin libre
			{
				emission_action_deplacement(action_tab,NB_MAX_ACTION,&ply1,NULL,+1,+1,false);
				return 0;
			}
			else if(buff==4)//pnj combat cac.
			{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y+1),+1,+1,false);
				return 0;
			}
			if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
			{
				//if(buff==3 || buff==2 || buff==3)
				//{
				emission_action_cac(action_tab,NB_MAX_ACTION,&ply1,NULL,obtenir_ennemi(monde[carte_active],ply1.x+1,ply1.y+1),+1,+1,true);		
				return 0;
				//}
			}
			break;
			// *************************************
			// *************************************
			
			// RECHARGEMENT D'ARME
			case ALLEGRO_KEY_R:
				// si la main du joueur est equipée d'une arme rechargeable
				if(ply1.equipement[EQUIPMNT_MAIN_D]!= NULL  )
				{
					if(objet_est_arme_rechargeable(ply1.equipement[EQUIPMNT_MAIN_D]))
					{
						if( munition_arme_dans_inv(&ply1,EQUIPMNT_MAIN_D))
						{
							emission_action_rechargement_arme(action_tab,NB_MAX_ACTION,&ply1,NULL,EQUIPMNT_MAIN_D,false,false);
							return 0;
						}
						else//plus de munitions
						{
							ajouter_mess_console("Impossible de recharger; pas de munition dans l'inventraire!", al_map_rgb(255,0,0));	

						}
					}
					else// Si ce n'est pas une arme rechargeable
					{
						ajouter_mess_console("L'arme n'est pas rechargeable!", al_map_rgb(255,0,0));	
	
					}
					
				}
				
			continue;
			//LANCE DE COUTEAU SCALPEL ETC OU ALORS ARME A FEU
			case ALLEGRO_KEY_F:
			
			if(choix_cible(queue,&ciblex,&cibley,&tir_direction,&tir_lent)==1)
			{
				
				if(ply1.equipement[EQUIPMNT_MAIN_D]!=NULL)//Si le joueur tiens quelque chose dans sa main droite
				{
					////////// GESTION DES ARMES A FEU				  
					if(objet_est_arme_rechargeable(ply1.equipement[EQUIPMNT_MAIN_D]))
					{
						 if(tir_lent) // Gestion du tir lent
						 {
						 	
						 }
						 else // TIR RAPIDE
						 {

						 	if(tir_direction)// SI LA TIR EST JUSTE DANS UNE DIRECTION DONNEE
						 	{
						 		 emission_action_cafeur(action_tab,NB_MAX_ACTION,&ply1,NULL,NULL,ciblex,cibley,false,true);	
						 		 return 0;
							}
						 	else
						 	{
						 	
							 	act=obtenir_ennemi(monde[carte_active],ciblex,cibley);
							 	if(act==NULL)
							 	{
							 	 emission_action_cafeur(action_tab,NB_MAX_ACTION,&ply1,NULL,NULL,ciblex,cibley,true,false);
							 	 return 0;
								}
							 	else
							 	{
							 	 emission_action_cafeur(action_tab,NB_MAX_ACTION,&ply1,NULL,act,ciblex,cibley,false,false);	
							 	 return 0;
								}
							}
						 }
						
					}///////// GESTION DES ARMES DE JET
					else if(objet_est_arme(ply1.equipement[EQUIPMNT_MAIN_D]))
					{
						
					}	
					// Si la main n'est pas équipée d'une arme affichage d'un message
					ajouter_mess_console("Pourquoi ne pas jeter des cacahuette tant que vous y etes... Imbecile!", al_map_rgb(255,255,255));
				}
				else // sinon message
				{
					ajouter_mess_console("Vous n'avez rien dans la main.", al_map_rgb(255,255,255));
				}
			}	
				
			continue;
			//AFFICHAGE DE L'INVENTAIRE
			case ALLEGRO_KEY_I:
			 if(gestion_inventaire(queue)==1) // SI UNE ACTION DE L inventaire est choisie sortie fonction
			 return 0;	
			
			break;
			//AFFICHAGE DU MENU DE RAMASSAGE
			case ALLEGRO_KEY_P:
				if(gestion_ramassage(queue)==1)
				return 0;
			break;
			//AFFICHAGE DU MENU DE LOOT
			//CHOIX DE DIRECTION
			case ALLEGRO_KEY_L:
				if(gestion_loot(queue)==1)
				return 0;
			break;
			//
			case ALLEGRO_KEY_Q:
				if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)//forcage combat cac
				{
				sortie_boucle_jeu=true;
				return 1;	
				}
				break;
			//
			case ALLEGRO_KEY_O:
				if(gestion_ouverturefermeture(queue)==1)
				return 0;
			break;
			//
			case ALLEGRO_KEY_C:
				centrer_camera_joueur();
			break;
			
			}
	    }
		
		if (event.timer.source == timer_affichage) {
         affich = true;
         continue;
        }
	  
		
	}
	
	
return 0;	
}


//int choix_cible(ALLEGRO_EVENT_QUEUE *queue);
//
// Fonction pour choisir une cible dans l'entourage du joueur
// 
// retourne 1 si une cible est choisie sinon 0;
int moteur_jeu::choix_cible(ALLEGRO_EVENT_QUEUE *queue,int *x,int *y,bool *direction,bool *tirlent)
{
	 ALLEGRO_EVENT event;
   bool affich = true;
	*tirlent=false;
	*x=ply1.x;
	*y=ply1.y;
	
	recherche_cible(x,y);
	
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) {
        
        	if(*x<cameraX )cameraX=*x;
        	if(*y<cameraY )cameraY=*y;
        	if(*x>=cameraX+tile_nbX)cameraX+=1;
        	if(*y>=cameraY+tile_nbY)cameraY+=1;
        	
        	
        	affiche_tuiles();
			affiche_objets();
			affiche_acteurs(); 
         	affiche_joueur();
         	affiche_interface();
         	
         	al_draw_rectangle(float((*x-cameraX)*tile_res)+0.5+2., float((*y-cameraY)*tile_res)+0.5+2.,float((*x+1-cameraX)*tile_res)+0.5-2., float((*y+1-cameraY)*tile_res)+0.5-2.,al_map_rgb(200,0,0),2);
	    
         	 al_flip_display(); 
			   
         affich = false;
        }
		al_wait_for_event(queue, &event);
		
		if (event.timer.source == timer_affichage) {
         affich = true;
         continue;
        }
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
				//GESTION DES DIRECTIONS
				if(event.keyboard.modifiers&ALLEGRO_KEYMOD_SHIFT)
				{
								if(event.keyboard.keycode == ALLEGRO_KEY_UP ||
									event.keyboard.keycode == ALLEGRO_KEY_PAD_8 )
							    {
								   *direction=true;
								   *y=-1 ;
								   *x=0;
								   	return 1;
								}
									else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN ||
									event.keyboard.keycode == ALLEGRO_KEY_PAD_2 )
								{
									*direction=true;
							   		*y=1;
							   		*x=0;
									return 1;
								}
								else if(event.keyboard.keycode == ALLEGRO_KEY_LEFT ||
										event.keyboard.keycode == ALLEGRO_KEY_PAD_4 )
								{
									*direction=true;
									*x=-1;
									*y=0;
									return 1;
									// continue;
								}
								else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
										event.keyboard.keycode == ALLEGRO_KEY_PAD_6 )
								{
									
									*direction=true;
									*x=1;
									*y=0;
									return 1;
									// continue;
								}
								else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_1 )
								{
									*direction=true;
									*x=-1;
									*y=+1;
									return 1;
								//	 continue;
								}
								else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_3 )
								{
									*direction=true;
									*x=+1;
									*y=+1;
									return 1;
								//	 continue;			
						
								}
								else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_7 )
								{
									*direction=true;
									*x=-1;
									*y=-1;
									return 1;
									// continue;				
								}
								else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_9 )
								{
									*direction=true;
									*x=+1;
									*y=-1;
									return 1;
								
								}
								else if(event.keyboard.keycode == ALLEGRO_KEY_F)
								{
									
									*direction=false;
									*tirlent=true;
									return 1;
									
								}
				}
			//GESTION DES APPUIES DE TOUCHE STANDARDS
			//escape, le joueur renonce a choisir une cible
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				return 0;
			
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_C)
			{
				recherche_cible(x,y);
				 continue;
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_UP ||
					event.keyboard.keycode == ALLEGRO_KEY_PAD_8 )
			{
				(*y)--;
				if(*y<0)*y=0;
				 continue;
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN ||
					event.keyboard.keycode == ALLEGRO_KEY_PAD_2 )
			{
				(*y)++;
				if(*y>=monde[carte_active]->y)*y=monde[carte_active]->y-1;
				// continue;
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_LEFT ||
					event.keyboard.keycode == ALLEGRO_KEY_PAD_4 )
			{
				(*x)--;
				if(*x<0)*x=0;
				// continue;
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
					event.keyboard.keycode == ALLEGRO_KEY_PAD_6 )
			{
				(*x)++;
				if(*x>=monde[carte_active]->x)*x=monde[carte_active]->x-1;
			
				// continue;
			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_1 )
			{
				(*x)--;
				(*y)++;
				if(*x<0)*x=0;
				if(*y>=monde[carte_active]->y)*y=monde[carte_active]->y-1;
			
			//	 continue;
			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_3 )
			{
				(*x)++;
				(*y)++;	
				if(*x>=monde[carte_active]->x)*x=monde[carte_active]->x-1;
				if(*y>=monde[carte_active]->y)*y=monde[carte_active]->y-1;
			
			//	 continue;			

			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_7 )
			{
				(*x)--;
				(*y)--;
					if(*x<0)*x=0;
					if(*y<0)*y=0;
				// continue;				
			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_PAD_9 )
			{
				(*x)++;
				(*y)--;
				if(*x>=monde[carte_active]->x)*x=monde[carte_active]->x-1;
				if(*y<0)*y=0;
				 continue;
				
			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_J )
			{
				*x=ply1.x;
				*y=ply1.y;
				 continue;
				 
			}
			else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
					event.keyboard.keycode == ALLEGRO_KEY_SPACE ||
					event.keyboard.keycode == ALLEGRO_KEY_F)
			{
				*direction=false;
				return 1;
			}


			
			
		}
	}
	
	return 0;
}


int moteur_jeu::recherche_cible(int *x,int *y)
{
	
	//acteur_tab[NB_MAX_ACTEUR]
	for( register int i=0;i<NB_MAX_ACTEUR;i++)
	{
		
		if(monde[carte_active]->acteur_tab[i]!=NULL)
		{
			
			
			if(monde[carte_active]->donnee_carte[monde[carte_active]->acteur_tab[i]->y][monde[carte_active]->acteur_tab[i]->x].champ_vision)
			{
				
				if(monde[carte_active]->acteur_tab[i]->acteur_type>=ACTEUR_SCIENTIFIQUE_BASE && est_vivant(monde[carte_active]->acteur_tab[i]))
				{
					if(*x!=monde[carte_active]->acteur_tab[i]->x &&
						*y!=monde[carte_active]->acteur_tab[i]->y)
					{
					
					*x=monde[carte_active]->acteur_tab[i]->x;
					*y=monde[carte_active]->acteur_tab[i]->y;
					return 1;
					}
				}
				
			}
			
			
		}
		
		
	}
	
	
	return 0;
}



int moteur_jeu::gestion_inventaire(ALLEGRO_EVENT_QUEUE *queue)
{
	    ALLEGRO_EVENT event;
   		bool affich = true;
		bool trouve=false;
		
		int selection=-1;
		
		
		for(int i=0;i<MAX_EQUIPMNT;i++)
		{
		  if(ply1.equipement[i]!=NULL)
		  {
		  	selection=i;
		  	break;
		  }
		
		}
		
	
	
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) {
        
         	affiche_inventaire();
         	
         	if(selection!=-1) // Si l'inventaire contient quelque chose
         	{
         	
			         	if(selection<MAX_EQUIPMNT) // si la selection se situe dans l'équipement
			         	{
			         		al_draw_bitmap(bitmap_index[BMP_FLECHE_MENU], float(700), float((ecranY-((8+5+2+1)*tile_res+10*5))/2 +selection*tile_res), 0);													
						
			         	}
			         	else
			         	{
			         		al_draw_bitmap(bitmap_index[BMP_FLECHE_MENU], float(800), float((ecranY-((8+5+2+1)*tile_res+10*5))/2 +(selection-MAX_EQUIPMNT)*tile_res+(MAX_EQUIPMNT+2)*tile_res), 0);													
						
			         	}
			         	
			         		//On affiche l'inventaire au milieu de l'écran.
 	// IL y a 5 emplacement dans le sac a dos
 	// et 8 equipements différent sur le joueur.
 	// separation de 2 items entre le sac et le reste si il existe.
 	
 	// speration 1/2 tile res entre le nom de l objet et son image
 	
	 //separation 1 item entre description et reste
	// affichage de la description de l'objet sur 5 lignes de 10 pixels
 	
 	// affichage des objet à 300 pixels du bord gauche de l ecran
 	
 					if(selection<MAX_EQUIPMNT) // si la selection se situe dans l'équipement
			        {
			           affichage_texte(10,(ecranY-((8+5+2+1)*tile_res+10*5))/2+(((8+5+2+1)*tile_res)), 896-20, 10,8, ply1.equipement[selection]->description);
					}
					else
					   affichage_texte(10,(ecranY-((8+5+2+1)*tile_res+10*5))/2+(((8+5+2+1)*tile_res)), 896-20, 10,8, ply1.sac_contenu[selection-MAX_EQUIPMNT]->description);
				
						
			}
         	 al_flip_display(); 
			   
         affich = false;
        }
        
		al_wait_for_event(queue, &event);
		
		if (event.timer.source == moteur_jeu::timer_affichage) {
         affich = true;
        
         continue;
        }
		
		// GESTION DES ENTREE CLAVIER
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
		
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				return 0;
			
			}
			
			else if(event.keyboard.keycode == ALLEGRO_KEY_UP ||
			   event.keyboard.keycode == ALLEGRO_KEY_PAD_8	)
			{
				//recherche equipement plus haut
				for(int i=selection-1;i>=0;i--)
				{
						// POUR LA RECHERCHE DANS LE SAC
						if(i>=MAX_EQUIPMNT && ply1.sac)
						{
							if(ply1.sac_contenu[i-MAX_EQUIPMNT]!=NULL)
							{
								selection=i;
								//trouve=true;
								break;
							}
						}
						//POUR LA RECHERCHE DANS L EQUIPEMENT
						else if(i<MAX_EQUIPMNT)
						{
							if(ply1.equipement[i]!=NULL)
							{
								selection=i;
								//trouve=true;
								break;
							}
					
						}
				}
				
			
			}
			
			else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN ||
			   event.keyboard.keycode == ALLEGRO_KEY_PAD_2	)
			{
				//recherche equipement plus haut
				for(int i=selection+1;i<MAX_EQUIPMNT+MAX_SAC_EMPLACEMNT;i++)
				{
						// POUR LA RECHERCHE DANS LE SAC
						if(i>=MAX_EQUIPMNT && ply1.sac)
						{
							if(ply1.sac_contenu[i-MAX_EQUIPMNT]!=NULL)
							{
								selection=i;
								//trouve=true;
								break;
							}
						}
						//POUR LA RECHERCHE DANS L EQUIPEMENT
						else if(i<MAX_EQUIPMNT)
						{
							if(ply1.equipement[i]!=NULL)
							{
								selection=i;
								//trouve=true;
								break;
							}
					
						}
				}
				
			
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_E )// GESTION DE L EQUIPEMENT DESEQUIPEMENT DES OBJETS DE L INVENTAIRE
			{
				// dehabillage du joueur
				// NE FONCTIONNE QUE SI LE JOUEUR A UN EMPLACEMENT DE LIBRE 
				// DANS SON INVENTAIRE
				if(selection<MAX_EQUIPMNT && selection != EQUIPMNT_MAIN_G && selection != EQUIPMNT_MAIN_D)
				{
					
				 if(stockage_libre(&ply1)!=-1)
				 {
				 	/*****************EMISSION D ACTION ***************/
				 emission_action_habillement(action_tab,NB_MAX_ACTION,&ply1,NULL,selection,false,false);
				 return 1;
				 }
				}
				 // SI ON DESIRE EQUIPER DESEQUIPER LA MAIN D
				else if(selection==EQUIPMNT_MAIN_D)
				{
					//TEST POUR VOIR SI L OBJET TENU EST UNE ARME
					if(objet_est_arme(ply1.equipement[selection]))	{
					
							 if(stockage_libre(&ply1)!=-1)
						 	{		
							 emission_action_equipement_main(action_tab,NB_MAX_ACTION,&ply1, NULL, selection, false,false);
							 return 1;
							}
						
					}
					else // SINON ON TRAITE LES VETEMENTS EVENTUELS TENUS EN MAIN D 
					{
						
						 if(objet_est_habit(ply1.equipement[selection]))
						 {
						 	
						 	if(ply1.equipement[emplacement_equipe(ply1.equipement[selection])]==NULL)
						 	{
						 	 emission_action_habillement(action_tab,NB_MAX_ACTION,&ply1,NULL,selection,false,false);
							  return 1;
							 }
						 }
						 else
						 {			//Pour liberer la main si celle si tiens autres chose que des armes et des habits FONCTIONNE ! 
						 		 if(stockage_libre(&ply1)!=-1)
						 		{		
							 	emission_action_equipement_main(action_tab,NB_MAX_ACTION,&ply1, NULL, selection, false,false);
							 	return 1;
								}
						 }
						 	
						 	
						
					}
				}
				else if(selection==EQUIPMNT_MAIN_G)
				{
					// si on cherche a equiper la main et que l emplacement a equiper est libre
					if(objet_est_arme(ply1.equipement[selection])&& ply1.equipement[emplacement_equipe(ply1.equipement[selection])]==NULL)
					{
							 emission_action_equipement_main(action_tab,NB_MAX_ACTION,&ply1, NULL, selection, false,false);
							return 1;
					}
					else if(objet_est_habit(ply1.equipement[selection]) &&  ply1.equipement[emplacement_equipe(ply1.equipement[selection])]==NULL)
					{
						    	emission_action_habillement(action_tab,NB_MAX_ACTION,&ply1,NULL,selection,false,false);
								return 1;	
					}
				}
				//EQUIPEMENT DES OBJETS DANS LE SAC DU JOUEUR
				else if(selection>=MAX_EQUIPMNT)
				{
					
					if(objet_est_arme(ply1.sac_contenu[selection-MAX_EQUIPMNT])&& ply1.equipement[emplacement_equipe(ply1.sac_contenu[selection-MAX_EQUIPMNT])]==NULL)
					{
							 emission_action_equipement_main(action_tab,NB_MAX_ACTION,&ply1, NULL, selection-MAX_EQUIPMNT,true,false);
						     return 1;
					}
					else if(objet_est_habit(ply1.sac_contenu[selection-MAX_EQUIPMNT]) &&  ply1.equipement[emplacement_equipe(ply1.sac_contenu[selection-MAX_EQUIPMNT])]==NULL)
					{
						    	emission_action_habillement(action_tab,NB_MAX_ACTION,&ply1,NULL,selection-MAX_EQUIPMNT,true,false);
								return 1;	
					}
					
					
				}
			
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_R )
			{
				
				if(selection>=MAX_EQUIPMNT)
				{
				
					//Si l'arme sélectionné est rechargeable
					if(objet_est_arme_rechargeable(ply1.sac_contenu[selection-MAX_EQUIPMNT] ))
					{
						if(munition_arme_dans_inv(&ply1,selection))
						{
							emission_action_rechargement_arme(action_tab,NB_MAX_ACTION,&ply1, NULL,selection-MAX_EQUIPMNT,true,false);
							
							return 1;
						}					
					}
					//Si les munition choisis peuvent etre introduites
				/*	if(objet_est_munition(ply1.sac_contenu[selection-MAX_EQUIPMNT]))
					{
						if(arme_de_ces_muni_ds_inv(&ply1,selection))
						{
							
							return 1;
						}
					}*/
				}
				else
				{
					//Si l'arme sélectionné est rechargeable
					if(objet_est_arme_rechargeable(ply1.equipement[selection] ))
					{
						if(munition_arme_dans_inv(&ply1,selection))
						{
							emission_action_rechargement_arme(action_tab,NB_MAX_ACTION,&ply1, NULL,selection,false,false);
							//system("pause");
							return 1;
						}					
					}
					//Si les munition choisis peuvent etre introduites
				/*	if(objet_est_munition(ply1.equipement[selection]))
					{
						if(arme_de_ces_muni_ds_inv(&ply1,selection))
						{
							return 1;
						}
					}*/
				}
				
				
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_U )
			{
				
				if(selection>=MAX_EQUIPMNT)
				{
				
					//Si l'objet sélectionné est medical
					if(objet_est_medic(ply1.sac_contenu[selection-MAX_EQUIPMNT] ))
					{
						    emission_action_utilisation_medic(action_tab,NB_MAX_ACTION,&ply1,NULL,selection-MAX_EQUIPMNT,true, false);
							return 1;
					}
					//Si les munition choisis peuvent etre introduites
					if(objet_est_implant(ply1.sac_contenu[selection-MAX_EQUIPMNT]))
					{
						if(implant_deja_installe(&ply1,ply1.sac_contenu[selection-MAX_EQUIPMNT])==false)
						{
						    emission_action_modif_corpo(action_tab,NB_MAX_ACTION,&ply1, NULL, selection-MAX_EQUIPMNT, true,false);
							return 1;
						}
					}
				}
				else
				{
					//Si l'objet a utiliser est un medicament
					if(objet_est_medic(ply1.equipement[selection] ))
					{
							 emission_action_utilisation_medic(action_tab,NB_MAX_ACTION,&ply1,NULL,selection, false, false);			
							return 1;
							
					}
					//Si les munition choisis peuvent etre introduites
					if(objet_est_implant(ply1.equipement[selection]))
					{
						if(implant_deja_installe(&ply1,ply1.equipement[selection])==false)
						{
						   emission_action_modif_corpo(action_tab,NB_MAX_ACTION,&ply1, NULL, selection,false,false);	
							return 1;
						}
					}
				}
			
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_D )
			{
				
			  if(selection==EQUIPMNT_MAIN_D|| 
			  	selection== EQUIPMNT_MAIN_G	 ||
				   selection>=MAX_EQUIPMNT)
				{
				   	if(selection<MAX_EQUIPMNT)
				    emission_action_lacher_objet(action_tab,NB_MAX_ACTION,&ply1,NULL,selection,false, ply1.x,ply1.y);
					else
					emission_action_lacher_objet(action_tab,NB_MAX_ACTION,&ply1,NULL,selection-MAX_EQUIPMNT,true, ply1.x,ply1.y);
					
					
					return 1;	
				}
				
			}

			
			
		}
	}
}



int moteur_jeu::gestion_ramassage(ALLEGRO_EVENT_QUEUE *queue)
{
	ALLEGRO_EVENT event;
	bool affich=true;
	int selection=0;
	
	objet *obj[20];
	int obj_ind[20];
	int obj_act_ind[20];
	int obj_nb=0;	
	
	//pas si de stockage libre chez le joueur retourne 0
	if( stockage_libre(&ply1)==-1)
	{
					ajouter_mess_console("Pas de place dans l'inventaire pour prendre un objet", al_map_rgb(255,255,255));
		return 0;
	}
	
	
	//recherche des objets a placer dans l'inventaire
	for(int i=0;i<NB_MAX_OBJET;i++)
	{
		if(obj_nb==20)break;
		if(monde[carte_active]->objet_tab[i]!=NULL)
		{
			//si objet place sous joueur-> conservation
//			printf("x %d,y %d",monde[carte_active]->objet_tab[i]->x,monde[carte_active]->objet_tab[i]->y);
			if(monde[carte_active]->objet_tab[i]->x==ply1.x && monde[carte_active]->objet_tab[i]->y==ply1.y)
			{
			  obj[obj_nb]=monde[carte_active]->objet_tab[i];	
			  obj_ind[obj_nb]=i;
			  obj_act_ind[obj_nb]=-1;	
			  obj_nb++;
			}
			
			
		}
		
	}
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		
		if(obj_nb==20)break;
		if(monde[carte_active]->acteur_tab[i]!=NULL)
		{
			
			if(monde[carte_active]->acteur_tab[i]->x==ply1.x&& monde[carte_active]->acteur_tab[i]->y==ply1.y)
			{
				
				for(int j=0;j<MAX_EQUIPMNT;j++)
				{
					if(obj_nb==20)break;
					if(monde[carte_active]->acteur_tab[i]->equipement[j]!=NULL)
					{
						
						obj[obj_nb]=monde[carte_active]->acteur_tab[i]->equipement[j];
						obj_ind[obj_nb]=j;
						obj_act_ind[obj_nb]=i;
						obj_nb++;
					}
				}			
			}
		}
		
	}
	
	//SI PAS D'objet à l'endroit indiqué -> retour
	if(obj_nb==0)
	{
	return 0;
	}
	
	/**********************
	forçage de l affichage*
	**********************/
	 al_draw_bitmap(bitmap_index[BMP_PRENDRE_MENU], float(200), float(36), 0);													
		
         for(int i=0;i<obj_nb;i++)
		 {
		 	   	al_draw_bitmap_region(bitmap_index[obj[i]->bmp_index],0.,0.,float(tile_res),float(tile_res), float(200+30), float(36+28+tile_res*i), 0);													
				al_draw_text(font,al_map_rgb(0,0,0),float(200+30+tile_res+30),float(36+28+tile_res*i+(tile_res-8)/2),0,obj[i]->objet_nom);
				if(obj_act_ind[i]!=-1)al_draw_text(font,al_map_rgb(0,0,0),float(200+30+tile_res+30+100),float(36+28+tile_res*i+(tile_res-8)/2),0,"sur cadavre");
				
		 }	
         	
		   		al_draw_bitmap(bitmap_index[BMP_FLECHE_MENU], float(200+310), float(36+28+selection*tile_res), 0);													
						

		
         	 al_flip_display(); 
    /////////////////////////////////:
	
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) {
        
         //affichage du fond du menu 
		 al_draw_bitmap(bitmap_index[BMP_PRENDRE_MENU], float(200), float(36), 0);													
		
         for(int i=0;i<obj_nb;i++)
		 {
		 	   	al_draw_bitmap_region(bitmap_index[obj[i]->bmp_index],0.,0.,float(tile_res),float(tile_res), float(200+30), float(36+28+tile_res*i), 0);													
				al_draw_text(font,al_map_rgb(0,0,0),float(200+30+tile_res+30),float(36+28+tile_res*i+(tile_res-8)/2),0,obj[i]->objet_nom);
				if(obj_act_ind[i]!=-1)al_draw_text(font,al_map_rgb(0,0,0),float(200+30+tile_res+30+100),float(36+28+tile_res*i+(tile_res-8)/2),0,"sur cadavre");
				
		 }	
         	
		   		al_draw_bitmap(bitmap_index[BMP_FLECHE_MENU], float(200+310), float(36+28+selection*tile_res), 0);													
						

		
         	 al_flip_display(); 
			   
         affich = false;
        }
        
		al_wait_for_event(queue, &event);
		
		if (event.timer.source == moteur_jeu::timer_affichage) {
         affich = true;
        
         continue;
        }
		
		// GESTION DES ENTREE CLAVIER
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_PAD_8:
					
				selection--;
				if(selection<0)selection=0;	
				continue;
				//
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_PAD_2:
				selection++;	
				if(selection>=obj_nb)selection=obj_nb-1;	
				continue;
				
				case ALLEGRO_KEY_ESCAPE:
				return 0;
				
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
				if(obj_act_ind[selection]!=-1)
				{
			
				emission_action_prise_objet(action_tab,NB_MAX_ACTION,&ply1,NULL,monde[carte_active]->acteur_tab[obj_act_ind[selection]],obj_ind[selection], ply1.x,ply1.y);

				}
				else
				{
				
				emission_action_prise_objet(action_tab,NB_MAX_ACTION,&ply1,NULL,NULL,obj_ind[selection], ply1.x,ply1.y);

				}
				return 1;			
			}
	
		}
	}
	
return 0;
}

int moteur_jeu::gestion_loot(ALLEGRO_EVENT_QUEUE *queue)
{
    ALLEGRO_EVENT event;	
	bool affich=false;	
	int x=0;
	int y=0;
	acteur * act=NULL;
	int indiceobj[10];
	int nb_obj=0;
	
	// pas de stockage libre
		//pas si de stockage libre chez le joueur retourne 0
	if( stockage_libre(&ply1)==-1)
	{
			ajouter_mess_console("Pas de place dans l'inventaire pour prendre un objet", al_map_rgb(255,255,255));
		return 0;
	}
	// ****************************************************
	// CHOIX DE LA DIRECTION DU LOOT
	// **************************************************** 
	ajouter_mess_console("Donner la direction du mobilier dans lequel chercher", al_map_rgb(255,255,255));
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) 
        {
        	al_flip_display(); 
        	affich=false;
        }
        al_wait_for_event(queue, &event);
		
		if (event.timer.source == moteur_jeu::timer_affichage) {
         affich = true;
        
         continue;
        }
		// GESTION DES ENTREE CLAVIER
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_PAD_8:
				
				y=-1;	
					
				break;
				//
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_PAD_2:
				y=1;
				
				break;
				//
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_PAD_4:
				x=-1;
				
				break;
				//
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_PAD_6:
				x=1;
				
				break;
				//
				case ALLEGRO_KEY_PAD_1:
				x=-1;
				y=+1;
				break;
				//
				case ALLEGRO_KEY_PAD_3:
				x=+1;
				y=+1;
				break;
				//
				case ALLEGRO_KEY_PAD_7:
				x=-1;
				y=-1;
				break;
				//
				case ALLEGRO_KEY_PAD_9:
				x=+1;
				y=-1;
				break;
				case ALLEGRO_KEY_ESCAPE:
				return 0;
				
			
			}
	
		}
		if(x!=0|| y!=0)break;//sortie de la boucle while
	}
	/*****************************************************
	*****************************************************
	******************************************************/
	
	/*****************************************************
	****RECHERCHE DU CONTENEUR DANS LES ACTEURS**********
	******************************************************/
	
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(monde[carte_active]->acteur_tab[i]!=NULL)
		{
			if(monde[carte_active]->acteur_tab[i]->x==ply1.x+x && monde[carte_active]->acteur_tab[i]->y==ply1.y+y)
			{
				
				// Si le type de mobilier est un conteneur->
				if(monde[carte_active]->acteur_tab[i]->acteur_type<=ACTEUR_ARMOIRE_MEDIC)		
				{
					act=monde[carte_active]->acteur_tab[i];
					break;
				
				}
				
			}
			
		}
		
		
	}
	
	// Si pas d'objet trouve
	if(act==NULL)
	{
	ajouter_mess_console("... pas de mobilier dans cette direction ...", al_map_rgb(255,255,255));	
	return 0;
	}

	for(int i=0;i<MAX_EQUIPMNT;i++)
	{
		if(act->equipement[i]!=NULL)
		{
			indiceobj[nb_obj]=i;
			nb_obj++;
		}
	}


	if(nb_obj==0)
	{
		
	  ajouter_mess_console("...d'un rapide coup d'oeil, vous constatez que le conteneur est vide ...", al_map_rgb(255,255,255));
	  return 0;	
	}

   /*******************************************************
   ******************* CHOIX DE L'OBJET ******************
   *******************************************************/
   int selection=0;
   	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) {
        
         //affichage du fond du menu 
		 al_draw_bitmap(bitmap_index[BMP_PRENDRE_MENU], float(200), float(36), 0);													
		
         for(int i=0;i<nb_obj;i++)
		 {
		 	   	al_draw_bitmap_region(bitmap_index[act->equipement[indiceobj[i]]->bmp_index],0.,0.,float(tile_res),float(tile_res), float(200+30), float(36+28+tile_res*i), 0);													
				al_draw_text(font,al_map_rgb(0,0,0),float(200+30+tile_res+30),float(36+28+tile_res*i+(tile_res-8)/2),0,act->equipement[indiceobj[i]]->objet_nom);
				
				
		 }	
         	
		   		al_draw_bitmap(bitmap_index[BMP_FLECHE_MENU], float(200+310), float(36+28+selection*tile_res), 0);													
						

		
         	 al_flip_display(); 
			   
         affich = false;
        }
        
		al_wait_for_event(queue, &event);
		
		if (event.timer.source == moteur_jeu::timer_affichage) {
         affich = true;
        
         continue;
        }
		
		// GESTION DES ENTREE CLAVIER
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_PAD_8:
					
				selection--;
				if(selection<0)selection=0;	
				continue;
				//
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_PAD_2:
				selection++;	
				if(selection>=nb_obj)selection=nb_obj-1;	
				continue;
				
				case ALLEGRO_KEY_ESCAPE:
				return 0;
				
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
				
				emission_action_prise_objet(action_tab,NB_MAX_ACTION,&ply1,NULL,act,indiceobj[selection], ply1.x+x,ply1.y+y);
				return 1;			
			}
	
		}
	}
    	
}


///////////////////////////////
///////////////////////////////
int moteur_jeu::gestion_ouverturefermeture(ALLEGRO_EVENT_QUEUE *queue)
{
    ALLEGRO_EVENT event;	
	bool affich=false;	
	int x=0;
	int y=0;
	acteur * act=NULL;
	int indiceobj[10];
	int nb_obj=0;
	
	
	// ****************************************************
	// CHOIX DE LA DIRECTION DE L OUVERTURE FERMETURE DES PORTES
	// **************************************************** 
	ajouter_mess_console("Donner la direction de la porte", al_map_rgb(255,255,255));
	while(1)
	{
		if (affich && al_is_event_queue_empty(queue)) 
        {
        	al_flip_display(); 
        	affich=false;
        }
        al_wait_for_event(queue, &event);
		
		if (event.timer.source == moteur_jeu::timer_affichage) {
         affich = true;
        
         continue;
        }
		// GESTION DES ENTREE CLAVIER
		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_PAD_8:
				
				y=-1;	
					
				break;
				//
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_PAD_2:
				y=1;
				
				break;
				//
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_PAD_4:
				x=-1;
				
				break;
				//
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_PAD_6:
				x=1;
				
				break;
				//
				case ALLEGRO_KEY_PAD_1:
				x=-1;
				y=+1;
				break;
				//
				case ALLEGRO_KEY_PAD_3:
				x=+1;
				y=+1;
				break;
				//
				case ALLEGRO_KEY_PAD_7:
				x=-1;
				y=-1;
				break;
				//
				case ALLEGRO_KEY_PAD_9:
				x=+1;
				y=-1;
				break;
				case ALLEGRO_KEY_ESCAPE:
				return 0;
				
			
			}
	
		}
		if(x!=0|| y!=0)break;//sortie de la boucle while
	}
	/*****************************************************
	*****************************************************
	******************************************************/
	

	if(monde[carte_active]->donnee_carte[ply1.y+y][ply1.x+x].type==TILE_PORTE_FRAGILE ||
	   monde[carte_active]->donnee_carte[ply1.y+y][ply1.x+x].type==TILE_PORTE_NORMALE ||
	   monde[carte_active]->donnee_carte[ply1.y+y][ply1.x+x].type==TILE_PORTE_BLINDE)
	   {
	   	emission_action_ouvrir_fermer_porte(action_tab,NB_MAX_ACTION,&ply1,NULL, x, y);
	    return 1;
	   }
	   
	   
   	ajouter_mess_console("Pas de portes a cet endroit!", al_map_rgb(255,255,255));
	   
	   return 0;
}


// int calcul_champ_vision()
//
// Fonction pour calculer le 
// champ de vision autour du joueur.
// modifie l'ensemble des tuiles autour du joueur
//
int moteur_jeu::calcul_champ_vision()
{

	//cadrant NO
	for(int i=0;i<=ply1.y;i++)
	{
		lancer_rayon(ply1.x,ply1.y,0,i);
	}
	for(int i=0;i<ply1.x;i++)
	{
		lancer_rayon(ply1.x,ply1.y,i,0);
	}
	
	//cadrant NE
	for(int i=ply1.x;i<monde[carte_active]->x;i++)
	{
		lancer_rayon(ply1.x,ply1.y,i,0);
	} 
	for(int i=0;i<ply1.y;i++)
	{
		lancer_rayon(ply1.x,ply1.y,monde[carte_active]->x-1,i);
	}
	
	//cadrant SE
	
	for(int i=ply1.x;i<monde[carte_active]->x;i++)
	{
		lancer_rayon(ply1.x,ply1.y,i,monde[carte_active]->y-1);
	} 
	for(int i=ply1.y;i<monde[carte_active]->y;i++)
	{
		lancer_rayon(ply1.x,ply1.y,monde[carte_active]->x-1,i);
	}	


		//cadrant SO
	
	for(int i=0;i<=ply1.x;i++)
	{
		lancer_rayon(ply1.x,ply1.y,i,monde[carte_active]->y-1);
	} 
	for(int i=ply1.y;i<monde[carte_active]->y;i++)
	{
		lancer_rayon(ply1.x,ply1.y,0,i);
	}	
		
}


int moteur_jeu::lancer_rayon(int x1,int y1,int x2,int y2)
{
	
	int dx=abs(x2-x1);
	int dy=abs(y2-y1);
	int err=dx-dy;
	int e2;
	int signx=-1;
	int signy=-1;
	
	if(x2>x1)signx=1;
	if(y2>y1)signy=1;
	
	int x=x1;
	int y=y1;
	while(1)
	{
	//	printf("x %d, y %d\n",x,y);
		/*switch(cadran)
		{
		case 0:
		if(monde[carte_active]->donnee_carte[y-1][x].type==TILE_MUR ||
		   monde[carte_active]->donnee_carte[y-1][x].type==TILE_MUR_BRISE)
		   	
		break;
		
		case 1:	
		
		break;
		
		case 2:
			
		break;
		
		case 3:
			
		break;
		}*/
		monde[carte_active]->donnee_carte[y][x].decouvert=true;
		monde[carte_active]->donnee_carte[y][x].champ_vision=true;
		if(monde[carte_active]->donnee_carte[y][x].transparent==false)break;
		//ope sur position x;y
		if(x==x2 && y==y2)break;
		
		e2=2*err;
			if(e2>-dy)
			{
				err-=dy;
				x+=signx;
			}
		
		if(x==x2 && y==y2)
		{
			monde[carte_active]->donnee_carte[y][x].decouvert=true;
			monde[carte_active]->donnee_carte[y][x].champ_vision=true;
			//ope sur position;
		break;
		}
		if(e2<dx)
		{
			err+=dx;
			y+=signy;
		}
			
		
	}
/*	
   function line(x0, y0, x1, y1)
   dx := abs(x1-x0)
   dy := abs(y1-y0) 
   if x0 < x1 then sx := 1 else sx := -1
   if y0 < y1 then sy := 1 else sy := -1
   err := dx-dy
 
   loop
     plot(x0,y0)
     if x0 = x1 and y0 = y1 exit loop
     e2 := 2*err
     if e2 > -dy then 
       err := err - dy
       x0 := x0 + sx
     end if
     if x0 = x1 and y0 = y1 then 
       plot(x0,y0)
       exit loop
     end if
     if e2 < dx then 
       err := err + dx
       y0 := y0 + sy 
     end if
   end loop
	
	/*
	function line(x0, x1, y0, y1)
     int deltax := x1 - x0
     int deltay := y1 - y0
     real error := 0
     real deltaerr := abs (deltay / deltax)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
     int y := y0
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         if error = 0.5 then
             y := y + 1
             error := error - 1.0
*/
	
	return 0;
}



int moteur_jeu::suppr_artefact_vision()
{
	#define TILE_MUR			5
#define TILE_MUR_BRISE		6
	//gestion NO
	for( int i=0;i<=ply1.y;i++)
	{
		
		for(int j=0;j<=ply1.x;j++)
		{
			
			if(monde[carte_active]->donnee_carte[i][j].type==TILE_MUR ||
			 monde[carte_active]->donnee_carte[i][j].type==TILE_MUR_BRISE)
			{
						
				if(monde[carte_active]->donnee_carte[i][j].champ_vision==false &&
				 (monde[carte_active]->donnee_carte[i][j+1].champ_vision==true || monde[carte_active]->donnee_carte[i+1][j].champ_vision==true))
				 {
				 
					monde[carte_active]->donnee_carte[i][j].champ_vision=true;
					monde[carte_active]->donnee_carte[i][j].decouvert=true;	
				}
		
			}	
		}
		
	}
	
	
	//gestion NE
	for( int i=0;i<=ply1.y;i++)
	{
		
		for(int j=ply1.x;j<monde[carte_active]->x;j++)
		{
			
			if(monde[carte_active]->donnee_carte[i][j].type==TILE_MUR ||
			 monde[carte_active]->donnee_carte[i][j].type==TILE_MUR_BRISE)
			{
				if(monde[carte_active]->donnee_carte[i][j].champ_vision==false &&
				 (monde[carte_active]->donnee_carte[i][j-1].champ_vision==true || monde[carte_active]->donnee_carte[i+1][j].champ_vision==true))
				{
					
				
						monde[carte_active]->donnee_carte[i][j].champ_vision=true;
						monde[carte_active]->donnee_carte[i][j].decouvert=true;
						
					
				}
			}
		}
		
	}
	
	//gestion SE
	for( int i=ply1.y;i<monde[carte_active]->y;i++)
	{
		
		for(int j=ply1.x;j<monde[carte_active]->x;j++)
		{
			
			if(monde[carte_active]->donnee_carte[i][j].type==TILE_MUR ||
			 monde[carte_active]->donnee_carte[i][j].type==TILE_MUR_BRISE)
			{
				if(monde[carte_active]->donnee_carte[i][j].champ_vision==false &&
				 (monde[carte_active]->donnee_carte[i][j-1].champ_vision==true || monde[carte_active]->donnee_carte[i-1][j].champ_vision==true))
				{
					
				
						monde[carte_active]->donnee_carte[i][j].champ_vision=true;
						monde[carte_active]->donnee_carte[i][j].decouvert=true;
						
					
				}
		
			}
		}
		
	}
	
	
	//gestion SO
	for( int i=ply1.y;i<monde[carte_active]->y;i++)
	{
		
		for(int j=0;j<=ply1.x;j++)
		{
			
			if(monde[carte_active]->donnee_carte[i][j].type==TILE_MUR ||
			 monde[carte_active]->donnee_carte[i][j].type==TILE_MUR_BRISE)
			{
				if(monde[carte_active]->donnee_carte[i][j].champ_vision==false &&
				 (monde[carte_active]->donnee_carte[i][j+1].champ_vision==true || monde[carte_active]->donnee_carte[i-1][j].champ_vision==true))
				{
					
				
						monde[carte_active]->donnee_carte[i][j].champ_vision=true;
						monde[carte_active]->donnee_carte[i][j].decouvert=true;
						
					
				}
			}
		}
		
	}
}











////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//Fonction d'affichage de texte.
int affichage_texte(int x,int y, int larg, int ligne_h,int char_lar, char *source)
{
	ALLEGRO_USTR *src= al_ustr_new(source);
	ALLEGRO_USTR *aff=al_ustr_new("");
	
	
	int nb_char_ligne=larg/char_lar;
	int lcnt=0;
	
	
	while(lcnt*nb_char_ligne<al_ustr_size(src))
	{
		al_ustr_assign(aff,src);

		al_ustr_truncate(aff, (lcnt+1)*nb_char_ligne);		
		al_ustr_remove_range(aff, 0,lcnt*nb_char_ligne);
		al_draw_ustr(font,al_map_rgb(0,0,0),float(x),float(y+lcnt*ligne_h),0,aff);
		lcnt++;
	}
	
	al_ustr_free(src);
	al_ustr_free(aff);
		
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/************************************************************************************************
****************************FONCTIONS DE TRI QUICKSORT ******************************************
************************************************************************************************/


//fonction d'échange d'argument. Celle ci sont sorties des fonctions quick sort pour ne pas surcharger la pile.

void iechanger(int *tableau, int a, int b)
{
    int temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

/* FONCTION DE TRI DES ACTIONS TERMINEE
*/

void int_indquicksort(action *act,int *tableauindice, int debut, int fin,bool croissant)
{
    int gauche = debut-1;
    int droite = fin+1;
    
    /* Si le tableau est de longueur nulle, il n'y a rien à faire. */
    if(debut >= fin)
        return;
        
     const int pivot = act[tableauindice[debut]].point_action;
   
    /* Sinon, on parcourt le tableau, une fois de droite à gauche, et une
       autre de gauche à droite, à la recherche d'éléments mal placés,
       que l'on permute. Si les deux parcours se croisent, on arrête. */
    while(1)
    {
		if(croissant)
		{
		 do droite--; while(act[tableauindice[droite]].point_action > pivot);
         do gauche++; while(act[tableauindice[gauche]].point_action < pivot);
		}
		else
		{
		 do droite--; while(act[tableauindice[droite]].point_action < pivot);
         do gauche++; while(act[tableauindice[gauche]].point_action > pivot);
		}
        if(gauche < droite)
            iechanger(tableauindice, gauche, droite);
        else break;
    }
    
   /*  for(int i = 0; i <fin; i++)
    {
	printf("%d ", tableauvaleur[tableauindice[i]]);
    }
    putchar('\n');
    */
    /* Maintenant, tous les éléments inférieurs au pivot sont avant ceux
       supérieurs au pivot. On a donc deux groupes de cases à trier. On utilise
       pour cela... la méthode quickSort elle-même ! */
    int_indquicksort(act,tableauindice, debut, droite,croissant);
    int_indquicksort(act,tableauindice, droite+1, fin,croissant);
}

