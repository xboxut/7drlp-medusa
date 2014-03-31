
#include <string.h>

#include "const_bmp_index.h"
#include "tile.h"

//définition des tiles de base pour la construction des cartes.
tile prefab_tile[MAX_TILE];
char * nom_tile[MAX_TILE];
char * description_tile[MAX_TILE];
/////////////////////////////////////////

//////////////////////////////
//Fonction pour creer et détruire les tiles de base.
//
// Stocke les tiles de base dans prefab_tile
// stocke les noms et descriptions dans nom_til et description_tile 
int creation_tile_prefab()
{
	/////////////////////////////////////////////////////////
	//INTERIEUR MUR /////////////////////////////////////////
	nom_tile[TILE_INTERIEUR_MUR]=new char[strlen("interieur d'un mur")+1];
	strcpy(nom_tile[TILE_INTERIEUR_MUR],"interieur d'un mur");
	
	description_tile[TILE_INTERIEUR_MUR]=new char[strlen("interieur d'un mur.")+1];
	strcpy(description_tile[TILE_INTERIEUR_MUR],"interieur d'un mur.");
	
	
	prefab_tile[TILE_INTERIEUR_MUR].type=TILE_INTERIEUR_MUR;
	prefab_tile[TILE_INTERIEUR_MUR].bmp_index=BMP_INTERIEUR_MUR;
	prefab_tile[TILE_INTERIEUR_MUR].bmp_index2=BMP_INTERIEUR_MUR;
	prefab_tile[TILE_INTERIEUR_MUR].name=nom_tile[TILE_INTERIEUR_MUR];
	prefab_tile[TILE_INTERIEUR_MUR].description=description_tile[TILE_INTERIEUR_MUR];
	prefab_tile[TILE_INTERIEUR_MUR].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_INTERIEUR_MUR].transparent=false;
	prefab_tile[TILE_INTERIEUR_MUR].bloquant=true;
	prefab_tile[TILE_INTERIEUR_MUR].ferme=false;
	prefab_tile[TILE_INTERIEUR_MUR].verrouille=false;
	prefab_tile[TILE_INTERIEUR_MUR].decouvert=false;
	prefab_tile[TILE_INTERIEUR_MUR].champ_vision=false;
	////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////
	//SOL  /////////////////////////////////////////////////
	nom_tile[TILE_SOL]=new char[strlen("sol carrelé")+1];
	strcpy(nom_tile[TILE_SOL],"sol carrelé");
	
	description_tile[TILE_SOL]=new char[strlen("Un sol carrelé relativement propre, semblable à ceux des hopitaux et des laboratoires.")+1];
	strcpy(description_tile[TILE_SOL],"Un sol carrelé relativement propre, semblable à ceux des hopitaux et des laboratoires.");
	
	
	prefab_tile[TILE_SOL].type=TILE_SOL;
	prefab_tile[TILE_SOL].bmp_index=BMP_SOL;
	prefab_tile[TILE_SOL].bmp_index2=BMP_SOL;
	prefab_tile[TILE_SOL].name=nom_tile[TILE_SOL];
	prefab_tile[TILE_SOL].description=description_tile[TILE_SOL];
	prefab_tile[TILE_SOL].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_SOL].transparent=true;
	prefab_tile[TILE_SOL].bloquant=false;
	prefab_tile[TILE_SOL].ferme=false;
	prefab_tile[TILE_SOL].verrouille=false;
	prefab_tile[TILE_SOL].decouvert=false;
	prefab_tile[TILE_SOL].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//SOL BRISE  /////////////////////////////////////////////////
	nom_tile[TILE_SOL_BRISE]=new char[strlen("sol carrelé ebreche")+1];
	strcpy(nom_tile[TILE_SOL_BRISE],"sol carrelé ebreche");
	
	description_tile[TILE_SOL_BRISE]=new char[strlen("Un sol carrele ebreche, quelques cheuveux sanglants sont disperses sur le sol, peut etre des signes de lutte?")+1];
	strcpy(description_tile[TILE_SOL_BRISE],"Un sol carrele ebreche, quelques cheuveux sanglants sont disperses sur le sol, peut etre des signes de lutte?");
	
	
	prefab_tile[TILE_SOL_BRISE].type=TILE_SOL_BRISE;
	prefab_tile[TILE_SOL_BRISE].bmp_index=BMP_SOL_BRISE;
	prefab_tile[TILE_SOL_BRISE].bmp_index2=BMP_SOL_BRISE;
	prefab_tile[TILE_SOL_BRISE].name=nom_tile[TILE_SOL_BRISE];
	prefab_tile[TILE_SOL_BRISE].description=description_tile[TILE_SOL_BRISE];
	prefab_tile[TILE_SOL_BRISE].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_SOL_BRISE].transparent=true;
	prefab_tile[TILE_SOL_BRISE].bloquant=false;
	prefab_tile[TILE_SOL_BRISE].ferme=false;
	prefab_tile[TILE_SOL_BRISE].verrouille=false;
	prefab_tile[TILE_SOL_BRISE].decouvert=false;
	prefab_tile[TILE_SOL_BRISE].champ_vision=false;
	////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	//SOL VERRE  /////////////////////////////////////////////////
	nom_tile[TILE_SOL_VERRE]=new char[strlen("sol recouvert de verre")+1];
	strcpy(nom_tile[TILE_SOL_VERRE],"sol recouvert de verre");
	
	description_tile[TILE_SOL_VERRE]=new char[strlen("Un sol recouvert de débris de verre pointus et coupants.")+1];
	strcpy(description_tile[TILE_SOL_VERRE],"Un sol recouvert de débris de verre pointus et coupants.");
	
	
	prefab_tile[TILE_SOL_VERRE].type=TILE_SOL_VERRE;
	prefab_tile[TILE_SOL_VERRE].bmp_index=BMP_SOL_VERRE;
	prefab_tile[TILE_SOL_VERRE].bmp_index2=BMP_SOL_VERRE;
	prefab_tile[TILE_SOL_VERRE].name=nom_tile[TILE_SOL_VERRE];
	prefab_tile[TILE_SOL_VERRE].description=description_tile[TILE_SOL_VERRE];
	prefab_tile[TILE_SOL_VERRE].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_SOL_VERRE].transparent=true;
	prefab_tile[TILE_SOL_VERRE].bloquant=false;
	prefab_tile[TILE_SOL_VERRE].ferme=false;
	prefab_tile[TILE_SOL_VERRE].verrouille=false;
	prefab_tile[TILE_SOL_VERRE].decouvert=false;
	prefab_tile[TILE_SOL_VERRE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//SOL ACIDE  /////////////////////////////////////////////////
	nom_tile[TILE_SOL_ACIDE]=new char[strlen("sol recouvert d'acide")+1];
	strcpy(nom_tile[TILE_SOL_ACIDE],"sol recouvert d'acide");
	
	description_tile[TILE_SOL_ACIDE]=new char[strlen("Une flaque d'acide recouvre le sol, le dissolvant petit à petit.")+1];
	strcpy(description_tile[TILE_SOL_ACIDE],"Une flaque d'acide recouvre le sol, le dissolvant petit à petit.");
	
	
	prefab_tile[TILE_SOL_ACIDE].type=TILE_SOL_ACIDE;
	prefab_tile[TILE_SOL_ACIDE].bmp_index=BMP_SOL_ACIDE;
	prefab_tile[TILE_SOL_ACIDE].bmp_index2=BMP_SOL_ACIDE;
	prefab_tile[TILE_SOL_ACIDE].name=nom_tile[TILE_SOL_ACIDE];
	prefab_tile[TILE_SOL_ACIDE].description=description_tile[TILE_SOL_ACIDE];
	prefab_tile[TILE_SOL_ACIDE].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_SOL_ACIDE].transparent=true;
	prefab_tile[TILE_SOL_ACIDE].bloquant=false;
	prefab_tile[TILE_SOL_ACIDE].ferme=false;
	prefab_tile[TILE_SOL_ACIDE].verrouille=false;
	prefab_tile[TILE_SOL_ACIDE].decouvert=false;
	prefab_tile[TILE_SOL_ACIDE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//MUR  /////////////////////////////////////////////////
	nom_tile[TILE_MUR]=new char[strlen("mur")+1];
	strcpy(nom_tile[TILE_MUR],"mur");
	
	description_tile[TILE_MUR]=new char[strlen("Un mur de beton.")+1];
	strcpy(description_tile[TILE_MUR],"Un mur de beton.");
	
	
	prefab_tile[TILE_MUR].type=TILE_MUR;
	prefab_tile[TILE_MUR].bmp_index=BMP_MUR;
	prefab_tile[TILE_MUR].bmp_index2=BMP_MUR;
	prefab_tile[TILE_MUR].name=nom_tile[TILE_MUR];
	prefab_tile[TILE_MUR].description=description_tile[TILE_MUR];
	prefab_tile[TILE_MUR].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_MUR].transparent=false;
	prefab_tile[TILE_MUR].bloquant=true;
	prefab_tile[TILE_MUR].ferme=false;
	prefab_tile[TILE_MUR].verrouille=false;
	prefab_tile[TILE_MUR].decouvert=false;
	prefab_tile[TILE_MUR].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//MUR BRISE /////////////////////////////////////////////////
	nom_tile[TILE_MUR_BRISE]=new char[strlen("mur")+1];
	strcpy(nom_tile[TILE_MUR_BRISE],"mur");
	
	description_tile[TILE_MUR_BRISE]=new char[strlen("Un mur de beton crible d'impacts de balles.")+1];
	strcpy(description_tile[TILE_MUR_BRISE],"Un mur de beton crible d'impacts de balles.");
	
	
	prefab_tile[TILE_MUR_BRISE].type=TILE_MUR_BRISE;
	prefab_tile[TILE_MUR_BRISE].bmp_index=BMP_MUR_BRISE;
	prefab_tile[TILE_MUR_BRISE].bmp_index2=BMP_MUR_BRISE;
	prefab_tile[TILE_MUR_BRISE].name=nom_tile[TILE_MUR_BRISE];
	prefab_tile[TILE_MUR_BRISE].description=description_tile[TILE_MUR_BRISE];
	prefab_tile[TILE_MUR_BRISE].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_MUR_BRISE].transparent=false;
	prefab_tile[TILE_MUR_BRISE].bloquant=true;
	prefab_tile[TILE_MUR_BRISE].ferme=false;
	prefab_tile[TILE_MUR_BRISE].verrouille=false;
	prefab_tile[TILE_MUR_BRISE].decouvert=false;
	prefab_tile[TILE_MUR_BRISE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//VITRE /////////////////////////////////////////////////
	nom_tile[TILE_VITRE]=new char[strlen("vitre")+1];
	strcpy(nom_tile[TILE_VITRE],"vitre");
	
	description_tile[TILE_VITRE]=new char[strlen("Une vitre transparente, relativement epaisse")+1];
	strcpy(description_tile[TILE_VITRE],"Une vitre transparente, relativement epaisse.");
	
	
	prefab_tile[TILE_VITRE].type=TILE_VITRE;
	prefab_tile[TILE_VITRE].bmp_index=BMP_VITRE;
	prefab_tile[TILE_VITRE].bmp_index2=BMP_VITRE;
	prefab_tile[TILE_VITRE].name=nom_tile[TILE_VITRE];
	prefab_tile[TILE_VITRE].description=description_tile[TILE_VITRE];
	prefab_tile[TILE_VITRE].destructible_id=DESTRUC_FACILE;	
	prefab_tile[TILE_VITRE].transparent=true;
	prefab_tile[TILE_VITRE].bloquant=true;
	prefab_tile[TILE_VITRE].ferme=false;
	prefab_tile[TILE_VITRE].verrouille=false;
	prefab_tile[TILE_VITRE].decouvert=false;
	prefab_tile[TILE_VITRE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//TILE_PORTE_FRAGILE /////////////////////////////////////////////////
	nom_tile[TILE_PORTE_FRAGILE]=new char[strlen("porte")+1];
	strcpy(nom_tile[TILE_PORTE_FRAGILE],"porte");
	
	description_tile[TILE_PORTE_FRAGILE]=new char[strlen("Une porte, d'aspect frele. Elle semble consitutée de panneaux de contreplaqué, et est munie d'une serrure bas de gamme.")+1];
	strcpy(description_tile[TILE_PORTE_FRAGILE],"Une porte, d'aspect frele. Elle semble consitutée de panneaux de contreplaqué, et est munie d'une serrure bas de gamme.");
	
	
	prefab_tile[TILE_PORTE_FRAGILE].type=TILE_PORTE_FRAGILE;
	prefab_tile[TILE_PORTE_FRAGILE].bmp_index=BMP_PORTE_FRAGILE;
	prefab_tile[TILE_PORTE_FRAGILE].bmp_index2=BMP_PORTE_FRAGILE_OUVERT;
	prefab_tile[TILE_PORTE_FRAGILE].name=nom_tile[TILE_PORTE_FRAGILE];
	prefab_tile[TILE_PORTE_FRAGILE].description=description_tile[TILE_PORTE_FRAGILE];
	prefab_tile[TILE_PORTE_FRAGILE].destructible_id=DESTRUC_FACILE;	
	prefab_tile[TILE_PORTE_FRAGILE].transparent=false;
	prefab_tile[TILE_PORTE_FRAGILE].bloquant=true;
	prefab_tile[TILE_PORTE_FRAGILE].ferme=true;
	prefab_tile[TILE_PORTE_FRAGILE].verrouille=false;
	prefab_tile[TILE_PORTE_FRAGILE].decouvert=false;
	prefab_tile[TILE_PORTE_FRAGILE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//TILE_PORTE_NORMALE /////////////////////////////////////////////////
	nom_tile[TILE_PORTE_NORMALE]=new char[strlen("porte")+1];
	strcpy(nom_tile[TILE_PORTE_NORMALE],"porte");
	
	description_tile[TILE_PORTE_NORMALE]=new char[strlen("Une porte d'aspect lisse. Seule un lecteur de carte magnétique est visible non loin de son pene.")+1];
	strcpy(description_tile[TILE_PORTE_NORMALE],"Une porte d'aspect lisse. Seule un lecteur de carte magnétique est visible non loin de son pene.");
	
	
	prefab_tile[TILE_PORTE_NORMALE].type=TILE_PORTE_NORMALE;
	prefab_tile[TILE_PORTE_NORMALE].bmp_index=BMP_PORTE_NORMALE;
	prefab_tile[TILE_PORTE_NORMALE].bmp_index2=BMP_PORTE_NORMALE_OUVERT;
	prefab_tile[TILE_PORTE_NORMALE].name=nom_tile[TILE_PORTE_NORMALE];
	prefab_tile[TILE_PORTE_NORMALE].description=description_tile[TILE_PORTE_NORMALE];
	prefab_tile[TILE_PORTE_NORMALE].destructible_id=DESTRUC_MOYEN;	
	prefab_tile[TILE_PORTE_NORMALE].transparent=false;
	prefab_tile[TILE_PORTE_NORMALE].bloquant=true;
	prefab_tile[TILE_PORTE_NORMALE].ferme=true;
	prefab_tile[TILE_PORTE_NORMALE].verrouille=false;
	prefab_tile[TILE_PORTE_NORMALE].decouvert=false;
	prefab_tile[TILE_PORTE_NORMALE].champ_vision=false;
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	//TILE_PORTE_BLINDE /////////////////////////////////////////////////
	nom_tile[TILE_PORTE_BLINDE]=new char[strlen("porte blindee")+1];
	strcpy(nom_tile[TILE_PORTE_BLINDE],"porte blindee");
	
	description_tile[TILE_PORTE_BLINDE]=new char[strlen("Une lourde porte en acier. Aucune charnière ou serrure n'est discernable. Un lecteur de carte magnétique permet son ouverture.")+1];
	strcpy(description_tile[TILE_PORTE_BLINDE],"Une lourde porte en acier. Aucune charnière ou serrure n'est discernable. Un lecteur de carte magnétique permet son ouverture.");
	
	
	prefab_tile[TILE_PORTE_BLINDE].type=TILE_PORTE_BLINDE;
	prefab_tile[TILE_PORTE_BLINDE].bmp_index=BMP_PORTE_BLINDE;
	prefab_tile[TILE_PORTE_BLINDE].bmp_index2=BMP_PORTE_BLINDE_OUVERT;
	prefab_tile[TILE_PORTE_BLINDE].name=nom_tile[TILE_PORTE_BLINDE];
	prefab_tile[TILE_PORTE_BLINDE].description=description_tile[TILE_PORTE_BLINDE];
	prefab_tile[TILE_PORTE_BLINDE].destructible_id=DESTRUC_DUR;	
	prefab_tile[TILE_PORTE_BLINDE].transparent=false;
	prefab_tile[TILE_PORTE_BLINDE].bloquant=true;
	prefab_tile[TILE_PORTE_BLINDE].ferme=true;
	prefab_tile[TILE_PORTE_BLINDE].verrouille=false;
	prefab_tile[TILE_PORTE_BLINDE].decouvert=false;
	prefab_tile[TILE_PORTE_BLINDE].champ_vision=false;
	////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	//TILE_BARREAUX /////////////////////////////////////////////////
	nom_tile[TILE_BARREAUX]=new char[strlen("barreaux en acier")+1];
	strcpy(nom_tile[TILE_BARREAUX],"barreaux en acier");
	
	description_tile[TILE_BARREAUX]=new char[strlen("Des barreaux en acier trempé, ils ont l'air solides.")+1];
	strcpy(description_tile[TILE_BARREAUX],"Des barreaux en acier trempé, ils ont l'air solides.");
	
	
	prefab_tile[TILE_BARREAUX].type=TILE_BARREAUX;
	prefab_tile[TILE_BARREAUX].bmp_index=BMP_BARREAUX;
	prefab_tile[TILE_BARREAUX].bmp_index2=BMP_BARREAUX;
	prefab_tile[TILE_BARREAUX].name=nom_tile[TILE_BARREAUX];
	prefab_tile[TILE_BARREAUX].description=description_tile[TILE_BARREAUX];
	prefab_tile[TILE_BARREAUX].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_BARREAUX].transparent=true;
	prefab_tile[TILE_BARREAUX].bloquant=true;
	prefab_tile[TILE_BARREAUX].ferme=false;
	prefab_tile[TILE_BARREAUX].verrouille=false;
	prefab_tile[TILE_BARREAUX].decouvert=false;
	prefab_tile[TILE_BARREAUX].champ_vision=false;
	////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	//TILE_ESCALIER_BAS /////////////////////////////////////////////////
	nom_tile[TILE_ESCALIER_BAS]=new char[strlen("escalier vers le niveau inferieur")+1];
	strcpy(nom_tile[TILE_ESCALIER_BAS],"escalier vers le niveau inferieur");
	
	description_tile[TILE_ESCALIER_BAS]=new char[strlen("Un escalier vers le niveau inferieur.")+1];
	strcpy(description_tile[TILE_ESCALIER_BAS],"Un escalier vers le niveau inferieur.");
	
	
	prefab_tile[TILE_ESCALIER_BAS].type=TILE_ESCALIER_BAS;
	prefab_tile[TILE_ESCALIER_BAS].bmp_index=BMP_ESCALIER_BAS;
	prefab_tile[TILE_ESCALIER_BAS].bmp_index2=BMP_ESCALIER_BAS;
	prefab_tile[TILE_ESCALIER_BAS].name=nom_tile[TILE_ESCALIER_BAS];
	prefab_tile[TILE_ESCALIER_BAS].description=description_tile[TILE_ESCALIER_BAS];
	prefab_tile[TILE_ESCALIER_BAS].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_ESCALIER_BAS].transparent=true;
	prefab_tile[TILE_ESCALIER_BAS].bloquant=false;
	prefab_tile[TILE_ESCALIER_BAS].ferme=false;
	prefab_tile[TILE_ESCALIER_BAS].verrouille=false;
	prefab_tile[TILE_ESCALIER_BAS].decouvert=false;
	prefab_tile[TILE_ESCALIER_BAS].champ_vision=false;
	////////////////////////////////////////////////////////

	
	/////////////////////////////////////////////////////////
	//TILE_ESCALIER_HAUT /////////////////////////////////////////////////
	nom_tile[TILE_ESCALIER_HAUT]=new char[strlen("escalier vers le niveau superieur")+1];
	strcpy(nom_tile[TILE_ESCALIER_HAUT],"escalier vers le niveau superieur");
	
	description_tile[TILE_ESCALIER_HAUT]=new char[strlen("Un escalier vers le niveau superieur.")+1];
	strcpy(description_tile[TILE_ESCALIER_HAUT],"Un escalier vers le niveau superieur.");
	
	
	prefab_tile[TILE_ESCALIER_HAUT].type=TILE_ESCALIER_HAUT;
	prefab_tile[TILE_ESCALIER_HAUT].bmp_index=BMP_ESCALIER_HAUT;
	prefab_tile[TILE_ESCALIER_HAUT].bmp_index2=BMP_ESCALIER_HAUT;
	prefab_tile[TILE_ESCALIER_HAUT].name=nom_tile[TILE_ESCALIER_HAUT];
	prefab_tile[TILE_ESCALIER_HAUT].description=description_tile[TILE_ESCALIER_HAUT];
	prefab_tile[TILE_ESCALIER_HAUT].destructible_id=DESTRUC_IMPOSSIBLE;	
	prefab_tile[TILE_ESCALIER_HAUT].transparent=true;
	prefab_tile[TILE_ESCALIER_HAUT].bloquant=false;
	prefab_tile[TILE_ESCALIER_HAUT].ferme=false;
	prefab_tile[TILE_ESCALIER_HAUT].verrouille=false;
	prefab_tile[TILE_ESCALIER_HAUT].decouvert=false;
	prefab_tile[TILE_ESCALIER_HAUT].champ_vision=false;
	////////////////////////////////////////////////////////
	

return 0;	
}


