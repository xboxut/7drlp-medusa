



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const_act_joueur.h"
#include "const_bmp_index.h"
#include "objet.h"

// définition de l'ensemble des objets, de leurs noms et descriptions
objet prefab_objet[MAX_OBJ];
char *nom_objet[MAX_OBJ];
char *description_objet[MAX_OBJ];
/////////////////////////////////////////////////////////////////////

//constructeur destructeur
objet::objet()
{
	
}

objet::~objet()
{
	
}
//////////////////////////////////


int creer_prefab_objets()
{
	///////////////////////////////////////////////////////
	///OBJET RIEN
	nom_objet[OBJ_RIEN]=new char[strlen("rien")+1];
	strcpy(nom_objet[OBJ_RIEN],"rien");
	
	description_objet[OBJ_RIEN]=new char[strlen("rien")+1];
	strcpy(description_objet[OBJ_RIEN],"rien");
	
	prefab_objet[OBJ_RIEN].objet_type=OBJ_RIEN;
	prefab_objet[OBJ_RIEN].objet_nom=nom_objet[OBJ_RIEN];
	prefab_objet[OBJ_RIEN].description=description_objet[OBJ_RIEN];
	prefab_objet[OBJ_RIEN].x=-1;
	prefab_objet[OBJ_RIEN].y=-1;
	prefab_objet[OBJ_RIEN].bmp_index=BMP_INTERIEUR_MUR;
	prefab_objet[OBJ_RIEN].degat=0;
	prefab_objet[OBJ_RIEN].protection=0;
	prefab_objet[OBJ_RIEN].ajt_vie=0;
	prefab_objet[OBJ_RIEN].ajt_adrenaline=0;
	prefab_objet[OBJ_RIEN].ajt_furie=0;
	prefab_objet[OBJ_RIEN].stop_sang=false;	
	prefab_objet[OBJ_RIEN].etat_obj=0;
	prefab_objet[OBJ_RIEN].ajt_perm_frce=0;
	prefab_objet[OBJ_RIEN].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_RIEN].ajt_perm_vitesse=0;
	prefab_objet[OBJ_RIEN].max_munition=0;
	prefab_objet[OBJ_RIEN].munition=0;	
	prefab_objet[OBJ_RIEN].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	
	///////////////////////////////////////////////////////
	///OBJET SERUM PHYSIO
	nom_objet[OBJ_SERUM_PHYSIO]=new char[strlen("serum physiologique")+1];
	strcpy(nom_objet[OBJ_SERUM_PHYSIO],"serum physiologique");
	
	description_objet[OBJ_SERUM_PHYSIO]=new char[strlen("Une poche pleine de liquide physiologique. Elle possede un effet benefique pour les patients ayant subi des traumatismes, des blessures.")+1];
	strcpy(description_objet[OBJ_SERUM_PHYSIO],"Une poche pleine de liquide physiologique. Elle possede un effet benefique pour les patients ayant subi des traumatismes, des blessures.");
	
	prefab_objet[OBJ_SERUM_PHYSIO].objet_type=OBJ_SERUM_PHYSIO;
	prefab_objet[OBJ_SERUM_PHYSIO].objet_nom=nom_objet[OBJ_SERUM_PHYSIO];
	prefab_objet[OBJ_SERUM_PHYSIO].description=description_objet[OBJ_SERUM_PHYSIO];
	prefab_objet[OBJ_SERUM_PHYSIO].x=-1;
	prefab_objet[OBJ_SERUM_PHYSIO].y=-1;
	prefab_objet[OBJ_SERUM_PHYSIO].bmp_index=BMP_SERUM_PHYSIO;
	prefab_objet[OBJ_SERUM_PHYSIO].degat=0;
	prefab_objet[OBJ_SERUM_PHYSIO].protection=0;
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_vie=10;          // AJOUT DE VIE -> EFFET PRINCIPAL SERUM PHYSIO
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_adrenaline=0;
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_furie=0;
	prefab_objet[OBJ_SERUM_PHYSIO].stop_sang=false;	
	prefab_objet[OBJ_SERUM_PHYSIO].etat_obj=0;
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_perm_frce=0;
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_SERUM_PHYSIO].ajt_perm_vitesse=0;
	prefab_objet[OBJ_SERUM_PHYSIO].max_munition=0;
	prefab_objet[OBJ_SERUM_PHYSIO].munition=0;
	prefab_objet[OBJ_SERUM_PHYSIO].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	///OBJ_BANDAGE
	nom_objet[OBJ_BANDAGE]=new char[strlen("serum physiologique")+1];
	strcpy(nom_objet[OBJ_BANDAGE],"serum physiologique");
	
	description_objet[OBJ_BANDAGE]=new char[strlen("Une poche pleine de liquide physiologique. Elle possede un effet benefique pour les patients ayant subi des traumatismes, des blessures.")+1];
	strcpy(description_objet[OBJ_BANDAGE],"Une poche pleine de liquide physiologique. Elle possede un effet benefique pour les patients ayant subi des traumatismes, des blessures.");
	
	prefab_objet[OBJ_BANDAGE].objet_type=OBJ_BANDAGE;
	prefab_objet[OBJ_BANDAGE].objet_nom=nom_objet[OBJ_BANDAGE];
	prefab_objet[OBJ_BANDAGE].description=description_objet[OBJ_BANDAGE];
	prefab_objet[OBJ_BANDAGE].x=-1;
	prefab_objet[OBJ_BANDAGE].y=-1;
	prefab_objet[OBJ_BANDAGE].bmp_index=BMP_BANDAGE;
	prefab_objet[OBJ_BANDAGE].degat=0;
	prefab_objet[OBJ_BANDAGE].protection=0;
	prefab_objet[OBJ_BANDAGE].ajt_vie=1;          // AJOUT DE VIE 
	prefab_objet[OBJ_BANDAGE].ajt_adrenaline=0;
	prefab_objet[OBJ_BANDAGE].ajt_furie=0;
	prefab_objet[OBJ_BANDAGE].stop_sang=true;	  // ARRET SAIGNEMENT -> effet principal bandage
	prefab_objet[OBJ_BANDAGE].etat_obj=0;
	prefab_objet[OBJ_BANDAGE].ajt_perm_frce=0;
	prefab_objet[OBJ_BANDAGE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_BANDAGE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_BANDAGE].max_munition=0;
	prefab_objet[OBJ_BANDAGE].munition=0;
	prefab_objet[OBJ_BANDAGE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	
	
	///////////////////////////////////////////////////////
	///OBJ_MEDIPACK
	nom_objet[OBJ_MEDIPACK]=new char[strlen("medipack")+1];
	strcpy(nom_objet[OBJ_MEDIPACK],"medipack");
	
	description_objet[OBJ_MEDIPACK]=new char[strlen("Un kit medical d'ugence. Il contient des outils de chirurgie, des bandages et des antalgiques; le strict minimum pour se refaire une sante!")+1];
	strcpy(description_objet[OBJ_MEDIPACK],"Un kit medical d'ugence. Il contient des outils de chirurgie, des bandages et des antalgiques; le strict minimum pour se refaire une sante!");
	
	prefab_objet[OBJ_MEDIPACK].objet_type=OBJ_MEDIPACK;
	prefab_objet[OBJ_MEDIPACK].objet_nom=nom_objet[OBJ_MEDIPACK];
	prefab_objet[OBJ_MEDIPACK].description=description_objet[OBJ_MEDIPACK];
	prefab_objet[OBJ_MEDIPACK].x=-1;
	prefab_objet[OBJ_MEDIPACK].y=-1;
	prefab_objet[OBJ_MEDIPACK].bmp_index=BMP_MEDIPACK;
	prefab_objet[OBJ_MEDIPACK].degat=0;
	prefab_objet[OBJ_MEDIPACK].protection=0;
	prefab_objet[OBJ_MEDIPACK].ajt_vie=50;          // AJOUT DE VIE 
	prefab_objet[OBJ_MEDIPACK].ajt_adrenaline=0;
	prefab_objet[OBJ_MEDIPACK].ajt_furie=0;
	prefab_objet[OBJ_MEDIPACK].stop_sang=true;	  // ARRET SAIGNEMENT 
	prefab_objet[OBJ_MEDIPACK].etat_obj=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_frce=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MEDIPACK].max_munition=0;
	prefab_objet[OBJ_MEDIPACK].munition=0;
	prefab_objet[OBJ_MEDIPACK].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_MEDIPACK
	nom_objet[OBJ_MEDIPACK]=new char[strlen("medipack")+1];
	strcpy(nom_objet[OBJ_MEDIPACK],"medipack");
	
	description_objet[OBJ_MEDIPACK]=new char[strlen("Un kit medical d'ugence. Il contient des outils de chirurgie, des bandages et des antalgiques; le strict minimum pour se refaire une sante!")+1];
	strcpy(description_objet[OBJ_MEDIPACK],"Un kit medical d'ugence. Il contient des outils de chirurgie, des bandages et des antalgiques; le strict minimum pour se refaire une sante!");
	
	prefab_objet[OBJ_MEDIPACK].objet_type=OBJ_MEDIPACK;
	prefab_objet[OBJ_MEDIPACK].objet_nom=nom_objet[OBJ_MEDIPACK];
	prefab_objet[OBJ_MEDIPACK].description=description_objet[OBJ_MEDIPACK];
	prefab_objet[OBJ_MEDIPACK].x=-1;
	prefab_objet[OBJ_MEDIPACK].y=-1;
	prefab_objet[OBJ_MEDIPACK].bmp_index=BMP_MEDIPACK;
	prefab_objet[OBJ_MEDIPACK].degat=0;
	prefab_objet[OBJ_MEDIPACK].protection=0;
	prefab_objet[OBJ_MEDIPACK].ajt_vie=50;          // AJOUT DE VIE 
	prefab_objet[OBJ_MEDIPACK].ajt_adrenaline=0;
	prefab_objet[OBJ_MEDIPACK].ajt_furie=0;
	prefab_objet[OBJ_MEDIPACK].stop_sang=true;	  // ARRET SAIGNEMENT 
	prefab_objet[OBJ_MEDIPACK].etat_obj=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_frce=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MEDIPACK].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MEDIPACK].max_munition=0;
	prefab_objet[OBJ_MEDIPACK].munition=0;
	prefab_objet[OBJ_MEDIPACK].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////
	///OBJ_ADRENALINE
	nom_objet[OBJ_ADRENALINE]=new char[strlen("adrenaline")+1];
	strcpy(nom_objet[OBJ_ADRENALINE],"adrenaline");
	
	description_objet[OBJ_ADRENALINE]=new char[strlen("Une seringue pleine d'adrenaline. Son injection permettra de retarder legerement l'effet du poison qui coure dans vos veines.")+1];
	strcpy(description_objet[OBJ_ADRENALINE],"Une seringue pleine d'adrenaline. Son injection permettra de retarder legerement l'effet du poison qui coure dans vos veines.");
	
	prefab_objet[OBJ_ADRENALINE].objet_type=OBJ_ADRENALINE;
	prefab_objet[OBJ_ADRENALINE].objet_nom=nom_objet[OBJ_ADRENALINE];
	prefab_objet[OBJ_ADRENALINE].description=description_objet[OBJ_ADRENALINE];
	prefab_objet[OBJ_ADRENALINE].x=-1;
	prefab_objet[OBJ_ADRENALINE].y=-1;
	prefab_objet[OBJ_ADRENALINE].bmp_index=BMP_ADRENALINE;
	prefab_objet[OBJ_ADRENALINE].degat=0;
	prefab_objet[OBJ_ADRENALINE].protection=0;
	prefab_objet[OBJ_ADRENALINE].ajt_vie=0;          
	prefab_objet[OBJ_ADRENALINE].ajt_adrenaline=50;	  //AJOUT ADRENALINE	
	prefab_objet[OBJ_ADRENALINE].ajt_furie=0;
	prefab_objet[OBJ_ADRENALINE].stop_sang=true;	  
	prefab_objet[OBJ_ADRENALINE].etat_obj=0;
	prefab_objet[OBJ_ADRENALINE].ajt_perm_frce=0;
	prefab_objet[OBJ_ADRENALINE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_ADRENALINE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_ADRENALINE].max_munition=0;
	prefab_objet[OBJ_ADRENALINE].munition=0;
	prefab_objet[OBJ_ADRENALINE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_FURIE_PACK
	nom_objet[OBJ_FURIE_PACK]=new char[strlen("drogue de combat")+1];
	strcpy(nom_objet[OBJ_FURIE_PACK],"drogue de combat");
	
	description_objet[OBJ_FURIE_PACK]=new char[strlen("Une seringue de Berserk, une drogue de combat revolutionnaire! Les inscriptions sur la seringue indiquent de l'injecter dans le cou pour un effet immediat et puissant, mais de courte duree. Cette susbtance augmente de facon significative la vitesse, la coordination et la force.")+1];
	strcpy(description_objet[OBJ_FURIE_PACK],"Une seringue de Berserk, une drogue de combat revolutionnaire! Les inscriptions sur la seringue indiquent de l'injecter dans le cou pour un effet immediat et puissant, mais de courte duree. Cette susbtance augmente de facon significative la vitesse, la coordination et la force.");
	
	prefab_objet[OBJ_FURIE_PACK].objet_type=OBJ_FURIE_PACK;
	prefab_objet[OBJ_FURIE_PACK].objet_nom=nom_objet[OBJ_FURIE_PACK];
	prefab_objet[OBJ_FURIE_PACK].description=description_objet[OBJ_FURIE_PACK];
	prefab_objet[OBJ_FURIE_PACK].x=-1;
	prefab_objet[OBJ_FURIE_PACK].y=-1;
	prefab_objet[OBJ_FURIE_PACK].bmp_index=BMP_FURIE_PACK;
	prefab_objet[OBJ_FURIE_PACK].degat=0;
	prefab_objet[OBJ_FURIE_PACK].protection=0;
	prefab_objet[OBJ_FURIE_PACK].ajt_vie=0;          
	prefab_objet[OBJ_FURIE_PACK].ajt_adrenaline=5;	  //AJOUT ADRENALINE	
	prefab_objet[OBJ_FURIE_PACK].ajt_furie=50;		//ajout furie -> effet principal
	prefab_objet[OBJ_FURIE_PACK].stop_sang=false;	  
	prefab_objet[OBJ_FURIE_PACK].etat_obj=0;
	prefab_objet[OBJ_FURIE_PACK].ajt_perm_frce=0;
	prefab_objet[OBJ_FURIE_PACK].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_FURIE_PACK].ajt_perm_vitesse=0;
	prefab_objet[OBJ_FURIE_PACK].max_munition=0;
	prefab_objet[OBJ_FURIE_PACK].munition=0;
	prefab_objet[OBJ_FURIE_PACK].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_SCALPEL
	nom_objet[OBJ_SCALPEL]=new char[strlen("scalpel")+1];
	strcpy(nom_objet[OBJ_SCALPEL],"scalpel");
	
	description_objet[OBJ_SCALPEL]=new char[strlen("Un scalpel, relativement tranchant.")+1];
	strcpy(description_objet[OBJ_SCALPEL],"Un scalpel, relativement tranchant.");
	
	prefab_objet[OBJ_SCALPEL].objet_type=OBJ_SCALPEL;
	prefab_objet[OBJ_SCALPEL].objet_nom=nom_objet[OBJ_SCALPEL];
	prefab_objet[OBJ_SCALPEL].description=description_objet[OBJ_SCALPEL];
	prefab_objet[OBJ_SCALPEL].x=-1;
	prefab_objet[OBJ_SCALPEL].y=-1;
	prefab_objet[OBJ_SCALPEL].bmp_index=BMP_SCALPEL;
	prefab_objet[OBJ_SCALPEL].degat=7;			// DEGAT -> Effet principal
	prefab_objet[OBJ_SCALPEL].protection=0;
	prefab_objet[OBJ_SCALPEL].ajt_vie=0;          
	prefab_objet[OBJ_SCALPEL].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_SCALPEL].ajt_furie=0;		
	prefab_objet[OBJ_SCALPEL].stop_sang=false;	  
	prefab_objet[OBJ_SCALPEL].etat_obj=30;	   // durée de vie de l objet 	
	prefab_objet[OBJ_SCALPEL].ajt_perm_frce=0;
	prefab_objet[OBJ_SCALPEL].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_SCALPEL].ajt_perm_vitesse=0;
	prefab_objet[OBJ_SCALPEL].max_munition=0;
	prefab_objet[OBJ_SCALPEL].munition=0;
	prefab_objet[OBJ_SCALPEL].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////
	///OBJ_COUTEAU
	nom_objet[OBJ_COUTEAU]=new char[strlen("couteau")+1];
	strcpy(nom_objet[OBJ_COUTEAU],"couteau");
	
	description_objet[OBJ_COUTEAU]=new char[strlen("Un couteau de cuisine standard, pointu et coupant. La lame est peu epaisse, ce qui rend cette arme fragile.")+1];
	strcpy(description_objet[OBJ_COUTEAU],"Un couteau de cuisine standard, pointu et coupant. La lame est peu epaisse, ce qui rend cette arme fragile.");
	
	prefab_objet[OBJ_COUTEAU].objet_type=OBJ_COUTEAU;
	prefab_objet[OBJ_COUTEAU].objet_nom=nom_objet[OBJ_COUTEAU];
	prefab_objet[OBJ_COUTEAU].description=description_objet[OBJ_COUTEAU];
	prefab_objet[OBJ_COUTEAU].x=-1;
	prefab_objet[OBJ_COUTEAU].y=-1;
	prefab_objet[OBJ_COUTEAU].bmp_index=BMP_COUTEAU;
	prefab_objet[OBJ_COUTEAU].degat=12;			// DEGAT -> Effet principal
	prefab_objet[OBJ_COUTEAU].protection=0;
	prefab_objet[OBJ_COUTEAU].ajt_vie=0;          
	prefab_objet[OBJ_COUTEAU].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_COUTEAU].ajt_furie=0;		
	prefab_objet[OBJ_COUTEAU].stop_sang=false;	  
	prefab_objet[OBJ_COUTEAU].etat_obj=50;	   // durée de vie de l objet 	
	prefab_objet[OBJ_COUTEAU].ajt_perm_frce=0;
	prefab_objet[OBJ_COUTEAU].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_COUTEAU].ajt_perm_vitesse=0;
	prefab_objet[OBJ_COUTEAU].max_munition=0;
	prefab_objet[OBJ_COUTEAU].munition=0;
	prefab_objet[OBJ_COUTEAU].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_COUTEAU_CMBT
	nom_objet[OBJ_COUTEAU_CMBT]=new char[strlen("couteau de combat")+1];
	strcpy(nom_objet[OBJ_COUTEAU_CMBT],"couteau de combat");
	
	description_objet[OBJ_COUTEAU_CMBT]=new char[strlen("Un couteau de combat, possedant une lame epaisse de finition phosphatee. Il est tres solide, son tranchant est redoutable.")+1];
	strcpy(description_objet[OBJ_COUTEAU_CMBT],"Un couteau de combat, possedant une lame epaisse de finition phosphatee. Il est tres solide, son tranchant est redoutable.");
	
	prefab_objet[OBJ_COUTEAU_CMBT].objet_type=OBJ_COUTEAU_CMBT;
	prefab_objet[OBJ_COUTEAU_CMBT].objet_nom=nom_objet[OBJ_COUTEAU_CMBT];
	prefab_objet[OBJ_COUTEAU_CMBT].description=description_objet[OBJ_COUTEAU_CMBT];
	prefab_objet[OBJ_COUTEAU_CMBT].x=-1;
	prefab_objet[OBJ_COUTEAU_CMBT].y=-1;
	prefab_objet[OBJ_COUTEAU_CMBT].bmp_index=BMP_COUTEAU_CMBT;
	prefab_objet[OBJ_COUTEAU_CMBT].degat=15;			// DEGAT -> Effet principal
	prefab_objet[OBJ_COUTEAU_CMBT].protection=0;
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_vie=0;          
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_furie=0;		
	prefab_objet[OBJ_COUTEAU_CMBT].stop_sang=false;	  
	prefab_objet[OBJ_COUTEAU_CMBT].etat_obj=150;	   // durée de vie de l objet 	
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_perm_frce=0;
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_COUTEAU_CMBT].ajt_perm_vitesse=0;
	prefab_objet[OBJ_COUTEAU_CMBT].max_munition=0;
	prefab_objet[OBJ_COUTEAU_CMBT].munition=0;
	prefab_objet[OBJ_COUTEAU_CMBT].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_PISTOLET
	nom_objet[OBJ_PISTOLET]=new char[strlen("pistolet semi-automatique")+1];
	strcpy(nom_objet[OBJ_PISTOLET],"pistolet semi-automatique");
	
	description_objet[OBJ_PISTOLET]=new char[strlen("Un pistolet semi-automatique de la marque glock. C'est une arme tres repandu dans les forces de polices de nombreux pays. Il est chambre en .45 et a une contenance de 15 cartouches.")+1];
	strcpy(description_objet[OBJ_PISTOLET],"Un pistolet semi-automatique de la marque glock. C'est une arme tres repandu dans les forces de polices de nombreux pays. Il est chambre en .45 et a une contenance de 15 cartouches.");
	
	prefab_objet[OBJ_PISTOLET].objet_type=OBJ_PISTOLET;
	prefab_objet[OBJ_PISTOLET].objet_nom=nom_objet[OBJ_PISTOLET];
	prefab_objet[OBJ_PISTOLET].description=description_objet[OBJ_PISTOLET];
	prefab_objet[OBJ_PISTOLET].x=-1;
	prefab_objet[OBJ_PISTOLET].y=-1;
	prefab_objet[OBJ_PISTOLET].bmp_index=BMP_PISTOLET;
	prefab_objet[OBJ_PISTOLET].degat=25;			// DEGAT -> Effet principal
	prefab_objet[OBJ_PISTOLET].protection=0;
	prefab_objet[OBJ_PISTOLET].ajt_vie=0;          
	prefab_objet[OBJ_PISTOLET].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_PISTOLET].ajt_furie=0;		
	prefab_objet[OBJ_PISTOLET].stop_sang=false;	  
	prefab_objet[OBJ_PISTOLET].etat_obj=100;	   // durée de vie de l objet 	
	prefab_objet[OBJ_PISTOLET].ajt_perm_frce=0;
	prefab_objet[OBJ_PISTOLET].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_PISTOLET].ajt_perm_vitesse=0;
	prefab_objet[OBJ_PISTOLET].max_munition=15;	   //nombre max de munitions	
	prefab_objet[OBJ_PISTOLET].munition=0;
	prefab_objet[OBJ_PISTOLET].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_FUSIL_POMPE
	nom_objet[OBJ_FUSIL_POMPE]=new char[strlen("fusil a pompe")+1];
	strcpy(nom_objet[OBJ_FUSIL_POMPE],"fusil a pompe");
	
	description_objet[OBJ_FUSIL_POMPE]=new char[strlen("Un fusil a pompe Benelli; tres puissant, il permet l'envoi de charges massives de chevrotines a tres haute vitesse. Son reservoir de cartouche a une contenance de 4 munitions, lui permettant de faire face aux tres gros gibiers!")+1];
	strcpy(description_objet[OBJ_FUSIL_POMPE],"Un fusil a pompe Benelli; tres puissant, il permet l'envoi de charges massives de chevrotines a tres haute vitesse. Son reservoir de cartouche a une contenance de 4 munitions, lui permettant de faire face aux tres gros gibiers!");
	
	prefab_objet[OBJ_FUSIL_POMPE].objet_type=OBJ_FUSIL_POMPE;
	prefab_objet[OBJ_FUSIL_POMPE].objet_nom=nom_objet[OBJ_FUSIL_POMPE];
	prefab_objet[OBJ_FUSIL_POMPE].description=description_objet[OBJ_FUSIL_POMPE];
	prefab_objet[OBJ_FUSIL_POMPE].x=-1;
	prefab_objet[OBJ_FUSIL_POMPE].y=-1;
	prefab_objet[OBJ_FUSIL_POMPE].bmp_index=BMP_FUSIL_POMPE;
	prefab_objet[OBJ_FUSIL_POMPE].degat=45;			// DEGAT -> Effet principal
	prefab_objet[OBJ_FUSIL_POMPE].protection=0;
	prefab_objet[OBJ_FUSIL_POMPE].ajt_vie=0;          
	prefab_objet[OBJ_FUSIL_POMPE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_FUSIL_POMPE].ajt_furie=0;		
	prefab_objet[OBJ_FUSIL_POMPE].stop_sang=false;	  
	prefab_objet[OBJ_FUSIL_POMPE].etat_obj=100;	   // durée de vie de l objet 	
	prefab_objet[OBJ_FUSIL_POMPE].ajt_perm_frce=0;
	prefab_objet[OBJ_FUSIL_POMPE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_FUSIL_POMPE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_FUSIL_POMPE].max_munition=4;	   //nombre max de munitions	
	prefab_objet[OBJ_FUSIL_POMPE].munition=0;
	prefab_objet[OBJ_FUSIL_POMPE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////
	///OBJ_MITRAILLETTE
	nom_objet[OBJ_MITRAILLETTE]=new char[strlen("mitraillette")+1];
	strcpy(nom_objet[OBJ_MITRAILLETTE],"mitraillette");
	
	description_objet[OBJ_MITRAILLETTE]=new char[strlen("Une mitraillette uzi, fabrique en israel. Cette arme, chambree en 9mm, possede une munition peu puissante. Ce desavantage est compense par une cadence de tir extrement rapide de 950 coups par minutes! Un seul appuie sur la gachette et elle crache une dizaine de balles. Attention tout de meme, le chargeur ne contient que 32 munitions.")+1];
	strcpy(description_objet[OBJ_MITRAILLETTE],"Une mitraillette uzi, fabrique en israel. Cette arme, chambree en 9mm, possede une munition peu puissante. Ce desavantage est compense par une cadence de tir extrement rapide de 950 coups par minutes! Un seul appuie sur la gachette et elle crache une dizaine de balles. Attention tout de meme, le chargeur ne contient que 32 munitions.");
	
	prefab_objet[OBJ_MITRAILLETTE].objet_type=OBJ_MITRAILLETTE;
	prefab_objet[OBJ_MITRAILLETTE].objet_nom=nom_objet[OBJ_MITRAILLETTE];
	prefab_objet[OBJ_MITRAILLETTE].description=description_objet[OBJ_MITRAILLETTE];
	prefab_objet[OBJ_MITRAILLETTE].x=-1;
	prefab_objet[OBJ_MITRAILLETTE].y=-1;
	prefab_objet[OBJ_MITRAILLETTE].bmp_index=BMP_MITRAILLETTE;
	prefab_objet[OBJ_MITRAILLETTE].degat=18;			// DEGAT -> Effet principal
	prefab_objet[OBJ_MITRAILLETTE].protection=0;
	prefab_objet[OBJ_MITRAILLETTE].ajt_vie=0;          
	prefab_objet[OBJ_MITRAILLETTE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_MITRAILLETTE].ajt_furie=0;		
	prefab_objet[OBJ_MITRAILLETTE].stop_sang=false;	  
	prefab_objet[OBJ_MITRAILLETTE].etat_obj=100;	   // durée de vie de l objet 	
	prefab_objet[OBJ_MITRAILLETTE].ajt_perm_frce=0;
	prefab_objet[OBJ_MITRAILLETTE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MITRAILLETTE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MITRAILLETTE].max_munition=32;	   //nombre max de munitions	
	prefab_objet[OBJ_MITRAILLETTE].munition=0;
	prefab_objet[OBJ_MITRAILLETTE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_MUNITION_PISTO
	nom_objet[OBJ_MUNITION_PISTO]=new char[strlen("munitions .45")+1];
	strcpy(nom_objet[OBJ_MUNITION_PISTO],"munitions .45");
	
	description_objet[OBJ_MUNITION_PISTO]=new char[strlen("Des cartouches de .45 destinees aux pistolets GLOCK.")+1];
	strcpy(description_objet[OBJ_MUNITION_PISTO],"Des cartouches de .45 destinees aux pistolets GLOCK.");
	
	prefab_objet[OBJ_MUNITION_PISTO].objet_type=OBJ_MUNITION_PISTO;
	prefab_objet[OBJ_MUNITION_PISTO].objet_nom=nom_objet[OBJ_MUNITION_PISTO];
	prefab_objet[OBJ_MUNITION_PISTO].description=description_objet[OBJ_MUNITION_PISTO];
	prefab_objet[OBJ_MUNITION_PISTO].x=-1;
	prefab_objet[OBJ_MUNITION_PISTO].y=-1;
	prefab_objet[OBJ_MUNITION_PISTO].bmp_index=BMP_MUNITION_PISTO;
	prefab_objet[OBJ_MUNITION_PISTO].degat=0;		 
	prefab_objet[OBJ_MUNITION_PISTO].protection=0;
	prefab_objet[OBJ_MUNITION_PISTO].ajt_vie=0;          
	prefab_objet[OBJ_MUNITION_PISTO].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_MUNITION_PISTO].ajt_furie=0;		
	prefab_objet[OBJ_MUNITION_PISTO].stop_sang=false;	  
	prefab_objet[OBJ_MUNITION_PISTO].etat_obj=0;	    
	prefab_objet[OBJ_MUNITION_PISTO].ajt_perm_frce=0;
	prefab_objet[OBJ_MUNITION_PISTO].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MUNITION_PISTO].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MUNITION_PISTO].max_munition=0;	  
	prefab_objet[OBJ_MUNITION_PISTO].munition=15;		// nombre de munitions par chargeur ramasse
	prefab_objet[OBJ_MUNITION_PISTO].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	///OBJ_MUNITION_FUSIL
	nom_objet[OBJ_MUNITION_FUSIL]=new char[strlen("cartouches cal. 12")+1];
	strcpy(nom_objet[OBJ_MUNITION_FUSIL],"cartouches cal. 12");
	
	description_objet[OBJ_MUNITION_FUSIL]=new char[strlen("Un pack de cartouches de calibre 12.")+1];
	strcpy(description_objet[OBJ_MUNITION_FUSIL],"Un pack de cartouche de calibre 12.");
	
	prefab_objet[OBJ_MUNITION_FUSIL].objet_type=OBJ_MUNITION_FUSIL;
	prefab_objet[OBJ_MUNITION_FUSIL].objet_nom=nom_objet[OBJ_MUNITION_FUSIL];
	prefab_objet[OBJ_MUNITION_FUSIL].description=description_objet[OBJ_MUNITION_FUSIL];
	prefab_objet[OBJ_MUNITION_FUSIL].x=-1;
	prefab_objet[OBJ_MUNITION_FUSIL].y=-1;
	prefab_objet[OBJ_MUNITION_FUSIL].bmp_index=BMP_MUNITION_FUSIL;
	prefab_objet[OBJ_MUNITION_FUSIL].degat=0;	 
	prefab_objet[OBJ_MUNITION_FUSIL].protection=0;
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_vie=0;          
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_furie=0;		
	prefab_objet[OBJ_MUNITION_FUSIL].stop_sang=false;	  
	prefab_objet[OBJ_MUNITION_FUSIL].etat_obj=0;	  	
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_perm_frce=0;
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MUNITION_FUSIL].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MUNITION_FUSIL].max_munition=0;	   // nombre de munitions par chargeur ramasse	
	prefab_objet[OBJ_MUNITION_FUSIL].munition=4;
	prefab_objet[OBJ_MUNITION_FUSIL].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////	
	

	///////////////////////////////////////////////////////
	///OBJ_MUNITION_MITRA
	nom_objet[OBJ_MUNITION_MITRA]=new char[strlen("cartouches 9mm")+1];
	strcpy(nom_objet[OBJ_MUNITION_MITRA],"cartouches 9mm");
	
	description_objet[OBJ_MUNITION_MITRA]=new char[strlen("Un pack de munitions de calibre 9mm pour mitraillette UZI.")+1];
	strcpy(description_objet[OBJ_MUNITION_MITRA],"Un pack de munitions de calibre 9mm pour mitraillette UZI.");
	
	prefab_objet[OBJ_MUNITION_MITRA].objet_type=OBJ_MUNITION_MITRA;
	prefab_objet[OBJ_MUNITION_MITRA].objet_nom=nom_objet[OBJ_MUNITION_MITRA];
	prefab_objet[OBJ_MUNITION_MITRA].description=description_objet[OBJ_MUNITION_MITRA];
	prefab_objet[OBJ_MUNITION_MITRA].x=-1;
	prefab_objet[OBJ_MUNITION_MITRA].y=-1;
	prefab_objet[OBJ_MUNITION_MITRA].bmp_index=BMP_MUNITION_MITRA;
	prefab_objet[OBJ_MUNITION_MITRA].degat=0;			
	prefab_objet[OBJ_MUNITION_MITRA].protection=0;
	prefab_objet[OBJ_MUNITION_MITRA].ajt_vie=0;          
	prefab_objet[OBJ_MUNITION_MITRA].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_MUNITION_MITRA].ajt_furie=0;		
	prefab_objet[OBJ_MUNITION_MITRA].stop_sang=false;	  
	prefab_objet[OBJ_MUNITION_MITRA].etat_obj=0;	   	
	prefab_objet[OBJ_MUNITION_MITRA].ajt_perm_frce=0;
	prefab_objet[OBJ_MUNITION_MITRA].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_MUNITION_MITRA].ajt_perm_vitesse=0;
	prefab_objet[OBJ_MUNITION_MITRA].max_munition=0;	  
	prefab_objet[OBJ_MUNITION_MITRA].munition=32;		// nombre de munitions par chargeur ramasse
	prefab_objet[OBJ_MUNITION_MITRA].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					
	
	///////////////////////////////////////////////////////
	///OBJ_CHAUSSURE
	nom_objet[OBJ_CHAUSSURE]=new char[strlen("chaussures")+1];
	strcpy(nom_objet[OBJ_CHAUSSURE],"chaussure");
	
	description_objet[OBJ_CHAUSSURE]=new char[strlen("Des chaussures de villes en cuir marron. Elles semblent confortables et sont d'une pointure superieure a la votre.")+1];
	strcpy(description_objet[OBJ_CHAUSSURE],"Des chaussures de villes en cuir marron. Elles semblent confortables et sont d'une pointure superieure a la votre.");
	
	prefab_objet[OBJ_CHAUSSURE].objet_type=OBJ_CHAUSSURE;
	prefab_objet[OBJ_CHAUSSURE].objet_nom=nom_objet[OBJ_CHAUSSURE];
	prefab_objet[OBJ_CHAUSSURE].description=description_objet[OBJ_CHAUSSURE];
	prefab_objet[OBJ_CHAUSSURE].x=-1;
	prefab_objet[OBJ_CHAUSSURE].y=-1;
	prefab_objet[OBJ_CHAUSSURE].bmp_index=BMP_CHAUSSURE;
	prefab_objet[OBJ_CHAUSSURE].degat=0;			
	prefab_objet[OBJ_CHAUSSURE].protection=5;	   // Protection assuree par l objet
	prefab_objet[OBJ_CHAUSSURE].ajt_vie=0;          
	prefab_objet[OBJ_CHAUSSURE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_CHAUSSURE].ajt_furie=0;		
	prefab_objet[OBJ_CHAUSSURE].stop_sang=false;	  
	prefab_objet[OBJ_CHAUSSURE].etat_obj=10;	   // durée de vie de l objet 	
	prefab_objet[OBJ_CHAUSSURE].ajt_perm_frce=0;
	prefab_objet[OBJ_CHAUSSURE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_CHAUSSURE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_CHAUSSURE].max_munition=0;	   	
	prefab_objet[OBJ_CHAUSSURE].munition=0;
	prefab_objet[OBJ_CHAUSSURE].modif_vit_dplcment=30; //augmentation de la vitesse de deplacement
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_BOTTE_COMBAT
	nom_objet[OBJ_BOTTE_COMBAT]=new char[strlen("bottes de combat")+1];
	strcpy(nom_objet[OBJ_BOTTE_COMBAT],"bottes de combats");
	
	description_objet[OBJ_BOTTE_COMBAT]=new char[strlen("Des bottes de combats en cuir tres epais, elles protegent le pied et la cheville! Le bout du pied est renforce d'une protection en acier, ideal pour botter des fesses!")+1];
	strcpy(description_objet[OBJ_BOTTE_COMBAT],"Des bottes de combats en cuir tres epais, elles protegent le pied et la cheville! Le bout du pied est renforce d'une protection en acier, ideal pour botter des fesses!");
	
	prefab_objet[OBJ_BOTTE_COMBAT].objet_type=OBJ_BOTTE_COMBAT;
	prefab_objet[OBJ_BOTTE_COMBAT].objet_nom=nom_objet[OBJ_BOTTE_COMBAT];
	prefab_objet[OBJ_BOTTE_COMBAT].description=description_objet[OBJ_BOTTE_COMBAT];
	prefab_objet[OBJ_BOTTE_COMBAT].x=-1;
	prefab_objet[OBJ_BOTTE_COMBAT].y=-1;
	prefab_objet[OBJ_BOTTE_COMBAT].bmp_index=BMP_BOTTE_COMBAT;
	prefab_objet[OBJ_BOTTE_COMBAT].degat=0;			
	prefab_objet[OBJ_BOTTE_COMBAT].protection=10;	//protection
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_vie=0;          
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_furie=0;		
	prefab_objet[OBJ_BOTTE_COMBAT].stop_sang=false;	  
	prefab_objet[OBJ_BOTTE_COMBAT].etat_obj=30;	   // durée de vie de l objet 	
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_perm_frce=0;
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_BOTTE_COMBAT].ajt_perm_vitesse=0;
	prefab_objet[OBJ_BOTTE_COMBAT].max_munition=0;	  	
	prefab_objet[OBJ_BOTTE_COMBAT].munition=0;
	prefab_objet[OBJ_BOTTE_COMBAT].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					
	
	///////////////////////////////////////////////////////
	///OBJ_PANTALON
	nom_objet[OBJ_PANTALON]=new char[strlen("pantalon")+1];
	strcpy(nom_objet[OBJ_PANTALON],"pantalon");
	
	description_objet[OBJ_PANTALON]=new char[strlen("Un pantalon noir tout simple. Il vous protege surtout de la nudite!")+1];
	strcpy(description_objet[OBJ_PANTALON],"Un pantalon noir tout simple. Il vous protege surtout de la nudite!");
	
	prefab_objet[OBJ_PANTALON].objet_type=OBJ_PANTALON;
	prefab_objet[OBJ_PANTALON].objet_nom=nom_objet[OBJ_PANTALON];
	prefab_objet[OBJ_PANTALON].description=description_objet[OBJ_PANTALON];
	prefab_objet[OBJ_PANTALON].x=-1;
	prefab_objet[OBJ_PANTALON].y=-1;
	prefab_objet[OBJ_PANTALON].bmp_index=BMP_PANTALON;
	prefab_objet[OBJ_PANTALON].degat=0;			
	prefab_objet[OBJ_PANTALON].protection=3;	//protection
	prefab_objet[OBJ_PANTALON].ajt_vie=0;          
	prefab_objet[OBJ_PANTALON].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_PANTALON].ajt_furie=0;		
	prefab_objet[OBJ_PANTALON].stop_sang=false;	  
	prefab_objet[OBJ_PANTALON].etat_obj=15;	   // durée de vie de l objet 	
	prefab_objet[OBJ_PANTALON].ajt_perm_frce=0;
	prefab_objet[OBJ_PANTALON].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_PANTALON].ajt_perm_vitesse=0;
	prefab_objet[OBJ_PANTALON].max_munition=0;	  	
	prefab_objet[OBJ_PANTALON].munition=0;
	prefab_objet[OBJ_PANTALON].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_BLOUSE
	nom_objet[OBJ_BLOUSE]=new char[strlen("blouse")+1];
	strcpy(nom_objet[OBJ_BLOUSE],"blouse");
	
	description_objet[OBJ_BLOUSE]=new char[strlen("Une blouse de docteur avec toutes les options: stylo quatres couleur dans la poche, badge brillant avec le nom. Avec vous semblez intelligent, elle ne vous empeche cependant pas de prendre un peu de plomb dans la tete!")+1];
	strcpy(description_objet[OBJ_BLOUSE],"Une blouse de docteur avec toutes les options: stylo quatres couleur dans la poche, badge brillant avec le nom. Avec vous semblez intelligent, elle ne vous empeche cependant pas de prendre un peu de plomb dans la tete!");
	
	prefab_objet[OBJ_BLOUSE].objet_type=OBJ_BLOUSE;
	prefab_objet[OBJ_BLOUSE].objet_nom=nom_objet[OBJ_BLOUSE];
	prefab_objet[OBJ_BLOUSE].description=description_objet[OBJ_BLOUSE];
	prefab_objet[OBJ_BLOUSE].x=-1;
	prefab_objet[OBJ_BLOUSE].y=-1;
	prefab_objet[OBJ_BLOUSE].bmp_index=BMP_BLOUSE;
	prefab_objet[OBJ_BLOUSE].degat=0;			
	prefab_objet[OBJ_BLOUSE].protection=3;	//protection
	prefab_objet[OBJ_BLOUSE].ajt_vie=0;          
	prefab_objet[OBJ_BLOUSE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_BLOUSE].ajt_furie=0;		
	prefab_objet[OBJ_BLOUSE].stop_sang=false;	  
	prefab_objet[OBJ_BLOUSE].etat_obj=15;	   // durée de vie de l objet 	
	prefab_objet[OBJ_BLOUSE].ajt_perm_frce=0;
	prefab_objet[OBJ_BLOUSE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_BLOUSE].ajt_perm_vitesse=0;
	prefab_objet[OBJ_BLOUSE].max_munition=0;	  	
	prefab_objet[OBJ_BLOUSE].munition=0;
	prefab_objet[OBJ_BLOUSE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_GANT
	nom_objet[OBJ_GANT]=new char[strlen("gants")+1];
	strcpy(nom_objet[OBJ_GANT],"gants");
	
	description_objet[OBJ_GANT]=new char[strlen("Des gants en kevlar, ils protegent les mains des coupures.")+1];
	strcpy(description_objet[OBJ_GANT],"Des gants en kevlar, ils protegent les mains des coupures.");
	
	prefab_objet[OBJ_GANT].objet_type=OBJ_GANT;
	prefab_objet[OBJ_GANT].objet_nom=nom_objet[OBJ_GANT];
	prefab_objet[OBJ_GANT].description=description_objet[OBJ_GANT];
	prefab_objet[OBJ_GANT].x=-1;
	prefab_objet[OBJ_GANT].y=-1;
	prefab_objet[OBJ_GANT].bmp_index=BMP_GANT;
	prefab_objet[OBJ_GANT].degat=0;			
	prefab_objet[OBJ_GANT].protection=10;	//protection
	prefab_objet[OBJ_GANT].ajt_vie=0;          
	prefab_objet[OBJ_GANT].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_GANT].ajt_furie=0;		
	prefab_objet[OBJ_GANT].stop_sang=false;	  
	prefab_objet[OBJ_GANT].etat_obj=30;	   // durée de vie de l objet 	
	prefab_objet[OBJ_GANT].ajt_perm_frce=0;
	prefab_objet[OBJ_GANT].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_GANT].ajt_perm_vitesse=0;
	prefab_objet[OBJ_GANT].max_munition=0;	  	
	prefab_objet[OBJ_GANT].munition=0;
	prefab_objet[OBJ_GANT].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					
	
	///////////////////////////////////////////////////////
	///OBJ_BLOUSON
	nom_objet[OBJ_BLOUSON]=new char[strlen("blouson")+1];
	strcpy(nom_objet[OBJ_BLOUSON],"blouson");
	
	description_objet[OBJ_BLOUSON]=new char[strlen("Un blouson en cordura, il est solide et bien remboure, ideal lors des rixes ou des jours de grands froids.")+1];
	strcpy(description_objet[OBJ_BLOUSON],"Un blouson en cordura, il est solide et bien remboure, ideal lors des rixes ou des jours de grands froids.");
	
	prefab_objet[OBJ_BLOUSON].objet_type=OBJ_BLOUSON;
	prefab_objet[OBJ_BLOUSON].objet_nom=nom_objet[OBJ_BLOUSON];
	prefab_objet[OBJ_BLOUSON].description=description_objet[OBJ_BLOUSON];
	prefab_objet[OBJ_BLOUSON].x=-1;
	prefab_objet[OBJ_BLOUSON].y=-1;
	prefab_objet[OBJ_BLOUSON].bmp_index=BMP_BLOUSON;
	prefab_objet[OBJ_BLOUSON].degat=0;			
	prefab_objet[OBJ_BLOUSON].protection=10;	//protection
	prefab_objet[OBJ_BLOUSON].ajt_vie=0;          
	prefab_objet[OBJ_BLOUSON].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_BLOUSON].ajt_furie=0;		
	prefab_objet[OBJ_BLOUSON].stop_sang=false;	  
	prefab_objet[OBJ_BLOUSON].etat_obj=30;	   // durée de vie de l objet 	
	prefab_objet[OBJ_BLOUSON].ajt_perm_frce=0;
	prefab_objet[OBJ_BLOUSON].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_BLOUSON].ajt_perm_vitesse=0;
	prefab_objet[OBJ_BLOUSON].max_munition=0;	  	
	prefab_objet[OBJ_BLOUSON].munition=0;
	prefab_objet[OBJ_BLOUSON].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_GILET_PARE_B
	nom_objet[OBJ_GILET_PARE_B]=new char[strlen("gilet pare balle")+1];
	strcpy(nom_objet[OBJ_GILET_PARE_B],"gilet pare balle");
	
	description_objet[OBJ_GILET_PARE_B]=new char[strlen("Un gilet pare balle constitue de nombreuses couches de kevlar. Il est suffisament epais pour arreter les balles d'armes de poing.")+1];
	strcpy(description_objet[OBJ_GILET_PARE_B],"Un gilet pare balle constitue de nombreuses couches de kevlar. Il est suffisament epais pour arreter les balles d'armes de poing.");
	
	prefab_objet[OBJ_GILET_PARE_B].objet_type=OBJ_GILET_PARE_B;
	prefab_objet[OBJ_GILET_PARE_B].objet_nom=nom_objet[OBJ_GILET_PARE_B];
	prefab_objet[OBJ_GILET_PARE_B].description=description_objet[OBJ_GILET_PARE_B];
	prefab_objet[OBJ_GILET_PARE_B].x=-1;
	prefab_objet[OBJ_GILET_PARE_B].y=-1;
	prefab_objet[OBJ_GILET_PARE_B].bmp_index=BMP_GILET_PARE_B;
	prefab_objet[OBJ_GILET_PARE_B].degat=0;			
	prefab_objet[OBJ_GILET_PARE_B].protection=35;	//protection
	prefab_objet[OBJ_GILET_PARE_B].ajt_vie=0;          
	prefab_objet[OBJ_GILET_PARE_B].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_GILET_PARE_B].ajt_furie=0;		
	prefab_objet[OBJ_GILET_PARE_B].stop_sang=false;	  
	prefab_objet[OBJ_GILET_PARE_B].etat_obj=40;	   // durée de vie de l objet 	
	prefab_objet[OBJ_GILET_PARE_B].ajt_perm_frce=0;
	prefab_objet[OBJ_GILET_PARE_B].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_GILET_PARE_B].ajt_perm_vitesse=0;
	prefab_objet[OBJ_GILET_PARE_B].max_munition=0;	  	
	prefab_objet[OBJ_GILET_PARE_B].munition=0;
	prefab_objet[OBJ_GILET_PARE_B].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_IMPLANT_VITESSE
	nom_objet[OBJ_IMPLANT_VITESSE]=new char[strlen("implant de vitesse")+1];
	strcpy(nom_objet[OBJ_IMPLANT_VITESSE],"implant de vitesse");
	
	description_objet[OBJ_IMPLANT_VITESSE]=new char[strlen("Un implant qui ralentit la perception du temps et augmente la vitesse des influx nerveux jusqu'aux membres. Le boitier est munies de six broches tres pointues. Un schema grave sur l'implant montre le boitier installe sur la nuque d'une personne.")+1];
	strcpy(description_objet[OBJ_IMPLANT_VITESSE],"Un implant qui ralentit la perception du temps et augmente la vitesse des influx nerveux jusqu'aux membres. Le boitier est munies de six broches tres pointues. Un schema grave sur l'implant montre le boitier installe sur la nuque d'une personne.");
	
	prefab_objet[OBJ_IMPLANT_VITESSE].objet_type=OBJ_IMPLANT_VITESSE;
	prefab_objet[OBJ_IMPLANT_VITESSE].objet_nom=nom_objet[OBJ_IMPLANT_VITESSE];
	prefab_objet[OBJ_IMPLANT_VITESSE].description=description_objet[OBJ_IMPLANT_VITESSE];
	prefab_objet[OBJ_IMPLANT_VITESSE].x=-1;
	prefab_objet[OBJ_IMPLANT_VITESSE].y=-1;
	prefab_objet[OBJ_IMPLANT_VITESSE].bmp_index=BMP_IMPLANT_VITESSE;
	prefab_objet[OBJ_IMPLANT_VITESSE].degat=0;			
	prefab_objet[OBJ_IMPLANT_VITESSE].protection=0;	
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_vie=0;          
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_furie=0;		
	prefab_objet[OBJ_IMPLANT_VITESSE].stop_sang=false;	  
	prefab_objet[OBJ_IMPLANT_VITESSE].etat_obj=0;	    	
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_perm_frce=0;
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_IMPLANT_VITESSE].ajt_perm_vitesse=40;   //ajout permanent de vitesse.
	prefab_objet[OBJ_IMPLANT_VITESSE].max_munition=0;	  	
	prefab_objet[OBJ_IMPLANT_VITESSE].munition=0;
	prefab_objet[OBJ_IMPLANT_VITESSE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////					

	///////////////////////////////////////////////////////
	///OBJ_IMPLANT_FORCE
	nom_objet[OBJ_IMPLANT_FORCE]=new char[strlen("implant de force")+1];
	strcpy(nom_objet[OBJ_IMPLANT_FORCE],"implant de force");
	
	description_objet[OBJ_IMPLANT_FORCE]=new char[strlen("Un implant qui augmente de maniere significative le nombre des fibres musculaires dans le corps du porteur.")+1];
	strcpy(description_objet[OBJ_IMPLANT_FORCE],"Un implant qui augmente de maniere significative le nombre des fibres musculaires dans le corps du porteur.");
	
	prefab_objet[OBJ_IMPLANT_FORCE].objet_type=OBJ_IMPLANT_FORCE;
	prefab_objet[OBJ_IMPLANT_FORCE].objet_nom=nom_objet[OBJ_IMPLANT_FORCE];
	prefab_objet[OBJ_IMPLANT_FORCE].description=description_objet[OBJ_IMPLANT_FORCE];
	prefab_objet[OBJ_IMPLANT_FORCE].x=-1;
	prefab_objet[OBJ_IMPLANT_FORCE].y=-1;
	prefab_objet[OBJ_IMPLANT_FORCE].bmp_index=BMP_IMPLANT_FORCE;
	prefab_objet[OBJ_IMPLANT_FORCE].degat=0;			
	prefab_objet[OBJ_IMPLANT_FORCE].protection=0;	
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_vie=0;          
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_furie=0;		
	prefab_objet[OBJ_IMPLANT_FORCE].stop_sang=false;	  
	prefab_objet[OBJ_IMPLANT_FORCE].etat_obj=0;	    	
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_perm_frce=2;	// ajout permanent de force
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_perm_dxtrt=0;
	prefab_objet[OBJ_IMPLANT_FORCE].ajt_perm_vitesse=0; 
	prefab_objet[OBJ_IMPLANT_FORCE].max_munition=0;	  	
	prefab_objet[OBJ_IMPLANT_FORCE].munition=0;
	prefab_objet[OBJ_IMPLANT_FORCE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////
	///OBJ_IMPLANT_DXTRT
	nom_objet[OBJ_IMPLANT_DXTRT]=new char[strlen("implant de dexterite")+1];
	strcpy(nom_objet[OBJ_IMPLANT_DXTRT],"implant de dexterite");
	
	description_objet[OBJ_IMPLANT_DXTRT]=new char[strlen("Cet implant agit directement sur le cerveau du patient, augmentant sa coordination et la precision de ses gestes. L'implant se positionne au dessus de l'oreille droite ou gauche selon la lateralite du patient.")+1];
	strcpy(description_objet[OBJ_IMPLANT_DXTRT],"Cet implant agit directement sur le cerveau du patient, augmentant sa coordination et la precision de ses gestes. L'implant se positionne au dessus de l'oreille droite ou gauche selon la lateralite du patient.");
	
	prefab_objet[OBJ_IMPLANT_DXTRT].objet_type=OBJ_IMPLANT_DXTRT;
	prefab_objet[OBJ_IMPLANT_DXTRT].objet_nom=nom_objet[OBJ_IMPLANT_DXTRT];
	prefab_objet[OBJ_IMPLANT_DXTRT].description=description_objet[OBJ_IMPLANT_DXTRT];
	prefab_objet[OBJ_IMPLANT_DXTRT].x=-1;
	prefab_objet[OBJ_IMPLANT_DXTRT].y=-1;
	prefab_objet[OBJ_IMPLANT_DXTRT].bmp_index=BMP_IMPLANT_DXTRT;
	prefab_objet[OBJ_IMPLANT_DXTRT].degat=0;			
	prefab_objet[OBJ_IMPLANT_DXTRT].protection=0;	
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_vie=0;          
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_furie=0;		
	prefab_objet[OBJ_IMPLANT_DXTRT].stop_sang=false;	  
	prefab_objet[OBJ_IMPLANT_DXTRT].etat_obj=0;	    	
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_perm_frce=0;	
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_perm_dxtrt=2;	//ajout de dexterite
	prefab_objet[OBJ_IMPLANT_DXTRT].ajt_perm_vitesse=0; 
	prefab_objet[OBJ_IMPLANT_DXTRT].max_munition=0;	  	
	prefab_objet[OBJ_IMPLANT_DXTRT].munition=0;
	prefab_objet[OBJ_IMPLANT_DXTRT].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_GRENADE
	nom_objet[OBJ_GRENADE]=new char[strlen("implant de dexterite")+1];
	strcpy(nom_objet[OBJ_GRENADE],"implant de dexterite");
	
	description_objet[OBJ_GRENADE]=new char[strlen("Cet implant agit directement sur le cerveau du patient, augmentant sa coordination et la precision de ses gestes. L'implant se positionne au dessus de l'oreille droite ou gauche selon la lateralite du patient.")+1];
	strcpy(description_objet[OBJ_GRENADE],"Cet implant agit directement sur le cerveau du patient, augmentant sa coordination et la precision de ses gestes. L'implant se positionne au dessus de l'oreille droite ou gauche selon la lateralite du patient.");
	
	prefab_objet[OBJ_GRENADE].objet_type=OBJ_GRENADE;
	prefab_objet[OBJ_GRENADE].objet_nom=nom_objet[OBJ_GRENADE];
	prefab_objet[OBJ_GRENADE].description=description_objet[OBJ_GRENADE];
	prefab_objet[OBJ_GRENADE].x=-1;
	prefab_objet[OBJ_GRENADE].y=-1;
	prefab_objet[OBJ_GRENADE].bmp_index=BMP_GRENADE;
	prefab_objet[OBJ_GRENADE].degat=85;					// degat a l endroit ou a lieu l explosion, decroissance en 1/r^2			
	prefab_objet[OBJ_GRENADE].protection=0;	
	prefab_objet[OBJ_GRENADE].ajt_vie=0;          
	prefab_objet[OBJ_GRENADE].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_GRENADE].ajt_furie=0;		
	prefab_objet[OBJ_GRENADE].stop_sang=false;	  
	prefab_objet[OBJ_GRENADE].etat_obj=0;	    	
	prefab_objet[OBJ_GRENADE].ajt_perm_frce=0;	
	prefab_objet[OBJ_GRENADE].ajt_perm_dxtrt=0;	
	prefab_objet[OBJ_GRENADE].ajt_perm_vitesse=0; 
	prefab_objet[OBJ_GRENADE].max_munition=0;	  	
	prefab_objet[OBJ_GRENADE].munition=0;
	prefab_objet[OBJ_GRENADE].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	///OBJ_ANTIDOTE_FINAL
	nom_objet[OBJ_ANTIDOTE_FINAL]=new char[strlen("Antidote")+1];
	strcpy(nom_objet[OBJ_ANTIDOTE_FINAL],"Antidote");
	
	description_objet[OBJ_ANTIDOTE_FINAL]=new char[strlen("Cette seringue contient l'antidote au poison medusa.")+1];
	strcpy(description_objet[OBJ_ANTIDOTE_FINAL],"Cette seringue contient l'antidote au poison medusa.");
	
	prefab_objet[OBJ_ANTIDOTE_FINAL].objet_type=OBJ_ANTIDOTE_FINAL;
	prefab_objet[OBJ_ANTIDOTE_FINAL].objet_nom=nom_objet[OBJ_ANTIDOTE_FINAL];
	prefab_objet[OBJ_ANTIDOTE_FINAL].description=description_objet[OBJ_ANTIDOTE_FINAL];
	prefab_objet[OBJ_ANTIDOTE_FINAL].x=-1;
	prefab_objet[OBJ_ANTIDOTE_FINAL].y=-1;
	prefab_objet[OBJ_ANTIDOTE_FINAL].bmp_index=BMP_ANTIDOTE_FINAL;
	prefab_objet[OBJ_ANTIDOTE_FINAL].degat=0;			
	prefab_objet[OBJ_ANTIDOTE_FINAL].protection=0;	
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_vie=0;          
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_adrenaline=0;	  	
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_furie=0;		
	prefab_objet[OBJ_ANTIDOTE_FINAL].stop_sang=false;	  
	prefab_objet[OBJ_ANTIDOTE_FINAL].etat_obj=0;	    	
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_perm_frce=0;	
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_perm_dxtrt=0;	
	prefab_objet[OBJ_ANTIDOTE_FINAL].ajt_perm_vitesse=0; 
	prefab_objet[OBJ_ANTIDOTE_FINAL].max_munition=0;	  	
	prefab_objet[OBJ_ANTIDOTE_FINAL].munition=0;
	prefab_objet[OBJ_ANTIDOTE_FINAL].modif_vit_dplcment=0;
	///////////////////////////////////////////////////////
									
	return 0;
}


