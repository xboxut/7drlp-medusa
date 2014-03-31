
#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


#include "gestion_message.h"

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

#include "moteur_jeu.h"

#include "astarcarte.h"
//constructeur destructeur
carte::carte()
{
	donnee_carte=NULL;

	x=0;
	y=0;
	
	cle_acquise=false;

	 for(int i=0;i<NB_MAX_OBJET;i++)
	 objet_tab[i]=NULL;
	 
	 for(int i=0;i<NB_MAX_ACTEUR;i++)
	 acteur_tab[i]=NULL;
	
	
}


carte::~carte()
{

	
}
////////////////////////////////////////

/**********************************************************************
***********************DONNE POUR LA CREATION DES CARTES *************
**********************************************************************/

//taille des cartes de jeu
// -> tirage nb aleatoire autour de ces valeur slon la loi normale
//									1,	    	2,		  ,3		  ,4		,5									
int carte_taille[NB_MAX_CARTES*2]={50,50,     70,50,     70,70,       70,70,    100,90,        /*1*/
								   100,100,	  100,100,  100,100,     110,100,    110,100,	   /*2*/								
								   110,105,   110,110,  120,100,     90,140,   120,140, 	   /*3*/										
								   120,140,   130,140,  140,140,     100,180,  120,160,		   /*4*/								
								   130,160,   140,170,  200,200,     210,200,  300,300  	   /*5*/										
																			};


//									     1		2		3		4		5							
int ecart_type_ctaille[NB_MAX_CARTES]= {3,     4,	   6,		5,		5,
										6,	   6,	   6,	    7,      8,         
										8,	   8,      8,       8,      8,
										9,	   9,	   9,		9,		9,			
						 				10,		10,		10,		10,		10,
									};	 
//nombre d'ennemi a placer sur les cartes
// -> tirage nb aleatoire autour de ces valeurs selon loi normale 
//									1,	2,	3,	4,	5, 
int carte_nb_ennemi[NB_MAX_CARTES]={3  , 10, 15, 20, 30,			/*1 */            
									35 , 40, 45, 55, 65,			/*2 */
									75 , 85, 95,105,110 ,			/*3	*/
									120,130,140,150,160,			/*4 */
									170,190,210,230,250,			/*5 */
									270,300,350,390,400				/*6 */
													};

int ecart_type_ennemi;


/**********************************************************************
***************************FONCTIONS DE CREATION DES CARTES*************
**********************************************************************/

//Fonction pour récupere une porte sans issue sur le morceau x1,y1,x2,y2
int recuperer_pos_porte_sans_issue(carte *crte,int x1,int y1,int x2,int y2,int *xresult,int *yresult)
{
	int cnt;
//	printf("entre recherche porte y1%d y2 %d", y1,y2);
	for(register int i=y1;i<=y2;i++)
	{
		
		for(register int j=x1;j<=x2;j++)
		{
			
			if(crte->donnee_carte[i][j].type>=TILE_PORTE_FRAGILE  && crte->donnee_carte[i][j].type<=TILE_PORTE_BLINDE)
			{
				
				
			 cnt=0;
			 if(crte->donnee_carte[i+1][j].type==TILE_INTERIEUR_MUR)	
				cnt++;
			 if(crte->donnee_carte[i][j+1].type==TILE_INTERIEUR_MUR)	
				cnt++;
			 if(crte->donnee_carte[i-1][j].type==TILE_INTERIEUR_MUR)	
				cnt++;	
			 if(crte->donnee_carte[i][j-1].type==TILE_INTERIEUR_MUR)	
				cnt++;
				
				if(cnt==1){
							*xresult=j;
							*yresult=i;
							return 1;
							}
			}
			
		}
		
		
	}
	
	*xresult=-1;
	*yresult=-1;
	return 0;
}

int recuperer_pos_porte_aleatoire(carte *crte,int x1,int y1,int x2,int y2,int *xresult,int *yresult)
{

int portecoord[300];
int nb_porte=0;
		for(register int i=y1;i<=y2;i++)
			{
				
				for(register int j=x1;j<=x2;j++)
				{
					
					if(crte->donnee_carte[i][j].type>=TILE_PORTE_FRAGILE  && crte->donnee_carte[i][j].type<=TILE_PORTE_BLINDE)
					{
						
					   portecoord[nb_porte*2]=j;
					   portecoord[nb_porte*2+1]=i;	
					  nb_porte++;
					   if(nb_porte==150)break;
					}
							
				}
				if(nb_porte==150)break;
				
			}
			
int ret=genrand_int32()%nb_porte;
	*xresult=portecoord[ret*2];
	*yresult=portecoord[ret*2+1];
		
			
return 0;	
}



// Fonction pour tester si une porte existe au nord sud est ouest
bool pas_de_porte_autour(carte *crte, int x,int y)
{
	
	if(crte->donnee_carte[y][x].type>=TILE_PORTE_FRAGILE && crte->donnee_carte[y][x].type<=TILE_PORTE_BLINDE)
	{
		return false;
	}
	if(crte->donnee_carte[y+1][x].type>=TILE_PORTE_FRAGILE && crte->donnee_carte[y+1][x].type<=TILE_PORTE_BLINDE)
	{
		return false;
	}
	if(crte->donnee_carte[y-1][x].type>=TILE_PORTE_FRAGILE && crte->donnee_carte[y-1][x].type<=TILE_PORTE_BLINDE)
	{
		return false;
	}
	if(crte->donnee_carte[y][x+1].type>=TILE_PORTE_FRAGILE && crte->donnee_carte[y][x+1].type<=TILE_PORTE_BLINDE)
	{
		return false;
	}
	if(crte->donnee_carte[y][x-1].type>=TILE_PORTE_FRAGILE && crte->donnee_carte[y][x-1].type<=TILE_PORTE_BLINDE)
	{
		return false;
	}
	
	return true;
}



//Fonction pour tester si du mobilier existe autour de la position.
bool pas_de_mobilier_autour(carte *crte, int x,int y)
{
		
	for(register int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(crte->acteur_tab[i]!=NULL)
		{
		//	printf("x %d,y %d xb %d yb %d\n test %d",crte->acteur_tab[i]->x,crte->acteur_tab[i]->y,x,y,(crte->acteur_tab[i]->x-1)==(x-1) && crte->acteur_tab[i]->y==y  );
	
			 if((crte->acteur_tab[i]->x)==(x-1) && crte->acteur_tab[i]->y==y )
			 {
			 	return false;
			 }	
			 if(crte->acteur_tab[i]->x==x+1 && crte->acteur_tab[i]->y==y )
			 {
			 	return false;
			 }
			  if(crte->acteur_tab[i]->x==x && crte->acteur_tab[i]->y==y+1 )
			 {
			 	return false;
			 }
			  if(crte->acteur_tab[i]->x==x && crte->acteur_tab[i]->y==y-1 )
			 {
			 	return false;
			 }
		}
	}
		
	return true;
}



