#include <time.h>
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

int main()
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *queue;//file d'attente des evenement alleg
	ALLEGRO_EVENT event;
//int seed=time(NULL);
//printf("%d",seed);
//init_genrand(seed);	
//INITIALISATION DE LA LIBRAIRIE ALLEGRO***********************	
   if (!al_init()) {
      printf("erreur initialisation ALLEGRO");
      return 1;
   }
   if (!al_install_audio() || !al_reserve_samples(128)) {
     printf("erreur d'initialisation du son!");
     return 2;
     
   }
   
   	al_init_acodec_addon();
   	al_init_image_addon();
   
    al_init_primitives_addon();
    al_init_font_addon();
    
    al_install_mouse();
    al_install_keyboard();

// **********************************************************

	// chargement de la font standard allegro;
    font = al_load_bitmap_font("a4_font.tga");
    
    
  // al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

/********** CHOIX DU MODE D' AFFICHAGE ET CREATION DE CELUI CI *************
***************************************************************************/

	if(moteur_jeu::plein_ecran)
	 al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	else
	al_set_new_display_flags(ALLEGRO_WINDOWED);

// Creation du mode d'affichage	 
   display = al_create_display(moteur_jeu::ecranX, moteur_jeu::ecranY);
   if (display==NULL) {
      printf("impossible d'initialiser l'affichage");
      return 3;
   }
   al_set_window_title(display, "Projet Medusa");

/******************************************************************************
******************************************************************************/

/*************************INITIALISATION DES DONNES DU JEU*******************/
moteur_jeu::creation_contenu();
moteur_jeu::init_alleg_objects(display);
//////////////////////////////////////////////////////////////////////////////
/*  moteur_jeu::timer_affichage = al_create_timer(1.0 / float(moteur_jeu::frequence_affichage));
	al_start_timer(moteur_jeu::timer_affichage)	;

  queue = al_create_event_queue(); //creation de la queue d'evenement
   al_register_event_source(queue, al_get_display_event_source(display)); // enregistement 
   al_register_event_source(queue, al_get_keyboard_event_source());// des divers fournisseur d evenements
   al_register_event_source(queue, al_get_mouse_event_source());
   al_register_event_source(queue, al_get_timer_event_source(moteur_jeu::timer_affichage));
*/

//moteur_jeu::monde[0]=cree_carte_test();

moteur_jeu::monde[0]=creer_carte(0,14,68);

   //demarrage du timer

	//moteur_jeu::ply1.vie=100;
	//moteur_jeu::ply1.vitesse=100;
	creer_jean_dupont(&moteur_jeu::ply1);
//	moteur_jeu::placer_joueur(30,30);
moteur_jeu::ply1.x=37;
moteur_jeu::ply1.y=11;
	moteur_jeu::centrer_camera_joueur();
	moteur_jeu::calcul_champ_vision();
	moteur_jeu::suppr_artefact_vision();
	
	int x,y;
	bool t;
	strcpy(moteur_jeu::ply1.nom,"gregoire");
	moteur_jeu::ply1.equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1, -1, OBJ_CHAUSSURE);
		moteur_jeu::ply1.equipement[EQUIPMNT_PANTALON]=creer_objet(-1, -1, OBJ_PANTALON);	
		moteur_jeu::ply1.equipement[EQUIPMNT_MAIN_D]=creer_objet(-1, -1, OBJ_MITRAILLETTE);	
	moteur_jeu::ply1.equipement[EQUIPMNT_MAIN_G]=creer_objet(-1, -1, OBJ_PANTALON);	
	
	moteur_jeu::ply1.hemorragie=true;
	
	
	moteur_jeu::ply1.sac=true;
	moteur_jeu::ply1.sac_contenu[1]=creer_objet(-1, -1, OBJ_MUNITION_PISTO);
	moteur_jeu::ply1.sac_contenu[2]=creer_objet(-1, -1, OBJ_PISTOLET);
	moteur_jeu::ply1.sac_contenu[0]=creer_objet(-1, -1, OBJ_IMPLANT_FORCE);
	moteur_jeu::ply1.sac_contenu[3]=creer_objet(-1, -1, OBJ_MEDIPACK);
	moteur_jeu::ply1.sac_contenu[4]=creer_objet(-1, -1, OBJ_PANTALON);
	
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(moteur_jeu::monde[0]->acteur_tab[i]==NULL)
		{
			moteur_jeu::monde[0]->acteur_tab[i]=placer_personnage(27,27,ACTEUR_CHIEN);
			break;
		}
	}
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(moteur_jeu::monde[0]->acteur_tab[i]==NULL)
		{
			moteur_jeu::monde[0]->acteur_tab[i]=placer_mobilier(23,29,ACTEUR_CONTENEUR_ACIDE);
			break;
		}
	}
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(moteur_jeu::monde[0]->acteur_tab[i]==NULL)
		{
			moteur_jeu::monde[0]->acteur_tab[i]=placer_mobilier(25,27,ACTEUR_BOUTEILLE_GAZ);
			break;
		}
	}
//	moteur_jeu::gestion_ramassage(queue);
//	moteur_jeu::choix_cible(moteur_jeu::queue,&x,&y,&t); //OK
 //   moteur_jeu::gestion_inventaire(moteur_jeu::queue); // OK
 //carte *tt=creer_carte(0,8,50);
 //system("pause");
    
    placer_tile(&moteur_jeu::monde[0]->donnee_carte[25][25],TILE_VITRE); 
    
    gestionnaire_message::ajout_message("Voila un premier message pour verifier si la console fonctionne correctement. On fait une ligne assez longue de maniere a voir si les differents messages sont coupe convenablements",al_map_rgb(255,0,0));

gestionnaire_message::ajout_message("Pimpam poum second message",al_map_rgb(255,0,0));
gestionnaire_message::ajout_message("ET DE TROIS MESSAGES!",al_map_rgb(255,255,0));
gestionnaire_message::ajout_message("Jamais trois sans quatre!",al_map_rgb(255,255,255));
gestionnaire_message::ajout_message("Ou va t on s arreter!!!!",al_map_rgb(0,255,0));
gestionnaire_message::ajout_message("BlBlaBla!!!!",al_map_rgb(255,255,255));
//gestionnaire_message::ajout_message("Bliblibli!!!!",al_map_rgb(255,255,255));

message *m=gestionnaire_message::recup_dernier_message();

printf(m->mess);
	  printf("test mobilier autour  %d\n", pas_de_mobilier_autour(moteur_jeu::monde[0], 39,11));

for(int i=0;i<NB_MAX_ACTEUR;i++)
{
	if(moteur_jeu::monde[0]->acteur_tab[i]!=NULL)
	printf("x %d,y %d\n",moteur_jeu::monde[0]->acteur_tab[i]->x,moteur_jeu::monde[0]->acteur_tab[i]->y );
	
	
}
//system("pause");
	moteur_jeu::monde[0]->objet_tab[0]=creer_objet(37, 11, OBJ_IMPLANT_FORCE);
	moteur_jeu::monde[0]->objet_tab[1]=creer_objet(37, 11, OBJ_CLE);

	moteur_jeu::jeu();
//	moteur_jeu::gestion_action_joueur(queue);
	
/*	while (1) {
        
        al_wait_for_event(queue, &event);
 		
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
            
         moteur_jeu::affiche_tuiles();  
         moteur_jeu::affiche_joueur();
          moteur_jeu::affiche_inventaire();
   
	 al_flip_display();   
            
        

	 
    }
  */  
//	printf("%d",moteur_jeu::chargement_bitmap());
//	system("pause");

}
