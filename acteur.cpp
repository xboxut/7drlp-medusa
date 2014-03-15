#include <string.h>
#include <stdlib.h>

#include "mt19937ar.h"

#include "const_act_joueur.h"
#include "const_bmp_index.h"

#include "objet.h"
#include "acteur.h"



// DEFINITION DE L ENSEMBLE DES ACTEUR PREFAB, DE LEUR NOM ET DESCRIPTION
 acteur prefab_acteur[MAX_ACTEUR];
 char *nom_acteur[MAX_ACTEUR];
 char *description_acteur[MAX_ACTEUR];
////////////////////////////////////////////////////////

// Constructeur destructeur des acteurs.
acteur::acteur()
{
}
acteur::~acteur()
{
}
///////////////////////////////////////

int creer_prefab_acteurs()
{
	/*
	#define ACTEUR_BUREAU						0
#define ACTEUR_ETAGERE						1
#define ACTEUR_TABLE_OPERATION				2
#define ACTEUR_TABLE						3
#define ACTEUR_RACK_ARME					4
#define ACTEUR_ARMOIRE_MEDIC				5
#define ACTEUR_CONSOLE_INFO					6
#define ACTEUR_BOUTEILLE_GAZ				7
#define ACTEUR_CONTENEUR_ACIDE				8
#define ACTEUR_LAVABO						9
#define ACTEUR_TOILETTES					10
#define ACTEUR_LIT							11
		
	*/
	nom_acteur[ACTEUR_BUREAU]=new char[strlen("un bureau")+1];
	strcpy(nom_acteur[ACTEUR_BUREAU],"un bureau");
	
	description_acteur[ACTEUR_BUREAU]=new char[strlen("Un bureau, couvert de papier. Les tiroirs contiennent uniquement des dossiers, quelques stylos, et une bouteille de gnole.")+1];
	strcpy(description_acteur[ACTEUR_BUREAU],"Un bureau, couvert de papier. Les tiroirs contiennent uniquement des dossiers, quelques stylos, et une bouteille de gnole.");
	
	prefab_acteur[ACTEUR_BUREAU].acteur_type=ACTEUR_BUREAU;
	prefab_acteur[ACTEUR_BUREAU].bmp_index=BMP_BUREAU;
	prefab_acteur[ACTEUR_BUREAU].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_BUREAU].x=-1;
	prefab_acteur[ACTEUR_BUREAU].y=-1;
	prefab_acteur[ACTEUR_BUREAU].bloquant=true;
	prefab_acteur[ACTEUR_BUREAU].frce=0;
	prefab_acteur[ACTEUR_BUREAU].dxtrt=0;
	prefab_acteur[ACTEUR_BUREAU].vitesse=0;
	prefab_acteur[ACTEUR_BUREAU].vie=0;
	prefab_acteur[ACTEUR_BUREAU].vie_max=0;
	prefab_acteur[ACTEUR_BUREAU].coup_critique=0;
	prefab_acteur[ACTEUR_BUREAU].hemorragie=false;
	prefab_acteur[ACTEUR_BUREAU].hemorragie_tic=0;
	prefab_acteur[ACTEUR_BUREAU].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_BUREAU].fuite=false;
	prefab_acteur[ACTEUR_BUREAU].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_BUREAU].equipement[i]=NULL;
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_ETAGERE]=new char[strlen("etagere")+1];
	strcpy(nom_acteur[ACTEUR_ETAGERE],"etagere");
	
	description_acteur[ACTEUR_ETAGERE]=new char[strlen("Une etagere contenant des livres, du bric et du broc. Au milieux des ouvrages et des documents, des bibelots en cristal cotoient des tetes reduites et des seringues usagees.")+1];
	strcpy(description_acteur[ACTEUR_ETAGERE],"Une etagere contenant des livres, du bric et du broc. Au milieux des ouvrages et des documents, des bibelots en cristal cotoient des tetes reduites et des seringues usagees.");
	
	prefab_acteur[ACTEUR_ETAGERE].acteur_type=ACTEUR_ETAGERE;
	prefab_acteur[ACTEUR_ETAGERE].bmp_index=BMP_ETAGERE;
	prefab_acteur[ACTEUR_ETAGERE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_ETAGERE].x=-1;
	prefab_acteur[ACTEUR_ETAGERE].y=-1;
	prefab_acteur[ACTEUR_ETAGERE].bloquant=true;
	prefab_acteur[ACTEUR_ETAGERE].frce=0;
	prefab_acteur[ACTEUR_ETAGERE].dxtrt=0;
	prefab_acteur[ACTEUR_ETAGERE].vitesse=0;
	prefab_acteur[ACTEUR_ETAGERE].vie=0;
	prefab_acteur[ACTEUR_ETAGERE].vie_max=0;
	prefab_acteur[ACTEUR_ETAGERE].coup_critique=0;
	prefab_acteur[ACTEUR_ETAGERE].hemorragie=false;
	prefab_acteur[ACTEUR_ETAGERE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_ETAGERE].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_ETAGERE].fuite=false;
	prefab_acteur[ACTEUR_ETAGERE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_ETAGERE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_TABLE_OPERATION]=new char[strlen("table d'operation")+1];
	strcpy(nom_acteur[ACTEUR_TABLE_OPERATION],"table d'operation");
	
	description_acteur[ACTEUR_TABLE_OPERATION]=new char[strlen("Une table d'operation en acier inoxydable. Des taches de sang la parseme.")+1];
	strcpy(description_acteur[ACTEUR_TABLE_OPERATION],"Une table d'operation en acier inoxydable. Des taches de sang la parseme.");
	
	prefab_acteur[ACTEUR_TABLE_OPERATION].acteur_type=ACTEUR_TABLE_OPERATION;
	prefab_acteur[ACTEUR_TABLE_OPERATION].bmp_index=BMP_TABLE_OPERATION;
	prefab_acteur[ACTEUR_TABLE_OPERATION].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].x=-1;
	prefab_acteur[ACTEUR_TABLE_OPERATION].y=-1;
	prefab_acteur[ACTEUR_TABLE_OPERATION].bloquant=true;
	prefab_acteur[ACTEUR_TABLE_OPERATION].frce=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].dxtrt=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].vitesse=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].vie=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].vie_max=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].coup_critique=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].hemorragie=false;
	prefab_acteur[ACTEUR_TABLE_OPERATION].hemorragie_tic=0;
	prefab_acteur[ACTEUR_TABLE_OPERATION].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_TABLE_OPERATION].fuite=false;
	prefab_acteur[ACTEUR_TABLE_OPERATION].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_TABLE_OPERATION].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_TABLE]=new char[strlen("table")+1];
	strcpy(nom_acteur[ACTEUR_TABLE],"table");
	
	description_acteur[ACTEUR_TABLE]=new char[strlen("Une table de travail, couverte de marque de tasses.")+1];
	strcpy(description_acteur[ACTEUR_TABLE],"Une table de travail, couverte de marque de tasses.");
	
	prefab_acteur[ACTEUR_TABLE].acteur_type=ACTEUR_TABLE;
	prefab_acteur[ACTEUR_TABLE].bmp_index=BMP_TABLE;
	prefab_acteur[ACTEUR_TABLE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_TABLE].x=-1;
	prefab_acteur[ACTEUR_TABLE].y=-1;
	prefab_acteur[ACTEUR_TABLE].bloquant=true;
	prefab_acteur[ACTEUR_TABLE].frce=0;
	prefab_acteur[ACTEUR_TABLE].dxtrt=0;
	prefab_acteur[ACTEUR_TABLE].vitesse=0;
	prefab_acteur[ACTEUR_TABLE].vie=0;
	prefab_acteur[ACTEUR_TABLE].vie_max=0;
	prefab_acteur[ACTEUR_TABLE].coup_critique=0;
	prefab_acteur[ACTEUR_TABLE].hemorragie=false;
	prefab_acteur[ACTEUR_TABLE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_TABLE].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_TABLE].fuite=false;
	prefab_acteur[ACTEUR_TABLE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_TABLE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_RACK_ARME]=new char[strlen("rack d'armes")+1];
	strcpy(nom_acteur[ACTEUR_RACK_ARME],"rack d'armes");
	
	description_acteur[ACTEUR_RACK_ARME]=new char[strlen("Un rack destine a accueillir des armes. Une barre, habituellement cadenacee, permet de bloquer l'accès aux fusils")+1];
	strcpy(description_acteur[ACTEUR_RACK_ARME],"Un rack destine a accueillir des armes. Une barre, habituellement cadenacee, permet de bloquer l'accès aux fusils");
	
	prefab_acteur[ACTEUR_RACK_ARME].acteur_type=ACTEUR_RACK_ARME;
	prefab_acteur[ACTEUR_RACK_ARME].bmp_index=BMP_RACK_ARME;
	prefab_acteur[ACTEUR_RACK_ARME].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_RACK_ARME].x=-1;
	prefab_acteur[ACTEUR_RACK_ARME].y=-1;
	prefab_acteur[ACTEUR_RACK_ARME].bloquant=true;
	prefab_acteur[ACTEUR_RACK_ARME].frce=0;
	prefab_acteur[ACTEUR_RACK_ARME].dxtrt=0;
	prefab_acteur[ACTEUR_RACK_ARME].vitesse=0;
	prefab_acteur[ACTEUR_RACK_ARME].vie=0;
	prefab_acteur[ACTEUR_RACK_ARME].vie_max=0;
	prefab_acteur[ACTEUR_RACK_ARME].coup_critique=0;
	prefab_acteur[ACTEUR_RACK_ARME].hemorragie=false;
	prefab_acteur[ACTEUR_RACK_ARME].hemorragie_tic=0;
	prefab_acteur[ACTEUR_RACK_ARME].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_RACK_ARME].fuite=false;
	prefab_acteur[ACTEUR_RACK_ARME].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_RACK_ARME].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_ARMOIRE_MEDIC]=new char[strlen("armoire a pharmacie")+1];
	strcpy(nom_acteur[ACTEUR_ARMOIRE_MEDIC],"armoire a pharmacie");
	
	description_acteur[ACTEUR_ARMOIRE_MEDIC]=new char[strlen("Une armoire a pharmacie; elle contient l'ensemble des instruments et des medicaments necessaires aux soins des petits bobos.")+1];
	strcpy(description_acteur[ACTEUR_ARMOIRE_MEDIC],"Une armoire a pharmacie; elle contient l'ensemble des instruments et des medicaments necessaires aux soins des petits bobos.");
	
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].acteur_type=ACTEUR_ARMOIRE_MEDIC;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].bmp_index=BMP_ARMOIRE_MEDIC;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].x=-1;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].y=-1;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].bloquant=true;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].frce=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].dxtrt=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].vitesse=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].vie=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].vie_max=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].coup_critique=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].hemorragie=false;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].hemorragie_tic=0;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].fuite=false;
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_ARMOIRE_MEDIC].equipement[i]=NULL;
///////////////////////////////////////////////////////////	
		
