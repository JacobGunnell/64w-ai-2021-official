#include "Ball.h"

Color operator!(const Color &c)
{
  if(c == RED)
    return BLUE;
  else if(c == BLUE)
    return RED;
  else
    return NONE; 
}
