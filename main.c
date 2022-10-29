#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INVALID_CHAR_READING 101
#define CANT_OPEN_FILE 201
#define FAIL_UPDATE 102
unsigned int iteration = 0;
unsigned int is_alive = 1;

/// @brief Affiche le message d'aide
void help()
{
    printf("\n\nGOL - Page d'aide\n=================\n\nOptions disponibles:\n\t- h : Permet d'afficher la page d'aide\n\t- f : Permet de commencer le jeu de la vie à partir d'un fichier prédéfini\n\t\t  ATTENTION : le fichier doit suivre une nomenclature spéciale précisée dans le README\n\t- m : Permet de visualiser des modèles intéressants\n");

    system("man gol");
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
    int columns = 1;
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

/// @brief Initialise al grille à partir d'un fichier
/// @param content le pointeur vers le contenu du fichier
/// @param coords le pointeur vers la grille
/// @param taille la taille allouée à la matrice
void init_grid(FILE *content, char *coords, int taille)
{
    errno = 0;
    int index = 0;
    int ch;

    while ((ch = fgetc(content)) != EOF && index < taille)
    {
        *coords = (char)ch;
        coords++;
        index++;
    }
}

/// @brief Affiche la grille à l'écran
/// @param grid le pointeur vers les cases de la grille
/// @param taille la taille allouée à la grille
void print_grid(char *coords_tmp, int taille, int *dimensions)
{
    printf("Itération n° %d\n", iteration);
    for (int i = 0; i < taille; i++)
    {
        if (i % dimensions[1] == 0)
        {
            printf("\n");
        }
        printf("%c", *(coords_tmp + i));
    }
}

int valid_cell(int x, int taille)
{
    if (x >= 0 && x < taille)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void find_adjacent(char *coords, int *storage, int k, int taille, int *dimensions)
{
    int live = 0;
    int dead = 0;
    int offset[8] = {-dimensions[1] - 1, -dimensions[1], -dimensions[1] + 1, -1, 1, dimensions[1] - 1, dimensions[1], dimensions[1] + 1};

    for (int i = 0; i < 8; i++)
    {
        if (valid_cell((k + offset[i]), taille))
        {
            if (*(coords + k + offset[i]) == '1')
            {
                live++;
            }
        }
    }
    storage[0] = live;
    storage[1] = 8 - live;
    // printf("Live %d ; Dead %d \n", storage[0], storage[1]);
}

void update(char *coords, char *tmp_coords, int taille, int *dimensions)
{
    // int storage[2] = {0, 0};
    // find_adjacent(coords, storage, 31, taille, dimensions);
    // printf("Live %d ; Dead %d ; %c \n", storage[0], storage[1], *(coords+31));
    for (int k = 0; k < taille; k++)
    {
        int storage[2] = {0, 0};
        find_adjacent(coords, storage, k, taille, dimensions);

        if (storage[0] == 3)
        {
            *(tmp_coords + k) = '1';
        }
        else if (storage[0] == 2)
        {
            *(tmp_coords + k) = *(coords + k);
        }
        else
        {
            *(tmp_coords + k) = '0';
        }
    }
}

void paster(char *coords, char *coords_tmp, int taille)
{
    for (int k = 0; k < taille; k++)
    {
        *(coords + k) = *(coords_tmp + k);
    }
}

/// @brief Boucle principale du jeu
void gol()
{
    /* INITIALISATION DU NOM DU FICHIER */
    char filename[256];
    printf("Quel est le nom du fichier que vous cherchez à ouvrir ? (Merci d'entrer le chemin complet du fichier)\n> ");
    scanf("%s", filename);
    // printf("%s", filename);

    /* INITIALISATION DES DIMENSIONS */
    int dimensions[2];
    get_dimensions(filename, dimensions);
    // printf("%d %d\n", dimensions[0], dimensions[1]);

    /* INITIALISATION DE LA GRILLE DE JEU */
    char *grid = malloc((int)sizeof(char) * dimensions[0] * dimensions[1]); // Malgré les airs trompeurs, on a bien un tableau à 2 dimensions, on utilise juste une technique différente pour la manipuler
    char grid_tmp[dimensions[1]][dimensions[0]];
    char *coords_tmp = &grid_tmp[0][0];
    int taille = dimensions[0] * dimensions[1];
    printf("%d", sizeof(grid));

    /* OUVERTURE DU FICHIER */
    FILE *content = fopen(filename, "r");
    if (content == NULL)

    {
        fprintf(stderr, "Une erreur s'est produite a l'ouverture du fichier %s : %s\n", filename, strerror(errno));
        exit(CANT_OPEN_FILE);
    }

    /* TRAVAIL SUR LA GRILLE */
    init_grid(content, grid, taille);
    fclose(content);
    system("clear");

    for (int i = 0; i < taille; i++)
    {
        *(coords_tmp + i) = *(grid + i);
    }

    printf("Appuie sur la touche [Entrée] pour continuer.\n");
    getchar();

    while (is_alive)
    {
        update(grid, coords_tmp, taille, dimensions);
        paster(grid, coords_tmp, taille);
        print_grid(grid, taille, dimensions);
        printf("\n\n");
        iteration++;
        printf("Appuie sur la touche [Entrée] pour continuer.\n");
        fflush(stdin); // option ONE to clean stdin
        getchar();
        system("clear");
    }
}

void models()
{
    char tmp[5][1000] = {"1", "2", "3", "4", "5"};
    int iter = 0;
    while (getchar() != 'q')
    {
        system("clear");
        printf("%s\n", tmp[iter % 5]);
        iter++;
        printf("Appuyer sur [Entrée] pour continuer // [q] + [Entrée] pour quitter.\n");
    }
}

int main()
{
    printf("\n\n██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ███████╗    ██╗     ██╗███████╗███████╗\n██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██╔════╝    ██║     ██║██╔════╝██╔════╝\n██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║█████╗      ██║     ██║█████╗  █████╗  \n██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██╔══╝      ██║     ██║██╔══╝  ██╔══╝  \n╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝██║         ███████╗██║██║     ███████╗\n ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝ ╚═╝         ╚══════╝╚═╝╚═╝     ╚══════╝\n\nQue voulez-vous faire ? (h: aide, f: chemin de fichier, m: modèles)\n> ");
    char option;
    scanf("%c", &option);

    switch (option)
    {
    case 'h':
        help();
        break;

    case 'f':
        gol(); // Nécéssaire sinon bypass du contrôle d'initialisation??
        break;

    case 'm':
        models();
        break;

    default:
        printf("\nVous n'avez pas rentré d'option valable :( Merci de relancer le programme pour recommencer ;)\n\n");
        exit(INVALID_CHAR_READING);
    }

    return 0;
}