int destruct_tile_prefab()
{
	
	for(int i=0;i<MAX_TILE;i++)
	{
		delete [] description_tile[i];
		delete [] nom_tile[i];
	}
	
	return 0;
}
///////////////////////////////////////////////////
//////////////////////////////



//////////////////////////////
// Fonction pour placer un type de tile donne.
int placer_tile(tile *tle,int tile_type)
{
	
	tle->type=	prefab_tile[tile_type].type;
	tle->bmp_index=	prefab_tile[tile_type].bmp_index;
	tle->bmp_index2=prefab_tile[tile_type].bmp_index2;
	tle->name=prefab_tile[tile_type].name;
	tle->description=prefab_tile[tile_type].description;
	tle->destructible_id=prefab_tile[tile_type].destructible_id;	
	tle->transparent=prefab_tile[tile_type].transparent;
	tle->bloquant=prefab_tile[tile_type].bloquant;
	tle->ferme=prefab_tile[tile_type].ferme;
	tle->verrouille=prefab_tile[tile_type].verrouille;
	tle->decouvert=prefab_tile[tile_type].decouvert;
	tle->champ_vision=prefab_tile[tile_type].champ_vision;


	return 0;
}
//////////////////////////////
////////////////////////////


// fonction pour copier un tile
int copie_tile(tile *dest,tile *source)
{
	
	dest->type=	source->type;
	dest->bmp_index=	source->bmp_index;
	dest->bmp_index2=source->bmp_index2;
	dest->name=source->name;
	dest->description=source->description;
	dest->destructible_id=source->destructible_id;	
	dest->transparent=source->transparent;
	dest->bloquant=source->bloquant;
	dest->ferme=source->ferme;
	dest->verrouille=source->verrouille;
	dest->decouvert=source->decouvert;
	dest->champ_vision=source->champ_vision;


	
	return 0;
}