//Fonction pour tester si endroit choisi est un coin de salle.
bool coin_de_salle(carte *carte, int x,int y)
{
	
	int cnt=0;
	
	if(!(carte->donnee_carte[y][x].type==TILE_MUR ||carte->donnee_carte[y][x].type==TILE_MUR_BRISE ))return false;
	
	
	if(carte->donnee_carte[y][x+1].type==TILE_MUR ||carte->donnee_carte[y][x+1].type==TILE_MUR_BRISE )
	{
		
		if(carte->donnee_carte[y-1][x].type==TILE_MUR ||carte->donnee_carte[y-1][x].type==TILE_MUR_BRISE )	
		return true;
		
		else if(carte->donnee_carte[y+1][x].type==TILE_MUR ||carte->donnee_carte[y+1][x].type==TILE_MUR_BRISE )
		return true;
		
	}
	else if(carte->donnee_carte[y][x-1].type==TILE_MUR ||carte->donnee_carte[y][x+1].type==TILE_MUR_BRISE )
	{
		if(carte->donnee_carte[y-1][x].type==TILE_MUR ||carte->donnee_carte[y-1][x].type==TILE_MUR_BRISE )	
		return true;
		
		else if(carte->donnee_carte[y+1][x].type==TILE_MUR ||carte->donnee_carte[y+1][x].type==TILE_MUR_BRISE )
		return true;
				
		
	}
	
	//if(carte->donnee_carte[y][x-1].type==TILE_MUR ||carte->donnee_carte[y][x-1].type==TILE_MUR_BRISE )cnt++;
	//if(carte->donnee_carte[y-1][x].type==TILE_MUR ||carte->donnee_carte[y-1][x].type==TILE_MUR_BRISE )cnt++;
	//if(carte->donnee_carte[y+1][x].type==TILE_MUR ||carte->donnee_carte[y+1][x].type==TILE_MUR_BRISE )cnt++;

//	if(cnt>=3)return true;
	
	return false;
	
}


/************************************** gestion de l'arbre binaire****/
/*
int ajout_branche(branche * preced,bool d,int decoup_limitalea,int long_min)
{
	
	branche *res=new branche();
		
	if(gen_rand_int32()%101<decoup_limitalea)
	{
		res->separation_dg=true;
	}
	else 
		res->separation_dg=false;
		
		
	if(d==false)
	{
		
	 if(preced->dg=false)
	 {
	 	res->x=preced->x;
	 	res->y=preced->y;
	 	res->h=preced->pos;
	 }
	 else
	 {
	 	
	 }
	
	}
	else
	{
		 if(preced->dg=false)
		 {
		 	
		 }
		 else
		 {
		 	
		 }	
	}

}


int recherche_taille_min_salle(int *x,int *y);

int ajout_niveau_branche(branche *tronc);

int transformer_en_coordonnee(branche *tronc)
*/

carte *creer_carte( int profondeur,int taille_piece, int occupation)
{
	
	int *piece;
    
	bool *a_creuser;
	int nb_piece_reel=0;
	int nb_piece;
	
	carte *res=new carte();
	
	res->x=int_rgauss( float(carte_taille[profondeur*2]), float(ecart_type_ctaille[profondeur]));
	res->y=int_rgauss( float(carte_taille[profondeur*2+1]), float(ecart_type_ctaille[profondeur]));

	res->donnee_carte=new tile*[res->y];
	
	for(int i=0;i<res->y;i++)
	{
		res->donnee_carte[i]=new tile[res->x];
		
		for(int j=0;j<res->x;j++)
		placer_tile(&res->donnee_carte[i][j],TILE_INTERIEUR_MUR);
	}
	
	
	nb_piece=(res->x*res->y)/(taille_piece*taille_piece);
	
	piece=new int[nb_piece*4];
	a_creuser=new bool[nb_piece];
	
	
	// Calcul des position des pieces. On laisse toujours 1 de gras entre chaque pieces
	int xcnt=0;
	int ycnt=0;
	
	while(1)
	{
	   xcnt=0;
		while(1)
		{	
		    
			piece[nb_piece_reel*4]=xcnt+1;
			piece[nb_piece_reel*4+1]=ycnt+1;
			
			piece[nb_piece_reel*4+2]=xcnt+1+taille_piece-1;
			piece[nb_piece_reel*4+3]=ycnt+1+taille_piece-1;
			
			xcnt+=1+taille_piece;
			nb_piece_reel++;
			if(xcnt+1+taille_piece-1>=res->x)break;		
			
		}
	
		ycnt+=1+taille_piece;
		if(ycnt+1+taille_piece-1>=res->y)break;		
			
	}
	
	
	int px1,px2,py1,py2,buff;
	for(int i=0;i<nb_piece_reel;i++)
	{
	
		if(genrand_int32()%101<=occupation)
		{
		
		a_creuser[i]=true;
		
		printf("piece %d (x%d y%d)sur %d: x%d, y %d; w%d, h%d %d\n",i,res->x,res->y,nb_piece_reel,piece[i*4],piece[i*4+1],piece[i*4+2],piece[i*4+3],a_creuser[i]);
	
	     do{
	     
	        py1=piece[i*4+1]+ genrand_int32()%(piece[i*4+3]-piece[i*4+1]+1);
	     	py2=piece[i*4+1]+ genrand_int32()%(piece[i*4+3]-piece[i*4+1]+1);
	     	
	     	if(py1-py2>0)
		 	{
		 		buff=py1;
		 		py1=py2;
		 		py2=buff;
		 	}
	     	
	     	
	 	}while(abs(py1-py2)<3 || py2>=res->y-3 || py1<2);
		
		 do{
	        px1=piece[i*4]+ genrand_int32()%(piece[i*4+2]-piece[i*4]+1);
	     	px2=piece[i*4]+ genrand_int32()%(piece[i*4+2]-piece[i*4]+1);

		 	if(px1-px2>0)
		 	{
		 		buff=px1;
		 		px1=px2;
		 		px2=buff;
		 	}
	 	

	 	}while(abs(px1-px2)<5 || px2>=res->x-3 || px1<2);
	 	
	 	
	 	printf("fabriquation salle\n");

		  //creer_salle(res,px1,py1,px2,py2);
		  creer_salle_pcsecu(res,px1,py1,px2,py2,false);
		}
		else a_creuser[i]=false;
		//construction de la pièce
		
	 
	}
	
	
/******************************************************
************LIAISON DES SALLES NOUVELLEMENT CREER**************
*******************************************************/
	 
	 int salle1,salle2;
	 int xporte1,xporte2;
	 int yporte1,yporte2;
	 
	 tile tilep1,tilep2;
	 
	 // Pour traiter les portes de maniere aléatoires
	 for(int i=0;i<100;i++ )
	 {
	 	
	 	
	 	do{
	 	
		   salle1=genrand_int32()%nb_piece_reel;
		}while(a_creuser[salle1]==false);
		
		do{
		
		   salle2=genrand_int32()%nb_piece_reel;
		}while(a_creuser[salle1]==false || salle2==salle1);
	
	
		recuperer_pos_porte_sans_issue(res,piece[salle1*4],piece[salle1*4+1],piece[salle1*4+2],piece[salle1*4+3],&xporte1,&yporte1);
		recuperer_pos_porte_sans_issue(res,piece[salle2*4],piece[salle2*4+1],piece[salle2*4+2],piece[salle2*4+3],&xporte2,&yporte2);		 	
			printf("\n result x1%d y1%d x2%d y2%d  %d\n",piece[salle1*4],piece[salle1*4+1],piece[salle1*4+2],piece[salle1*4+3],xporte1); 
	 	if(xporte1!=-1 && xporte2!= -1 )
	 	{
	 		printf("x1%d y1%d x2%d y2%d",xporte1,yporte1,xporte2,yporte2);
	 		copie_tile(&tilep1,&res->donnee_carte[yporte1][xporte1]);
	 		copie_tile(&tilep2,&res->donnee_carte[yporte2][xporte2]);
	 		placer_tile(&res->donnee_carte[yporte1][xporte1],TILE_SOL);
	 		placer_tile(&res->donnee_carte[yporte2][xporte2],TILE_SOL);
	 		astar(res, xporte1, yporte1, xporte2,yporte2);
	 		copie_tile(&res->donnee_carte[yporte1][xporte1],&tilep1);
	 		copie_tile(&res->donnee_carte[yporte2][xporte2],&tilep2);
	 		
	 		
	 	}
	 }
	
// pour traiter les portes restantes
	
	for(int i=0;i<20;i++ )
	 {
	 	
	 	
	 
	
		recuperer_pos_porte_sans_issue(res,2,2,res->x,res->y-2,&xporte1,&yporte1);
		recuperer_pos_porte_aleatoire(res,2,2,res->x,res->y-2,&xporte2,&yporte2);
			printf("\n resultbis x1%d y1%d x2%d y2%d  %d\n",piece[salle1*4],piece[salle1*4+1],piece[salle1*4+2],piece[salle1*4+3],xporte1); 
	 	if(xporte1!=-1  )
	 	{
	 		printf("x1%d y1%d x2%d y2%d",xporte1,yporte1,xporte2,yporte2);
	 		copie_tile(&tilep1,&res->donnee_carte[yporte1][xporte1]);
	 		copie_tile(&tilep2,&res->donnee_carte[yporte2][xporte2]);
	 		placer_tile(&res->donnee_carte[yporte1][xporte1],TILE_SOL);
	 		placer_tile(&res->donnee_carte[yporte2][xporte2],TILE_SOL);
	 		astar(res, xporte1, yporte1, xporte2,yporte2);
	 		copie_tile(&res->donnee_carte[yporte1][xporte1],&tilep1);
	 		copie_tile(&res->donnee_carte[yporte2][xporte2],&tilep2);
	 		
	 		
	 	}
	 }
//

	for(int i=0;i<20;i++ )
	 {
	 	
	 	
	 
	
		recuperer_pos_porte_aleatoire(res,2,2,res->x,res->y-2,&xporte1,&yporte1);
		recuperer_pos_porte_aleatoire(res,2,2,res->x,res->y-2,&xporte2,&yporte2);
			printf("\n resultbis x1%d y1%d x2%d y2%d  %d\n",piece[salle1*4],piece[salle1*4+1],piece[salle1*4+2],piece[salle1*4+3],xporte1); 
	 	if(xporte1!=-1  )
	 	{
	 		printf("x1%d y1%d x2%d y2%d",xporte1,yporte1,xporte2,yporte2);
	 		copie_tile(&tilep1,&res->donnee_carte[yporte1][xporte1]);
	 		copie_tile(&tilep2,&res->donnee_carte[yporte2][xporte2]);
	 		placer_tile(&res->donnee_carte[yporte1][xporte1],TILE_SOL);
	 		placer_tile(&res->donnee_carte[yporte2][xporte2],TILE_SOL);
	 		astar(res, xporte1, yporte1, xporte2,yporte2);
	 		copie_tile(&res->donnee_carte[yporte1][xporte1],&tilep1);
	 		copie_tile(&res->donnee_carte[yporte2][xporte2],&tilep2);
	 		
	 		
	 	}
	 }	 
////////////////////////////////
	
//	 astar(res, 1, 30, 45,30);
 decrouvrir_toute_carte(res);
	
	
	return res;
	
}


