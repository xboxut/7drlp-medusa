

#define MAX_LIST_TAILLE     10000

#define SCORE_BLOC_PLEIN	2
#define SCORE_BLOC_CREUX	1

class point{
public:
point *parent;

int score_arrive;
int score_depart;

int x, y;

point(){parent=NULL;}	

};



extern point *ouvert[MAX_LIST_TAILLE];
extern point *fermer[MAX_LIST_TAILLE];
extern int point_actif;

//fonction qui retourne l endroit ou le score est le plus faible.
int recup_score_faible();

//fonction qui permet de stocker le point dans la liste fermée
int passer_liste_fermer(int pos);

//calcul cout


// traiter les points adjacent au point  actuel
int recherche_traitement_adjacent(carte *crte,int finx,int finy);

int astar(carte *crte, int debx, int deby, int finx,int finy);

int vider_memoire_astar();
/*
 Add the starting square (or node) to the open list.

2) Repeat the following:

a) Look for the lowest F cost square on the open list. We refer to this as the current square.

b) Switch it to the closed list.

c) For each of the 8 squares adjacent to this current square …

If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.           

If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the F, G, and H costs of the square. 

If it is on the open list already, check to see if this path to that square is better, using G cost as the measure. A lower G cost means that this is a better path. If so, change the parent of the square to the current square, and recalculate the G and F scores of the square. If you are keeping your open list sorted by F score, you may need to resort the list to account for the change.

d) Stop when you:

Add the target square to the closed list, in which case the path has been found (see note below), or
Fail to find the target square, and the open list is empty. In this case, there is no path.   
3) Save the path. Working backwards from the target square, go from each square to its parent square until you reach the starting square. That is your path. 


*/
