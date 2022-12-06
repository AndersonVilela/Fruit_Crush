#include <stdio.h>
#include <string.h>

void save_game(Game *game)
{
    FILE *file = fopen("./files/data/scoreboards.txt", "a");
    char line[255];

    if (file == NULL)
    {
        printf("Houve um erro ao criar o arquivo de placares");
        return;
    }

    char points[10];
    strcat(line, game->player1.name);
    strcat(line, " : ");
    sprintf(points, "%d", game->player1.points);
    strcat(line, points);

    strcat(line, " X ");
    sprintf(points, "%d", game->player2.points);
    strcat(line, points);
    strcat(line, " : ");
    strcat(line, game->player2.name);
    strcat(line, "\n");
    fputs(line, file);

    fclose(file);
}

void print_scoreboards()
{

    printf("\t\t\t    .----------------------. \n");
    printf("\t\t\t    |   **  Placares  **   | \n");
    printf("\t\t\t    '----------------------' \n\n");

    FILE *file = fopen("./files/data/scoreboards.txt", "r");

    if (file == NULL)
    {
        printf("Houve um erro ao ler o arquivo de placares");
        return;
    }

    int count = 0;
    char line[255];

    while (fgets(line, ++count, file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}
