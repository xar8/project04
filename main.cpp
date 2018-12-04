//Author:Jason Evans
#include <cstring> //Needed for atoi() string->int conversion
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <ctime>

//#include "MyNixCLI/MyNixCLI.h"

using namespace std;
                                                            
//Global Variables
int GAME_HEIGHT = 65;
int GAME_WIDTH = 100;
int GAME_BORDER = 4;
//function prototypes
vector <vector <char> > createGameBoard(vector <vector <char> >&);
void clearGameBoard(vector <vector <char> >&);
void updateGameBoard(vector <vector <char> >&);
vector<int> createDinosaur(vector <vector <char> >&,vector<int>&);
vector<int> moveDinosaur(vector <vector <char> >&,vector<int>&,char,vector<int>);
vector<int> createPerson(vector <vector <char> >&,int,int);

int main()
{
  //make it so enter is not required
  struct termios old_tio, new_tio;
  unsigned char action;
  tcgetattr(STDIN_FILENO,&old_tio);
  new_tio=old_tio;
  new_tio.c_lflag &=(~ICANON & ~ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
  
  //Setup
  vector <vector <char> > gameBoard;
  vector<int> dinosaurLocation;
  dinosaurLocation.resize(4);
  dinosaurLocation[2] = 2;
  vector<int> personLocation;
  personLocation.resize(2);
  srand(time(0));
  int personLocationColumn = (rand() % GAME_WIDTH-GAME_BORDER)+GAME_BORDER;
  int personLocationRow = (rand() % GAME_HEIGHT-GAME_BORDER)+GAME_BORDER;
 
  //Setup gameboard
  gameBoard = createGameBoard(gameBoard);
  clearGameBoard(gameBoard);
  dinosaurLocation = createDinosaur(gameBoard,dinosaurLocation);
  personLocation = createPerson(gameBoard,personLocationRow,personLocationColumn);
  updateGameBoard(gameBoard);

  //Play game
  do
  {
    action = getchar();
    clearGameBoard(gameBoard);
    dinosaurLocation = moveDinosaur(gameBoard,dinosaurLocation,action,personLocation);
    if(dinosaurLocation[3] == 1)
    {
      personLocationColumn = rand() % GAME_WIDTH;
      personLocationRow = rand() % GAME_HEIGHT;
      personLocation = createPerson(gameBoard,personLocationRow,personLocationColumn);
    }
    else
    {
      personLocation = createPerson(gameBoard,personLocationRow,personLocationColumn);
    }
    dinosaurLocation[3] = 0;
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
  board[startRow][startColumn] = '|';
  board[startRow][startColumn-1] = '\\';
  board[startRow][startColumn+1] = '|';
  board[startRow][startColumn+2] = '|';
  board[startRow][startColumn+3] = '|';
  board[startRow][startColumn+4] = ',';
  board[startRow][startColumn+5] = ',';
  board[startRow+1][startColumn] = '|';
  board[startRow+1][startColumn+2] = '|';
  board[startRow+2][startColumn] = '-';
  board[startRow+2][startColumn+2] = '-';
  board[startRow-1][startColumn-1] = '_';
  board[startRow-1][startColumn-2] = '_';
  board[startRow-1][startColumn-3] = '_';
  board[startRow-1][startColumn-4] = '_';
  board[startRow-1][startColumn-5] = '_';
  board[startRow-1][startColumn-6] = '_';
  board[startRow-1][startColumn+2] = '/';
  board[startRow-1][startColumn+3] = '|';
  board[startRow-2][startColumn+3] = '|';
  board[startRow-2][startColumn+4] = '\'';
  board[startRow-2][startColumn+5] = '|';
  board[startRow-2][startColumn+6] = ']';
 
  location[0] = startRow;
  location[1] = startColumn;

  return location;
}

//Move Dinosaur
vector<int> moveDinosaur(vector <vector <char> > &board,vector<int> &location,char moveAction,vector<int> personLoc)
{
  int startColumn = location[1];
  int startRow = location[0];
  int direction = location[2];
  int personBump = location[3];
  int personRow = personLoc[0];
  int personColumn = personLoc[1];

  switch(moveAction)
  {
    case 'a': //move left
      if(startColumn-6 > GAME_BORDER)
      {
        switch(direction)
        {
          case 1:
            startColumn = location[1]-2;
            startRow = location[0];
            break;
          case 2:
            startColumn = location[1];
            startRow = location[0];
            break;
          case 3:
            startColumn = location[1];
            startRow = location[0];
            break;
          case 4:
            startColumn = location[1];
            startRow = location[0];
            break;
        }
      }
      board[startRow][startColumn] = '|';
      board[startRow][startColumn+1] = '/';
      board[startRow][startColumn-1] = '|';
      board[startRow][startColumn-2] = '|';
      board[startRow][startColumn-3] = '|';
      board[startRow][startColumn-4] = ',';
      board[startRow][startColumn-5] = ',';
      board[startRow+1][startColumn] = '|';
      board[startRow+1][startColumn-2] = '|';
      board[startRow+2][startColumn] = '-';
      board[startRow+2][startColumn-2] = '-';
      board[startRow-1][startColumn+1] = '_';
      board[startRow-1][startColumn+2] = '_';
      board[startRow-1][startColumn+3] = '_';
      board[startRow-1][startColumn+4] = '_';
      board[startRow-1][startColumn+5] = '_';
      board[startRow-1][startColumn+6] = '_';
      board[startRow-1][startColumn-2] = '\\';
      board[startRow-1][startColumn-3] = '|';
      board[startRow-2][startColumn-3] = '|';
      board[startRow-2][startColumn-4] = '\'';
      board[startRow-2][startColumn-5] = '|';
      board[startRow-2][startColumn-6] = '[';
 
      //check if you have bumped the person
      if((personRow <= startRow+2 && personRow >= startRow-2) && (personColumn <= startColumn+6 && personColumn >= startColumn-6))
      {
        personBump = 1; 
      }
      else
      {
        personBump = 0;
      }
      direction = 1;
      break;    
    case 'd': //move right
      if(startColumn+6 < GAME_WIDTH-GAME_BORDER)    
      {
        switch(direction)
        {
          case 1:
            startColumn = location[1];
            startRow = location[0];
            break;
          case 2:
            startColumn = location[1]+2;
            startRow = location[0];
            break;
          case 3:
            startColumn = location[1];
            startRow = location[0];
            break;
          case 4:
            startColumn = location[1];
            startRow = location[0];
            break;
        }
      }
      board[startRow][startColumn] = '|';
      board[startRow][startColumn-1] = '\\';
      board[startRow][startColumn+1] = '|';
      board[startRow][startColumn+2] = '|';
      board[startRow][startColumn+3] = '|';
      board[startRow][startColumn+4] = ',';
      board[startRow][startColumn+5] = ',';
      board[startRow+1][startColumn] = '|';
      board[startRow+1][startColumn+2] = '|';
      board[startRow+2][startColumn] = '-';
      board[startRow+2][startColumn+2] = '-';
      board[startRow-1][startColumn-1] = '_';
      board[startRow-1][startColumn-2] = '_';
      board[startRow-1][startColumn-3] = '_';
      board[startRow-1][startColumn-4] = '_';
      board[startRow-1][startColumn-5] = '_';
      board[startRow-1][startColumn-6] = '_';
      board[startRow-1][startColumn+2] = '/';
      board[startRow-1][startColumn+3] = '|';
      board[startRow-2][startColumn+3] = '|';
      board[startRow-2][startColumn+4] = '\'';
      board[startRow-2][startColumn+5] = '|';
      board[startRow-2][startColumn+6] = ']';
 
      //check if you have bumped the person
      if((personRow <= startRow+2 && personRow >= startRow-2) && (personColumn <= startColumn+6 && personColumn >= startColumn-6))
      {
        personBump = 1; 
      }
      else
      {
        personBump = 0;
      }    
      
      direction = 2;
      break;
    case 'w': //move up
      if(startRow-2 > GAME_BORDER)  
      {  
        switch(direction)
        {
          case 1:
            startColumn = location[1];
            startRow = location[0]-1;  
            break;
          case 2:
            startColumn = location[1];
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
      }
      board[startRow][startColumn] = '_';
      board[startRow][startColumn+1] = '_';
      board[startRow][startColumn-1] = '_';
      board[startRow][startColumn+2] = '|';
      board[startRow][startColumn-2] = '|';
      board[startRow-1][startColumn] = '_';
      board[startRow-1][startColumn+1] = '_';
      board[startRow-1][startColumn-1] = '_';
      board[startRow-2][startColumn] = '_';
      board[startRow+1][startColumn] = '|';
      board[startRow+1][startColumn+2] = '|';
      board[startRow+1][startColumn-2] = '|';
      board[startRow+2][startColumn] = '|';
      board[startRow+2][startColumn+2] = '-';
      board[startRow+2][startColumn-2] = '-';
     
      //check if you have bumped the person
      if((personRow <= startRow+2 && personRow >= startRow-2) && (personColumn <= startColumn+2 && personColumn >= startColumn -2))
      {
        personBump = 1; 
      }
      else
      {
        personBump = 0;
      } 
      
      direction = 3;
      break;
    case 's': //move down
      if(startRow+2 < GAME_HEIGHT-GAME_BORDER)
      {
        switch(direction)
        {
          case 1:
            startColumn = location[1];
            startRow = location[0];  
            break;
          case 2:
            startColumn = location[1];
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
      }  
      board[startRow][startColumn+1] = ',';
      board[startRow][startColumn-1] = ',';
      board[startRow-1][startColumn] = 'v';
      board[startRow-1][startColumn+1] = 'v';
      board[startRow-1][startColumn-1] = 'v';
      board[startRow-2][startColumn] = '_';
      board[startRow-2][startColumn+1] = '.';
      board[startRow-2][startColumn-1] = '.';
      board[startRow+1][startColumn+2] = '|';
      board[startRow+1][startColumn] = '-';
      board[startRow+1][startColumn-2] = '|';
      board[startRow+2][startColumn+2] = '-';
      board[startRow+2][startColumn-2] = '-';
      
      //check if you have bumped the person
      if((personRow <= startRow+2 && personRow >= startRow-2) && (personColumn <= startColumn+2 && personColumn >= startColumn -2))
      {
        personBump = 1; 
      }
      else
      {
        personBump = 0;
      } 
      
      direction = 4;
      break;
  }
  
  location[0] = startRow;
  location[1] = startColumn;
  location[2] = direction;
  location[3] = personBump;

  return location;
}

//create Person
vector<int> createPerson(vector <vector <char> > &board,int startRow,int startColumn)
{
  vector<int> personLocation;
  personLocation.resize(2);
  board[startRow][startColumn] = 'o';
  board[startRow+1][startColumn] = '|';
  board[startRow+1][startColumn-1] = '~';
  board[startRow+1][startColumn+1] = '~';
  board[startRow+2][startColumn-1] = '/';
  board[startRow+2][startColumn+1] = '\\';

  personLocation[0] = startRow;
  personLocation[1] = startColumn;

  return personLocation;
}


