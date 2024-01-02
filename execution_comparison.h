#ifndef H_EXE_CMP
#define H_EXE_CMP
#include "descentes.h"
#include "local_search.h"

void execute_descentes(char *instances_path[], int nb_instances, Algorithm descentes_algos[], char *algo_names[], int nb_algo, int nb_initial_solution);

void execute_ILS(char *instances_path[], int nb_instances, AlgorithmILS ils_algos[], char *algo_names[], int nb_algo, int nb_initial_solution, int max_eval);
void execute_SW(char *instances_path[], int nb_instances, AlgorithmSW sw_algos[], char *algo_names[], int nb_algo, int nb_initial_solution, int max_eval);
void execute();
#endif