/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_CONSOLE_INFO]=new char[strlen("console informatique")+1];
	strcpy(nom_acteur[ACTEUR_CONSOLE_INFO],"console informatique");
	
	description_acteur[ACTEUR_CONSOLE_INFO]=new char[strlen("Une console informatique, avec de nombreux claviers et ecrans.")+1];
	strcpy(description_acteur[ACTEUR_CONSOLE_INFO],"Une console informatique, avec de nombreux claviers et ecrans.");
	
	prefab_acteur[ACTEUR_CONSOLE_INFO].acteur_type=ACTEUR_CONSOLE_INFO;
	prefab_acteur[ACTEUR_CONSOLE_INFO].bmp_index=BMP_CONSOLE_INFO;
	prefab_acteur[ACTEUR_CONSOLE_INFO].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].x=-1;
	prefab_acteur[ACTEUR_CONSOLE_INFO].y=-1;
	prefab_acteur[ACTEUR_CONSOLE_INFO].bloquant=true;
	prefab_acteur[ACTEUR_CONSOLE_INFO].frce=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].dxtrt=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].vitesse=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].vie=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].vie_max=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].coup_critique=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].hemorragie=false;
	prefab_acteur[ACTEUR_CONSOLE_INFO].hemorragie_tic=0;
	prefab_acteur[ACTEUR_CONSOLE_INFO].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_CONSOLE_INFO].fuite=false;
	prefab_acteur[ACTEUR_CONSOLE_INFO].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_CONSOLE_INFO].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_BOUTEILLE_GAZ]=new char[strlen("bouteille de gaz")+1];
	strcpy(nom_acteur[ACTEUR_BOUTEILLE_GAZ],"bouteille de gaz");
	
	description_acteur[ACTEUR_BOUTEILLE_GAZ]=new char[strlen("Une bouteille de dihydrogene. Attention, cette bouteille contient du gaz tres inflammable, evitez de l'endommager.")+1];
	strcpy(description_acteur[ACTEUR_BOUTEILLE_GAZ],"Une bouteille de dihydrogene. Attention, cette bouteille contient du gaz tres inflammable, evitez de l'endommager.");
	
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].acteur_type=ACTEUR_BOUTEILLE_GAZ;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].bmp_index=BMP_BOUTEILLE_GAZ;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].x=-1;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].y=-1;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].bloquant=true;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].frce=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].dxtrt=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].vitesse=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].vie=40;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].vie_max=40;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].coup_critique=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].hemorragie=false;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].hemorragie_tic=0;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].fuite=false;
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_BOUTEILLE_GAZ].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_CONTENEUR_ACIDE]=new char[strlen("conteneur d'acide")+1];
	strcpy(nom_acteur[ACTEUR_CONTENEUR_ACIDE],"conteneur d'acide");
	
	description_acteur[ACTEUR_CONTENEUR_ACIDE]=new char[strlen("Un conteneur en plastique rempli d'acide nitrique.")+1];
	strcpy(description_acteur[ACTEUR_CONTENEUR_ACIDE],"Un conteneur en plastique rempli d'acide nitrique.");
	
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].acteur_type=ACTEUR_CONTENEUR_ACIDE;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].bmp_index=BMP_CONTENEUR_ACIDE;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].x=-1;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].y=-1;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].bloquant=true;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].frce=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].dxtrt=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].vitesse=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].vie=20;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].vie_max=20;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].coup_critique=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].hemorragie=false;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].fuite=false;
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_CONTENEUR_ACIDE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_LAVABO]=new char[strlen("lavabo")+1];
	strcpy(nom_acteur[ACTEUR_LAVABO],"lavabo");
	
	description_acteur[ACTEUR_LAVABO]=new char[strlen("Un lavabo en email blanc, a la proprete douteuse.")+1];
	strcpy(description_acteur[ACTEUR_LAVABO],"Un lavabo en email blanc, a la proprete douteuse.");
	
	prefab_acteur[ACTEUR_LAVABO].acteur_type=ACTEUR_LAVABO;
	prefab_acteur[ACTEUR_LAVABO].bmp_index=BMP_LAVABO;
	prefab_acteur[ACTEUR_LAVABO].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_LAVABO].x=-1;
	prefab_acteur[ACTEUR_LAVABO].y=-1;
	prefab_acteur[ACTEUR_LAVABO].bloquant=true;
	prefab_acteur[ACTEUR_LAVABO].frce=0;
	prefab_acteur[ACTEUR_LAVABO].dxtrt=0;
	prefab_acteur[ACTEUR_LAVABO].vitesse=0;
	prefab_acteur[ACTEUR_LAVABO].vie=0;
	prefab_acteur[ACTEUR_LAVABO].vie_max=0;
	prefab_acteur[ACTEUR_LAVABO].coup_critique=0;
	prefab_acteur[ACTEUR_LAVABO].hemorragie=false;
	prefab_acteur[ACTEUR_LAVABO].hemorragie_tic=0;
	prefab_acteur[ACTEUR_LAVABO].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_LAVABO].fuite=false;
	prefab_acteur[ACTEUR_LAVABO].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_LAVABO].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_TOILETTES]=new char[strlen("toilettes")+1];
	strcpy(nom_acteur[ACTEUR_TOILETTES],"toilettes");
	
	description_acteur[ACTEUR_TOILETTES]=new char[strlen("Des toilettes en email. Au vu des taches qui les parsemes, le dernier utilisateur a du avoir une experience malheureuse avec la nourriture asiatique.")+1];
	strcpy(description_acteur[ACTEUR_TOILETTES],"Des toilettes en email. Au vu des taches qui les parsemes, le dernier utilisateur a du avoir une experience malheureuse avec la nourriture asiatique.");
	
	prefab_acteur[ACTEUR_TOILETTES].acteur_type=ACTEUR_TOILETTES;
	prefab_acteur[ACTEUR_TOILETTES].bmp_index=BMP_TOILETTES;
	prefab_acteur[ACTEUR_TOILETTES].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_TOILETTES].x=-1;
	prefab_acteur[ACTEUR_TOILETTES].y=-1;
	prefab_acteur[ACTEUR_TOILETTES].bloquant=true;
	prefab_acteur[ACTEUR_TOILETTES].frce=0;
	prefab_acteur[ACTEUR_TOILETTES].dxtrt=0;
	prefab_acteur[ACTEUR_TOILETTES].vitesse=0;
	prefab_acteur[ACTEUR_TOILETTES].vie=0;
	prefab_acteur[ACTEUR_TOILETTES].vie_max=0;
	prefab_acteur[ACTEUR_TOILETTES].coup_critique=0;
	prefab_acteur[ACTEUR_TOILETTES].hemorragie=false;
	prefab_acteur[ACTEUR_TOILETTES].hemorragie_tic=0;
	prefab_acteur[ACTEUR_TOILETTES].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_TOILETTES].fuite=false;
	prefab_acteur[ACTEUR_TOILETTES].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_TOILETTES].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_LIT]=new char[strlen("lit")+1];
	strcpy(nom_acteur[ACTEUR_LIT],"lit");
	
	description_acteur[ACTEUR_LIT]=new char[strlen("Un lit de camp.")+1];
	strcpy(description_acteur[ACTEUR_LIT],"Un lit de camp.");
	
	prefab_acteur[ACTEUR_LIT].acteur_type=ACTEUR_LIT;
	prefab_acteur[ACTEUR_LIT].bmp_index=BMP_LIT;
	prefab_acteur[ACTEUR_LIT].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_LIT].x=-1;
	prefab_acteur[ACTEUR_LIT].y=-1;
	prefab_acteur[ACTEUR_LIT].bloquant=true;
	prefab_acteur[ACTEUR_LIT].frce=0;
	prefab_acteur[ACTEUR_LIT].dxtrt=0;
	prefab_acteur[ACTEUR_LIT].vitesse=0;
	prefab_acteur[ACTEUR_LIT].vie=0;
	prefab_acteur[ACTEUR_LIT].vie_max=0;
	prefab_acteur[ACTEUR_LIT].coup_critique=0;
	prefab_acteur[ACTEUR_LIT].hemorragie=false;
	prefab_acteur[ACTEUR_LIT].hemorragie_tic=0;
	prefab_acteur[ACTEUR_LIT].comportement_type=CMPRTMNT_RIEN;
	prefab_acteur[ACTEUR_LIT].fuite=false;
	prefab_acteur[ACTEUR_LIT].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_LIT].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