/*********************************************************************/

int creer_salle(carte*crte,int x1,int y1,int x2,int y2)
{

	for(int i=y1;i<=y2;i++)
	{
		
		for(int j=x1;j<=x2;j++)
		{
			placer_tile(&crte->donnee_carte[i][j],TILE_SOL);
			if(i==y1 || i==y2)
			{
				placer_tile(&crte->donnee_carte[i][j],TILE_MUR);
				
			}
		}
		placer_tile(&crte->donnee_carte[i][x1],TILE_MUR);
		placer_tile(&crte->donnee_carte[i][x2],TILE_MUR);
				
		
	}
	
	
	int x,y;
	for(int i=0;i<5;i++)
	{
		
		do
		{
			x=x1+genrand_int32()%(x2-x1+1);
			y=y1+genrand_int32()%(y2-y1+1);
		}while( !pas_de_porte_autour(crte,x,y)|| !(crte->donnee_carte[y][x].type==TILE_MUR) );
		
		placer_tile(&crte->donnee_carte[y][x],TILE_PORTE_FRAGILE);
	}	
	
	return 0;
}


int creer_salle_pcsecu(carte *crte, int x1, int y1, int x2, int y2,int orientation)
{
	
	int x_console;
	int y_mobilier;
	bool rack_arme=false;
	bool deux_console=false;
	bool table=false;
	bool bureau=false;
	int nb_porte=0;
	acteur *act;
	
	
    // creation du sol.
	for(int i=y1;i<=y2;i++)
	{
		
		for(int j=x1;j<=x2;j++)
		{
			if(genrand_int32()%101<93)
			placer_tile(&crte->donnee_carte[i][j],TILE_SOL);
			else
			placer_tile(&crte->donnee_carte[i][j],TILE_SOL_BRISE);
			if(i==y1 || i==y2)
			{
				placer_tile(&crte->donnee_carte[i][j],TILE_MUR);	
			}
		}
			placer_tile(&crte->donnee_carte[i][x1],TILE_MUR);
			placer_tile(&crte->donnee_carte[i][x2],TILE_MUR);
	}

	if(abs(x2-x1)*abs(y2-y1)>=40)
	{
		if(genrand_int32()%101<60)
		deux_console=true;
		
		if(genrand_int32()%101<50)
		bureau=true;
		if(genrand_int32()%101<50)
		table=true;
		
		nb_porte=2+genrand_int32()%2;
	}	
	else if(abs(x2-x1)*abs(y2-y1)>20)
	{
		
		rack_arme=true;
		
		if(genrand_int32()%101<30)
		table=true;
	    nb_porte=1+genrand_int32()%2;
	}
	
	// position de la premiere console
	x_console=genrand_int32()%(x2-x1-2);
	
 	act=placer_mobilier(x_console+x1+1, y1+1,ACTEUR_CONSOLE_INFO);
	ajouter_acteur(crte,act);
	
	
	// mise en place de la seconde console
	if(deux_console)
	{
		do
		{
			x_console=genrand_int32()%(x2-x1-2);
	
		}while(mobilier_present(crte,x_console,y1-1));
		
		act=placer_mobilier(x_console+x1+1, y1+1,ACTEUR_CONSOLE_INFO);
	    ajouter_acteur(crte,act);
				
		
	}
	
	//mise en place du rack d'arme	
	if(rack_arme)
	{
		do
		{
			y_mobilier=genrand_int32()%(y2-y1-2);
	
		}while(mobilier_present(crte,x2-1,y1+1+y_mobilier));
		
		act=placer_mobilier(x2-1, y1+1+y_mobilier,ACTEUR_RACK_ARME);
	    ajouter_acteur(crte,act);
		
	}
	
	

	
	if(bureau)
	{
		do
		{
			y_mobilier=genrand_int32()%(y2-y1-4);
     		x_console=genrand_int32()%(x2-x1-4);
	
		}while(mobilier_present(crte,x1+2+x_console,y1+2+y_mobilier));
		
		act=placer_mobilier(x1+2+x_console, y1+2+y_mobilier,ACTEUR_BUREAU);
	    ajouter_acteur(crte,act);
	}

	
	//position des portes
	for(int i=0;i<=nb_porte;i++)
	{
		
		do
		{
			y_mobilier=genrand_int32()%(y2-y1);
     		x_console=genrand_int32()%(x2-x1+1);
	     
		}while(pas_de_mobilier_autour(crte, x1+x_console ,y_mobilier+y1+1)==false ||
			   !pas_de_porte_autour(crte,x1+x_console,y_mobilier+y1+1) ||	
			   !(crte->donnee_carte[y_mobilier+y1+1][x1+x_console].type==TILE_MUR || crte->donnee_carte[y_mobilier+y1+1][x1+x_console].type==TILE_MUR_BRISE)
			   || coin_de_salle(crte, x1+x_console,y1+1+y_mobilier));
		
			printf("x%d, y%d    %d\n", x1+x_console,y1+1+y_mobilier,pas_de_mobilier_autour(crte, x1+x_console ,y_mobilier+y1+1) );
		    
			if(genrand_int32()%101<30)
			placer_tile(&crte->donnee_carte[y1+1+y_mobilier][x1+x_console],TILE_PORTE_FRAGILE);
			else
			placer_tile(&crte->donnee_carte[y1+1+y_mobilier][x1+x_console],TILE_PORTE_NORMALE);
			
			//positionnement des portes
			if(genrand_int32()%101<85)// GESTION DU VERROUILLAGE DE LA PORTE
			{
				crte->donnee_carte[y1+1+y_mobilier][x1+x_console].verrouille=true;
			}
			else if(genrand_int32()%101<8)// GESTION DE L'OUVERTURE DE LA PORTE
			{
				ouvrir_fermer_porte(&crte->donnee_carte[y1+1+y_mobilier][x1+x_console]);
			}
			
	}
	
	 for(int i=0;i<NB_MAX_ACTEUR;i++)
	 {
	 	if(crte->acteur_tab[i]!=NULL)
	 	printf("act %d x%d  y%d\n",i,crte->acteur_tab[i]->x,crte->acteur_tab[i]->y);
	 	
	 }

}


