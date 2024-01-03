#include "execution_comparison.h"
#include "lib.h"

void execute_descentes(char *instances_path[], int nb_instances, Algorithm descente_algos[], char *algos_names[], int nb_algo, int nb_initial_solution)
{
    int seed = 50, cost;
    int *initial_solution, *final;
    clock_t start_time, end_time;
    FILE *file = fopen("execution_results2/execute_descentes_incremental.csv", "w");
    fprintf(file, "Instance,Algorithme,Seed,Score,CPU-Used-Time (ms)");

    printf("\033[32m");
    for (int i = 0; i < nb_instances; i++)
    {

        printf("\n\033[34mStarted with instance %s\033[32m", instances_path[i]);
        Instance *instance = load_instance(instances_path[i]);
        for (int j = 0; j < nb_algo; j++)
        {
            for (int k = 0; k < nb_initial_solution; k++)
            {
                printf("\n%s %d/%d...", algos_names[j], k + 1, nb_initial_solution);

                initial_solution = random_solution(instance->dim, seed + k);
                start_time = clock();
                final = descente(instance, initial_solution, descente_algos[j]);
                end_time = clock();
                cost = cost_function(instance, final);
                double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                fprintf(file, "\n%s,%s_descente,%d,%d,%f", instances_path[i], algos_names[j], seed + k, cost, cpu_time_used * 1000);
                printf(".............Done %f ms", cpu_time_used * 1000);
            }
            printf("\n");
        }
        printf("\033[34mInstance %s end\033[32m\n", instances_path[i]);
        free_instance(instance);
    }
    printf("\n\033[0m");
}

void execute_ILS(char *instances_path[], int nb_instances, AlgorithmILS ils_algos[], char *algos_names[], int nb_algo, int nb_initial_solution, int max_eval)
{
    int seed = 50, cost;
    int *initial_solution, *final;
    clock_t start_time, end_time;
    // Nombre de pertubations;
    int nb_pertubations[] = {6, 9};

    FILE *file = fopen("execution_results2/execute_ils.csv", "w");
    fprintf(file, "Instance,Algorithme,Seed,Score,NbPertubations,MaxEval,CPU-Used-Time (ms)");

    printf("\033[32m");
    for (int i = 0; i < nb_instances; i++)
    {

        printf("\n\033[34mStarted with instance %s\033[32m", instances_path[i]);
        Instance *instance = load_instance(instances_path[i]);
        for (int j = 0; j < nb_algo; j++)
        {
            for (int k = 0; k < nb_initial_solution; k++)
            {

                initial_solution = random_solution(instance->dim, seed + k);
                AlgorithmILS algo = ils_algos[j];

                for (size_t l = 0; l < 2; l++)
                {
                    printf("\n%s %d/%d (nb_pertubation: %d)...", algos_names[j], k + 1, nb_initial_solution, nb_pertubations[l]);

                    start_time = clock();
                    final = algo(instance, initial_solution, nb_pertubations[l], max_eval);
                    end_time = clock();

                    cost = cost_function(instance, final);
                    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                    fprintf(file, "\n%s,%s,%d,%d,%d,%d,%f", instances_path[i], algos_names[j], seed + k, cost, nb_pertubations[l], max_eval, cpu_time_used * 1000);
                    printf(".............Done %f ms", cpu_time_used * 1000);
                }
            }
            printf("\n");
        }
        printf("\033[34mInstance %s end\033[32m\n", instances_path[i]);
        free_instance(instance);
    }
    printf("\n\033[0m");
}

