#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// @brief Affiche le message d'aide
void help()
{
    printf("\n\nGOL - Page d'aide\n=================\n\nOptions disponibles:\n\t- h : Permet d'afficher la page d'aide\n\t- f : Permet de commencer le jeu de la vie à partir d'un fichier prédéfini\n\t\t  ATTENTION : le fichier doit suivre une nomenclature spéciale précisée dans le README\n\t- r : Permet de commencer avec une grille aléatoire\n");
}

/// @brief Obtient les dimensions de la grille du jeu de la vie
/// @param filename le nom du fichier
/// @return un tableau d'entier contenant dans l'ordre lignes, colonnes
int *get_dimensions(char *filename)
{
    errno = 0;
    FILE *content = fopen(filename, "r");
    if (content == NULL)
    {
        printf("Une erreur s'est produite `a l'ouverture du fichier %s : %s\n",
               filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    int columns = 0;
    while (fscanf(content, '\n') != EOF)
    {
        columns++;
    }
    int lines = 0;
    while (fscanf(content, '\0') != EOF)
    {
        if (fscanf(content, '\n'))
        {
            lines++;
        }
    }
    fclose(content);
    int *grid[2] = {lines, columns};
    return *grid;
}

void read_file(char *filename)
{
    errno = 0;
    FILE *content = fopen(filename, "r");
    if (content == NULL)

    {
        printf("Une erreur s'est produite `a l'ouverture du fichier %s : %s\n",
               filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* traitements sur le fichier */
    fclose(content);
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

void findAdjacent(int grid[5][5], int *storage, int i, int j, int rows, int columns)
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

int update(int grid[5][5], int tmp_grid[5][5], int rows, int columns)
{
    for (int k = 0; k < rows; k++)
    {
        for (int l = 0; l < columns; l++)
        {
            int storage[2] = {0, 0};
            findAdjacent(grid, storage, k, l, rows, columns);
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
    return 201;
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

        char *filename;
        printf("Quel est le nom du fichier que vous cherchez à ouvrir ? (Merci d'entrer le chemin complet du fichier)\n> ");
        fscanf("%s", &filename);

        int *dimensions = get_dimensions(filename);
        char *_lignes = (char *)malloc(sizeof(char) * dimensions[1]); // Variables temporaire mais nécéssaire pour allouer la matrice non carrée
        char **grid = (char **)malloc(sizeof(_lignes) * dimensions[0]);

        break;

    case 'r':
        // TODO implémentation de la grille random
        break;

    default:
        printf("\nVous n'avez pas rentré d'option valable :( Merci de relancer le programme pour recommencer ;)\n\n");
        return 101;
    }

    return 0;
}
