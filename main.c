#include "initialisation.h"
#include "descentes.h"
#include "local_search.h"
#include "execution_comparison.h"
#include "lib.h"
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Instance *instance = load_instance("instances/atsp_rand_50_75.txt");
    printf("size : %d\n", instance->dim);

    //print_matrix(instance->matrix, instance->dim);

    int *solution = random_solution(instance->dim, 5);
    printf("\nSolution:\n");
    print_tab(solution, instance->dim);

    int cost = cost_function(instance, solution);
    printf("Cost : %d\n", cost);

    // test apply_move_2opt
    Move mv = {0, 4};
    printf("\nTest apply swap : (0,4):\n");

    print_tab(apply_move_swap(solution, instance->dim, mv), instance->dim);
    printf("\n");

    printf("\ncout normal: %d\n",cost_function(instance,apply_move_swap(solution, instance->dim, mv)));
    printf("\ncout incremental: %d\n", new_cost_swap(instance,solution,cost,mv));
    int num_cities = 5;

    int num_moves;
    Move *moves = generate_swap_moves(num_cities, &num_moves);

    // Tests
    // int best_found;
    // int *best = best_improver_swap(instance, solution, cost, moves, num_moves, &best_found);
    //  int *best = best_improver_2opt(instance, solution, cost, moves, num_moves, &best_found);

    // int *best = worst_improver_swap(instance, solution, cost, moves, num_moves, &best_found);
    // int *best = worst_improver_2opt(instance, solution, cost, moves, num_moves, &best_found);

    // int *best = first_improver_swap(instance, solution, cost, moves, num_moves, &best_found);
    //  int *best = first_improver_2opt(instance, solution, cost, moves, num_moves, &best_found);

    // if (best_found)
    // {
    //     printf("\nImprovment: \n");
    //     print_tab(best, instance->dim);
    // }
    // else
    // {
    //     printf("\nNo improvment found: \n");
    // }

    // Test algo
    //int *final = descente(instance, solution, best_improver_swap);
    // int *final = descente(instance,solution, best_improver_2opt);

    //int *final = descente(instance,solution, worst_improver_swap);
    //int *final = descente(instance,solution, worst_improver_2opt);

    //int *final = descente(instance,solution, first_improver_swap);
    //int *final = descente(instance,solution, first_improver_2opt);

    // Local search
    // int *final = iterated_local_search_best_improver_swap(instance, solution, 3, 500000);

    // int *final = sampled_walk_swap(instance, solution, 4, 200);

    // printf("\nSolution final: \n");
    // print_tab(final, instance->dim);
    // printf("\nNombre evaluations: %d", nombre_evaluations);
    free_instance(instance);
    free(solution);
    free(moves);


    execute();

    return 0;
}