//fonction pour remplacer un tile
// Contraitement à la copie, ne modifie pas les propriete 
// de vision des tile.
int remplacer_tile(tile *tle,int tile_type)
{
	
	tle->type=	prefab_tile[tile_type].type;
	tle->bmp_index=	prefab_tile[tile_type].bmp_index;
	tle->bmp_index2=	prefab_tile[tile_type].bmp_index2;
	tle->name=prefab_tile[tile_type].name;
	tle->description=prefab_tile[tile_type].description;
	tle->destructible_id=prefab_tile[tile_type].destructible_id;	
	tle->transparent=prefab_tile[tile_type].transparent;
	tle->bloquant=prefab_tile[tile_type].bloquant;
	tle->ferme=prefab_tile[tile_type].ferme;
	tle->verrouille=prefab_tile[tile_type].verrouille;
	
}



//fonction pour ouvrir ou fermer une porte.
// SI la porte a ouvrir était verouillée 
// cette derniere est déverouillé pour eviter les
// eventuels probleme de joueur bloqué dans une piece sans issues
int ouvrir_fermer_porte(tile *prte)
{
	
	prte->bloquant=!prte->bloquant;
	prte->transparent=!prte->transparent;
	prte->ferme=!prte->ferme;
	prte->verrouille=false;
	
	
	return 0;
}