//DEFINITION DES PNJ///////////////////////////
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_SCIENTIFIQUE_BASE]=new char[strlen("scientifique")+1];
	strcpy(nom_acteur[ACTEUR_SCIENTIFIQUE_BASE],"scientifique");
	
	description_acteur[ACTEUR_SCIENTIFIQUE_BASE]=new char[strlen("Un scientifique a l'air particulierement bete et mauvais.")+1];
	strcpy(description_acteur[ACTEUR_SCIENTIFIQUE_BASE],"Un scientifique a l'air particulierement bete et mauvais.");
	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].acteur_type=ACTEUR_SCIENTIFIQUE_BASE;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].bmp_index=BMP_SCIENTIFIQUE;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].x=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].y=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].bloquant=true;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].frce=8;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].dxtrt=15;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].vitesse=100;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].vie=30;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].vie_max=30;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].coup_critique=10;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].hemorragie=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].comportement_type=CMPRTMNT_AGRESSIF_FUYARD;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].fuite=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_BASE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX]=new char[strlen("scientifique")+1];
	strcpy(nom_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX],"scientifique");
	
	description_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX]=new char[strlen("Un scientifique a l'air particulierement bete et mauvais.")+1];
	strcpy(description_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX],"Un scientifique a l'air particulierement bete et mauvais.");
	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].acteur_type=ACTEUR_SCIENTIFIQUE_PEUREUX;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].bmp_index=BMP_SCIENTIFIQUE;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].x=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].y=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].bloquant=true;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].frce=8;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].dxtrt=15;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].vitesse=100;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].vie=15;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].vie_max=15;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].coup_critique=3;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].hemorragie=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].hemorragie_tic=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].comportement_type=CMPRTMNT_FUYARD;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].fuite=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_PEUREUX].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_SCIENTIFIQUE_FOU]=new char[strlen("scientifique")+1];
	strcpy(nom_acteur[ACTEUR_SCIENTIFIQUE_FOU],"scientifique");
	
	description_acteur[ACTEUR_SCIENTIFIQUE_FOU]=new char[strlen("Un scientifique a l'air particulierement bete et mauvais. Une lueur inquietante brille dans ses yeux.")+1];
	strcpy(description_acteur[ACTEUR_SCIENTIFIQUE_FOU],"Un scientifique a l'air particulierement bete et mauvais. Une lueur inquietante brille dans ses yeux.");
	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].acteur_type=ACTEUR_SCIENTIFIQUE_FOU;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].bmp_index=BMP_SCIENTIFIQUE;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].x=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].y=-1;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].bloquant=true;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].frce=11;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].dxtrt=15;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].vitesse=110;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].vie=25;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].vie_max=25;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].coup_critique=20;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].hemorragie=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].hemorragie_tic=0;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].fuite=false;
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_SCIENTIFIQUE_FOU].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////
	nom_acteur[ACTEUR_INFIRMIER]=new char[strlen("infirmier")+1];
	strcpy(nom_acteur[ACTEUR_INFIRMIER],"infirmier");
	
	description_acteur[ACTEUR_INFIRMIER]=new char[strlen("Un infirmier a la carrure impressionnante.")+1];
	strcpy(description_acteur[ACTEUR_INFIRMIER],"Un infirmier a la carrure impressionnante.");
	
	prefab_acteur[ACTEUR_INFIRMIER].acteur_type=ACTEUR_INFIRMIER;
	prefab_acteur[ACTEUR_INFIRMIER].bmp_index=BMP_INFIRMIER;
	prefab_acteur[ACTEUR_INFIRMIER].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_INFIRMIER].x=-1;
	prefab_acteur[ACTEUR_INFIRMIER].y=-1;
	prefab_acteur[ACTEUR_INFIRMIER].bloquant=true;
	prefab_acteur[ACTEUR_INFIRMIER].frce=13;
	prefab_acteur[ACTEUR_INFIRMIER].dxtrt=11;
	prefab_acteur[ACTEUR_INFIRMIER].vitesse=90;
	prefab_acteur[ACTEUR_INFIRMIER].vie=50;
	prefab_acteur[ACTEUR_INFIRMIER].vie_max=50;
	prefab_acteur[ACTEUR_INFIRMIER].coup_critique=23;
	prefab_acteur[ACTEUR_INFIRMIER].hemorragie=false;
	prefab_acteur[ACTEUR_INFIRMIER].hemorragie_tic=0;
	prefab_acteur[ACTEUR_INFIRMIER].comportement_type=CMPRTMNT_AGRESSIF_LIMIT;
	prefab_acteur[ACTEUR_INFIRMIER].fuite=false;
	prefab_acteur[ACTEUR_INFIRMIER].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_INFIRMIER].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_INFIRMIER_FOU]=new char[strlen("infirmier")+1];
	strcpy(nom_acteur[ACTEUR_INFIRMIER_FOU],"infirmier");
	
	description_acteur[ACTEUR_INFIRMIER_FOU]=new char[strlen("Un infirmier a la carrure impressionnante.")+1];
	strcpy(description_acteur[ACTEUR_INFIRMIER_FOU],"Un infirmier a la carrure impressionnante.");
	
	prefab_acteur[ACTEUR_INFIRMIER_FOU].acteur_type=ACTEUR_INFIRMIER_FOU;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].bmp_index=BMP_INFIRMIER;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].x=-1;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].y=-1;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].bloquant=true;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].frce=15;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].dxtrt=10;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].vitesse=100;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].vie=65;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].vie_max=65;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].coup_critique=13;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].hemorragie=false;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].hemorragie_tic=0;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].fuite=false;
	prefab_acteur[ACTEUR_INFIRMIER_FOU].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_INFIRMIER_FOU].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_CHIMPANZE]=new char[strlen("Singe")+1];
	strcpy(nom_acteur[ACTEUR_CHIMPANZE],"Singe");
	
	description_acteur[ACTEUR_CHIMPANZE]=new char[strlen("Une sorte de chimpanze sur-musculeux. Une chose est sure, on n'en trouve pas de telle sorte dans la nature!")+1];
	strcpy(description_acteur[ACTEUR_CHIMPANZE],"Une sorte de chimpanze sur-musculeux. Une chose est sure, on n'en trouve pas de telle sorte dans la nature!");
	
	prefab_acteur[ACTEUR_CHIMPANZE].acteur_type=ACTEUR_CHIMPANZE;
	prefab_acteur[ACTEUR_CHIMPANZE].bmp_index=BMP_CHIMPANZE;
	prefab_acteur[ACTEUR_CHIMPANZE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_CHIMPANZE].x=-1;
	prefab_acteur[ACTEUR_CHIMPANZE].y=-1;
	prefab_acteur[ACTEUR_CHIMPANZE].bloquant=true;
	prefab_acteur[ACTEUR_CHIMPANZE].frce=7;
	prefab_acteur[ACTEUR_CHIMPANZE].dxtrt=18;
	prefab_acteur[ACTEUR_CHIMPANZE].vitesse=180;
	prefab_acteur[ACTEUR_CHIMPANZE].vie=45;
	prefab_acteur[ACTEUR_CHIMPANZE].vie_max=45;
	prefab_acteur[ACTEUR_CHIMPANZE].coup_critique=0;
	prefab_acteur[ACTEUR_CHIMPANZE].hemorragie=false;
	prefab_acteur[ACTEUR_CHIMPANZE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_CHIMPANZE].comportement_type=CMPRTMNT_AGRESSIF_FUYARD;
	prefab_acteur[ACTEUR_CHIMPANZE].fuite=false;
	prefab_acteur[ACTEUR_CHIMPANZE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_CHIMPANZE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_GORILLE]=new char[strlen("gorille")+1];
	strcpy(nom_acteur[ACTEUR_GORILLE],"gorille");
	
	description_acteur[ACTEUR_GORILLE]=new char[strlen("Un gorille. Depuis qu'il est en liberte, il est tres enerve et desire faire payer son emprisonnement a tous le monde.")+1];
	strcpy(description_acteur[ACTEUR_GORILLE],"Un gorille. Depuis qu'il est en liberte, il est tres enerve et desire faire payer son emprisonnement a tous le monde.");
	
	prefab_acteur[ACTEUR_GORILLE].acteur_type=ACTEUR_GORILLE;
	prefab_acteur[ACTEUR_GORILLE].bmp_index=BMP_GORILLE;
	prefab_acteur[ACTEUR_GORILLE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_GORILLE].x=-1;
	prefab_acteur[ACTEUR_GORILLE].y=-1;
	prefab_acteur[ACTEUR_GORILLE].bloquant=true;
	prefab_acteur[ACTEUR_GORILLE].frce=15;
	prefab_acteur[ACTEUR_GORILLE].dxtrt=17;
	prefab_acteur[ACTEUR_GORILLE].vitesse=80;
	prefab_acteur[ACTEUR_GORILLE].vie=90;
	prefab_acteur[ACTEUR_GORILLE].vie_max=90;
	prefab_acteur[ACTEUR_GORILLE].coup_critique=25;
	prefab_acteur[ACTEUR_GORILLE].hemorragie=false;
	prefab_acteur[ACTEUR_GORILLE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_GORILLE].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_GORILLE].fuite=false;
	prefab_acteur[ACTEUR_GORILLE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_GORILLE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_SINGE_MUTANT]=new char[strlen("singe mutant?")+1];
	strcpy(nom_acteur[ACTEUR_SINGE_MUTANT],"singe mutant?");
	
	description_acteur[ACTEUR_SINGE_MUTANT]=new char[strlen("Un animal etrange et difforme qui a du etre un singe autrefois.")+1];
	strcpy(description_acteur[ACTEUR_SINGE_MUTANT],"Un animal etrange et difforme qui a du etre un singe autrefois.");
	
	prefab_acteur[ACTEUR_SINGE_MUTANT].acteur_type=ACTEUR_SINGE_MUTANT;
	prefab_acteur[ACTEUR_SINGE_MUTANT].bmp_index=BMP_SINGE_MUTANT;
	prefab_acteur[ACTEUR_SINGE_MUTANT].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_SINGE_MUTANT].x=-1;
	prefab_acteur[ACTEUR_SINGE_MUTANT].y=-1;
	prefab_acteur[ACTEUR_SINGE_MUTANT].bloquant=true;
	prefab_acteur[ACTEUR_SINGE_MUTANT].frce=13;
	prefab_acteur[ACTEUR_SINGE_MUTANT].dxtrt=18;
	prefab_acteur[ACTEUR_SINGE_MUTANT].vitesse=150;
	prefab_acteur[ACTEUR_SINGE_MUTANT].vie=105;
	prefab_acteur[ACTEUR_SINGE_MUTANT].vie_max=105;
	prefab_acteur[ACTEUR_SINGE_MUTANT].coup_critique=20;
	prefab_acteur[ACTEUR_SINGE_MUTANT].hemorragie=false;
	prefab_acteur[ACTEUR_SINGE_MUTANT].hemorragie_tic=0;
	prefab_acteur[ACTEUR_SINGE_MUTANT].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_SINGE_MUTANT].fuite=false;
	prefab_acteur[ACTEUR_SINGE_MUTANT].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_SINGE_MUTANT].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_CHIEN]=new char[strlen("chien")+1];
	strcpy(nom_acteur[ACTEUR_CHIEN],"chien");
	
	description_acteur[ACTEUR_CHIEN]=new char[strlen("Un chien de laboratoire.")+1];
	strcpy(description_acteur[ACTEUR_CHIEN],"Un chien de laboratoire.");
	
	prefab_acteur[ACTEUR_CHIEN].acteur_type=ACTEUR_CHIEN;
	prefab_acteur[ACTEUR_CHIEN].bmp_index=BMP_CHIEN;
	prefab_acteur[ACTEUR_CHIEN].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_CHIEN].x=-1;
	prefab_acteur[ACTEUR_CHIEN].y=-1;
	prefab_acteur[ACTEUR_CHIEN].bloquant=true;
	prefab_acteur[ACTEUR_CHIEN].frce=9;
	prefab_acteur[ACTEUR_CHIEN].dxtrt=17;
	prefab_acteur[ACTEUR_CHIEN].vitesse=200;
	prefab_acteur[ACTEUR_CHIEN].vie=20;
	prefab_acteur[ACTEUR_CHIEN].vie_max=20;
	prefab_acteur[ACTEUR_CHIEN].coup_critique=3;
	prefab_acteur[ACTEUR_CHIEN].hemorragie=false;
	prefab_acteur[ACTEUR_CHIEN].hemorragie_tic=0;
	prefab_acteur[ACTEUR_CHIEN].comportement_type=CMPRTMNT_AGRESSIF_FUYARD;
	prefab_acteur[ACTEUR_CHIEN].fuite=false;
	prefab_acteur[ACTEUR_CHIEN].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_CHIEN].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_CHIEN_MUTANT]=new char[strlen("chien")+1];
	strcpy(nom_acteur[ACTEUR_CHIEN_MUTANT],"chien");
	
	description_acteur[ACTEUR_CHIEN_MUTANT]=new char[strlen("Un chien de laboratoire.")+1];
	strcpy(description_acteur[ACTEUR_CHIEN_MUTANT],"Un chien de laboratoire.");
	
	prefab_acteur[ACTEUR_CHIEN_MUTANT].acteur_type=ACTEUR_CHIEN_MUTANT;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].bmp_index=BMP_CHIEN_MUTANT;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].x=-1;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].y=-1;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].bloquant=true;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].frce=13;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].dxtrt=16;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].vitesse=250;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].vie=40;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].vie_max=40;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].coup_critique=10;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].hemorragie=false;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].hemorragie_tic=0;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].comportement_type=CMPRTMNT_AGRESSIF_LIMIT;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].fuite=false;
	prefab_acteur[ACTEUR_CHIEN_MUTANT].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_CHIEN_MUTANT].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_AGENT_SECURITE]=new char[strlen("agent de securite")+1];
	strcpy(nom_acteur[ACTEUR_AGENT_SECURITE],"agent de securite");
	
	description_acteur[ACTEUR_AGENT_SECURITE]=new char[strlen("Un agent de securite, assez lourdement protege.")+1];
	strcpy(description_acteur[ACTEUR_AGENT_SECURITE],"Un agent de securite, assez lourdement protege.");
	
	prefab_acteur[ACTEUR_AGENT_SECURITE].acteur_type=ACTEUR_AGENT_SECURITE;
	prefab_acteur[ACTEUR_AGENT_SECURITE].bmp_index=BMP_AGENT_SECU;
	prefab_acteur[ACTEUR_AGENT_SECURITE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE].x=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE].y=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE].bloquant=true;
	prefab_acteur[ACTEUR_AGENT_SECURITE].frce=14;
	prefab_acteur[ACTEUR_AGENT_SECURITE].dxtrt=13;
	prefab_acteur[ACTEUR_AGENT_SECURITE].vitesse=130;
	prefab_acteur[ACTEUR_AGENT_SECURITE].vie=60;
	prefab_acteur[ACTEUR_AGENT_SECURITE].vie_max=60;
	prefab_acteur[ACTEUR_AGENT_SECURITE].coup_critique=12;
	prefab_acteur[ACTEUR_AGENT_SECURITE].hemorragie=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_AGENT_SECURITE].fuite=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_AGENT_SECURITE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_AGENT_SECURITE_ARME]=new char[strlen("agent de securite")+1];
	strcpy(nom_acteur[ACTEUR_AGENT_SECURITE_ARME],"agent de securite");
	
	description_acteur[ACTEUR_AGENT_SECURITE_ARME]=new char[strlen("Un agent de securite equipe d'un pistolet.")+1];
	strcpy(description_acteur[ACTEUR_AGENT_SECURITE_ARME],"Un agent de securite equipe d'un pistolet.");
	
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].acteur_type=ACTEUR_AGENT_SECURITE_ARME;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].bmp_index=BMP_AGENT_SECU_ARME;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].x=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].y=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].bloquant=true;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].frce=14;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].dxtrt=14;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].vitesse=110;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].vie=70;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].vie_max=70;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].coup_critique=10;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].hemorragie=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].hemorragie_tic=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].fuite=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_AGENT_SECURITE_ARME_L]=new char[strlen("agent de securite")+1];
	strcpy(nom_acteur[ACTEUR_AGENT_SECURITE_ARME_L],"agent de securite");
	
	description_acteur[ACTEUR_AGENT_SECURITE_ARME_L]=new char[strlen("Un agent de securite lourdement arme.")+1];
	strcpy(description_acteur[ACTEUR_AGENT_SECURITE_ARME_L],"Un agent de securite lourdement arme.");
	
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].acteur_type=ACTEUR_AGENT_SECURITE_ARME_L;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].bmp_index=BMP_AGENT_SECU_ARME_L;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].x=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].y=-1;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].bloquant=true;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].frce=13;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].dxtrt=14;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].vitesse=95;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].vie=90;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].vie_max=90;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].coup_critique=20;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].hemorragie=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].hemorragie_tic=0;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].fuite=false;
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_AGENT_SECURITE_ARME_L].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_SOLDAT]=new char[strlen("soldat")+1];
	strcpy(nom_acteur[ACTEUR_SOLDAT],"soldat");
	
	description_acteur[ACTEUR_SOLDAT]=new char[strlen("Un soldat, surprotege et surarme.")+1];
	strcpy(description_acteur[ACTEUR_SOLDAT],"Un soldat, surprotege et surarme.");
	
	prefab_acteur[ACTEUR_SOLDAT].acteur_type=ACTEUR_SOLDAT;
	prefab_acteur[ACTEUR_SOLDAT].bmp_index=BMP_SOLDAT;
	prefab_acteur[ACTEUR_SOLDAT].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_SOLDAT].x=-1,
	prefab_acteur[ACTEUR_SOLDAT].y=-1;
	prefab_acteur[ACTEUR_SOLDAT].bloquant=true;
	prefab_acteur[ACTEUR_SOLDAT].frce=12;
	prefab_acteur[ACTEUR_SOLDAT].dxtrt=16;
	prefab_acteur[ACTEUR_SOLDAT].vitesse=90;
	prefab_acteur[ACTEUR_SOLDAT].vie=110;
	prefab_acteur[ACTEUR_SOLDAT].vie_max=110;
	prefab_acteur[ACTEUR_SOLDAT].coup_critique=15;
	prefab_acteur[ACTEUR_SOLDAT].hemorragie=false;
	prefab_acteur[ACTEUR_SOLDAT].hemorragie_tic=0;
	prefab_acteur[ACTEUR_SOLDAT].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_SOLDAT].fuite=false;
	prefab_acteur[ACTEUR_SOLDAT].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_SOLDAT].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_H_COBAYE]=new char[strlen("cobaye")+1];
	strcpy(nom_acteur[ACTEUR_H_COBAYE],"cobaye");
	
	description_acteur[ACTEUR_H_COBAYE]=new char[strlen("Un cobaye humain comme vous. Il est hagard et famelique.")+1];
	strcpy(description_acteur[ACTEUR_H_COBAYE],"Un cobaye humain comme vous. Il est hagard et famelique.");
	
	prefab_acteur[ACTEUR_H_COBAYE].acteur_type=ACTEUR_H_COBAYE;
	prefab_acteur[ACTEUR_H_COBAYE].bmp_index=BMP_H_COBAYE;
	prefab_acteur[ACTEUR_H_COBAYE].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_H_COBAYE].x=-1;
	prefab_acteur[ACTEUR_H_COBAYE].y=-1;
	prefab_acteur[ACTEUR_H_COBAYE].bloquant=true;
	prefab_acteur[ACTEUR_H_COBAYE].frce=9;
	prefab_acteur[ACTEUR_H_COBAYE].dxtrt=9;
	prefab_acteur[ACTEUR_H_COBAYE].vitesse=70;
	prefab_acteur[ACTEUR_H_COBAYE].vie=20;
	prefab_acteur[ACTEUR_H_COBAYE].vie_max=20;
	prefab_acteur[ACTEUR_H_COBAYE].coup_critique=1;
	prefab_acteur[ACTEUR_H_COBAYE].hemorragie=false;
	prefab_acteur[ACTEUR_H_COBAYE].hemorragie_tic=0;
	prefab_acteur[ACTEUR_H_COBAYE].comportement_type=CMPRTMNT_AGRESSIF_FUYARD;
	prefab_acteur[ACTEUR_H_COBAYE].fuite=false;
	prefab_acteur[ACTEUR_H_COBAYE].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_H_COBAYE].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_H_COBAYE_FOU]=new char[strlen("cobaye")+1];
	strcpy(nom_acteur[ACTEUR_H_COBAYE_FOU],"cobaye");
	
	description_acteur[ACTEUR_H_COBAYE_FOU]=new char[strlen("Un cobaye humain comme vous. Il est hagard et famelique.")+1];
	strcpy(description_acteur[ACTEUR_H_COBAYE_FOU],"Un cobaye humain comme vous. Il est hagard et famelique.");
	
	prefab_acteur[ACTEUR_H_COBAYE_FOU].acteur_type=ACTEUR_H_COBAYE_FOU;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].bmp_index=BMP_H_COBAYE_FOU;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].x=-1;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].y=-1;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].bloquant=true;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].frce=11;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].dxtrt=8;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].vitesse=70;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].vie=40;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].vie_max=40;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].coup_critique=5;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].hemorragie=false;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].hemorragie_tic=0;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].fuite=false;
	prefab_acteur[ACTEUR_H_COBAYE_FOU].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_H_COBAYE_FOU].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

