
#define TILE_INTERIEUR_MUR	0
#define TILE_SOL			1
#define TILE_SOL_BRISE		2
#define TILE_SOL_VERRE		3
#define TILE_SOL_ACIDE		4
#define TILE_MUR			5
#define TILE_MUR_BRISE		6
#define TILE_VITRE			7
#define TILE_PORTE_FRAGILE	8
#define TILE_PORTE_NORMALE	9
#define TILE_PORTE_BLINDE	10
#define TILE_BARREAUX		11
#define TILE_ESCALIER_BAS	12
#define TILE_ESCALIER_HAUT	13

#define MAX_TILE			14

#define DESTRUC_IMPOSSIBLE	0
#define DESTRUC_FACILE		1
#define DESTRUC_MOYEN		2
#define DESTRUC_DUR			3

#define DOMMAGE_MARCHE_VERRE	3
#define DOMMAGE_RESTER_ACIDE	1

//description des tuiles constitutives des cartes
class tile
{
public:
	int type;
	int bmp_index;
	int bmp_index2; // pour les portes ouvertes
	char *name;
	char *description;
	
	int destructible_id;
	
	bool transparent;
	bool bloquant;
	
	bool ferme;
	bool verrouille;
	
	bool decouvert;
	bool champ_vision;
};

//définition des tiles de base pour la construction des cartes.
extern tile  prefab_tile[MAX_TILE];
extern char * nom_tile[MAX_TILE];
extern char * description_tile[MAX_TILE];
/////////////////////////////////////////

//////////////////////////////
//Fonction pour creer et détruire les tiles de base.
//
// Stocke les tiles de base dans prefab_tile
// stocke les noms et descriptions dans nom_til et description_tile 
int creation_tile_prefab();
int destruct_tile_prefab();
///////////////////////////////////////////////////
//////////////////////////////


//////////////////////////////
// Fonction pour placer un type de tile donne.
int placer_tile(tile *tle,int tile_type);
//////////////////////////////
////////////////////////////

// fonction pour copier un tile
int copie_tile(tile *dest,tile *source);


//fonction pour remplacer un tile
// Contraitement à la copie, ne modifie pas les propriete 
// de vision des tile.
int remplacer_tile(tile *dest,int tile_type);


//fonction pour ouvrir ou fermer une porte.
// SI la porte a ouvrir était verouillée 
// cette derniere est déverouillé pour eviter les
// eventuels probleme de joueur bloqué dans une piece sans issues
int ouvrir_fermer_porte(tile *prte);