void execute_SW(char *instances_path[], int nb_instances, AlgorithmSW sw_algos[], char *algos_names[], int nb_algo, int nb_initial_solution, int max_eval)
{
    int seed = 50, cost;
    int *initial_solution, *final;
    clock_t start_time, end_time;
    Instance *instance;
    AlgorithmILS algo;
    // L'argument lambda;
    int lambdas[] = {5, 9};

    FILE *file = fopen("execution_results2/execute_sw.csv", "w");
    fprintf(file, "Instance,Algorithme,Seed,Score,Lambda,MaxEval,CPU-Used-Time (ms)");

    printf("\033[32m");
    for (int i = 0; i < nb_instances; i++)
    {

        printf("\n\033[34mStarted with instance %s\033[32m", instances_path[i]);
        instance = load_instance(instances_path[i]);
        for (int j = 0; j < nb_algo; j++)
        {
            algo = sw_algos[j];
            for (int k = 0; k < nb_initial_solution; k++)
            {

                initial_solution = random_solution(instance->dim, seed + k);

                for (size_t l = 0; l < 2; l++)
                {
                    printf("\n%s %d/%d (lambda: %d)...", algos_names[j], k + 1, nb_initial_solution, lambdas[l]);

                    start_time = clock();
                    final = algo(instance, initial_solution, lambdas[l], max_eval);
                    end_time = clock();

                    cost = cost_function(instance, final);
                    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                    fprintf(file, "\n%s,%s,%d,%d,%d,%d,%f", instances_path[i], algos_names[j], seed + k, cost, lambdas[l], max_eval, cpu_time_used * 1000);

                    printf(".............Done %f ms", cpu_time_used * 1000);
                    free(final);
                }
                free(initial_solution);
            }
            printf("\n");
        }
        printf("\033[34mInstance %s end\033[32m\n", instances_path[i]);
        free_instance(instance);
    }
    printf("\n\033[0m");
}

void execute_genetique(char *instances_path[], int nb_instances)
{
    // Genetique arguments
    int nb_generations = 1000, population_size = 50, cost;
    double crossover_rate = 0.7, mutation_rate = 0.1;

    FILE *file = fopen("execution_results2/generique.csv", "w");
    fprintf(file, "Instance,Score");

    for (int i = 0; i < nb_instances; i++)
    {
        printf("\n\033[34mStarted with instance %s\033\n[32m", instances_path[i]);
        Instance *instance = load_instance(instances_path[i]);
        int *solution = genetic_algorithm(instance, nb_generations, population_size, crossover_rate, mutation_rate);
        cost = cost_function(instance, solution);
        fprintf(file,"\n%s,%d",instances_path[i],cost);
        free_instance(instance);
        free(solution);
    }

    fclose(file);
}

void execute()
{
    clock_t start_time, end_time;

    // Instances paths
    char *instances_path[] = {
        "instances/atsp_rand_50_75.txt",
        "instances/atsp_rand_50_100.txt",
        "instances/atsp_rand_60_50.txt",
        "instances/atsp_rand_60_100.txt",
        "instances/atsp_rand_70_55.txt",
        "instances/atsp_rand_70_100.txt",
        "instances/atsp_rand_80_70.txt",
        "instances/atsp_rand_80_100.txt"};

    // Descentes algos
    Algorithm descente_algos[] = {
        best_improver_swap,
        first_improver_swap,
        worst_improver_swap,
        best_improver_2opt,
        first_improver_2opt,
        worst_improver_2opt};

    char *descente_algos_names[] = {
        "best_improver_swap",
        "first_improver_swap",
        "worst_improver_swap",
        "best_improver_2opt",
        "first_improver_2opt",
        "worst_improver_2opt"};

    // ILS algo
    AlgorithmILS ils_algos[] = {
        iterated_local_search_best_improver_2opt,
        iterated_local_search_best_improver_swap,
        iterated_local_search_first_improver_2opt,
        iterated_local_search_first_improver_swap};

    char *ils_algos_names[] = {
        "iterated_local_search_best_improver_2opt",
        "iterated_local_search_best_improver_swap",
        "iterated_local_search_first_improver_2opt",
        "iterated_local_search_first_improver_swap"};

    // SW algo
    AlgorithmSW sw_algos[] = {
        sampled_walk_swap,
        sampled_walk_2opt};

    char *sw_algos_names[] = {
        "sampled_walk_swap",
        "sampled_walk_2opt"};

    // int max_evaluation = 10000000;
    int max_evaluation = 1000000;

    start_time = clock();
    // execute_descentes(instances_path, 8, descente_algos, descente_algos_names, 6, 10);
    //  execute_ILS(instances_path, 8, ils_algos, ils_algos_names, 4, 10, max_evaluation);
    //  execute_SW(instances_path, 8, sw_algos, sw_algos_names, 2, 10, max_evaluation);

    execute_genetique(instances_path, 8);
    end_time = clock();
    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n \nExecution end\nUsed CPU Time: %f secondes\n\n", cpu_time_used);
}
