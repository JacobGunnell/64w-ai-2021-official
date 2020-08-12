#include "SP.h"

SP::SP(int numInputs)
{
  W = arma::colvec(numInputs, arma::fill::randu);
}

arma::mat SP::integrate(arma::mat inputs) // TODO: possible problem with matrix dimensions? add some input validation
{
  return inputs * W;
}

bool SP::save(string filename)
{
  ofstream stream(filename + getExtension(), ios_base::binary);
  return W.save(stream);
}

bool SP::load(string filename)
{
  ifstream stream(filename, ios_base::binary);
  return W.load(stream);
}

void SP::mutate()
{
  // TODO
}
