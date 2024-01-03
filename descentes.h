#ifndef H_DESCENTES
#define H_DESCENTES
#include "initialisation.h"

// swap
int new_cost_swap(Instance *instance, int *solution, int cost, Move move);
int *apply_move_swap(int *solution, int size, Move move);
int *best_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *worst_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *first_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);

int isNeighbour(Move move,int size);


// 2-opt
int new_cost_2opt(Instance *instance, int *solution, int cost, Move move);
int *apply_move_2opt(int *solution, int size, Move move);
int *best_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *worst_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);
int *first_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found);

// descente
// Il prend en argument l'instance , une solution initiale et la fonction de descente (algo) comme worst_improver_2opt, best_improver_swap, ...
typedef int *(*Algorithm)(Instance *, int *, int, Move *, int, int *);  // Pointeur de fonction, descentes algo
int *descente(Instance *instance, int *solution, Algorithm algo);

#endif