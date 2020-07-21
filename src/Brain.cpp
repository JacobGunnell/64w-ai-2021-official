#include "Brain.h"

Brain::Brain(int numInputs, int numHidden) // create a random brain with specific dimensions
{
  int R = numInputs / numHidden;
  WL1 = mat(numInputs, numHidden, fill::randu);
  for(int row = numHidden; row < numInputs; row++)
  {
    for(int col = 0; col < row/R; col++)
      WL1(row,col) = 0;
  }
  WL2 = mat(numHidden, 1, fill::randu);
  B = mat(1, numHidden, fill::randn);
}

Brain::Brain(mat wl1, mat wl2, mat b) // create a brain from matrices
{
  WL1 = wl1;
  WL2 = wl2;
  B = b;

  try
  {
    mat temp = wl1 * wl2; // if this either of these multiplications fail (user has inputted bad data) it will throw
    temp = b * wl2;
  }
  catch(logic_error e)
  {
    cout << "Constructor Error: Bad matrix dimensions for a Brain object!" << endl;
    terminate();
  }
}

Brain::Brain(Brain *mother, Brain *father) // breed a brain from a mother and a father
{
  // TODO
}

mat Brain::integrate(mat X)
{
  mat EB(X.n_rows, B.n_cols, fill::zeros);
  EB.each_row() += B;
  mat U = (f(X*WL1 + EB) * WL2);
  return U;
}

bool Brain::save(string filename)
{
  return
  WL1.save(filename + "-wl1.brn") &&
  WL2.save(filename + "-wl2.brn") &&
  B.save(filename + "-b.brn");
}

bool Brain::load(string filename)
{
  return
  WL1.load(filename + "-wl1.brn") &&
  WL2.load(filename + "-wl2.brn") &&
  B.load(filename + "-b.brn");
}

void Brain::mutate()
{
  // TODO
}
