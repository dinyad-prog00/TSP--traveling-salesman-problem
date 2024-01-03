#ifndef H_GENETIQUE
#define H_GENETIQUE
#include "descentes.h"

/**
 * BONUS
 * J'ai choisi de faire l'algorithme génétique comme on a fait que des recherches locales.
*/

typedef struct
{
    int *solution;
    int cost;
} Individual;

//Initialiser la population
Individual *initialize_population(Instance *instance, int population_size);

//La sélection des parents
//La sélection des parents se fait sous la forme d’un tournoi entre tournament_size individus.
Individual tournament_selection(Individual *population, int population_size, int tournament_size);

//Générer n positions pour le croisement
int *generate_n_positions(int size, int n);

//Croisement
void crossover(Instance *instance, Individual parent1, Individual parent2, Individual *child1, Individual *child2);

//Mutation
void mutate(Instance *instance, Individual *individual);

//L'algo complet
int *genetic_algorithm(Instance *instance, int nb_generations, int population_size, double crossover_rate, double mutation_rate);

#endif