//////////////////////////////////////////////////
	nom_acteur[ACTEUR_H_COBAYE_MUTANT]=new char[strlen("cobaye")+1];
	strcpy(nom_acteur[ACTEUR_H_COBAYE_MUTANT],"cobaye");
	
	description_acteur[ACTEUR_H_COBAYE_MUTANT]=new char[strlen("Autrefois, cette chose etait un cobaye humain, comme vous. Maintenant, c'est un amas de muscle a l'air eteint.")+1];
	strcpy(description_acteur[ACTEUR_H_COBAYE_MUTANT],"Autrefois, cette chose etait un cobaye humain, comme vous. Maintenant, c'est un amas de muscle a l'air eteint.");
	
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].acteur_type=ACTEUR_H_COBAYE_MUTANT;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].bmp_index=BMP_H_COBAYE_MUTANT;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].x=-1;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].y=-1;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].bloquant=true;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].frce=16;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].dxtrt=15;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].vitesse=90;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].vie=80;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].vie_max=80;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].coup_critique=10;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].hemorragie=false;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].hemorragie_tic=0;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].fuite=false;
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_H_COBAYE_MUTANT].equipement[i]=NULL;
///////////////////////////////////////////////////////////	



//////////////////////////////////////////////////
	nom_acteur[ACTEUR_H_COBAYE_TANK]=new char[strlen("cobaye??")+1];
	strcpy(nom_acteur[ACTEUR_H_COBAYE_TANK],"cobaye??");
	
	description_acteur[ACTEUR_H_COBAYE_TANK]=new char[strlen("Un colosse d'au moins 2.5m. Ses yeux, enfonces dans sa tete sous proportionnee et osseuse, brillent de colere.")+1];
	strcpy(description_acteur[ACTEUR_H_COBAYE_TANK],"Un colosse d'au moins 2.5m. Ses yeux, enfonces dans sa tete sous proportionnee et osseuse, brillent de colere.");
	
	prefab_acteur[ACTEUR_H_COBAYE_TANK].acteur_type=ACTEUR_H_COBAYE_TANK;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].bmp_index=BMP_H_COBAYE_TANK;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].x=-1;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].y=-1;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].bloquant=true;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].frce=20;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].dxtrt=10;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].vitesse=60;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].vie=250;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].vie_max=250;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].coup_critique=20;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].hemorragie=false;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].hemorragie_tic=0;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].fuite=false;
	prefab_acteur[ACTEUR_H_COBAYE_TANK].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_H_COBAYE_TANK].equipement[i]=NULL;
