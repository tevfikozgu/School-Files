#include <iostream>
#include <stdlib.h>

using namespace std;

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

bool find_path(char lab[8][8], int y, int x, int camefrom) { 
  lab[y][x] = 'o';
  if ( x == 7 && y == 1 )
    return true;
  if ( x > 0 && lab[y][x - 1] != 'x' && camefrom != LEFT ) 
    if ( find_path(lab, y, x - 1, RIGHT) ) // go left
      return true;
  if ( y < 7 && lab[y + 1][x] != 'x' && camefrom != DOWN )
    if ( find_path(lab, y + 1, x, UP) ) // go down
      return true;
  if ( y > 0 && lab[y - 1][x] != 'x' && camefrom != UP ) 
    if ( find_path(lab, y - 1, x, DOWN)) // go up
      return true;
  if ( x < 7 && lab[y][x + 1] != 'x' && camefrom != RIGHT)
    if ( find_path(lab, y, x + 1, LEFT) ) // go right
      return true;
  lab[y][x] = ' '; // delete incorrect paths
   // display the return from the incorrect paths as well 
  return false;
}

int main(){
  char lab[8][8] = {{'x','x','x','x','x','x','x','x'},
                    {' ',' ','x','x','x',' ',' ',' '},
                    {'x',' ','x','x','x',' ','x','x'},
                    {'x',' ',' ',' ',' ',' ',' ','x'},
                    {'x',' ','x',' ','x','x',' ','x'},
                    {'x',' ','x','x',' ','x',' ','x'}, 
                    {'x',' ',' ','x',' ',' ',' ','x'},
                    {'x','x','x','x','x','x','x','x'}
  };
  if ( find_path(lab, 1, 0, LEFT) )
    cout << "PATH found" << endl;
     return EXIT_SUCCESS;
   }