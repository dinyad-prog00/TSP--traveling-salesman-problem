#include "local_search.h"
#include "lib.h"
int *apply_pertubations(int *solution, int size, MoveApplicator move_applicator, Move *moves, int num_moves, int nb_pertubations)
{
    int *new = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++)
    {
        new[i] = solution[i];
    }
    srand(time(NULL));

    for (size_t i = 0; i < nb_pertubations; i++)
    {
        int index = rand() % num_moves;
        Move move = moves[index];
        new = move_applicator(new, size, move);
    }

    return new;
}

int *iterated_local_search(Instance *instance, int *soltution, Algorithm algo, MoveApplicator move_applicator, int nb_pertubations, int max_eval)
{
    int step = 0;

    int *best_sol = soltution;
    int *cur_sol = soltution;
    int nb_moves;
    Move *moves = generate_swap_moves(instance->dim, &nb_moves);
    nombre_evaluations = 0;
    while (nombre_evaluations < max_eval)
    {
        int *new_sol = descente(instance, cur_sol, algo);

        // printf("\033[33mnew_sol ++++\n");
        // print_tab(best_sol, instance->dim);
        // print_tab(new_sol, instance->dim);
        // printf("new_sol ----\033[0m\n");

        // printf("\nnew=%d, old=%d\n", cost_function(instance, new_sol), cost_function(instance, best_sol));
        if (cost_function(instance, new_sol) < cost_function(instance, best_sol))
        {
            // printf("\n\033[31mbest found==========================\033[0m\n");
            best_sol = new_sol;
        }

        cur_sol = apply_pertubations(best_sol, instance->dim, move_applicator, moves, nb_moves, nb_pertubations);
        // printf("\033[31mpertub ++++\n");
        // print_tab(best_sol, instance->dim);
        // print_tab(cur_sol, instance->dim);
        // printf("pertub ----\033[0m\n");
        step++;
        // printf("\nstep ILS: %d", step);
    }

    return best_sol;
}



int *iterated_local_search_best_improver_swap(Instance *instance, int *soltution, int nb_pertubations, int max_eval)
{
    return iterated_local_search(instance, soltution, best_improver_swap, apply_move_swap, nb_pertubations, max_eval);
}

int *iterated_local_search_best_improver_2opt(Instance *instance, int *soltution, int nb_pertubations, int max_eval)
{
    return iterated_local_search(instance, soltution, best_improver_2opt, apply_move_2opt, nb_pertubations, max_eval);
}

int *iterated_local_search_first_improver_swap(Instance *instance, int *soltution, int nb_pertubations, int max_eval)
{
    return iterated_local_search(instance, soltution, first_improver_swap, apply_move_swap, nb_pertubations, max_eval);
}

int *iterated_local_search_first_improver_2opt(Instance *instance, int *soltution, int nb_pertubations, int max_eval)
{
    return iterated_local_search(instance, soltution, first_improver_2opt, apply_move_2opt, nb_pertubations, max_eval);
}

Move *generate_n_moves(Move *moves, int nb_moves, int n)
{
    int *indexes = malloc(nb_moves * sizeof(int));
    int i, j, tmp;
    Move *gen_moves = malloc(sizeof(Move) * n);

    for (i = 0; i < nb_moves; i++)
    {
        indexes[i] = i;
    }
    srand(time(NULL));

    // Melange Fisher-Yates
    for (i = nb_moves - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        tmp = indexes[i];
        indexes[i] = indexes[j];
        indexes[j] = tmp;
    }

    for (i = 0; i < n; i++)
    {
        gen_moves[i] = moves[indexes[i]];
    }
    free(indexes);
    return gen_moves;
}

int *sampled_walk(Instance *instance, int *soltution, MoveApplicator move_applicator, int lambda, int max_eval)
{
    nombre_evaluations = 0;
    int nb_moves;
    Move *moves = generate_swap_moves(instance->dim, &nb_moves);

    int step = 0;
    int *best_sol = soltution, *new_sol;
    Move *lambda_moves;

    while (nombre_evaluations < max_eval)
    {
        lambda_moves = generate_n_moves(moves, nb_moves, lambda);
        for (int i = 0; i < lambda; i++)
        {
            new_sol = move_applicator(best_sol, instance->dim, lambda_moves[i]);

            if (i == 0)
            {
                best_sol = new_sol;
            }
            else if (cost_function(instance, new_sol) < cost_function(instance, best_sol))
            {
                // printf("\n\033[31mbest found==========================\033[0m\n");
                best_sol = new_sol;
            }

            else
            {
                free(new_sol);
            }
        }
        step++;
    }

    return best_sol;
}



int *sampled_walk_swap(Instance *instance, int *soltution, int lambda, int max_eval)
{
    return sampled_walk(instance, soltution, apply_move_swap, lambda, max_eval);
}
int *sampled_walk_2opt(Instance *instance, int *soltution, int lambda, int max_eval)
{
    return sampled_walk(instance, soltution, apply_move_2opt, lambda, max_eval);
}
