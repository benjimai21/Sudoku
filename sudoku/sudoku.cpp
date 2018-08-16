#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}


bool is_complete(char board[9][9])
{

  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      if(board[i][j] == '.') 
	return false;
    }

  }

  return true;
}

bool make_move(const char* position, char number, char board[9][9])
{

  int r = position[0] - 'A';
  int c = position[1] - '1';
  int num = number - '1';

   if(c > 8 || c < 0)
    return false;

   if(r > 8 || r < 0)
    return false;

   if(num < 0 || num > 8)
     return false;

   if(board[r][c] != '.')
     return false;

   for(int i = 0 ; i < 9 ; i++) {

     if(board[r][i] == number)
       return false;

     if(board[i][c] == number)
       return false;
   }

   if(same_case(r, c, number, board))
     return false;

   board[r][c] = number;

   return true;
}

bool same_case(int r, int c, char number, char board[9][9])
{

  int min_c = c - (c%3);
  int max_c = min_c + 3;
  int min_r = r - (r%3);
  int max_r = min_r + 3;

  for(int i = min_r ; i < max_r ; i++) {

    for(int j = min_c ; j < max_c ; j++) {

      if(board[i][j] == number)
	return true;
    }

  }

  return false;

}

bool save_board(const char* file, char board[9][9])
{

  ofstream of;
  of.open(file);

  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      of << board[i][j];

    }
    of << endl;
  }

  return true;

}

bool solve_board(char board[9][9])
{

  if(is_complete(board))
    return true;

  int r;
  int c;

  get_position(r, c, board);

  char position[3];

  position[0] = r + 'A';
  position[1] = c + '1';
  position[2] = '\0';

  for(int i = 0 ; i < 9 ; i++) {

    char num = i + '1';

    if(make_move(position, num, board)) {

       if(solve_board(board))
	 return true;

       board[r][c] = '.';

    }
  }

  return false;
      
}

void get_position(int& r, int& c, char board[9][9])
{

  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      if(board[i][j] == '.') {
	r = i;
	c = j;
	return;
      }
    }
  }
}

/* add your functions here */
/*question 1*/
/*
bool is_complete(char board[9][9])
{
  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      if(board[i][j] == '.')
	return false;

    }

  }

  return true;
}

//question 2
bool make_move(const char position[], char digit, char board[9][9])
{
  int r = position[0] - 'A';
  int c = position[1] - '1';
  int dig = digit - '0';

  if(r < 0 || r > 8)
    return false;

  if(c < 0 || c > 8)
    return false;

  if(dig < 1 || dig > 9)
    return false;

  if(board[r][c] != '.')
    return false;

  for(int i = 0 ; i < 9 ; i++) {

    if(board[r][i] == digit)
      return false;

    if(board[i][c] == digit)
      return false;
  }

  if(check_subcase(r, c, digit, board))
    return false;

  board[r][c] = digit;

  return true;
}

bool check_subcase(int r, int c, char digit, char board[9][9])
{
  int row_low = r - r%3;
  int column_low = c - c%3;
  int row_high = row_low + 2;
  int column_high = column_low + 2;

  for(int i = row_low ; i <= row_high ; i++) {

    for(int j = column_low ; j <= column_high ; j++) {

      if(board[i][j] == digit)
	return true;
    }
  }

  return false;
}

//question 3
bool save_board(const char filename[], char board[9][9])
{
  ofstream outstream;

  outstream.open(filename);

  if(outstream.fail())
    return false;

  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      outstream.put(board[i][j]);
    }
    outstream << endl;

  }

  return true;
}

//question 4
bool solve_board(char board[9][9])
{
  int r;
  int c;
  char position[512];
  position[2] = '\0';

  if(is_complete(board))
    return true;

  find_next_empty_cell(board, r, c);
  position[0] = r + 'A';
  position[1] = c + '1';

  for(int i = 1 ; i <= 9 ; i++) {

    char digit = i + '0';

    if(make_move(position, digit, board)) {

    if(solve_board(board))
      return true;

    board[r][c] = '.';
    }
  }
  return false;
}


void find_next_empty_cell(char board[9][9], int& r, int& c)
{

  for(int i = 0 ; i < 9 ; i++) {

    for(int j = 0 ; j < 9 ; j++) {

      if(board[i][j] == '.') {
	r = i;
	c = j;
	return;
      }
    }
  }
}
*/