int supprimer_prefab_objets()
{
	
	//Seules les chaines de char sont a desallouer.
	for(int i=0;i<MAX_OBJ;i++)
	{
		delete []	nom_objet[i];
		delete []description_objet[i];
	}	
		
		
	return 0;
}
/////////////////////////////////////////////////

//objet *creer_objet(int x, int y, int type)
//
//Fonction pour creer un objet pour placer sur une carte, dans un inventaire
// ou dans un acteur de contenu.
//
//retourne un pointeur sur l'objet
objet *creer_objet(int x, int y, int type)
{
	objet *obj=new objet();
	
obj->objet_type=prefab_objet[type].objet_type;
obj->objet_nom=prefab_objet[type].objet_nom;
obj->description=prefab_objet[type].description;
obj->x=x;
obj->y=y;
obj->bmp_index=prefab_objet[type].bmp_index;
obj->degat=prefab_objet[type].degat;			
obj->protection=prefab_objet[type].protection;	
obj->ajt_vie=prefab_objet[type].ajt_vie;          
obj->ajt_adrenaline=prefab_objet[type].ajt_adrenaline;	  	
obj->ajt_furie=prefab_objet[type].ajt_furie;		
obj->stop_sang=prefab_objet[type].stop_sang;	  
obj->etat_obj=prefab_objet[type].etat_obj;	    	
obj->ajt_perm_frce=prefab_objet[type].ajt_perm_frce;	
obj->ajt_perm_dxtrt=prefab_objet[type].ajt_perm_dxtrt;	
obj->ajt_perm_vitesse=prefab_objet[type].ajt_perm_vitesse; 
obj->max_munition=prefab_objet[type].max_munition;	  	
obj->munition=prefab_objet[type].munition;
obj->modif_vit_dplcment=prefab_objet[type].modif_vit_dplcment;
	
	
	
return obj;	
}
//////////////////////////////////////////


