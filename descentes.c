#include "descentes.h"
#include "initialisation.h"
#include "lib.h"

int *apply_move_swap(int *solution, int size, Move move)
{
    int *new = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++)
    {
        new[i] = solution[i];
    }
    new[move.c1] = solution[move.c2];
    new[move.c2] = solution[move.c1];
    return new;
}

int *apply_move_2opt(int *solution, int size, Move move)
{
    int *new = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++)
    {
        new[i] = solution[i];
    }
    int s1 = move.c1, s2 = move.c2;
    while (s1 < s2)
    {
        int tmp = new[s1];
        new[s1] = new[s2];
        new[s2] = tmp;
        s1++;
        s2--;
    }
    return new;
}

int new_cost_swap(Instance *instance, int *solution, int cost, Move move)
{
    // return cost - instance->matrix[move.c1 - 1][move.c1] - instance->matrix[move.c2][move.c2 + 1] + instance->matrix[move.c1 - 1][move.c2] + instance->matrix[move.c1][move.c2 + 1];

    int *new_sol = apply_move_swap(solution, instance->dim, move);
    int c = cost_function(instance, new_sol);
    free(new_sol);
    return c;
}

int new_cost_2opt(Instance *instance, int *solution, int cost, Move move)
{
    int *new_sol = apply_move_2opt(solution, instance->dim, move);
    int c = cost_function(instance, new_sol);
    free(new_sol);
    return c;
}

int *best_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;

    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_swap(instance, solution, cost, moves[i]);

        if (new_cost < cost)
        {
            cost = new_cost;
            best_move = moves[i];
            *best_found = 1;
        }
    }

    if (*best_found)
    {
        return apply_move_swap(solution, instance->dim, best_move);
    }
    return NULL;
}

int *worst_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;
    int wost;
    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_swap(instance, solution, cost, moves[i]);

        if (!(*best_found) && new_cost < cost)
        {
            wost = new_cost;
            best_move = moves[i];
            *best_found = 1;
        }

        else if (new_cost < cost && new_cost > wost)
        {
            wost = new_cost;
            best_move = moves[i];
        }
    }

    if (*best_found)
    {
        return apply_move_swap(solution, instance->dim, best_move);
    }
    return NULL;
}

int *first_improver_swap(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;
    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_swap(instance, solution, cost, moves[i]);

        if (new_cost < cost)
        {
            cost = new_cost;
            best_move = moves[i];
            *best_found = 1;
            break;
        }
    }

    if (*best_found)
    {

        return apply_move_swap(solution, instance->dim, best_move);
    }
    return NULL;
}

int *best_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;
    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_2opt(instance, solution, cost, moves[i]);

        if (new_cost < cost)
        {

            cost = new_cost;
            best_move = moves[i];
            *best_found = 1;
        }
    }

    if (*best_found)
    {
        return apply_move_2opt(solution, instance->dim, best_move);
    }
    return NULL;
}

int *worst_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;
    int wost;
    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_2opt(instance, solution, cost, moves[i]);

        if (!(*best_found) && new_cost < cost)
        {
            wost = new_cost;
            best_move = moves[i];
            *best_found = 1;
        }

        else if (new_cost < cost && new_cost > wost)
        {
            wost = new_cost;
            best_move = moves[i];
        }
    }

    if (*best_found)
    {
        return apply_move_2opt(solution, instance->dim, best_move);
    }
    return NULL;
}

int *first_improver_2opt(Instance *instance, int *solution, int cost, Move *moves, int num_moves, int *best_found)
{

    Move best_move;
    *best_found = 0;
    for (int i = 0; i < num_moves; i++)
    {

        int new_cost = new_cost_2opt(instance, solution, cost, moves[i]);

        if (new_cost < cost)
        {
            cost = new_cost;
            best_move = moves[i];
            *best_found = 1;
            break;
        }
    }

    if (*best_found)
    {
        return apply_move_2opt(solution, instance->dim, best_move);
    }
    return NULL;
}

int *descente(Instance *instance, int *solution, Algorithm algo)
{
    int num_moves, found = 0, nb_itter = 0;

    Move *moves = generate_swap_moves(instance->dim, &num_moves);
    int cost = cost_function(instance, solution);

    int *new_solution = algo(instance, solution, cost, moves, num_moves, &found);
    int *best_solution;

    if (!found)
    {
        // printf("No improvement done");
        return solution;
    }

    //printf("\nitter %d => , found :%d , cost : %d", nb_itter, found, cost);
    nb_itter++;
    // print_tab(new_solution, instance->dim);

    while (found)
    {
        cost = cost_function(instance, new_solution);
        //printf("\nitter %d => , found :%d , cost : %d", nb_itter, found, cost);
        nb_itter++;
        // print_tab(new_solution, instance->dim);
        // printf("\n");
        best_solution = new_solution;
        new_solution = algo(instance, new_solution, cost, moves, num_moves, &found);
        nb_itter++;
    }

    return best_solution;
}
