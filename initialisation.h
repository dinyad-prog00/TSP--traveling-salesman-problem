#ifndef H_FUNCTIONS
#define H_FUNCTIONS
/**
 * Partie 1
*/


//Structure d'une instance
typedef struct instance
{
    int dim; //dimension
    int **matrix;
} Instance;

//Mouvement possible : un couple d'entiers.
typedef struct
{
    int c1;
    int c2;
} Move;


// Charger instance, seulement pour les matrices asymétriques
Instance *load_instance(char *file_name);

//Alouer de l'espace pour une matrice
int **locate_matrix_memory(int size);

//Affchier une matrice
void print_matrix(int **matrix, int size);

//Affchier un tableau
void print_tab(int *tab, int size);


// Solution aléatoire
int *random_solution(int size, int seed);

// Fonction d'évalution
int cost_function(Instance *instance, int *solution);

// Générer les mouvements possibles
Move *generate_swap_moves(int num_cities, int *num_moves);


void print_moves(Move *moves, int num_moves);

//Liberer l'espace mémoire d'une instance
void free_instance(Instance *instance);

#endif