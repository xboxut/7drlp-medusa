


class message
{
public:

message *precedent;
message *suivant;
	
char * mess;	
ALLEGRO_COLOR col;	
  message();
  ~message();
};


/*
Classe de gestion de messages.

permet d'afficher les messages envoyés par les différentes fonctions du jeu.
comme -> l equipement du joueur, les dégat pris et données, la destruction dobjet
etc
*/
class gestionnaire_message
{
	public:
	
	static message *premier_mess;
	
	static int ajout_message(const char *msg,ALLEGRO_COLOR col);
	static message *recup_dernier_message();
	static message *message_precedent(message *mess);
	static int calcul_nombre_message();
	
	static int vider_messages();
	
};








