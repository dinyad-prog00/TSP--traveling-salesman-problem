#include "initialisation.h"
#include "lib.h"

//Variable globale externe definie dans lib.h
int nombre_evaluations;

int **locate_matrix_memory(int size)
{
    int **matrix;
    int i;

    matrix = (int **)malloc(size * sizeof(int *));

    if (matrix == NULL)
    {
        printf("Memory allocation failed for rows.\n");
        return NULL;
    }

    for (i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed for row %d.\n", i);
            return NULL;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = INT_MAX;
        }
    }

    return matrix;
}

//Seulement pour les matrices asymétriques
Instance *load_instance(char *file_name)
{
    Instance *instance = malloc(sizeof(Instance));
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening file");
    }

    char read[100];
    char reading = 1;
    int startFill = 0;
    int i = 0, j = 0;

    while (reading)
    {
        if (!startFill)
        {
            fscanf(file, "%s", read);

            if (strcmp(read, "DIMENSION:") == 0)
            {
                fscanf(file, "%d", &(instance->dim));

                instance->matrix = locate_matrix_memory(instance->dim);
                if (instance->matrix == NULL)
                {
                    break;
                }
            }
            if (strcmp(read, "EDGE_WEIGHT_SECTION") == 0)
            {

                startFill = 1;
            }
        }
        else
        {
            if (i != j)
            {
                fscanf(file, "%d", &(instance->matrix[j][i]));
            }
            else
            {
                fscanf(file, "%s", read);
            }
            i++;
            if (i == instance->dim)
            {
                i = 0;
                j++;
            }

            if (j == instance->dim)
            {
                break;
            }
        }
    }

    fclose(file);

    return instance;
}



void print_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_tab(int *tab, int size)
{

    for (int i = 0; i < size; i++)
    {

        printf("%d\t", tab[i]);
    }
    printf("\n");
}


int *random_solution(int size, int seed)
{
    int *permutation = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        permutation[i] = i;
    }
    srand(seed);

    // Melange Fisher-Yates
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;
    }
    return permutation;
}


int cost_function(Instance *instance, int *solution)
{
    
    /// Incrementer le nombre d'évaluation pour chaque appel
    nombre_evaluations++;
    ///

    int ct = 0;
    for (int i = 0; i < instance->dim - 1; i++)
    {
        ct += instance->matrix[solution[i]][solution[i + 1]];
    }

    ct += instance->matrix[solution[instance->dim - 1]][solution[0]];

    return ct;
}


Move *generate_swap_moves(int num_cities, int *num_moves)
{
    *num_moves = num_cities * (num_cities - 1) / 2;
    Move *moves = (Move *)malloc(*num_moves * sizeof(Move));

    if (moves == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int count = 0;
    for (int i = 0; i < num_cities - 1; i++)
    {
        for (int j = i + 1; j < num_cities; j++)
        {
            moves[count].c1 = i;
            moves[count].c2 = j;
            count++;
        }
    }

    return moves;
}

void print_moves(Move *moves, int num_moves)
{
    printf("Possible moves:\n");
    for (int i = 0; i < num_moves; i++)
    {
        printf("(%d, %d) ", moves[i].c1, moves[i].c2);
    }
    printf("\n");
}

void free_instance(Instance *instance)
{
    if (instance == NULL)
        return;

    if (instance->matrix != NULL)
    {
        for (size_t i = 0; i < instance->dim; i++)
        {
            if (instance->matrix[i] != NULL)
            {
                free(instance->matrix[i]);
            }
        }

        free(instance->matrix);
    }

    free(instance);
}
