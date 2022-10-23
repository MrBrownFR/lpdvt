#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INVALID_CHAR_READING 101
#define CANT_OPEN_FILE 201
#define FAIL_UPDATE 102

/// @brief Affiche le message d'aide
void help()
{
    printf("\n\nGOL - Page d'aide\n=================\n\nOptions disponibles:\n\t- h : Permet d'afficher la page d'aide\n\t- f : Permet de commencer le jeu de la vie à partir d'un fichier prédéfini\n\t\t  ATTENTION : le fichier doit suivre une nomenclature spéciale précisée dans le README\n\t- r : Permet de commencer avec une grille aléatoire\n");
}

/// @brief Obtient les dimensions de la grille du jeu de la vie
/// @param filename le nom du fichier
/// @param dimensions un tableau de dimensions non instancié
/// @return un tableau d'entier contenant dans l'ordre lignes, colonnes
void get_dimensions(char filename[], int *dimensions)
{
    errno = 0;
    FILE *content = fopen(filename, "r");
    if (content == NULL)
    {
        fprintf(stderr, "Une erreur s'est produite a l'ouverture du fichier %s : %s\n", filename, strerror(errno));
        exit(CANT_OPEN_FILE);
    }
    int lines = 1;
    int columns = 0;
    char buffer;
    for (buffer = getc(content); buffer != EOF; buffer = getc(content))
    {
        if (buffer == '\n')
        {
            lines = lines + 1;
        }
        columns += 1;
    }

    columns /= lines;
    // columns /= 2; // on a compté les espaces

    fclose(content);
    dimensions[0] = lines;
    dimensions[1] = columns;
}

void init_grid(char filename[], char **grid)
{
    errno = 0;
    FILE *content = fopen(filename, "r");
    if (content == NULL)

    {
        fprintf(stderr, "Une erreur s'est produite a l'ouverture du fichier %s : %s\n", filename, strerror(errno));
        exit(CANT_OPEN_FILE);
    }

    int lines = 0;
    int columns = 0;
    char buffer;
    for (buffer = getc(content); buffer != EOF; buffer = getc(content))
    {
        if (buffer == '\n')
        {
            lines = lines + 1;
            columns = 0;
            break;
        }
        columns += 1;
        switch (buffer)
        {
        case 'o':
            grid[lines][columns] = ' ';

        case 'x':
            grid[lines][columns] = '█';

        default:
            printf("Une erreur s'est produite lors de la lecture du caractère");
            exit(INVALID_CHAR_READING);
        }
    }
}

void print_grid(char **grid, int *dimensions)
{
    for (int i = 0; i < dimensions[0]; i++)
    {
        for (int j = 0; j < dimensions[1]; j++)
        {
            printf("%c", grid[i][j]);
        }
    }
}

int valid_cell(int x, int y, int rows, int columns)
{
    if (x >= 0 && x < rows && y >= 0 && y < columns)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void find_adjacent(int grid[5][5], int *storage, int i, int j, int rows, int columns)
{
    int live = 0;
    int dead = 0;
    int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int k = 0; k < 8; k++)
    {
        int x = i + offset[k][0];
        int y = j + offset[k][1];
        if (valid_cell(x, y, rows, columns))
        {
            if (grid[x][y] == 1)
            {
                live += 1;
            }
            else if (grid[x][y] == 0)
            {
                dead += 1;
            }
            else
            {
                printf("Erreur : que des 0 et des 1");
            }
        }
    }
    storage[0] = live;
    storage[1] = dead;
}

void update(int grid[5][5], int tmp_grid[5][5], int rows, int columns)
{
    for (int k = 0; k < rows; k++)
    {
        for (int l = 0; l < columns; l++)
        {
            int storage[2] = {0, 0};
            find_adjacent(grid, storage, k, l, rows, columns);
            if (storage[0] == 3)
            {
                tmp_grid[k][l] = 1;
            }
            else if (storage[0] == 2)
            {
                tmp_grid[k][l] = grid[k][l];
            }
            else
            {
                tmp_grid[k][l] = 0;
            }
        }
    }

    // Il faut copier tmp_grid dans grid dcp avec deux for imbriqués je pense
    exit(FAIL_UPDATE);
}

void gol()
{
    char filename[256];
    printf("Quel est le nom du fichier que vous cherchez à ouvrir ? (Merci d'entrer le chemin complet du fichier)\n> ");
    scanf("%s", &filename);
    // printf("%s", filename);
    int dimensions[2];

    get_dimensions(filename, dimensions);
    char grid[dimensions[1]][dimensions[0]];
    printf("%d", sizeof(grid));

    init_grid(filename, (char **)grid);
}

int main()
{
    printf("GOL\n===\nQue voulez-vous faire ? (h: aide, f: chemin de fichier, r: random)\n> ");
    char option;
    scanf("%c", &option);

    switch (option)
    {
    case 'h':
        help();
        break;

    case 'f':
        gol();
        break;

    case 'r':
        // TODO implémentation de la grille random
        break;

    default:
        printf("\nVous n'avez pas rentré d'option valable :( Merci de relancer le programme pour recommencer ;)\n\n");
        exit(INVALID_CHAR_READING);
    }

    return 0;
}