int creer_salle_animalerie(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_bloc_operatoire(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_cobayes(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_stocks(carte *crte, int x1, int y1, int x2, int y2,int orientation)
{
	acteur *act;
	int orien=0;
	int nb1,nb2;// variables diverse
	int stock_type; // 1-> stock medical, 2 stock arme, 3-> diverse -> etageres
	/********************************************************************************
	***********************PETIT STOCK***********************************************
	*********************************************************************************/
	
	stock_type=genrand_int32()%4;//choix du type de stock

	// REMPLISSAGE DE LA BASE DE LA PIECE	
	for(int i=y1;i<=y2;i++)
	{
		for(int j=x1;j<=x2;j++)
		{
			placer_tile(&crte->donnee_carte[i][j],TILE_SOL);
				//placer_tile(&crte->donnee_carte[y1][i],TILE_MUR);
		//	placer_tile(&crte->donnee_carte[y1+1][i],TILE_SOL);
		if(i==y1 || i==y2)placer_tile(&crte->donnee_carte[i][j],TILE_MUR);
		}
		placer_tile(&crte->donnee_carte[i][x1],TILE_MUR);
		placer_tile(&crte->donnee_carte[i][x2],TILE_MUR);
	}
	///////////////////////////////////
			
	if(abs(x2-x1)*abs(y2-y1)<= 20)
	{
		//*********PETIT STOCK TOUT EN LONGUEUR *********/
		if(abs(x2-x1)==2 || abs(y2-y1)==2) 	
		{
			// LONGUEUR SELON X ///////////////////////////////////////
			if((y2-y1)==3)
			{
			/*	for(int i=x1;i<=x2;i++)
				{
					placer_tile(&crte->donnee_carte[y1][i],TILE_MUR);
					placer_tile(&crte->donnee_carte[y1+1][i],TILE_SOL);
					placer_tile(&crte->donnee_carte[y2][i],TILE_MUR);
					if(i==x1 || i==x2)placer_tile(&crte->donnee_carte[y1+1][i],TILE_MUR);
				}	
			  */   
			    // Si la longueur est >= a 6  porte au milieu 2 etagere au bout
			    if(x2-x1>=5)
			    {
			    	orien=genrand_int32()%2;//tirage de l orientation 
			    	if(orien==0)nb1=y1;
			    	if(orien==1)nb1=y2;
			    	orien=genrand_int32()%(x2-x1-4);
			    	nb2=x1+2+orien;
			    	
			    	 	switch(stock_type)
					        {
					        	case 1://stock medical
					        			
					        			
			    						if(genrand_int32()%101<50)
			    						{
			    							//mise en place de l'armoire a medoc
						        			act=placer_mobilier(x1+1, y1+1,ACTEUR_ARMOIRE_MEDIC);
				    						ajouter_acteur(crte,act);
				    						  
				    						  if(genrand_int32()%101<30)
				    						  {
				    						  	act=placer_mobilier(x2-1, y1+1,ACTEUR_BOUTEILLE_GAZ);
				    							ajouter_acteur(crte,act);
				    						  }
				    						  else
				    						  {
				    						  	act=placer_mobilier(x2-1, y1+1,ACTEUR_ARMOIRE_MEDIC);
				    							ajouter_acteur(crte,act);
				    						  }
				    						
			    						}
			    						else
			    						{
			    							//mise en place de l'armoire a medoc
					        				act=placer_mobilier(x2-1, y1+1,ACTEUR_ARMOIRE_MEDIC);
			    							ajouter_acteur(crte,act);
			    							
			    							if(genrand_int32()%101<30)
				    						  {
				    						  	act=placer_mobilier(x1+1, y1+1,ACTEUR_BOUTEILLE_GAZ);
				    							ajouter_acteur(crte,act);
				    						  }
				    						  else
				    						  {
				    						  	act=placer_mobilier(x1+1, y1+1,ACTEUR_ARMOIRE_MEDIC);
				    							ajouter_acteur(crte,act);
				    						  }
				    							
			    						
			    						}
			    						// mise en place de la porte
			    						    if(genrand_int32()%101<40)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb1][nb2],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<30)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb1][nb2].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<5)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[nb1][nb2]);
			    							}
												
			    						   
					        	break;
					        	case 2:// stock militaire
					        			//mise en place de l'armoire a medoc
					        		
			    						   act=placer_mobilier(x2-1, y1+1,ACTEUR_RACK_ARME);
			    						   ajouter_acteur(crte,act);
			    						   act=placer_mobilier(x1+1, y1+1,ACTEUR_RACK_ARME);
			    						   ajouter_acteur(crte,act);
			    						   
			    						   // mise en place de la porte
			    						    if(genrand_int32()%101<60)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb1][nb2],TILE_PORTE_BLINDE);
			    						    }
			    							
			    							if(genrand_int32()%101<90)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb1][nb2].verrouille=true;
			    							}
					        	break;
					        	
					        	case 3://stock divers
					        		//mise en place de l'armoire a medoc
					        			act=placer_mobilier(x2-1, y1+1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						act=placer_mobilier(x1+1, y1+1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						  	
					        	break;
					        }
			    }
			    // Si la longueur <6 porte a un des bout/////////////////////////////////////
			    else{
			    
						    orien=genrand_int32()%2;//tirage de l orientation
						        if(orien==0)
			        			{
			        			  nb1=x1+1;
								  nb2=x2;	
			        			}
			        			else
			        			{
			        				nb1=x2-1;
			        				nb2=x1;
			        			}
							switch(stock_type)
					        {
					        	case 1://stock medical
					        			
					        			//mise en place de l'armoire a medoc
					        			act=placer_mobilier(nb1, y1+1,ACTEUR_ARMOIRE_MEDIC);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<40)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<30)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[y1+1][nb2].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<5)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[y1+1][nb2]);
			    							}
			    							
			    						
					        	break;
					        	case 2:// stock militaire
					        			//mise en place de l'armoire a medoc
					        			act=placer_mobilier(nb1, y1+1,ACTEUR_RACK_ARME);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<60)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_BLINDE);
			    						    }
			    							
			    							if(genrand_int32()%101<90)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[y1+1][nb2].verrouille=true;
			    							}
					        	
					        	break;
					        	case 3://stock divers
					        		//mise en place de l'armoire a medoc
					        			act=placer_mobilier(nb1, y1+1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<50)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<25)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[y1+1][nb2].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<8)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[y1+1][nb2]);
			    							}
			    							
					        	break;
					        }
			    }
			    ///FIN LONGUEUR SELON X//////////////////////////////////////////////
			}
			// LONGUEUR SELON Y
			else
			{
/*				for(int i=y1;i<=y2;i++)
				{
					placer_tile(&crte->donnee_carte[i][x1],TILE_MUR);
					placer_tile(&crte->donnee_carte[i][x1+1],TILE_SOL);
					placer_tile(&crte->donnee_carte[i][x2],TILE_MUR);
					if(i==y1 || i==y2)placer_tile(&crte->donnee_carte[i][x1+1],TILE_MUR);
				}	
*/				
				
				  // Si la longueur est >= a 6  porte au milieu 2 etagere au bout
			    if(y2-y1>=5)
			    {
			    	orien=genrand_int32()%2;//tirage de l orientation 
			    	if(orien==0)nb1=x1;
			    	if(orien==1)nb1=x2;
			    	orien=genrand_int32()%(y2-y1-4);
			    	nb2=y1+2+orien;
			    	
			    	 	switch(stock_type)
					        {
					        	case 1://stock medical
					        			
					        			
			    						if(genrand_int32()%101<50)
			    						{
			    							//mise en place de l'armoire a medoc
						        			act=placer_mobilier(x1+1, y1+1,ACTEUR_ARMOIRE_MEDIC);
				    						ajouter_acteur(crte,act);
				    						  
				    						  if(genrand_int32()%101<30)
				    						  {
				    						  	act=placer_mobilier(x1+1, y2-1,ACTEUR_BOUTEILLE_GAZ);
				    							ajouter_acteur(crte,act);
				    						  }
				    						  else
				    						  {
				    						  	act=placer_mobilier(x1+1, y2-1,ACTEUR_ARMOIRE_MEDIC);
				    							ajouter_acteur(crte,act);
				    						  }
				    						
			    						}
			    						else
			    						{
			    							//mise en place de l'armoire a medoc
					        				act=placer_mobilier(x1+1, y2-1,ACTEUR_ARMOIRE_MEDIC);
			    							ajouter_acteur(crte,act);
			    							
			    							if(genrand_int32()%101<30)
				    						  {
				    						  	act=placer_mobilier(x1+1, y1+1,ACTEUR_BOUTEILLE_GAZ);
				    							ajouter_acteur(crte,act);
				    						  }
				    						  else
				    						  {
				    						  	act=placer_mobilier(x1+1, y1+1,ACTEUR_ARMOIRE_MEDIC);
				    							ajouter_acteur(crte,act);
				    						  }
				    							
			    						
			    						}
			    						// mise en place de la porte
			    						    if(genrand_int32()%101<40)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][nb1],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][nb1],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<30)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb2][nb1].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<5)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[nb2][nb1]);
			    							}
												
			    						   
					        	break;
					        	case 2:// stock militaire
					        			//mise en place de l'armoire a medoc
					        		
			    						   act=placer_mobilier(x1+1, y1+1,ACTEUR_RACK_ARME);
			    						   ajouter_acteur(crte,act);
			    						   act=placer_mobilier(x1+1, y2-1,ACTEUR_RACK_ARME);
			    						   ajouter_acteur(crte,act);
			    						   
			    						   // mise en place de la porte
			    						    if(genrand_int32()%101<60)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][nb1],TILE_PORTE_NORMALE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][nb1],TILE_PORTE_BLINDE);
			    						    }
			    							
			    							if(genrand_int32()%101<90)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb2][nb1].verrouille=true;
			    							}
					        	break;
					        	
					        	case 3://stock divers
					        		//mise en place de l'armoire a medoc
					        			act=placer_mobilier(x1+1, y2-1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						act=placer_mobilier(x1+1, y1+1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						  	
					        	break;
					        }
			    }
			    // Si la longueur <6 porte a un des bout/////////////////////////////////////
			    else{
			    
						    orien=genrand_int32()%2;//tirage de l orientation
						        if(orien==0)
			        			{
			        			  nb1=y1+1;
								  nb2=y2;	
			        			}
			        			else
			        			{
			        				nb1=y2-1;
			        				nb2=y1;
			        			}
							switch(stock_type)
					        {
					        	case 1://stock medical
					        			
					        			//mise en place de l'armoire a medoc
					        			act=placer_mobilier(x1+1, nb1,ACTEUR_ARMOIRE_MEDIC);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<40)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][x1+1],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][x1+1],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<30)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb2][x1+1].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<5)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[nb2][x1+1]);
			    							}
			    							
			    						
					        	break;
					        	case 2:// stock militaire
					        			//mise en place de l'armoire a medoc
					        			act=placer_mobilier( x1+1,nb1,ACTEUR_RACK_ARME);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<60)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][x1+1],TILE_PORTE_NORMALE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[nb2][x1+1],TILE_PORTE_BLINDE);
			    						    }
			    							
			    							if(genrand_int32()%101<90)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[nb2][x1+1].verrouille=true;
			    							}
					        	
					        	break;
					        	case 3://stock divers
					        		//mise en place de l'armoire a medoc
					        			act=placer_mobilier(nb1, y1+1,ACTEUR_ETAGERE);
			    						ajouter_acteur(crte,act);
			    						    // mise en place de la porte
			    						    if(genrand_int32()%101<50)
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_FRAGILE);
			    						    }
			    						    else
			    						    {
			    						    	placer_tile(&crte->donnee_carte[y1+1][nb2],TILE_PORTE_NORMALE);
			    						    }
			    							
			    							if(genrand_int32()%101<25)// GESTION DU VERROUILLAGE DE LA PORTE
			    							{
			    								crte->donnee_carte[y1+1][nb2].verrouille=true;
			    							}
			    							else if(genrand_int32()%101<8)// GESTION DE L'OUVERTURE DE LA PORTE
			    							{
			    								ouvrir_fermer_porte(&crte->donnee_carte[y1+1][nb2]);
			    							}
			    							
					        	break;
					        }
			    }
			    ///FIN LONGUEUR SELON Y///////////////////////////////////////
			}
			
			
		}
		else
		{
			
		}
		/***********************************************/
	}
	else if(abs(x2-x1)*abs(y2-y1)<= 30)
	
	
	
	
	
}

