void print_path(Cell* cell)
{
  if (cell->parent->parent!=0)
  {
    print_path(cell->parent);
    std::cout << "(" << cell->parent->x << "," << cell->parent->y << ")";
  }
  else
    return;
}
