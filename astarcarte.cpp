

#include <stdlib.h>
#include <stdio.h>

#include "mt19937ar.h"
#include "rgauss.h" 
#include "const_bmp_index.h"
#include "const_act_joueur.h"

#include "tile.h"
#include "objet.h"
#include "joueur.h"
#include "acteur.h"

#include "action.h"

#include "carte.h"


#include "astarcarte.h"



point *ouvert[MAX_LIST_TAILLE];
point *fermer[MAX_LIST_TAILLE];
int point_actif;



//fonction qui retourne l endroit ou le score est le plus faible.
int recup_score_faible()
{
	int scoremin=100000000;
	int result=-1;
	for(register int i=0;i<MAX_LIST_TAILLE;i++)
	{
		
		if(ouvert[i]!=NULL)
		{
			if(ouvert[i]->score_arrive+ouvert[i]->score_depart<scoremin)
			{
		
			scoremin=ouvert[i]->score_arrive+ouvert[i]->score_depart;
		//	printf("score %d, %d %d %d",scoremin,ouvert[i]->score_arrive,ouvert[i]->score_depart,i);	
			result=i;
			
			}
		}
		
	}
	
	return result;
}

//fonction qui permet de stocker le point dans la liste fermée
int passer_liste_fermer(int pos)
{
	
	
	for(register int i=0;i<MAX_LIST_TAILLE;i++)
	{
		
		if(fermer[i]==NULL)
		{
			fermer[i]=ouvert[pos];
			ouvert[pos]=NULL;
			return i;
		}
	}
return 0;
}
//calcul cout


bool existe_dans_fermer(int x,int y)
{
	for(register int i=0;i<MAX_LIST_TAILLE;i++)
	{
		
		if(fermer[i]!=NULL)
		{
			if(fermer[i]->x==x && fermer[i]->y==y)
			return true;
		}
	}
	
	return false;
}

bool existe_dans_ouvert(int x,int y, int *indice=NULL)
{
	for(register int i=0;i<MAX_LIST_TAILLE;i++)
	{
		
		if(ouvert[i]!=NULL)
		{
			if(ouvert[i]->x==x && ouvert[i]->y==y)
			{
			
			if(indice!=NULL)*indice=i;
			return true;
			}
		}
	}
	
	return false;
}

int placer_dans_ouvert(point *ptr)
{
	for(int i=0;i<MAX_LIST_TAILLE;i++)
	{
		if(ouvert[i]==NULL)
		{
			ouvert[i]=ptr;
			return 1;
		}
	}
	return 0;
}