///////////////////////////////////////////////////////////	


//////////////////////////////////////////////////
	nom_acteur[ACTEUR_H_COBAYE_MUT_COUREUR]=new char[strlen("cobaye coureur")+1];
	strcpy(nom_acteur[ACTEUR_H_COBAYE_MUT_COUREUR],"cobaye coureur");
	
	description_acteur[ACTEUR_H_COBAYE_MUT_COUREUR]=new char[strlen("Un cobaye sec et musculeux. Ses pieds et ses mains griffues lui permettent de se deplacer tres rapidement sur le sol comme sur les murs.")+1];
	strcpy(description_acteur[ACTEUR_H_COBAYE_MUT_COUREUR],"Un cobaye sec et musculeux. Ses pieds et ses mains griffues lui permettent de se deplacer tres rapidement sur le sol comme sur les murs.");
	
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].acteur_type=ACTEUR_H_COBAYE_MUT_COUREUR;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].bmp_index=BMP_H_COBAYE_MUT_COUREUR;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].bmp_index_detruit=0;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].x=-1;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].y=-1;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].bloquant=true;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].frce=8;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].dxtrt=19;	  // carac principales
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].vitesse=250; // CARAC PRINCIPALES
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].vie=40;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].vie_max=40;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].coup_critique=70;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].hemorragie=false;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].hemorragie_tic=0;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].comportement_type=CMPRTMNT_AGRESSIF_NO_LIMIT;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].fuite=false;
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].point_action_restant=0;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	prefab_acteur[ACTEUR_H_COBAYE_MUT_COUREUR].equipement[i]=NULL;
///////////////////////////////////////////////////////////	

	return 0;
}


