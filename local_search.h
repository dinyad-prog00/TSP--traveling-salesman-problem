#ifndef H_LOCAL_SEARCH
#define H_LOCAL_SEARCH
#include "initialisation.h"
#include "descentes.h"

typedef int *(*MoveApplicator)(int *, int, Move);

int *apply_pertubations(int *solution, int size, MoveApplicator move_applicator, Move *moves, int num_moves, int nb_pertubations);
int *iterated_local_search(Instance *instance, int *soltution, Algorithm algo, MoveApplicator move_applicator, int nb_pertubations, int max_eval);

int *iterated_local_search_best_improver_swap(Instance *instance, int *soltution, int nb_pertubations, int max_eval);
int *iterated_local_search_best_improver_2opt(Instance *instance, int *soltution, int nb_pertubations, int max_eval);
int *iterated_local_search_first_improver_swap(Instance *instance, int *soltution, int nb_pertubations, int max_eval);
int *iterated_local_search_first_improver_2opt(Instance *instance, int *soltution, int nb_pertubations, int max_eval);
typedef int *(*AlgorithmILS)(Instance *, int *, int, int);

Move *generate_n_moves(Move *moves, int nb_moves, int n);
int *sampled_walk(Instance *instance, int *soltution, MoveApplicator move_applicator, int lambda, int max_eval);
int *sampled_walk_swap(Instance *instance, int *soltution, int lambda, int max_eval);
int *sampled_walk_2opt(Instance *instance, int *soltution, int lambda, int max_eval);
typedef int *(*AlgorithmSW)(Instance *, int *, int, int);
#endif