int creer_salle_bureau(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_laboratoire(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_toilettes(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_hall(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_cafeteria(carte *crte, int x, int y, int w, int h,int orientation);
int creer_salle_dortoir(carte *crte, int x, int y, int w, int h,int orientation);



/*********************************************************************
**************************FONCTIONS DIVERSES ****************************
*********************************************************************/

int vider_champ_vision_carte(carte *crte)
{
	
	if(crte->donnee_carte==NULL)return 1;
	
	for(register int i=0;i<crte->y;i++)
	{
		for(register int j=0;j<crte->x;j++)
		crte->donnee_carte[i][j].champ_vision=false;
	}
	
	
	return 0;
}


int decrouvrir_toute_carte(carte *crte)
{
	
	if(crte->donnee_carte==NULL)return 1;
	
	for(register int i=0;i<crte->y;i++)
	{
		for(register int j=0;j<crte->x;j++)
		crte->donnee_carte[i][j].decouvert=true;
	}
		return 0;
}

//int validite_deplacement(carte *crte,int x,int y, int dx,int dy)
//
// Fonction pour tester la validité d'un déplacement
// RETOURNE 0 SI PAS DE  OBSTACLE
// RETOURNE 1 SI OBSTACLE TILE CASSABLE
// RETOURNE 2 SI OBSTACLE TILE INCASSABLE
// RETOURNE 3 SI OBSTACLE ACTEUR MOBILIER
// RETOURNE 4 SI OBSTACLE ACTEUR PERSONNAGE 
int validite_deplacement(carte *crte,int x,int y, int dx,int dy)
{
	
	if(crte->donnee_carte[y+dy][x+dx].bloquant==true)
	{
		if(crte->donnee_carte[y+dy][x+dx].destructible_id!=DESTRUC_IMPOSSIBLE)return 1;

		
		return 2;
	}

		
		for(int i=0;i<NB_MAX_ACTEUR ;i++)
		{
			if(crte->acteur_tab[i]!=NULL)
			{
				if(crte->acteur_tab[i]->x==x+dx && crte->acteur_tab[i]->y==y+dy)
				{
					if(crte->acteur_tab[i]->acteur_type<= ACTEUR_LIT && crte->acteur_tab[i]->bloquant==true)return 3;
					if(crte->acteur_tab[i]->acteur_type> ACTEUR_LIT && est_vivant(crte->acteur_tab[i]))return 4;//gestion des personnages vivants
				}
			}	
		}	
	
	
	return 0;
}



acteur* obtenir_ennemi(carte *crte,int x, int y)
{
	
		for(register int i=0;i<NB_MAX_ACTEUR ;i++)
		{
			if(crte->acteur_tab[i]!=NULL)
			{
				if(crte->acteur_tab[i]->x==x && crte->acteur_tab[i]->y==y)
				{
					if(crte->acteur_tab[i]->acteur_type> ACTEUR_LIT && est_vivant(crte->acteur_tab[i]))return crte->acteur_tab[i];
				}
			}	
		}	
	
return NULL;	
}


// Fonction pour recupererun pointeur sur l eventuel
// moilier present en x y
acteur *obtenir_mobilier(carte *crte,int x, int y)
{
			for(int i=0;i<NB_MAX_ACTEUR ;i++)
		{
			if(crte->acteur_tab[i]!=NULL)
			{
				if(crte->acteur_tab[i]->x==x && crte->acteur_tab[i]->y==y)
				{
					if(crte->acteur_tab[i]->acteur_type<= ACTEUR_LIT &&  crte->acteur_tab[i]->bloquant==true )return crte->acteur_tab[i];
		
				}
			}	
		}	
	
return NULL;
}


bool mobilier_present(carte *crte,int x, int  y)
{
	
	
		for(int i=0;i<NB_MAX_ACTEUR ;i++)
		{
			if(crte->acteur_tab[i]!=NULL)
			{
				if(crte->acteur_tab[i]->x==x && crte->acteur_tab[i]->y==y)
				{
					if(crte->acteur_tab[i]->acteur_type<= ACTEUR_LIT)return true;
				}
			}	
		}	
	
	return false;
}



//Fonction pour stocker les acteurs dans la carte.
int ajouter_acteur(carte *crte,acteur *act)
{
	
	
	for( int i=0;i<NB_MAX_ACTEUR;i++)
	{
		if(crte->acteur_tab[i]==NULL)
		{
			
			crte->acteur_tab[i]=act;
			return 1;
		}
		
	}
	
	return 0;
}

// fonction pour placer un objet deja existant sur la carte
int ajouter_objet(carte *crte,objet *obj)
{
	for( int i=0;i<NB_MAX_OBJET;i++)
	{
		if(crte->objet_tab[i]==NULL)
		{
			
			crte->objet_tab[i]=obj;
			return 1;
		}
		
	}
	
	return 0;
	
}

carte * cree_carte_test()
{
	carte *crt=new carte();
	
	
	crt->x=50;
	crt->y=50;
	
	crt->donnee_carte=new tile*[crt->y];
	
	for(int i=0;i<crt->y;i++)
	{
	   crt->donnee_carte[i]=new tile[crt->x];
		
		for(int j=0;j<crt->x;j++)
		placer_tile(&crt->donnee_carte[i][j], TILE_INTERIEUR_MUR);
	
	}
	
	for(int i=21;i<39;i++)
	{
	  	
		for(int j=20;j<40;j++)
		{
		placer_tile(&crt->donnee_carte[i][j], TILE_SOL);
	//	crt->donnee_carte[i][j].decouvert=true;
		}
		
		placer_tile(&crt->donnee_carte[i][20], TILE_MUR);
		placer_tile(&crt->donnee_carte[i][39], TILE_MUR);
	   
//	    crt->donnee_carte[i][20].decouvert=true;
//	    crt->donnee_carte[i][39].decouvert=true;
	    
	}
	
	for(int j=20;j<40;j++)
	{
		placer_tile(&crt->donnee_carte[20][j], TILE_MUR);
//		crt->donnee_carte[20][j].decouvert=true;
	
	}
	
	for(int j=20;j<40;j++)
	{
	
		placer_tile(&crt->donnee_carte[39][j], TILE_MUR);
//		crt->donnee_carte[39][j].decouvert=true;	
	}

	for(int j=39;j<45;j++)
	{
		placer_tile(&crt->donnee_carte[22][j], TILE_MUR);
		placer_tile(&crt->donnee_carte[23][j], TILE_SOL);		
		placer_tile(&crt->donnee_carte[24][j], TILE_SOL);		
		placer_tile(&crt->donnee_carte[25][j], TILE_SOL);
		placer_tile(&crt->donnee_carte[26][j], TILE_MUR);				
	}
	
	for(int j=39;j<45;j++)
	{
		placer_tile(&crt->donnee_carte[29][j], TILE_MUR);
		placer_tile(&crt->donnee_carte[30][j], TILE_SOL);	
		placer_tile(&crt->donnee_carte[31][j], TILE_MUR);				
	}
	
	
 	crt->objet_tab[0]=creer_objet(25, 25, OBJ_MUNITION_PISTO);
	crt->objet_tab[1]=creer_objet(30, 30, OBJ_MUNITION_PISTO);
	crt->objet_tab[2]=creer_objet(30, 30, OBJ_MEDIPACK);	
return crt;	
}



/*****************************************************************************
*********************** INTERACTION DU MOBILIER AVEC LA CARTE ***************/

//int effectuer_explosion(carte *crte, int x, int y, int rayon, int max_dmg);
//
//Fonction pour faire exploser les grenades ou les bouteilles de gaz
// applique des degats a l'ensemble des acteur autour de l'explosion
// avec un facteur 1/r^2 pour plus de realisme.
// Le degat sont ensuite infligés aux tiles comme les portes les vites etc.
int effectuer_explosion(carte *crte, joueur *ply1, int x, int y, int rayon, int max_dmg)
{
	int retour=0;
	int dommage=0;
	bool mort=false;
	char message[512];
	
	/*******************TRAITEMENT DES ACTEUR *******************
	************************************************************/
	for(int i=0;i<NB_MAX_ACTEUR;i++)
	{
		
	 if(crte->acteur_tab[i]!=NULL)
	 {           
	               printf("i %d\n",i);    
	 	 		 // SI L ACTEUR EST DANS LE RAYON DE L'EXPLOSION
				 if((x-crte->acteur_tab[i]->x)*(x-crte->acteur_tab[i]->x)+
				  (y-crte->acteur_tab[i]->y)*(y-crte->acteur_tab[i]->y)<=rayon*rayon )
				{
				
				    if(crte->acteur_tab[i]->acteur_type==ACTEUR_BOUTEILLE_GAZ &&  est_vivant(crte->acteur_tab[i]))
				    {
				    	crte->acteur_tab[i]->vie-=max_dmg/((x-crte->acteur_tab[i]->x)*(x-crte->acteur_tab[i]->x)+
				  											(y-crte->acteur_tab[i]->y)*(y-crte->acteur_tab[i]->y));
				  		
				  		//GESTION DE L EXPLOSION POSSIBLE
				  		if(crte->acteur_tab[i]->vie<=0)
				  		{
				  		  moteur_jeu::ajouter_mess_console("L'explosion detruit la bouteille de gaz.",al_map_rgb(255,0,0));
				  		if(detruire_bouteille_gaz(crte,crte->acteur_tab[i],ply1)==1)retour=1;
						}
						else
						{
						  moteur_jeu::ajouter_mess_console("L'explosion endommage la bouteille de gaz.",al_map_rgb(255,0,0));	
						}
				    }
				    else if(crte->acteur_tab[i]->acteur_type==ACTEUR_CONTENEUR_ACIDE &&  est_vivant(crte->acteur_tab[i]))
				    {
				    	crte->acteur_tab[i]->vie-=max_dmg/((x-crte->acteur_tab[i]->x)*(x-crte->acteur_tab[i]->x)+
				  											(y-crte->acteur_tab[i]->y)*(y-crte->acteur_tab[i]->y));
				  	    if(crte->acteur_tab[i]->vie<=0)
				  	    {
				  	    moteur_jeu::ajouter_mess_console("L'explosion eventre le conteneur d'acide!",al_map_rgb(255,0,0));
						detruire_conteneur_acide(crte,crte->acteur_tab[i]);
				  		}
				  		else
				  		{
				  		  moteur_jeu::ajouter_mess_console("Le recipient d'acide est endommage par l'explosion.",al_map_rgb(255,0,0));
					  	}
					
					}
				    else if(crte->acteur_tab[i]->acteur_type>=ACTEUR_SCIENTIFIQUE_BASE &&  est_vivant(crte->acteur_tab[i]))
				    {
				    	dommage=max_dmg/((x-crte->acteur_tab[i]->x)*(x-crte->acteur_tab[i]->x)+
				  											(y-crte->acteur_tab[i]->y)*(y-crte->acteur_tab[i]->y));
				  	
					  	crte->acteur_tab[i]->vie-=dommage;
					  	
					  	//gestion de la mort
					  	if(est_vivant(crte->acteur_tab[i])==false)mort=true;
					  	
					  	if(mort)
					  	{
					  		sprintf(message,"Le souffle de l'explosion tue un %s",crte->acteur_tab[i]->acteur_nom);
					  		ajout_adrenaline(ply1,0,ply1->adrenaline_max/20,false);
					  		transformer_en_cadavre(crte->acteur_tab[i]);
						}
					  	else
					  	{
					  		sprintf(message,"Le souffle de l'explosion blesse un %s",crte->acteur_tab[i]->acteur_nom);
					  		ajout_adrenaline(ply1,0,2,false);
						}
						
						moteur_jeu::ajouter_mess_console(message,al_map_rgb(255,0,0));
									
					  	mort=false;
				    }
				
				}  
				  
	 }	
		
	}
	
	/*******************TRAITEMENT DU JOUEUR ********************
	************************************************************/
		 if((x-ply1->x)*(x-ply1->x)+
				  (y-ply1->y)*(y-ply1->y)<=rayon*rayon )
		 {
		 	
		 	ply1->vie-=max_dmg/((x-ply1->x)*(x-ply1->x)+
				  					(y-ply1->y)*(y-ply1->y));
				  					
		   if(ply1->vie<=0)
		   retour=1;
		 	
		 }		
	
	/*******************TRAITEMENT DES TILES*********************
	*************************************************************/
	int i=y-rayon;
	int j;
	int limx=x+rayon;
	int limy=y+rayon;
	
	if(i<0)i=0;
	if(limx>=crte->x)limx=crte->x-1;
	if(limy>=crte->y)limy=crte->y-1;
	
	
	for(;i<=limy;i++)
	{
		j=y-rayon;
		if(j<0)j=0;
		
		for(int j=x-rayon;j<limx;j++)
		{
			if((x-j)*(x-j)+(y-i)*(y-i)<=rayon*rayon) // Si le tile est dans le rayon d'explosion
			{
				switch(crte->donnee_carte[i][j].type)
				{
					case TILE_SOL:
						if(genrand_int32()%101<30)
						{
							remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL_BRISE);
						}
						
					break;
					//////
					case TILE_VITRE:
						remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL_VERRE);
						
					break;
					//////
					case TILE_PORTE_FRAGILE:
					case TILE_PORTE_NORMALE:
						remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL);
						
					break;
					//////
					case TILE_PORTE_BLINDE:
						if(genrand_int32()%101<90)
						{
							if(genrand_int32()%101<30)
							{
								remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL_BRISE);
							}
							else
								remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL);

						}
					break;
					//////
					case TILE_BARREAUX:
						if(genrand_int32()%101<90)
						{
								if(genrand_int32()%101<30)
								{
									remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL_BRISE);
								}
								else
									remplacer_tile(&crte->donnee_carte[i][j],TILE_SOL);
						}
					break;
					//////
					
				}
			}
		}
	}
	
	return retour;
}