int supprimer_prefab_acteurs()
{
	
	return 0;
}



/**************** FONCTION DE GESTION DES ACTEURS 
******************************************************/

bool est_vivant(acteur* act)
{
	
	if (act->vie>0)return true;
	
	return false;
}


/************************************************************************
*********************FONCTION DE CALCUL EN RAPPORT AVEC L EQUIPEMENT****/

//int calcul_protec(acteur *act);
//fonction qui calcule la somme totale de protection due aux vetements equipes
//
// retourne le score protection total
int calcul_protec(acteur *act)
{
	int prot=0;
	
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	if(act->equipement[i]!=NULL)prot+=act->equipement[i]->protection;
	
	if(act->equipement[EQUIPMNT_TETE]!=NULL)prot+=act->equipement[EQUIPMNT_TETE]->protection;
	
	
	return prot;
	
}

//int degradation_equip_protec(acteur *act);
//Fonction qui calcule la degradation des vetements equipes.
//
//Si l acteur est touche et que les protections font leur job,
//on selectionne un equipement de protection aleatoire et on le dégrade d'un point
//Si l'etat d'un objet tombe a zero, il est détruit et on le supprime.
//
//retourne le nombre d'equipement detruit
int degradation_equip_protec(acteur *act)
{
	int equip[MAX_EQUIPMNT];
	int nb_equip;
	
	//recup de l'ensemble des équipement de protection
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	{
		if(act->equipement[i]!=NULL)
		{
			equip[nb_equip]=i;
			nb_equip++;
		}
	}
	
	if(act->equipement[EQUIPMNT_TETE]!=NULL)
	{
		equip[nb_equip]=EQUIPMNT_TETE;
		nb_equip++;
	}
	
	//choix aleatoire de l objet.
	nb_equip=genrand_int32()%nb_equip;
	
	//degradation de l objet
	act->equipement[nb_equip]->etat_obj--;
	
	//suppression de l'objet si celui-ci est casse
	if(act->equipement[nb_equip]->etat_obj<=0)
	{
		delete act->equipement[nb_equip];
		act->equipement[nb_equip]=NULL;
		return 1;
		
	}
	
	return 0;
	
}