// traiter les points adjacent au point  actuel
int recherche_traitement_adjacent(carte *crte,int finx,int finy)
{
	 int x=fermer[point_actif]->x;
	 int y=fermer[point_actif]->y;
	 int ind=0;
	 int sc=0;
	 // test des 4 tiles adjacents.
	 
	 if(x>0 && x<crte->x-1)
	 {
	     //ouest
		 if(crte->donnee_carte[y][x-1].type<TILE_MUR)
		 {
		 	
		 	if(existe_dans_ouvert( x-1, y)==false && existe_dans_fermer(x-1,y)==false)
		 	{
		 		point *a_ajouter=new point();
		 		a_ajouter->parent=fermer[point_actif];
		 		a_ajouter->x=x-1;
		 		a_ajouter->y=y;
		 		
		 		// CALCUL DU SCORE DE DEPART
		 		a_ajouter->score_depart=fermer[point_actif]->score_depart;
		 		if(crte->donnee_carte[y][x-1].type==TILE_INTERIEUR_MUR)
		 		{
		 			a_ajouter->score_depart+=SCORE_BLOC_PLEIN;
		 		}
		 		else
		 			a_ajouter->score_depart+=SCORE_BLOC_CREUX;
		 		///////////////////////////////////////////
		 		
		 		// Calcul du score d arrivee
		 		a_ajouter->score_arrive=abs(a_ajouter->x-finx)+abs(a_ajouter->y-finy);
		 		
		 		
		 		//placement de a_ajouter dans ouvert.
		 		placer_dans_ouvert(a_ajouter);
		 		
		 	}
		 	else if( existe_dans_ouvert( x-1, y,&ind))
		 	{
		 		 	
		 		 	if(crte->donnee_carte[y][x-1].type==TILE_INTERIEUR_MUR)
		 			{
		 			sc+=SCORE_BLOC_PLEIN+fermer[point_actif]->score_depart;
		 			}
		 			else
		 			sc+=SCORE_BLOC_CREUX+fermer[point_actif]->score_depart;
		 			
		 			
		 		 	// si le score est inferieur
					  if(ouvert[ind]->score_depart>sc)
					  {
					  	ouvert[ind]->parent=fermer[point_actif];
					  	ouvert[ind]->score_depart=sc;
					  }	
		 		
		 	}
		 	
		 	
		 }
		 //est 	
		 if(crte->donnee_carte[y][x+1].type<TILE_MUR)
		 {
		 	
		 	if(existe_dans_ouvert( x+1, y)==false && existe_dans_fermer(x+1,y)==false)
		 	{
		 		point *a_ajouter=new point();
		 		a_ajouter->parent=fermer[point_actif];
		 		a_ajouter->x=x+1;
		 		a_ajouter->y=y;
		 		
		 		// CALCUL DU SCORE DE DEPART
		 		a_ajouter->score_depart=fermer[point_actif]->score_depart;
		 		if(crte->donnee_carte[y][x+1].type==TILE_INTERIEUR_MUR)
		 		{
		 			a_ajouter->score_depart+=SCORE_BLOC_PLEIN;
		 		}
		 		else
		 			a_ajouter->score_depart+=SCORE_BLOC_CREUX;
		 		///////////////////////////////////////////
		 		
		 		// Calcul du score d arrivee
		 		a_ajouter->score_arrive=abs(a_ajouter->x-finx)+abs(a_ajouter->y-finy);
		 		
		 		//placement de a_ajouter dans ouvert.
		 		placer_dans_ouvert(a_ajouter);
		 		
		 	}
		 	else if( existe_dans_ouvert( x+1, y,&ind))
		 	{
		 		 	
		 		 	if(crte->donnee_carte[y][x+1].type==TILE_INTERIEUR_MUR)
		 			{
		 			sc+=SCORE_BLOC_PLEIN+fermer[point_actif]->score_depart;
		 			}
		 			else
		 			sc+=SCORE_BLOC_CREUX+fermer[point_actif]->score_depart;
		 			
		 			
		 		 	// si le score est inferieur
					  if(ouvert[ind]->score_depart>sc)
					  {
					  	ouvert[ind]->parent=fermer[point_actif];
					  	ouvert[ind]->score_depart=sc;
					  }	
		 		
		 	}
		 	
		 
	 	
	 	}	 
	 
	 
	}
	if(y>0 && y<crte->y-1)
	 {
	     //ouest
		 if(crte->donnee_carte[y-1][x].type<TILE_MUR)
		 {
		 	
		 	if(existe_dans_ouvert( x, y-1)==false && existe_dans_fermer(x,y-1)==false)
		 	{
		 		point *a_ajouter=new point();
		 		a_ajouter->parent=fermer[point_actif];
		 		a_ajouter->x=x;
		 		a_ajouter->y=y-1;
		 		
		 		// CALCUL DU SCORE DE DEPART
		 		a_ajouter->score_depart=fermer[point_actif]->score_depart;
		// 		printf("score depart %d\n",a_ajouter->score_depart);
		 		if(crte->donnee_carte[y-1][x].type==TILE_INTERIEUR_MUR)
		 		{
		 			a_ajouter->score_depart+=SCORE_BLOC_PLEIN;
		 		}
		 		else
		 			a_ajouter->score_depart+=SCORE_BLOC_CREUX;
		 		///////////////////////////////////////////
		 		
		 		// Calcul du score d arrivee
		 		a_ajouter->score_arrive=abs(a_ajouter->x-finx)+abs(a_ajouter->y-finy);
		 		
		 		
		 		//placement de a_ajouter dans ouvert.
		 		placer_dans_ouvert(a_ajouter);
		 		
		 	}
		 	else if( existe_dans_ouvert( x, y-1,&ind))
		 	{
		 		 	
		 		 	if(crte->donnee_carte[y-1][x].type==TILE_INTERIEUR_MUR)
		 			{
		 			sc+=SCORE_BLOC_PLEIN+fermer[point_actif]->score_depart;
		 			}
		 			else
		 			sc+=SCORE_BLOC_CREUX+fermer[point_actif]->score_depart;
		 			
		 			
		 		 	// si le score est inferieur
					  if(ouvert[ind]->score_depart>sc)
					  {
					  	ouvert[ind]->parent=fermer[point_actif];
					  	ouvert[ind]->score_depart=sc;
					  }	
		 		
		 	}
		 	
		 	
		 }
		 //est 	
		 if(crte->donnee_carte[y+1][x].type<TILE_MUR)
		 {
		 	
		 	if(existe_dans_ouvert( x, y+1)==false && existe_dans_fermer(x,y+1)==false)
		 	{
		 		point *a_ajouter=new point();
		 		a_ajouter->parent=fermer[point_actif];
		 		a_ajouter->x=x;
		 		a_ajouter->y=y+1;
		 		
		 		// CALCUL DU SCORE DE DEPART
		 		a_ajouter->score_depart=fermer[point_actif]->score_depart;
		 		if(crte->donnee_carte[y+1][x].type==TILE_INTERIEUR_MUR)
		 		{
		 			a_ajouter->score_depart+=SCORE_BLOC_PLEIN;
		 		}
		 		else
		 			a_ajouter->score_depart+=SCORE_BLOC_CREUX;
		 		///////////////////////////////////////////
		 		
		 		// Calcul du score d arrivee
		 		a_ajouter->score_arrive=abs(a_ajouter->x-finx)+abs(a_ajouter->y-finy);
		 		
		 		//placement de a_ajouter dans ouvert.
		 		placer_dans_ouvert(a_ajouter);
		 		
		 	}
		 	else if( existe_dans_ouvert( x, y+1,&ind))
		 	{
		 		 	
		 		 	if(crte->donnee_carte[y][x+1].type==TILE_INTERIEUR_MUR)
		 			{
		 			sc+=SCORE_BLOC_PLEIN+fermer[point_actif]->score_depart;
		 			}
		 			else
		 			sc+=SCORE_BLOC_CREUX+fermer[point_actif]->score_depart;
		 			
		 			
		 		 	// si le score est inferieur
					  if(ouvert[ind]->score_depart>sc)
					  {
					  	ouvert[ind]->parent=fermer[point_actif];
					  	ouvert[ind]->score_depart=sc;
					  }	
		 		
		 	}
		 	
		 
	 	
	 	}	 
	 
	 
	}
	

return 0;
}


