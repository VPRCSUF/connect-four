#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

const int ROWS = 6;
const int COLUMNS = 8;
const char EMPTY = ' ';
const char PLAYER_PIECE = 'x';
const char COMPUTER_PIECE = 'o';
const string PLAYER_WINS = "Player wins!";
const string COMPUTER_WINS = "Computer wins!";
const string OUTCOME_IS_DRAW = "The game ended in a draw.";
const string GAME_IN_PROGRESS = "The game is not finished yet.";

//------------------------------------------------------------------------------
//CREATE THE BOARD
//------------------------------------------------------------------------------
void Print(char board[ROWS][COLUMNS]) {

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      cout << "|";
      cout << board[i][j];
    }
    cout << endl;
  }
}

//------------------------------------------------------------------------------
//PLAYER CHOICE
//------------------------------------------------------------------------------
void SetPlayerMove(char board[ROWS][COLUMNS]) {
  int column_choice;
  bool input;

  //Loops through until the user chooses a valid column.
  do {
    cout << "Please choose a column...\n";
    cin >> column_choice;

    //Prompt the user to choose another column if the column they chose is not
    //from 0 - 6.
    if (column_choice < 0 || column_choice > 6) {
      cout << "Sorry, that is an invalid column. Please choose column 0 thru 6.\n";
      input = false;

      //Checks if the column is full. If so, prompts the user to choose another
      //column.
    } else if (board[0][column_choice] != EMPTY) {
      cout << "Sorry, that column is full. Please choose another column.\n";
      input = false;
    } else {
      int row_choice;

      //Loops through the rows of that column and finds the bottom most empty
      //row.
      for (int i = 0; i < ROWS; i++) {

        //The chosen row becomes the last row that was detected as empty.
        if (board[i][column_choice] == EMPTY) {
          row_choice = i;
        }
      }
      board[row_choice][column_choice] = PLAYER_PIECE;

      //Input becomes true to exit the loop.
      input = true;
    }
  } while (input == false);
}

//------------------------------------------------------------------------------
//COMPUTER CHOICE
//------------------------------------------------------------------------------
void SetComputerMove(char board[ROWS][COLUMNS]) {
  bool input;

  cout << "My turn...";
  this_thread::sleep_for(chrono::seconds(1));

  //Loops through until the computer chooses a valid column.
  do {
    //Randomly generate a valid column choice from 0 to 6.
    int column_choice = rand() % 7;

    //Checks if the column is full. If so, the computer will try again.
    if (board[0][column_choice] != EMPTY) {
      input = false;
    } else {
      int row_choice;

      //Loops through the rows of that column to find the bottom most empty row.
      for (int i = 0; i < ROWS; i++) {

        //The chosen row becomes the last row that was detected as empty.
        if (board[i][column_choice] == EMPTY) {
          row_choice = i;
        }
      }
      board[row_choice][column_choice] = COMPUTER_PIECE;
      input = true;
    }
  } while (input == false);
}

//------------------------------------------------------------------------------
//CHECK ROWS
//------------------------------------------------------------------------------
bool CheckRows(char board[ROWS][COLUMNS], char piece) {
  //Loops through the rows and checks each column of that row for connect 4.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < 4; j++) {

      //Checks all possible connect 4's in each row since there are four
      //possible ways to get a connect 4 in each row.
      if (board[i][j] == piece &&
          board[i][j + 1] == piece &&
          board[i][j + 2] == piece &&
          board[i][j + 3] == piece) {
            return true;
          }
    }
  }

  return false;
}

//------------------------------------------------------------------------------
//CHECK COLUMNS
//------------------------------------------------------------------------------
bool CheckColumns(char board[ROWS][COLUMNS], char piece) {
  //Loops through each column and checks each row in that column for a connect 4.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < COLUMNS; j++) {

      //Checks all possible connect 4's in each column since there are three
      //possible ways to get a connect 4 in each column.
      if (board[i][j] == piece &&
          board[i + 1][j] == piece &&
          board[i + 2][j] == piece &&
          board[i + 3][j] == piece) {
            return true;
          }
    }
  }

  return false;
}

