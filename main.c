#include "initialisation.h"
#include "descentes.h"
#include "lib.h"
int main(int argc, char const *argv[])
{
    Instance *instance = load_instance("instances/atsp_rand_80_70.txt");
    printf("size : %d\n", instance->dim);

    print_matrix(instance->matrix, instance->dim);

    int *solution = random_solution(instance->dim);
    printf("\nSolution:\n");
    print_tab(solution, instance->dim);

    int cost = cost_function(instance, solution);
    printf("Cost : %d\n", cost);

    // test apply_move_2opt
    Move mv = {0, 4};
    printf("\nTest apply 2opt : (0,4):\n");

    print_tab(apply_move_2opt(solution, instance->dim, mv), instance->dim);
    printf("\n");

    int num_cities = 5;

    int num_moves;
    Move *moves = generate_swap_moves(num_cities, &num_moves);

    // Tests
    //int best_found;
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
     int *final = descente(instance, best_improver_swap);
    // int *final = descente(instance, best_improver_2opt);

    // int *final = descente(instance, worst_improver_swap);
    // int *final = descente(instance, worst_improver_2opt);

    // int *final = descente(instance, first_improver_swap);
    //int *final = descente(instance, first_improver_2opt);

    printf("\nSolution final: \n");
    print_tab(final, instance->dim);

    free(instance);
    free(solution);
    free(moves);

    return 0;
}