int astar(carte *crte, int debx, int deby, int finx,int finy)
{
	
	point *depart=new point();
	
	depart->parent=NULL;
	depart->x=debx;
	depart->y=deby;
	depart->score_depart=0;
	depart->score_arrive=abs(finx-debx)+abs(finy-deby);
	
	placer_dans_ouvert(depart);
//	point_actif=recup_score_faible();
	do
	{
		
		point_actif=recup_score_faible();
		if(point_actif==-1)
		{
/*			printf("-----------------------\n");
				for(int i=0;i<MAX_LIST_TAILLE;i++)	
				{
//					if(ouvert[i]!=NULL)printf("i%d, score%d\n",i,ouvert[i]->score_arrive);
				}
*/		
			vider_memoire_astar();
		return 0;		
		system("pause");
		break;
		
		}
		point_actif=passer_liste_fermer(point_actif);
		
		recherche_traitement_adjacent(crte,finx,finy);
		
	}while(fermer[point_actif]->x!=finx || fermer[point_actif]->y!=finy );
	
//	printf("fin");
	
//	printf("%d   %d",fermer[point_actif]->x,fermer[point_actif]->y);
	point *ptr=fermer[point_actif];
	
	while(ptr!=depart)
	{
		placer_tile(&crte->donnee_carte[ptr->y][ptr->x],TILE_SOL);
		
		ptr=ptr->parent;
		
	}
	
	vider_memoire_astar();
	return 0;
}

int vider_memoire_astar()
{
	
	for(int i=0;i<MAX_LIST_TAILLE ;i++)
	{
		if(ouvert[i]!=NULL)
		{
		delete ouvert[i];
		ouvert[i]=NULL;
		}
		if(fermer[i]!=NULL)
		{
		delete fermer[i];
		fermer[i]=NULL;
		}
	}
	
	return 0;
}