//------------------------------------------------------------------------------
//CHECK DIAGONALS
//------------------------------------------------------------------------------
bool CheckDiagonals(char board[ROWS][COLUMNS], char piece) {
  //Check Top Left to Bottom Right.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (
          //Checks all the diagonals of length 4 that start in row 0.(4 total)
          //Checks all the diagonals of length 4 that start in row 1.(4 total)
          //Checks all the diagonals of length 4 that start in row 2.(4 total)
          //Checks for all 12 possible connect 4's from the diagonals that go
          //from the TOP LEFT to the BOTTOM RIGHT.
          board[i][j] == piece &&
          board[i + 1][j + 1] == piece &&
          board[i + 2][j + 2] == piece &&
          board[i + 3][j + 3] == piece) {
            return true;
          }
    }
  }

  //Check Bottom to Top Right.
  for (int i = 5; i > 2; i--) {
    for (int j = 0; j < 4; j++) {
      if (
          //Checks all the diagonals of length 4 that start in row 5.(4 total)
          //Checks all the diagonals of length 4 that start in row 4.(4 total)
          //Checks all the diagonals of length 4 that start in row 3.(4 total)
          //Checks for all 12 possible connect 4's from the diagonals that go
          //from the BOTTOM LEFT to the TOP RIGHT.
          board[i][j] == piece &&
          board[i - 1][j + 1] == piece &&
          board[i - 2][j + 2] == piece &&
          board[i - 3][j + 3] == piece) {
            return true;
          }
    }
  }
  return false;
}

//------------------------------------------------------------------------------
//CHECK WINNER
//------------------------------------------------------------------------------
bool IsWinner(char board[ROWS][COLUMNS], char piece) {
  //Checks all the rows, columns, and diagonals for a connect 4.
  if (CheckRows(board, piece) == true ||
      CheckColumns(board, piece) == true ||
      CheckDiagonals(board, piece) == true) {
        return true;
      }

  //Returns false if there are no connect 4's detected.
  return false;
}

//------------------------------------------------------------------------------
//CHECK BOARD
//------------------------------------------------------------------------------
bool IsBoardFull(char board[ROWS][COLUMNS]) {
  //Loops through the array and checks all the spaces. If at least one space is
  //found to be empty, it is automatically assumed that the board is not full.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (board[i][j] == EMPTY) {
        return false;
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
//DETERMINE BOARD STATE
//------------------------------------------------------------------------------
string DetermineBoardState(char board[ROWS][COLUMNS]) {
  //Determines the state of the board. If the player won, will print out that
  //the player has won.
  if (IsWinner(board, PLAYER_PIECE) == true) {
    return PLAYER_WINS;

    //If the computer won, will print out that the computer has won.
  } else if (IsWinner(board, COMPUTER_PIECE) == true) {
    return COMPUTER_WINS;

    //If the board is found to be full, it is assumed that the game ended in a
    //draw. Will print out that the game ended in a draw.
  } else if (IsBoardFull(board) == true) {
    return OUTCOME_IS_DRAW;
  }

  //If none of the above cases are met, prints that the game is in progress.
  return GAME_IN_PROGRESS;
}

//******************************************************************************
int main(int argc, char* argv[]) {
  srand(time(0));

  char game_board[ROWS][COLUMNS] = {};

  //Initialize all spaces of the game board as empty.
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      game_board[i][j] = EMPTY;
    }
  }

  //Print game board.
  Print(game_board);

  //Loops through a maximum 42 times, which is the most moves that can be made
  //in this game, or until a connect 4 is detected.
  for (int i = 0; i < 42; i++) {

    //First, checks if the board is full or if there are any connect 4's.
    //If so, exits the loop and ends the game.
    if ((DetermineBoardState(game_board) != GAME_IN_PROGRESS) ||
         IsBoardFull(game_board) == true) {
      i = 42;

      //Player's turn. Prints the updated board showing where the player placed
      //their piece.
    } else {
      SetPlayerMove(game_board);
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));

      Print(game_board);
      cout << endl;
    }

    //Checks if the board is full or if there are any connect 4's.
    //If so, exits the loop and ends the game.
    if ((DetermineBoardState(game_board) != GAME_IN_PROGRESS) ||
         IsBoardFull(game_board) == true) {
      i = 42;

      //Computer's turn. Prints the updated board showing where the computer
      //placed their piece.
    } else {
      SetComputerMove(game_board);
      cout << endl;

      this_thread::sleep_for(chrono::seconds(1));
      Print(game_board);
      this_thread::sleep_for(chrono::seconds(1));
      cout << endl;
    }
  }

  //Prints the outcome of the game.
  string outcome = DetermineBoardState(game_board);
  cout << outcome << endl;

  return 0;
}
