//Author:Jason Evans
#include <cstring> //Needed for atoi() string->int conversion
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

//#include "MyNixCLI/MyNixCLI.h"

using namespace std;
                                                            
//Global Variables
int GAME_HEIGHT = 65;
int GAME_WIDTH = 100;

//function prototypes
vector <vector <char> > createGameBoard(vector <vector <char> >&);
void clearGameBoard(vector <vector <char> >&);
void updateGameBoard(vector <vector <char> >&);
vector<int> createDinosaur(vector <vector <char> >&,vector<int>&);
vector<int> moveDinosaur(vector <vector <char> >&,vector<int>&,char);

int main()
{
  //make it so enter is not required
  struct termios old_tio, new_tio;
  unsigned char action;
  tcgetattr(STDIN_FILENO,&old_tio);
  new_tio=old_tio;
  new_tio.c_lflag &=(~ICANON & ~ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

  vector <vector <char> > gameBoard;
  vector<int> dinosaurLocation;
  dinosaurLocation.resize(3);
  dinosaurLocation[2] = 2;
  int rand();
  gameBoard = createGameBoard(gameBoard);
  clearGameBoard(gameBoard);
  dinosaurLocation = createDinosaur(gameBoard,dinosaurLocation);
  updateGameBoard(gameBoard);        
  do
  {
    action = getchar();
    clearGameBoard(gameBoard);
    dinosaurLocation = moveDinosaur(gameBoard,dinosaurLocation,action);
    updateGameBoard(gameBoard);
  } while(action != 'q');
  
  //restore enter functionality
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
  return 0;
}

//Functions

//Create gameboard
vector <vector <char> > createGameBoard(vector <vector <char> > &board)
{
  board.resize(GAME_HEIGHT);
  for(int row = 0;row < GAME_HEIGHT;row++)
  {
    for(int column=0;column < GAME_WIDTH;column++)
    {
      board[row].resize(GAME_WIDTH);
    }        
  }
  return board;
}

//Clear gameboard
void clearGameBoard(vector <vector <char> > &board)
{
  for(int row = 0;row < board.size();row++)
  {
    for(int column=0;column < board[row].size();column++)
    {
      if(row == 0 || row == GAME_HEIGHT-1 || column == 0 || column == GAME_WIDTH-1)
      {
        board[row][column] = ' ';
        cout<<board[row][column];
      }
      else
      {
        board[row][column] = ' ';
      }
    }  
  }
}

//Update gameboard
void updateGameBoard(vector <vector <char> > &board)
{
  for(int row = 0;row < board.size();row++)
  {
    for(int column=0;column < board[row].size();column++)
    {
      cout<<board[row][column];
    }
  cout<<endl;  
  }
}

//create Dinosaur
vector<int> createDinosaur(vector <vector <char> > &board, vector <int> &location)
{
  int startRow = GAME_HEIGHT/2;
  int startColumn = GAME_WIDTH/2;
  board[startRow][startColumn] = '_';
  board[startRow][startColumn+1] = '_';
  board[startRow][startColumn+2] = '_';
  board[startRow][startColumn+3] = '_';
  board[startRow][startColumn+4] = '_';
  board[startRow][startColumn+5] = '_';
  board[startRow][startColumn+8] = '/';
  board[startRow][startColumn+9] = '|';
  board[startRow-1][startColumn+9] = '|';
  board[startRow-1][startColumn+10] = '\'';
  board[startRow-1][startColumn+11] = '|';
  board[startRow-1][startColumn+12] = ']';
  board[startRow+1][startColumn+5] = '\\';
  board[startRow+1][startColumn+6] = '|';
  board[startRow+1][startColumn+7] = '|';
  board[startRow+1][startColumn+8] = '|';
  board[startRow+1][startColumn+9] = '|';
  board[startRow+1][startColumn+10] = ',';
  board[startRow+1][startColumn+11] = ',';
  board[startRow+2][startColumn+6] = '|';
  board[startRow+2][startColumn+8] = '|';
  board[startRow+3][startColumn+6] = '-';
  board[startRow+3][startColumn+8] = '-';
  
  location[0] = startRow;
  location[1] = startColumn;

  return location;
}

//Move Dinosaur Right
vector<int> moveDinosaur(vector <vector <char> > &board,vector<int> &location,char moveAction)
{
  int startColumn = location[1];
  int startRow = location[0];
  int direction = location[2];
  
  switch(moveAction)
  {
    case 'a': //move left 
      switch(direction)
      {
        case 1:
          startColumn = location[1]-2;
          startRow = location[0];
          break;
        case 2:
          startColumn = location[1]+11;
          startRow = location[0];
          break;
        case 3:
          startColumn = location[1]+7;
          startRow = location[0];
          break;
        case 4:
          startColumn = location[1]+7;
          startRow = location[0];
          break;
      }        
      board[startRow][startColumn] = '_';
      board[startRow][startColumn-1] = '_';
      board[startRow][startColumn-2] = '_';
      board[startRow][startColumn-3] = '_';
      board[startRow][startColumn-4] = '_';
      board[startRow][startColumn-5] = '_';
      board[startRow][startColumn-8] = '\\';
      board[startRow][startColumn-9] = '|';
      board[startRow-1][startColumn-9] = '|';
      board[startRow-1][startColumn-10] = '\'';
      board[startRow-1][startColumn-11] = '|';
      board[startRow-1][startColumn-12] = '[';
      board[startRow+1][startColumn-5] = '/';
      board[startRow+1][startColumn-6] = '|';
      board[startRow+1][startColumn-7] = '|';
      board[startRow+1][startColumn-8] = '|';
      board[startRow+1][startColumn-9] = '|';
      board[startRow+1][startColumn-10] = ',';
      board[startRow+1][startColumn-11] = ',';
      board[startRow+2][startColumn-6] = '|';
      board[startRow+2][startColumn-8] = '|';
      board[startRow+3][startColumn-6] = '-';
      board[startRow+3][startColumn-8] = '-';
    
      direction = 1;
      break;    
    case 'd': //move right
      switch(direction)
      {
        case 1:
          startColumn = location[1]-11;
          startRow = location[0];
          break;
        case 2:
          startColumn = location[1]+2;
          startRow = location[0];
          break;
        case 3:
          startColumn = location[1]-7;
          startRow = location[0];
          break;
        case 4:
          startColumn = location[1]-7;
          startRow = location[0];
          break;
      }    
      board[startRow][startColumn] = '_';
      board[startRow][startColumn+1] = '_';
      board[startRow][startColumn+2] = '_';
      board[startRow][startColumn+3] = '_';
      board[startRow][startColumn+4] = '_';
      board[startRow][startColumn+5] = '_';
      board[startRow][startColumn+8] = '/';
      board[startRow][startColumn+9] = '|';
      board[startRow-1][startColumn+9] = '|';
      board[startRow-1][startColumn+10] = '\'';
      board[startRow-1][startColumn+11] = '|';
      board[startRow-1][startColumn+12] = ']';
      board[startRow+1][startColumn+5] = '\\';
      board[startRow+1][startColumn+6] = '|';
      board[startRow+1][startColumn+7] = '|';
      board[startRow+1][startColumn+8] = '|';
      board[startRow+1][startColumn+9] = '|';
      board[startRow+1][startColumn+10] = ',';
      board[startRow+1][startColumn+11] = ',';
      board[startRow+2][startColumn+6] = '|';
      board[startRow+2][startColumn+8] = '|';
      board[startRow+3][startColumn+6] = '-';
      board[startRow+3][startColumn+8] = '-';
      
      direction = 2;
      break;
    case 'w': //move up
      switch(direction)
      {
        case 1:
          startColumn = location[1]-7;
          startRow = location[0]-1;  
          break;
        case 2:
          startColumn = location[1]+7;
          startRow = location[0]-1;  
          break;
        case 3:
          startColumn = location[1];
          startRow = location[0]-2;  
          break;
        case 4:
          startColumn = location[1];
          startRow = location[0]-2;  
          break;     
      }
      board[startRow][startColumn] = '|';
      board[startRow-1][startColumn] = '_';
      board[startRow-1][startColumn-1] = '_';
      board[startRow-1][startColumn+1] = '_';
      board[startRow+1][startColumn] = '_';
      board[startRow+1][startColumn-1] = '_';
      board[startRow+1][startColumn+1] = '_';
      board[startRow+2][startColumn-2] = '|';
      board[startRow+2][startColumn-1] = '_';
      board[startRow+2][startColumn] = '_';
      board[startRow+2][startColumn+1] = '_';
      board[startRow+2][startColumn+2] = '|';
      board[startRow+3][startColumn-2] = '|';
      board[startRow+3][startColumn] = '|';
      board[startRow+3][startColumn+2] = '|';
      board[startRow+4][startColumn-2] = '-';
      board[startRow+4][startColumn] = '|';
      board[startRow+4][startColumn+2] = '-';
      board[startRow+5][startColumn] = '|';
     
      direction = 3;
      break;
    case 's': //move down
      switch(direction)
      {
        case 1:
          startColumn = location[1]-7;
          startRow = location[0];  
          break;
        case 2:
          startColumn = location[1]+7;
          startRow = location[0];  
          break;
        case 3:
          startColumn = location[1];
          startRow = location[0]+2;  
          break;
        case 4:
          startColumn = location[1];
          startRow = location[0]+2;  
          break;     
      }
      board[startRow][startColumn] = '|';
      board[startRow-1][startColumn] = 'v';
      board[startRow-1][startColumn-1] = 'v';
      board[startRow-1][startColumn+1] = 'v';
      board[startRow-2][startColumn] = '_';
      board[startRow-2][startColumn-1] = '.';
      board[startRow-2][startColumn+1] = '.';
      board[startRow+1][startColumn-1] = ',';
      board[startRow+1][startColumn+1] = ',';
      board[startRow+2][startColumn] = '-';
      board[startRow+2][startColumn+2] = '|';
      board[startRow+2][startColumn-2] = '|';
      board[startRow+3][startColumn-2] = '-';
      board[startRow+3][startColumn+2] = '-';
     
      direction = 4;
      break;
  }
  
  location[0] = startRow;
  location[1] = startColumn;
  location[2] = direction;

  return location;
}
