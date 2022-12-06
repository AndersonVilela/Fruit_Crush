#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef __unix__
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows
#include <windows.h>

#endif

// Custom modules
#include "timer.c"
#include "console.c"
#include "structs.c"
#include "files.c"

// Global variables
const char emojis[][15] = {"🍎", "🍒", "🍉", "🍇", "🍐"};
const int columns[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const char rows[] = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
};

void show_credits();
char input_panel_option();
void game();
void clear_window();
void start_game();
void exit_game();
void generate_table(int table[9][9], int size);
void print_table(int table[9][9], int table_size);
void input_position(int round, Player *player, int table[9][9], int table_size, int position[2]);
int is_correct(int table[9][9], int position[2]);
int verify_y(int table[9][9], int position[2]);
int verify_x(int table[9][9], int position[2]);
void print_instructions();

void show_credits()
{
  delay(1000);
  printf("\n\n");
  printf("          **                   **                                         \n");
  printf("        ****                 /**                                          \n");
  printf("       **//**   *******      /**  *****  ******  ******  ******  *******  \n");
  printf("      **  //** //**///**  ****** **///**//**//* **////  **////**//**///** \n");
  printf("     ********** /**  /** **///**/******* /** / //***** /**   /** /**  /** \n");
  printf("    /**//////** /**  /**/**  /**/**////  /**    /////**/**   /** /**  /** \n");
  printf("    /**     /** ***  /**//******//******/***    ****** //******  ***  /** \n");
  printf("    //      // ///   //  //////  ////// ///    //////   //////  ///   //  \n");
  printf("\n");
  printf("\n");
  delay(1000);
  printf("     **                                         \n");
  printf("    /**                                         \n");
  printf("    /**       **   **  *****   ******    ****** \n");
  printf("    /**      /**  /** **///** //////**  **////  \n");
  printf("    /**      /**  /**/**  //   ******* //*****  \n");
  printf("    /**      /**  /**/**   ** **////**  /////** \n");
  printf("    /********//******//***** //******** ******  \n");
  printf("    ////////  //////  /////   //////// //////   \n");
  printf("\n");
  printf("\n");
  delay(1000);
  printf("     ****     ****             **   **                              \n");
  printf("    /**/**   **/**            /**  /**                              \n");
  printf("    /**//** ** /**  ******   ******/**       *****  **   **  ****** \n");
  printf("    /** //***  /** //////** ///**/ /******  **///**/**  /** **////  \n");
  printf("    /**  //*   /**  *******   /**  /**///**/*******/**  /**//*****  \n");
  printf("    /**   /    /** **////**   /**  /**  /**/**//// /**  /** /////** \n");
  printf("    /**        /**//********  //** /**  /**//******//****** ******  \n");
  printf("    //         //  ////////    //  //   //  //////  ////// //////   \n");
  printf("\n");
  printf("\n");
  delay(4000);
}

char input_panel_option()
{
  char option;

  delay(1000);
  printf("\n\n");
  printf("   ********                **   **       ******                         **     \n");
  printf("  /**/////                //   /**      **////**                       /**     \n");
  printf("  /**       ****** **   ** ** ******   **    //  ****** **   **  ******/**     \n");
  printf("  /******* //**//*/**  /**/**///**/   /**       //**//*/**  /** **//// /****** \n");
  printf("  /**////   /** / /**  /**/**  /**    /**        /** / /**  /**//***** /**///**\n");
  printf("  /**       /**   /**  /**/**  /**    //**    ** /**   /**  /** /////**/**  /**\n");
  printf("  /**      /***   //******/**  //**    //****** /***   //****** ****** /**  /**\n");
  printf("  //       ///     ////// //    //      //////  ///     ////// //////  //   // \n");
  printf("\n");
  printf("                            .-----------------------. \n");
  printf("                            |                       | \n");
  printf("                            |  N  - Novo Jogo       | \n");
  printf("                            |  P  - Pontuações      | \n");
  printf("                            |  I  - Instruções      | \n");
  printf("                            |  S  - Sair            | \n");
  printf("                            |                       | \n");
  printf("                            '-----------------------' \n\n");
  print_line();
  printf("Qual opção deseja? ");
  scanf(" %c", &option);

  return toupper(option);
}