//int repandre_acide(carte *crte,int x, int y);
//
// Fontion pour remplacer le sol autour de bouteilles d'acide
// par des flaques de liquide corrosif 1 carreau autour de la position x,y
int repandre_acide(carte *crte,int x, int y)
{
	
	if(crte->donnee_carte[y][x].type==TILE_SOL || 
	   crte->donnee_carte[y][x].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y][x].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y][x],TILE_SOL_ACIDE);
	
	if(crte->donnee_carte[y-1][x-1].type==TILE_SOL || 
	   crte->donnee_carte[y-1][x-1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y-1][x-1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y-1][x-1],TILE_SOL_ACIDE);
	
	if(crte->donnee_carte[y-1][x].type==TILE_SOL || 
	   crte->donnee_carte[y-1][x].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y-1][x].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y-1][x],TILE_SOL_ACIDE);

	if(crte->donnee_carte[y-1][x+1].type==TILE_SOL || 
	   crte->donnee_carte[y-1][x+1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y-1][x+1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y-1][x+1],TILE_SOL_ACIDE);
	
	if(crte->donnee_carte[y][x-1].type==TILE_SOL || 
	   crte->donnee_carte[y][x-1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y][x-1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y][x-1],TILE_SOL_ACIDE);
	
	if(crte->donnee_carte[y][x+1].type==TILE_SOL || 
	   crte->donnee_carte[y][x+1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y][x+1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y][x+1],TILE_SOL_ACIDE);
	
	if(crte->donnee_carte[y+1][x-1].type==TILE_SOL || 
	   crte->donnee_carte[y+1][x-1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y+1][x-1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y+1][x-1],TILE_SOL_ACIDE);

	if(crte->donnee_carte[y+1][x].type==TILE_SOL || 
	   crte->donnee_carte[y+1][x].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y+1][x].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y+1][x],TILE_SOL_ACIDE);


	if(crte->donnee_carte[y+1][x+1].type==TILE_SOL || 
	   crte->donnee_carte[y+1][x+1].type==TILE_SOL_BRISE ||
	   crte->donnee_carte[y+1][x+1].type==TILE_SOL_VERRE)
	remplacer_tile(&crte->donnee_carte[y+1][x+1],TILE_SOL_ACIDE);

	return 0;	
}



