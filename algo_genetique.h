#ifndef H_GENETIQUE
#define H_GENETIQUE
#include "descentes.h"

// #define POPULATION_SIZE 50
// #define NUM_GENERATIONS 10000
// #define CROSSOVER_RATE 0.7
// #define MUTATION_RATE 0.1

typedef struct
{
    int *solution;
    int cost;
} Individual;

Individual *initialize_population(Instance *instance, int population_size);
Individual tournament_selection(Individual *population, int population_size, int tournament_size);
int *generate_n_positions(int size, int n);
void crossover(Instance *instance, Individual parent1, Individual parent2, Individual *child1, Individual *child2);
void mutate(Instance *instance, Individual *individual);
int *genetic_algorithm(Instance *instance, int nb_generations, int population_size, double crossover_rate, double mutation_rate);

#endif