//int calcul_bonus_vit_deplacement(joeur *jr);
// Retourne le bonus de vitesse de déplacement du à l'equipement 
int calcul_bonus_equip_vitdeplace(acteur *act)
{
	
		int vit=0;
	
	for(int i=EQUIPMNT_CHAUSSURE;i<EQUIPMNT_MAIN_D;i++)
	if(act->equipement[i]!=NULL)vit+=act->equipement[i]->modif_vit_dplcment;
	
	if(act->equipement[EQUIPMNT_TETE]!=NULL)vit+=act->equipement[EQUIPMNT_TETE]->modif_vit_dplcment;
	
	
	return vit;

	
}



// Fonction pour savoir si un sotckage est
// libre chez les perso non joueur et 'lindice de celui
// ci. Si pas de Stockage libre, retourne -1
int stockage_libre(acteur *act)
{
	
	if(act->acteur_type<=ACTEUR_ARMOIRE_MEDIC)
	{
		 for(int i=0;i<MAX_EQUIPMNT;i++)
		 if(act->equipement[i]==NULL)return i;
	}
	else if(act->acteur_type>=ACTEUR_SCIENTIFIQUE_BASE)
	{
		if(act->equipement[EQUIPMNT_MAIN_G]==0)return EQUIPMNT_MAIN_G;
		 
		if(act->equipement[EQUIPMNT_MAIN_D]==0)return EQUIPMNT_MAIN_D;
		
		
	}
	
	return -1;
}


// Fonction pour obtenir l'inde de munitions dans l'inventaire en fonction
// de l arme choisie.
int indice_munition_de_arme(acteur *act,int inv)
{
	
	
	int munitype=0;
	
	
		switch(act->equipement[inv]->objet_type)
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
		
		
		for(int i=0;i<MAX_EQUIPMNT;i++)
		{
			
			if(act->equipement[i]!=NULL)
			{
				if(act->equipement[i]->objet_type==munitype)
				return i;
				
			}
		}

return -1;
}

/******************************************************************/
/*******RECOPIE ET CREATION D ACTEURS *****************************/
/******************************************************************/



//Fonction pour placer le mobilier sur les cartes en x, y
//
// Gestion de l'inventaire dans le mobilier.
// MODIFIER CETTE FONCTION POUR CHANGER LES PROBA DE LOOT
acteur * placer_mobilier(int x, int  y,int acteur_type)
{
	int objcnt=0;
	acteur *act;
	act=new acteur;
	
	// RECOPIE DE L ACTEUR
	act->acteur_type=prefab_acteur[acteur_type].acteur_type;
	act->bmp_index=prefab_acteur[acteur_type].bmp_index;
	act->bmp_index_detruit=prefab_acteur[acteur_type].bmp_index_detruit;
	act->x=x;
	act->y=y;
	act->bloquant=prefab_acteur[acteur_type].bloquant;
	act->frce=prefab_acteur[acteur_type].frce;
	act->dxtrt=prefab_acteur[acteur_type].dxtrt;	  // carac principales
	act->vitesse=prefab_acteur[acteur_type].vitesse; // CARAC PRINCIPALES
	act->vie=prefab_acteur[acteur_type].vie;
	act->vie_max=prefab_acteur[acteur_type].vie_max;
	act->coup_critique=prefab_acteur[acteur_type].coup_critique;
	act->hemorragie=prefab_acteur[acteur_type].hemorragie;
	act->hemorragie_tic=prefab_acteur[acteur_type].hemorragie_tic;
	act->comportement_type=prefab_acteur[acteur_type].comportement_type;
	act->fuite=prefab_acteur[acteur_type].fuite;
	act->point_action_restant=prefab_acteur[acteur_type].point_action_restant;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	act->equipement[i]=prefab_acteur[acteur_type].equipement[i]=NULL;
	
	/*
	#define ACTEUR_BUREAU						0
#define ACTEUR_ETAGERE						1
#define ACTEUR_TABLE_OPERATION				2
#define ACTEUR_TABLE						3
#define ACTEUR_RACK_ARME					4
#define ACTEUR_ARMOIRE_MEDIC				5
#define ACTEUR_CONSOLE_INFO					6
#define ACTEUR_BOUTEILLE_GAZ				7
#define ACTEUR_CONTENEUR_ACIDE				8
#define ACTEUR_LAVABO						9
#define ACTEUR_TOILETTES					10
#define ACTEUR_LIT	
	*/
	
	switch(act->acteur_type)
	{
		case ACTEUR_BUREAU:
			
			if(genrand_int32()%101<=10)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_BANDAGE);
			 objcnt++;
			}
			if(genrand_int32()%101<=5)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MUNITION_PISTO);
			 objcnt++;
			}
			if(genrand_int32()%101<=5)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MUNITION_FUSIL);
			 objcnt++;
			}
			if(genrand_int32()%101<=1)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MUNITION_MITRA);
			 objcnt++;
			}			
			
		break;
		
		case ACTEUR_ETAGERE:
	    	if(genrand_int32()%1001<=5)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_IMPLANT_FORCE);
			 objcnt++;
			}
		 	if(genrand_int32()%1001<=2)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_IMPLANT_DXTRT);
			 objcnt++;
			}
			if(genrand_int32()%1001<=2)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_IMPLANT_VITESSE);
			 objcnt++;
			}
			if(genrand_int32()%1001<=100)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_SERUM_PHYSIO);
			 objcnt++;
			}
			if(genrand_int32()%1001<=20)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MEDIPACK);
			 objcnt++;
			}
		break;
		
		case ACTEUR_RACK_ARME:
			if(genrand_int32()%1001<=60)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_PISTOLET);
			 objcnt++;
			}
			if(genrand_int32()%1001<=25)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_FUSIL_POMPE);
			 objcnt++;
			}
			if(genrand_int32()%1001<=10)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MITRAILLETTE);
			 objcnt++;
			}
		break;
		
	case	ACTEUR_ARMOIRE_MEDIC:
			if(genrand_int32()%1001<=600)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_BANDAGE);
			 objcnt++;
			}
			if(genrand_int32()%1001<=200)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_SERUM_PHYSIO);
			 objcnt++;
			}
			if(genrand_int32()%1001<=100)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_MEDIPACK);
			 objcnt++;
			}
			if(genrand_int32()%1001<=100)
			{
			 act->equipement[objcnt]=creer_objet(-1,-1,OBJ_ADRENALINE);
			 objcnt++;
			}


		break;
		
	}
	
	return act;
}

