#include "lib.h"
#include "algo_genetique.h"

Individual *initialize_population(Instance *instance, int population_size)
{
    Individual *population = (Individual *)malloc(population_size * sizeof(Individual));

    for (int i = 0; i < population_size; i++)
    {
        population[i].solution = random_solution(instance->dim, i); //  une seed différente pour chaque individu
        population[i].cost = cost_function(instance, population[i].solution);
    }
    return population;
}


Individual tournament_selection(Individual *population, int population_size, int tournament_size)
{
    // Sélectionnons plusieurs individus aléatoires, puis retournons le meilleur
    Individual best_individual = population[rand() % population_size];

    for (int i = 1; i < tournament_size; i++)
    {
        Individual random_individual = population[rand() % population_size];
        if (random_individual.cost < best_individual.cost)
        {
            best_individual = random_individual;
        }
    }
    return best_individual;
}

int *generate_n_positions(int size, int n)
{
    int *indexes = malloc(size * sizeof(int));
    int i, j, tmp;
    int *gen = malloc(n * sizeof(int));

    for (i = 0; i < size; i++)
    {
        indexes[i] = i;
    }

    // Melange Fisher-Yates
    for (i = size - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        tmp = indexes[i];
        indexes[i] = indexes[j];
        indexes[j] = tmp;
    }

    for (i = 0; i < n; i++)
    {
        gen[i] = indexes[i];
    }
    free(indexes);
    return gen;
}



int contains(int *array, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            return 1;
        }
    }
    return 0;
}


/**
 * Nous choisissons aléatoirement nb_gen gènes du parent 1 et les copions à la même position dans l’enfant 1. 
 * Puis nous copions les gènes restants du parent 2 dans l’ordre dans lequel ils apparaissent. 
 * Ensuite, nous recommençons de même pour l’enfant 2 en commençant par le parent 2.
*/
void crossover(Instance *instance, Individual parent1, Individual parent2, Individual *child1, Individual *child2)
{

    int size = instance->dim, nb_gen = instance->dim / 3; // choix de nombre de genes pour le croisement

    // Sélectionner nb_gen positions aléatoires
    int *positions = generate_n_positions(size, nb_gen);

    

    // Initialiser les solutions des enfants
    child1->solution = (int *)malloc(size * sizeof(int));
    child2->solution = (int *)malloc(size * sizeof(int));


    for (int i = 0; i < size; i++)
    {
        child1->solution[i] = -1;
        child2->solution[i] = -1;
    }

    // Copier les gènes sélectionnés du parent 1 à l'enfant 1
    for (int i = 0; i < nb_gen; i++)
    {
        child1->solution[positions[i]] = parent1.solution[positions[i]];
    }

    // Copier les gènes restants du parent 2 à l'enfant 1
    int child1_index = 0;
    for (int i = 0; i < size; i++)
    {
        if (!contains(child1->solution, size, parent2.solution[i]))
        {
            while (child1_index < size && child1->solution[child1_index] != -1)
            {
                child1_index++;
            }
            if (child1_index < size)
            {
                child1->solution[child1_index] = parent2.solution[i];
            }
        }
    }

    // Répéter le processus pour l'enfant 2
    for (int i = 0; i < nb_gen; i++)
    {
        child2->solution[positions[i]] = parent2.solution[positions[i]];
    }

    int child2_index = 0;
    for (int i = 0; i < size; i++)
    {
        if (!contains(child2->solution, size, parent1.solution[i]))
        {
            while (child2_index < size && child2->solution[child2_index] != -1)
            {
                child2_index++;
            }
            if (child2_index < size)
            {
                child2->solution[child2_index] = parent1.solution[i];
            }
        }
    }

    child1->cost = cost_function(instance, child1->solution);
    child2->cost = cost_function(instance, child2->solution);
    free(positions);
}


/**
 * La mutation est simplement une permutation de deux gènes, tirés aléatoirement
*/
void mutate(Instance *instance, Individual *individual)
{
    // Sélectionner deux positions aléatoires à permuter

    int position1 = rand() % instance->dim;
    int position2 = rand() % instance->dim;

    // S'assurer que les positions sélectionnées sont différentes
    while (position1 == position2)
    {
        position2 = rand() % instance->dim;
    }

    // Permuter les gènes aux positions sélectionnées
    int temp = individual->solution[position1];

    individual->solution[position1] = individual->solution[position2];
    individual->solution[position2] = temp;
    individual->cost = cost_function(instance, individual->solution);
}



int *genetic_algorithm(Instance *instance, int nb_generations, int population_size, double crossover_rate, double mutation_rate)
{
    Individual *population = initialize_population(instance, population_size);

    for (int generation = 0; generation < nb_generations; generation++)
    {
        Individual *new_population = (Individual *)malloc(population_size * sizeof(Individual));

        for (int i = 0; i < population_size; i += 2)
        {

            Individual parent1 = tournament_selection(population, population_size, 5);
            Individual parent2 = tournament_selection(population, population_size, 5);

            Individual child1, child2;

            if (rand() / (double)RAND_MAX < crossover_rate) // simulation de probabilté (nb aléatoire entre 0 et 1)
            {

                crossover(instance, parent1, parent2, &child1, &child2);
            }
            else
            {
                child1 = parent1;
                child2 = parent2;
            }

            if (rand() / (double)RAND_MAX < mutation_rate) // simulation de probabilté (nb aléatoire entre 0 et 1)
            {

                mutate(instance, &child1);
            }
            if (rand() / (double)RAND_MAX < mutation_rate) // simulation de probabilté (nb aléatoire entre 0 et 1)
            {
                mutate(instance, &child2);
            }

            new_population[i] = child1;
            new_population[i + 1] = child2;
        }

        // Remplacez l'ancienne population par la nouvelle
        free(population);
        population = new_population;
    }

    // Sélectionnez le meilleur individu de la population finale comme solution
    Individual best_solution = population[0];
    for (int i = 1; i < population_size; i++)
    {
        if (population[i].cost < best_solution.cost)
        {
            best_solution = population[i];
        }
    }

    printf("Best solution found:\n");
    printf("Cost: %d\n", best_solution.cost);

    // print_tab(best_solution.solution, instance->dim);

    return best_solution.solution;
}
