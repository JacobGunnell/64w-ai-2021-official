#ifndef BRAIN_H
#define BRAIN_H


#include <string>
#include <fstream>
using namespace std;

#include "armadillo" // optimized (fast) matrix library

class Brain
{
public:
  Brain() {} // create an empty (uninitialized) brain; to be used in conjunction with load()
  Brain(int, int); // create a random brain with specific dimensions
  Brain(arma::mat &, arma::mat &, arma::mat &); // create a brain from matrices
  Brain(Brain &, Brain &); // breed a brain from a mother and a father
  Brain(const Brain &); // copy constructor

  arma::mat getWL1() const { return WL1; }
  void setWL1(arma::mat &weights) { WL1 = weights; }
  arma::mat getWL2() const { return WL2; }
  void setWL2(arma::mat &weights) { WL2 = weights; }
  arma::mat getB() const { return B; }
  void setB(arma::mat &bias) { B = bias; }

  arma::mat integrate(arma::mat);
  bool save(string);
  bool load(string);

  void mutate();

private:
  arma::mat WL1, WL2;
  arma::mat B;

  arma::mat f(arma::mat x) { return x; } // Activation function
};

#endif // BRAIN_H