//Fonction pour placer les personnages sur la carte.
// 
//Elle permet de tirer l inventaire des perso  
acteur * placer_personnage(int x,int y,int acteur_type)
{
	int objcnt=0;
	acteur *act;
	act=new acteur;
	
	// RECOPIE DE L ACTEUR
	act->acteur_type=prefab_acteur[acteur_type].acteur_type;
	act->bmp_index=prefab_acteur[acteur_type].bmp_index;
	act->bmp_index_detruit=prefab_acteur[acteur_type].bmp_index_detruit;
	act->x=x;
	act->y=y;
	act->bloquant=prefab_acteur[acteur_type].bloquant;
	act->frce=prefab_acteur[acteur_type].frce;
	act->dxtrt=prefab_acteur[acteur_type].dxtrt;	  // carac principales
	act->vitesse=prefab_acteur[acteur_type].vitesse; // CARAC PRINCIPALES
	act->vie=prefab_acteur[acteur_type].vie;
	act->vie_max=prefab_acteur[acteur_type].vie_max;
	act->coup_critique=prefab_acteur[acteur_type].coup_critique;
	act->hemorragie=prefab_acteur[acteur_type].hemorragie;
	act->hemorragie_tic=prefab_acteur[acteur_type].hemorragie_tic;
	act->comportement_type=prefab_acteur[acteur_type].comportement_type;
	act->fuite=prefab_acteur[acteur_type].fuite;
	act->point_action_restant=prefab_acteur[acteur_type].point_action_restant;
	for(int i=0;i<MAX_EQUIPMNT;i++)	
	act->equipement[i]=prefab_acteur[acteur_type].equipement[i]=NULL;
	
	/*
	// DEFINITION DES PERSONNAGES
#define ACTEUR_SCIENTIFIQUE_BASE			12
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

	
	*/
	switch(act->acteur_type)
	{
		case ACTEUR_SCIENTIFIQUE_BASE:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSE);
			
		if(genrand_int32()%1001<=400)
		{
			 act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_SCALPEL);
			 objcnt++;
		}
		if(genrand_int32()%1001<=300)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_BANDAGE);
			 objcnt++;
		}
			
		break;
		///////////////////////////////////////////////
		case ACTEUR_SCIENTIFIQUE_PEUREUX:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSE);
			
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_SCALPEL);
			  
		}
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_ADRENALINE);
			 
		}
		else if(genrand_int32()%1001<=50)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MEDIPACK);
			 
		}
		break;
		///////////////////////////////////
		case ACTEUR_SCIENTIFIQUE_FOU:
		if(genrand_int32()%1001<=200)
		{
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		}
		if(genrand_int32()%1001<=700)
		{
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		}
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSE);
			
		if(genrand_int32()%1001<=900)
		{
			 act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_SCALPEL);
			  
		}
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_ADRENALINE);
			 
		}
		else if(genrand_int32()%1001<=50)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MEDIPACK);
			 
		}
		break;
		///////////////////////////////////
		case ACTEUR_INFIRMIER: 
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSE);
		
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_ADRENALINE);
		}
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_BANDAGE);
		}
		break;
		/////////////////////////////
		case ACTEUR_INFIRMIER_FOU: 
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		if(genrand_int32()%1001<=400)
		{
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSE);
		}
		else if(genrand_int32()%1001<=100)
		{
			act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSON);
		}
		if(genrand_int32()%1001<=100)
		{
			 act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_ADRENALINE);
		}
		if(genrand_int32()%1001<=600)
		{
			 act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_SCALPEL);
		}
		
		break;
		//////////////////////////
		case ACTEUR_AGENT_SECURITE:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_CHAUSSURE);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSON);
		if(genrand_int32()%1001<=400)
		{
		act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_PISTO);
		}
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_COUTEAU);
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_COUTEAU_CMBT);
		}
		break;
		/////////////////////////
		
		case ACTEUR_AGENT_SECURITE_ARME:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_BOTTE_COMBAT);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSON);
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_PISTO);
		}
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_COUTEAU_CMBT);
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_PISTOLET);
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_MEDIPACK);
		}
		break;
		//////////////////////////////////
		case ACTEUR_AGENT_SECURITE_ARME_L:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_BOTTE_COMBAT);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_BLOUSON);
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_FUSIL);
		}
		else if(genrand_int32()%1001<=500)
		{
			act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_MITRA);			
		}
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_FUSIL_POMPE);
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_MITRAILLETTE);
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_MEDIPACK);
		}
		break;
		/////////////////////////////
		
		
		case ACTEUR_SOLDAT:
		act->equipement[EQUIPMNT_CHAUSSURE]=creer_objet(-1,-1,OBJ_BOTTE_COMBAT);
		act->equipement[EQUIPMNT_PANTALON]=creer_objet(-1,-1,OBJ_PANTALON);
		act->equipement[EQUIPMNT_TORSE]=creer_objet(-1,-1,OBJ_GILET_PARE_B);
		
		if(genrand_int32()%1001<=500)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_FUSIL_POMPE);
		act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_FUSIL);
	
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_MITRAILLETTE);
		act->equipement[EQUIPMNT_MAIN_G]=creer_objet(-1,-1,OBJ_MUNITION_MITRA);
	
		}
		else if(genrand_int32()%1001<=800)
		{
		act->equipement[EQUIPMNT_MAIN_D]=creer_objet(-1,-1,OBJ_MEDIPACK);
		}
		/////////////////////////////
		
	}

	return act;
}