//int detruire_bouteille_gaz(carte *crte,acteur *act);
//
//Fonction pour détruire une bouteille de gaz.
// transforme l'affichage, la caracteristique passable ou non
// et genere une explosion
//
//retourne 0 si ras
// retoune 1 si l'explosion tue le joueur
int detruire_bouteille_gaz(carte *crte,acteur *act,joueur *ply1)
{
	for(int i=0;i<NB_MAX_OBJET;i++)
	{
		
        if(crte->acteur_tab[i]==act)
		{
			
			act->bmp_index=act->bmp_index_detruit;
			act->bloquant=false;
			
			if(effectuer_explosion(crte, ply1, crte->acteur_tab[i]->x, crte->acteur_tab[i]->y, RAYON_EXPLOSION, DEGAT_EXPLOSION)==1)
			return 1;
			else
			return 0;

		}		
		
	}
	return 0;
}
int detruire_bouteille_gaz(carte *crte,int index,joueur *ply1)
{
	if(crte->acteur_tab[index]!=NULL && 
	   crte->acteur_tab[index]->acteur_type==ACTEUR_BOUTEILLE_GAZ)
	{
			crte->acteur_tab[index]->bmp_index=crte->acteur_tab[index]->bmp_index_detruit;
			crte->acteur_tab[index]->bloquant=false;
			
			if(effectuer_explosion(crte, ply1, crte->acteur_tab[index]->x, crte->acteur_tab[index]->y, RAYON_EXPLOSION, DEGAT_EXPLOSION)==1);
			return 1;
	}
	return 0;
}

 