bool objet_est_arme(objet *obj)
{
	
	if(obj->objet_type==OBJ_SCALPEL ||
	   obj->objet_type==OBJ_COUTEAU ||
	   obj->objet_type==OBJ_COUTEAU_CMBT ||
	   obj->objet_type==OBJ_PISTOLET	||
	   obj->objet_type==OBJ_FUSIL_POMPE	||
	   obj->objet_type==OBJ_MITRAILLETTE	||
	   obj->objet_type==OBJ_GRENADE  )
		return true;
	
	return false;
}


bool objet_est_arme_rechargeable(objet *obj)
{
	
		if(obj->objet_type==OBJ_PISTOLET	||
	   obj->objet_type==OBJ_FUSIL_POMPE	||
	   obj->objet_type==OBJ_MITRAILLETTE	 )
		return true;
	
	return false;
	
	
}

bool objet_est_habit(objet *obj)
{
	 if(obj->objet_type==OBJ_CHAUSSURE ||
	 	obj->objet_type==OBJ_BOTTE_COMBAT ||
	 	obj->objet_type==OBJ_PANTALON 	||
	 	obj->objet_type==OBJ_BLOUSE		 ||
	 	obj->objet_type==OBJ_GANT	 ||
	 	obj->objet_type==OBJ_BLOUSON ||
	 	obj->objet_type==OBJ_GILET_PARE_B ||
	 	obj->objet_type==OBJ_SAC)
	 	return true;
	return false;
}
bool objet_est_medic(objet *obj)
{
	if(obj->objet_type==OBJ_SERUM_PHYSIO ||
		obj->objet_type==OBJ_BANDAGE ||
		obj->objet_type==OBJ_MEDIPACK ||
		obj->objet_type==OBJ_ADRENALINE ||
		obj->objet_type==OBJ_FURIE_PACK)
	return true;

	return false;

}
bool objet_est_implant(objet *obj)
{
	
	if(obj->objet_type==OBJ_IMPLANT_VITESSE	 ||
		obj->objet_type==OBJ_IMPLANT_FORCE||
		obj->objet_type==OBJ_IMPLANT_DXTRT)
	return true;


	
	return false;
}

bool objet_est_munition(objet *obj)
{
	
	if(obj->objet_type==OBJ_MUNITION_PISTO ||
		obj->objet_type==OBJ_MUNITION_FUSIL ||
		obj->objet_type==OBJ_MUNITION_PISTO )	
		return true;
return false;		
}


//renvoi le numero de l'emplacement a equiper
int emplacement_equipe(objet *obj)
{
	
	if(objet_est_arme(obj))return EQUIPMNT_MAIN_D;
	
	if(obj->objet_type==OBJ_GANT)return EQUIPMNT_GANT;
	if(obj->objet_type==OBJ_CHAUSSURE ||obj->objet_type==OBJ_BOTTE_COMBAT )
	return EQUIPMNT_CHAUSSURE;
	
	if(obj->objet_type==OBJ_PANTALON)return EQUIPMNT_PANTALON;
	if(obj->objet_type==OBJ_BLOUSE || obj->objet_type==OBJ_BLOUSON ||
	  obj->objet_type==OBJ_GILET_PARE_B)return EQUIPMNT_TORSE;
	  
	if(obj->objet_type==OBJ_SAC)return EQUIPMNT_DOS;  
		
return -1;	
}

