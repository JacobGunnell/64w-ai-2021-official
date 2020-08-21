#include "Move.h"

double Move::getPoints(SensorWrapper &sensorwrapper, Alliance a)
{
  SensorWrapper temp(sensorwrapper);
  double initialScore = Match::score(temp, a) - Match::score(temp, !a);
  vexecute(temp);
  return (Match::score(temp, a) - Match::score(temp, !a)) - initialScore;
}

arma::mat Move::toMatrix(Move **m, const int len, SensorWrapper &sensorwrapper)
{
  arma::mat matrix;
  if(m != NULL)
  {
    for(int i = 0; i < len; i++)
    {
      if(m[i] != NULL)
        matrix.insert_rows(i, m[i]->getData(sensorwrapper).vectorize());
      else
        matrix.insert_rows(i, MoveData().vectorize());
    }
    return matrix;
  }
  return MoveData().vectorize();
}

arma::mat Move::toMatrix(MoveContainer m, SensorWrapper &sensorwrapper)
{
  return toMatrix(m.moves.data(), m.moves.size(), sensorwrapper);
}
