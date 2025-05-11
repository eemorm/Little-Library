//AJ, Sean, Everett

#include <stdio.h>
#include <stdlib.h>

void playGame();
void printBoard();
int checkWin();
int checkTie();
void endGame(int scenario);
  
char playersettings[3] = {'_', 'X', 'O'};

int choice;
char board[3][3] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};
int player1_wins = 0, player2_wins = 0;
int player = 1, winner;
int row, column;
int ties;

int main() 
{
  while (1) 
  {
    printf("Welcome to Tic Tac Toe!\n\nWould you like to play? (1 to play 2 to quit): ");
    scanf("%d", &choice);

    if (choice == 1) 
    {
      system("clear");
      printf("Use coordinates to input your space. X and Y, bottom left is (1, 1), top right is (3, 3), etc. When inputting, input the X coordinate and hit enter. Then input the Y coordinate and hit enter.\n\n");
      playGame();
      choice = 0; 
    } 
    else if (choice == 2) 
    {
      system("clear");
      printf("Player 1 won %d times and Player 2 won %d times. There were %d ties.\n", player1_wins, player2_wins, ties);
      break;
    }
    else
    {
      system("clear");
      continue;
    }
  }
}

void playGame()
{
  int x, y;
  for (x = 0; x < 3; x++) 
  {
    for (y = 0; y < 3; y++) 
    {
      board[x][y] = '_';
    }
  }
  player = 1;
  while (1)
  {
    printf("Player %d's turn.\n\n", player);
    printBoard();
    printf("Where would you like to place your piece? (You are %c): " , playersettings[player]);
    scanf("%d%d", &column, &row);
    system("clear");
    if (row <= 3 && row >= 1 && column <= 3 && column >= 1)
    {
      if (board[row-1][column-1] == '_')
      {
        board[row-1][column-1] = playersettings[player];
      }
      else
      {
        printf("A piece is already there!\n\n");
        continue;
      }
    }
    else
    {
      printf("That is not a valid coordinate!\n\n");
      continue;
    }
    
    if (checkWin() == 1)
    {
      endGame(1);
      printBoard();
      break;
    }

    if (checkTie() == 1)
    {
      endGame(0);
      printBoard();
      break;
    }
    if (player == 1)
    {
      player = 2;
    }
    else
    {
      player = 1;
    }
  }
}

void printBoard() 
{
  printf("-------------\n");
  
  int x, y;
  for (x = 2; x >= 0; x--) 
  {
    for (y = 0; y < 3; y++) 
    {
      printf("| %c ", board[x][y]);
    }
    printf("|\n-------------\n");
  }
  printf("\n");
}

int checkWin() {
  int x, y;

  for (x = 0; x < 3; x++) 
  {
    if (board[x][0] == board[x][1] && board[x][0] == board[x][2] && board[x][0] != '_') 
    {
      if (board[x][0] == 'X') 
      {
        winner = 1;
      } 
      else if (board[x][0] == 'O') 
      {
        winner = 2;
      }
      return 1;
    }
  }

  for (y = 0; y < 3; y++)
  {
    if (board[0][y] == board[1][y] && board[0][y] == board[2][y] && board[0][y] != '_')
    {
      if (board[0][y] == 'X')
      {
        winner = 1;
      }
      else if (board[0][y] == 'O') 
      {
        winner = 2;
      }
      return 1;
    }
  }

  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_')
  {
    if (board[0][0] == 'X')
      {
        winner = 1;
      }
      else if (board[0][0] == 'O')
      {
        winner = 2;
      }
    return 1;
  }

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_')
  {
    if (board[0][2] == 'X')
      {
        winner = 1;
      }
      else if (board[0][2] == 'O')
      {
        winner = 2;
      }
    return 1;
  }
  
  return 0;
}

int checkTie()
{
  int x, y;
  
  for (x = 0; x < 3; x++)
    {
      for (y = 0; y < 3; y++)
        {
          if (board[x][y] == '_')
            return 0;
          else
            continue;
        }
    }

  return 1;
}

void endGame(int scenario)
{
  if (scenario == 0)
  {
    printf("It's a tie!\n");
    ties += 1;
  }
  else if (scenario == 1)
  {
    printf("Player %d wins!\n", winner);
    if (winner == 1)
    {
      player1_wins += 1;
    }
    else if (winner == 2)
    {
      player2_wins += 1;
    }
  }
}
