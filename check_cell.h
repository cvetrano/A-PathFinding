//Check Cells Up Down Left Right

void check_cell(int x, int y, int g, Cell* current_cell, Cell* goal_cell,
  std::vector<std::vector<char> > map, std::vector<Cell*> &Open_List,
  std::vector<Cell*> &Closed_List, int map_width, int map_height)
{

  if (x < 1 || y < 1 || x >= map_width || y >= map_height)
  {
    return;
  }

  for (int i=0; i<Closed_List.size(); i++)
  {
    if ((Closed_List[i]->x == x) && (Closed_List[i]->y == y))
    {
      //TESTING
      //std::cout << "Found a closed node at: " << x << "," << y << '\n' ;
      return;
    }
  }

  for (int i=0; i<Open_List.size(); i++)
  {
    if ((Open_List[i]->x == x) && (Open_List[i]->y == y))
    {
      //TESTING
      //std::cout << "Found an Open node at: " << x << "," << y << '\n' ;
      return;
    }
  }

  Cell* new_cell = new Cell;
  new_cell->x = x;
  new_cell->y = y;
  new_cell->g = g;
  new_cell->h = new_cell->GetH(goal_cell);
  new_cell->f = new_cell->GetF();
  new_cell->parent = current_cell;

  //FOR TESTING
  //std::cout << "x:" << new_cell->x << " y:" << new_cell->y << " g:" << new_cell->g
  //  << " f:" << new_cell->f << '\n';
  if (map[x][y] == '#')
  {
    //TESTING
    //std::cout << "Closing: " << x << "," << y << "," << map[x][y] << '\n';
    Closed_List.push_back(new_cell);
  }
  else
  {
    Open_List.push_back(new_cell);
  }

  return;
}
