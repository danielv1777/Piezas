#include "Piezas.h"
#include <vector>
using namespace std;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  for(int i = 0; i < BOARD_ROWS; i++)
  {
    vector<Piece> temp(BOARD_COLS);
    board.push_back(temp);
  }

  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for(int i = 0; i < (int)board.size(); i++)
  {
    for(int j = 0; j < (int)board[i].size(); j++)
    {
      board[i][j] = Blank;
    }
  }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
    if(column >= BOARD_COLS || column < 0){
      return Invalid;
    }
    else if (board[BOARD_ROWS-1][column] != Blank){
      return Blank;
    }
    else{
      for(int i = 0; i < BOARD_ROWS; i++){
        if(board[i][column] == Blank){
          board[i][column] = turn;
          break;
        }
      }
    }

    Piece temp = turn;

    if(turn == X){
      turn = O;
    }
    else
      turn = X;

    return temp;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if(row >= BOARD_ROWS || row < 0 || column >= BOARD_COLS || column < 0){
      return Invalid;
    }
    else if(board[row][column] == Blank){
      return Blank;
    }
    else{
      return board[row][column];
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    for(int i = 0; i < BOARD_ROWS; i++){//checks if game ended
      for(int j = 0; j < BOARD_COLS; j++){
        if(board[i][j] == Blank){
          return Invalid;
        }
      }
    }

    int cur = 1, max = 0, maxX = 0, maxO = 0;
    Piece temp;

    for(int i = 0; i < BOARD_ROWS; i++){
      for(int j = 1; j < BOARD_COLS; j++){
        if(board[i][j] == board[i][j-1]){
          cur++;
        }
        else{
          cur = 1;
        }
        if(cur >= max){
          max = cur;
          temp = board[i][j];
          if(temp == X){
            maxX = max;
          }
          else
            maxO = max;
        }
      }
    }
    cur = 1;

    for(int i = 0; i < BOARD_COLS; i++){
      for(int j = 1; j < BOARD_ROWS; j++){
        if(board[j][i] == board[j-1][i]){
          cur++;
        }
        else{
          cur = 1;
        }
        if(cur >= max){
          max = cur;
          temp = board[j][i];
          if(temp == X){
            maxX = max;
          }
          else{
            maxO = max;
          }
        }
      }
    }

    if(maxX == maxO){
      return Blank;
    }
    else if(maxX > maxO){
      return X;
    }
    return O;
}
