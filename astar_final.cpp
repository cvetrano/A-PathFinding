#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>      // std::ifstream
#include <string.h>
#include "cell.h"
#include "print_path.h"
#include "check_cell.h"

int main( int argc, char *argv[] )
{

  if (argc==1)
  {
    std::cout << "No map file was included in the command line. \n";
    return 0;
  }

  //List of Cells available to visit
  std::vector<Cell*> Open_List;
  //List of Cells we shouldn't visit
  std::vector<Cell*> Closed_List;
  //2D LIST of NODES
  std::vector<std::vector<char> > map_chars(125, std::vector<char>(125));
  //ROWS for 2D LIST of NODES
  std::vector<char> vector_char;
  //Open the input file
  std::ifstream map_file(argv[1]);

  char c;
  int cur_x=0, cur_y=0;
  int i = 1;
  int j = 1;
  int map_width = 0;
  int map_height = 0;

  //Read each character of the file and place into a 2D Vector
  while (map_file.get(c))          // loop getting single characters
  {
    if (c == '\n')
    {
      //Set the map width constraint
      map_width = i;
      j++;
      i = 1;
    }
    else
    {
      //Add Character to the 2D Vector
      //This will be referenced later when seeing if there is a wall or open space
      map_chars[i][j] = c;
      i++;
    }
    //Set the map height constraint
    map_height = j;
  }


  Cell* start_cell = new Cell;
  Cell* current_cell = new Cell;
  Cell* goal_cell = new Cell;
  //SET start_cell
  if (!strcmp(argv[1],"maze_No_1.txt"))
  {
    start_cell->x = 1;
    start_cell->y = 1;
    start_cell->g = 0;
    start_cell->f = start_cell->GetF();

    current_cell-> x = start_cell->x;
    current_cell-> y = start_cell->y;
    current_cell-> g = start_cell->g;
    current_cell->f = current_cell->GetF();

    //SET goal_cell
    goal_cell->x = 78;
    goal_cell->y = 47;
  }
  else if (!strcmp(argv[1],"maze_No_2.txt"))
  {
    start_cell->x = 101;
    start_cell->y = 101;
    start_cell->g = 0;
    start_cell->f = start_cell->GetF();

    current_cell-> x = start_cell->x;
    current_cell-> y = start_cell->y;
    current_cell-> g = start_cell->g;
    current_cell->f = current_cell->GetF();

    //SET goal_cell
    goal_cell->x = 1;
    goal_cell->y = 53;
  }
  else if (!strcmp(argv[1],"maze_No_3.txt")) //My small sample maze, also included.
  {
    start_cell->x = 1;
    start_cell->y = 1;
    start_cell->g = 0;
    start_cell->f = start_cell->GetF();

    current_cell-> x = start_cell->x;
    current_cell-> y = start_cell->y;
    current_cell-> g = start_cell->g;
    current_cell->f = current_cell->GetF();

    //SET goal_cell
    goal_cell->x = 10;
    goal_cell->y = 1;
  }
  else
  {
    std::cout << "The file names you used are not consistent with the assignment." <<
      " Use   maze_No_2.txt   or   maze_No_1.txt   \n";
    return 0;
  }

  //Now figure out h of the current cell
  start_cell->h = start_cell->GetH(goal_cell);
  current_cell->h = current_cell->GetH(goal_cell);
  start_cell->f = start_cell->GetF();
  current_cell->f = current_cell->GetF();

  Open_List.push_back(current_cell);

  //Check cells up, down, left, right
  while (!(current_cell->x == goal_cell->x && current_cell->y == goal_cell->y))
  {
    //Check cell Right
    check_cell(current_cell->x+1, current_cell->y,
      current_cell->g+1, current_cell, goal_cell, map_chars, Open_List, Closed_List,
      map_width, map_height);
    //Check cell Left
    check_cell(current_cell->x-1, current_cell->y,
      current_cell->g+1, current_cell, goal_cell, map_chars, Open_List, Closed_List,
      map_width, map_height);
    //Check cell Up
    check_cell(current_cell->x, current_cell->y-1,
      current_cell->g+1, current_cell, goal_cell, map_chars, Open_List, Closed_List,
      map_width, map_height);
    //Check cell Down
    check_cell(current_cell->x, current_cell->y+1,
      current_cell->g+1, current_cell, goal_cell, map_chars, Open_List, Closed_List,
      map_width, map_height);

    //First sort by f
    std::sort(Open_List.begin(), Open_List.end(), sort_by_f());

      current_cell = Open_List[Open_List.size()-1];

      if (current_cell->x == goal_cell->x && current_cell->y == goal_cell->y)
      {
        std::cout << "[ ";
        std::cout << "(" << start_cell->x << "," << start_cell->y << ")";
        print_path(current_cell);
        std::cout << "(" << goal_cell->x << "," << goal_cell->y << ")";
        std::cout << " ]\n";
      }
      else
      {
        Closed_List.push_back(current_cell);
        Open_List.pop_back();
      }
  }
}