// int detruire_conteneur_acide(carte *crte,acteur *act);
//
//Fonction pour détruire un conteneur d'acide.
// transforme l'affichage, la caracteristique passable ou non
// et repand l'acide surle sol
//
int detruire_conteneur_acide(carte *crte,acteur *act)
{
	
	for(int i=0;i<NB_MAX_OBJET;i++)
	{
		
        if(crte->acteur_tab[i]==act)
		{
			
			act->bmp_index=act->bmp_index_detruit;
			act->bloquant=false;
			
			repandre_acide(crte,act->x,act->y);
			
			return 1;
			
		}		
		
	}
	
	return 0;
}

int detruire_conteneur_acide(carte *crte,int index)
{
	
	if(crte->acteur_tab[index]!=NULL && 
	   crte->acteur_tab[index]->acteur_type==ACTEUR_CONTENEUR_ACIDE)
	{
			crte->acteur_tab[index]->bmp_index=crte->acteur_tab[index]->bmp_index_detruit;
			crte->acteur_tab[index]->bloquant=false;
			
			repandre_acide(crte,crte->acteur_tab[index]->x,crte->acteur_tab[index]->y);
			
			return 1;
	}

return 0;
}

 
 
 

 /****************************************************************
 *****************INTERACTION DES ACTEURS AVEC LA CARTE *********/
 
 //int maj_degat_acide(joueur *jr);
//
//Fonction pour ajouter d'eventuels degat du
// a l'acide.
// retourne 0 si la santé atteint 0
// retourne 1 si il y a dégat du a l acide
// retourne 2 si il n y a pas de dégat du a l acide
// LES CHAUSSURES PROTEGENT DE L ACIDE MAIS SE DEGRADENT VITE.
int maj_degat_acide(joueur *jr,carte *crte)
{
	char message[512];
	if(crte->donnee_carte[jr->y][jr->x].type==TILE_SOL_ACIDE)
	{
		
		if(jr->equipement[EQUIPMNT_CHAUSSURE]!=NULL)
		{
			jr->equipement[EQUIPMNT_CHAUSSURE]->etat_obj-=DOMMAGE_RESTER_ACIDE;
			
			// Prise en compte de la destruction des objets chaussess
			if(jr->equipement[EQUIPMNT_CHAUSSURE]->etat_obj<=0)
			{
				delete jr->equipement[EQUIPMNT_CHAUSSURE];
				jr->equipement[EQUIPMNT_CHAUSSURE]=NULL;
				moteur_jeu::ajouter_mess_console("Vos chaussures, gravement attaquees par l'acide, partent en lambeaux.",al_map_rgb(255,255,255));
 
			}
			else
			{
			sprintf(message,"Vos chaussures fondent sous l'effet de l'acide. Etat: %d.", jr->equipement[EQUIPMNT_CHAUSSURE]->etat_obj);
			moteur_jeu::ajouter_mess_console(message,al_map_rgb(255,255,255));
			}
			return 1;
		}
		else
		{
			jr->vie-=DOMMAGE_RESTER_ACIDE;
			ajout_adrenaline(jr,DOMMAGE_RESTER_ACIDE,0,false);
			sprintf(message,"La plante de vos pieds est attaque par l'acide: %d de degats.",DOMMAGE_RESTER_ACIDE);
			moteur_jeu::ajouter_mess_console(message,al_map_rgb(0,0,255));
		
			if(jr->vie<=0)return 0;
		
			return 1;
		}
		
	}
	
	return 2;
}

int maj_degat_acide(acteur *act,carte *crte)
{
	
	if(crte->donnee_carte[act->y][act->x].type==TILE_SOL_ACIDE)
	{
		
		if(act->equipement[EQUIPMNT_CHAUSSURE]!=NULL)
		{
			act->equipement[EQUIPMNT_CHAUSSURE]->etat_obj-=DOMMAGE_RESTER_ACIDE;
			
			// Prise en compte de la destruction des objets chaussess
			if(act->equipement[EQUIPMNT_CHAUSSURE]->etat_obj<=0)
			{
				delete act->equipement[EQUIPMNT_CHAUSSURE];
				act->equipement[EQUIPMNT_CHAUSSURE]=NULL;
				
			}
			
			return 1;
		}
		else
		{
			act->vie-=DOMMAGE_RESTER_ACIDE;
			
			if(act->vie<=0)
			{
			
				 transformer_en_cadavre(act);
				return 0;
			}
			
			
			return 1;
		}
		
	}
	
	
	return 2;
}

//int ajout_degat_verre(joueur *jr);
//
//Fonction pour ajouter d'eventuels degat du
// aux morceaux de verrespar terre si l'acteur ou le joueur
// ne possède pas de chaussure
// retourne 0 si la santé atteint 0
// retourne 1 si il y a dégat du a verre
// retourne 2 si il le joueur ne prend pas de dégat 
int ajout_degat_verre(joueur *jr,carte *crte)
{
	char message[512];
	if(crte->donnee_carte[jr->y][jr->x].type==TILE_SOL_VERRE)
	{
		
		if(jr->equipement[EQUIPMNT_CHAUSSURE]==NULL)
		{
		
		
			jr->vie-=DOMMAGE_MARCHE_VERRE;
			ajout_adrenaline(jr,DOMMAGE_MARCHE_VERRE,0,false);
			faire_saigner(jr);
			sprintf(message,"Des morceaux s'enfoncent dans vos plantes de pieds: %d de degats.",DOMMAGE_MARCHE_VERRE);
			moteur_jeu::ajouter_mess_console(message,al_map_rgb(0,0,255));
		
			if(jr->vie<=0)return 0;
		
			return 1;
		}
		
	}
	
	return 2;
	
	
	
}
int ajout_degat_verre(acteur *act,carte *crte)
{
	char message[512];
	if(crte->donnee_carte[act->y][act->x].type==TILE_SOL_VERRE)
	{
		
		if(act->equipement[EQUIPMNT_CHAUSSURE]==NULL)
		{
		
		
			act->vie-=DOMMAGE_MARCHE_VERRE;
		
		
			if(act->vie<=0)
			{
			
				 transformer_en_cadavre(act);
				return 0;
			}
		
			return 1;
		}
		
	}
	
	return 2;
	
}
	
