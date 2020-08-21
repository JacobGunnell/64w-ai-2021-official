#include "GameObject.h"

void GameObject::setX(double x_)
{
  if(x_ >= X_MIN)
  {
    if(x_ <= X_MAX)
      x = x_;
    else
      x = X_MAX;
  }
  else
    x = X_MIN;
}

void GameObject::setY(double y_)
{
  if(y_ >= Y_MIN)
  {
    if(y_ <= Y_MAX)
      y = y_;
    else
      y = Y_MAX;
  }
  else
    y = Y_MIN;
}
