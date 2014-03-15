
#include <stdlib.h>
#include <string.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


#include "gestion_message.h"

/*************************
***CONSTRUCTEUR DESTRUCTEUR MESSAGE ******/

message::message()
{
	
	precedent=NULL;
    suivant=NULL;
	
    mess=NULL;	
	
	
	
}


message::~message()
{
	if(mess!=NULL)
	delete[] mess;
	
	
}
/////////////////////////////////////////////////////



/********************************************************
***********GESTIONNAIRE DE MESSAGE *********************/


//premier message du gestionnaire
message *gestionnaire_message::premier_mess=NULL;

int gestionnaire_message::ajout_message(const char *msg,ALLEGRO_COLOR colo)
{
	message *m=new message();
	message *der;
	
	m->mess=new char[strlen(msg)+1];
	strcpy(m->mess,msg);
	
	if(premier_mess==NULL)
	{
	premier_mess=m;
	m->col=colo;
	}
	else
	{
		
		der=recup_dernier_message();
		der->suivant=m;
		m->precedent=der;
		m->col=colo;
	   	
	}

return 0;
}





message *gestionnaire_message::recup_dernier_message()
{
	message *m;
	
	m=premier_mess;
	if(m==NULL)return m;
	
	while(m->suivant!=NULL)
	{
		
	  m=m->suivant;	
	}
	
	return m;
}

 message *gestionnaire_message::message_precedent(message *mess)
 {
 	


   return mess->precedent;
 }

	
	

int gestionnaire_message::calcul_nombre_message()
{
	message *m;
	int compt=0;
	
	m=premier_mess;
	
	if(m==NULL)return 0;
	
	compt++;
	while(m->suivant!=NULL)
	{
	  m=m->suivant;
	  compt++;	
	}
	
	return compt;
}




int gestionnaire_message::vider_messages()
{
	message *m;
	
	m=premier_mess;
	if(m==NULL)return 0;
	
	while(m->suivant!=NULL)
	{	
	  m=m->suivant;
	  delete m->precedent;
	}
	
	delete m;
	
	return 1;
}
/*******************************************************
*******************************************************/









