typedef struct Player
{
    char name[255];
    int points;
} Player;

typedef struct Game
{
    Player player1;
    Player player2;
} Game;
