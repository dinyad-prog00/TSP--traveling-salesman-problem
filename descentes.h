#ifndef H_DESCENTES
#define H_DESCENTES
#include "initialisation.h"

/**
 * Partie 2
*/

// Avec swap
// -------------------------

//Evaluation incrémentale (ou non: décommenter), seulement utilisée dans les descentes
int new_cost_swap(Instance *instance, int *solution, int cost, Move move);

//Appliquer le mouvement à la solution pour obtenir une nouvelle solution.
int *apply_move_swap(int *solution, int size, Move move);

//Les méthodes swap
int *best_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *worst_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *first_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);

//c1,c2 deux villes qui se suivent
int isNeighbour(Move move,int size);


// Avec 2-opt
// -------------------------

//Evaluation 
int new_cost_2opt(Instance *instance, int *solution, int cost, Move move);

//Appliquer le mouvement à la solution pour obtenir une nouvelle solution.
int *apply_move_2opt(int *solution, int size, Move move);

//Les méthodes 2-opt
int *best_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *worst_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *first_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);

// Descente complète
// Il prend en argument l'instance , une solution initiale et la fonction de descente (algo) comme worst_improver_2opt, best_improver_swap, ...
typedef int *(*Algorithm)(Instance *, int *, int, Move *, int, int *);  // Pointeur de fonction, descentes algo
int *descente(Instance *instance, int *solution, Algorithm algo);

#endif