void game()
{
  show_credits();

  while (1)
  {
    clear_window();
    char option = input_panel_option();
    clear_window();

    switch (option)
    {
    case 'N':
      start_game();
      break;

    case 'S':
      exit_game();
      break;

    case 'P':
      print_scoreboards();
      pause();
      break;

    case 'I':
      print_instructions();
      pause();
      break;

    default:
      continue;
      break;
    }
  }
}

void start_game()
{
  Game game = {
      {"Jogador 1", 0},
      {"Jogador 2", 0},
  };

  int total_of_rounds = 10;
  int table_size = 9;
  int table[table_size][table_size];

  for (int i = 0; i < total_of_rounds; i++)
  {
    Player *player = i % 2 == 0 ? &game.player1 : &game.player2;
    generate_table(table, table_size);
    clear_window();
    int position[2];
    input_position(
        i + 1,
        player,
        table,
        table_size,
        position);

    if (is_correct(table, position))
    {
      player->points++;
    }
  }

  save_game(&game);
}

void print_table(int table[9][9], int table_size)
{
  for (int i = 0; i < table_size; i++)
  {
    printf("       %i", columns[i]);

    if (i == table_size - 1)
    {
      printf("\n\n");
    }
  }

  for (int i = 0; i < table_size; i++)
  {
    printf("%c", rows[i]);

    for (int j = 0; j < table_size; j++)
    {
      printf("      %s", emojis[table[i][j]]);
    }

    printf("\n\n");
  }
}

void print_instructions()
{
  printf("\t\t\t    .----------------------. \n");
  printf("\t\t\t    |  **  Instruções  **  | \n");
  printf("\t\t\t    '----------------------' \n\n");
  printf(" 1 - Basta encontrar padrões de 3 emojis seguidos na vertical ou diagonal.     \n\n");
  printf(" 2 - Ao encontrar um padrão, informe as coordenadas de linha e coluna do emoji do meio (TEM QUE SER O DO MEIO!)     \n\n");
  printf(" 3 - Vença o seu oponente e prove que é o melhor!    \n\n");
  printf("\t\t\t\t Bom jogo! :)\n");
}

void generate_table(int table[9][9], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      table[i][j] = rand() % 5;
    }
  }
}

void input_position(int round, Player *player, int table[9][9], int table_size, int position[2])
{
  char *pontuation_word = player->points != 1 ? "pontos" : "ponto";
  printf("                           %s | %i %s | Rodada %i \n", player->name, player->points, pontuation_word, round);
  print_table(table, table_size);
  print_line();

  char row, column;
  printf("Linha: ");
  scanf(" %c", &row);
  printf("Coluna: ");
  scanf(" %c", &column);

  if ((row < 65 && row > 73) || (column < 49 && column > 57))
  {
    exit(1);
  }
  else
  {
    position[0] = row - 65;
    position[1] = column - 49;
  }
}

int is_correct(int table[9][9], int position[2])
{
  int row = position[0];
  int column = position[1];
  int correct = 0;

  if (
      (row == 1 && column == 1) ||
      (row == 1 && column == 9) ||
      (row == 9 && column == 1) ||
      (row == 9 && column == 9))
  {
    return 0;
  }
  else
  {
    return verify_x(table, position) || verify_y(table, position);
  }
}

int verify_y(int table[9][9], int position[2])
{
  int row = position[0];
  int column = position[1];

  int
      old_value = table[row - 1][column],
      current_value = table[row][column],
      next_value = table[row + 1][column];

  return old_value == current_value && current_value == next_value;
}

int verify_x(int table[9][9], int position[2])
{
  int row = position[0];
  int column = position[1];

  int
      old_value = table[row][column - 1],
      current_value = table[row][column],
      next_value = table[row][column + 1];

  return old_value == current_value && current_value == next_value;
}

void exit_game()
{
  printf("                         🌹 thanks for playing 🌹");
  exit(1);
}

int main(void)
{
  game();
  return (0);
}
