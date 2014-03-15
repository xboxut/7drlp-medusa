
#define OBJ_RIEN					1
#define OBJ_SERUM_PHYSIO			2
#define OBJ_BANDAGE					3
#define OBJ_MEDIPACK				4
#define OBJ_ADRENALINE				5
#define OBJ_FURIE_PACK				6
#define OBJ_SCALPEL					7
#define OBJ_COUTEAU					8
#define OBJ_COUTEAU_CMBT			9
#define OBJ_PISTOLET				10
#define OBJ_FUSIL_POMPE				11
#define OBJ_MITRAILLETTE			12
#define OBJ_MUNITION_PISTO			13
#define OBJ_MUNITION_FUSIL			14
#define OBJ_MUNITION_MITRA			15
#define OBJ_CHAUSSURE				16
#define OBJ_BOTTE_COMBAT			17
#define OBJ_PANTALON				18
#define OBJ_BLOUSE					19
#define OBJ_GANT					20
#define OBJ_BLOUSON					21
#define OBJ_GILET_PARE_B			22
#define OBJ_SAC						24 // A INTEGRER DANS PREFAB ACTUELLEMENT 13/04/2014 CETTE POSSIBILITE EST BRIDEE
#define OBJ_IMPLANT_VITESSE			25
#define OBJ_IMPLANT_FORCE			26
#define OBJ_IMPLANT_DXTRT			27
#define OBJ_GRENADE					28
#define OBJ_ANTIDOTE_FINAL			29
#define OBJ_CLE						30 // A INTEGRER DANS PREFAB

#define MAX_OBJ						31

class objet
{
	public:
	
	int objet_type;
	char *objet_nom;
	char *description;
	int x,y;
	int bmp_index;
	
	
	int degat;
	int protection;// Protection en pourcentage -> si la protect total fait 50 % cette qtté de degat sera absorbe a chaque coup
	
	int ajt_vie;
	int ajt_adrenaline;
	int ajt_furie;
	
	bool stop_sang;
	
	int etat_obj; // durée de vie de l objet  max 500 ?
	
	int ajt_perm_frce; //force max 20
	int ajt_perm_dxtrt;// dexterite max 20
	int ajt_perm_vitesse;
	
	int max_munition;
	int munition;
	
	int modif_vit_dplcment;
	
    objet();
    ~objet();
};
	
	
extern	objet prefab_objet[MAX_OBJ];
extern char *nom_objet[MAX_OBJ];
extern char *description_objet[MAX_OBJ];

//Fonction pour creer les ressources de base du jeu
// Ici, on creer les objets de base
//
// IL EST POSSIBLE DE MODIFIER LES PROPRIETES DES OBJETS 
// EN MODIFIANT LA FONCTION creer_prefab_objets
int creer_prefab_objets();
int supprimer_prefab_objets();
/////////////////////////////////////////////////

//objet *creer_objet(int x, int y, int type)
//
//Fonction pour creer un objet pour placer sur une carte, dans un inventaire
// ou dans un acteur de contenu.
//
//retourne un pointeur sur l'objet
objet *creer_objet(int x, int y, int type);
//////////////////////////////////////////


bool objet_est_arme(objet *obj);
bool objet_est_arme_rechargeable(objet *obj);
bool objet_est_habit(objet *obj);
bool objet_est_medic(objet *obj);
bool objet_est_implant(objet *obj);
bool objet_est_munition(objet *obj);



//renvoi le numero de l'emplacement a equiper
int emplacement_equipe(objet *obj);


