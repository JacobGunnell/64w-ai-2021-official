#include "GameObject.h"

double GameObject::distFrom(int xCoord, int yCoord)
{
  return sqrt((x - xCoord)*(x - xCoord) + (y - yCoord)*(y - yCoord));
}
