#include "Brain.h"

Brain::Brain(int numInputs, int numHidden) // create a random brain with specific dimensions
{
  int R = numInputs / numHidden;
  WL1 = arma::mat(numInputs, numHidden, arma::fill::randu);
  for(int row = numHidden; row < numInputs; row++)
  {
    for(int col = 0; col < row/R; col++)
      WL1(row,col) = 0;
  }
  WL2 = arma::mat(numHidden, 1, arma::fill::randu);
  B = arma::mat(1, numHidden, arma::fill::randn);
}

Brain::Brain(arma::mat &wl1, arma::mat &wl2, arma::mat &b) // create a brain from matrices
{
  WL1 = wl1;
  WL2 = wl2;
  B = b;

  try
  {
    arma::mat temp = wl1 * wl2; // if either of these multiplications fail (user has inputted bad data) it will throw
    temp = b * wl2;
  }
  catch(logic_error &e)
  {
    cout << "Constructor Error: Bad matrix dimensions for a Brain object!" << endl;
    terminate();
  }
}

Brain::Brain(Brain &mother, Brain &father) // breed a brain from a mother and a father
{
  // TODO
}

Brain::Brain(const Brain &cpy)
{
  WL1 = arma::mat(cpy.WL1);
  WL2 = arma::mat(cpy.WL2);
  B = arma::mat(cpy.B);
}

arma::mat Brain::integrate(arma::mat X)
{
  arma::mat EB(X.n_rows, B.n_cols, arma::fill::zeros);
  EB.each_row() += B;
  arma::mat U = (f(X*WL1 + EB) * WL2);
  return U;
}

bool Brain::save(string filename)
{
  ofstream stream(filename, ios_base::binary);
  return
  WL1.save(stream) &&
  WL2.save(stream) &&
  B.save(stream);
}

bool Brain::load(string filename)
{
  ifstream stream(filename, ios_base::binary);
  return
  WL1.load(stream) &&
  WL2.load(stream) &&
  B.load(stream);
}

void Brain::mutate()
{
  // TODO
}
