struct Cell
{
  int x, y;
  //int id;
  float g;
  float h;
  float f;
  Cell *parent;

  //Get the cost of this  node.
  float GetF()
  {
    return g + h;
  }

  int GetH(Cell* goal_cell)
  {
    int g_x = abs(goal_cell->x);
    int g_y = abs(goal_cell->y);

    return 2 * abs(x - g_x) + abs(y - g_y);
  }
};

struct sort_by_f
{
    inline bool operator() (const Cell* cell1, const Cell* cell2)
    {
        return (cell1->f > cell2->f);
    }
};
