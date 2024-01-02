#ifndef H_FUNCTIONS
#define H_FUNCTIONS

typedef struct instance
{
    int dim;
    int **matrix;
} Instance;

typedef struct
{
    int c1;
    int c2;
} Move;
Instance *load_instance(char *file_name);
int **locate_matrix_memory(int size);
void print_matrix(int **matrix, int size);
void print_tab(int *tab, int size);
int *random_solution(int size, int seed);
int cost_function(Instance *instance, int *solution);
Move *generate_swap_moves(int num_cities, int *num_moves);
void print_moves(Move *moves, int num_moves);
void free_instance(Instance *instance);

#endif