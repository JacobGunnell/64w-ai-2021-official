#ifndef SMP_H
#define SMP_H


#include <string>
#include <fstream>
using namespace std;

#include "Brain.h"
#include "armadillo"

class SMP : public Brain
{
public:
  SMP() {}
  SMP(int, int); // create a random brain with specific dimensions
  SMP(int inputSize) : SMP(inputSize, 3) {} // TODO: random number of hidden cells
  SMP(arma::mat &, arma::mat &, arma::mat &); // create a brain from matrices
  ~SMP() {}

  arma::mat getWL1() const { return WL1; } // TODO: input validation
  void setWL1(arma::mat &weights) { WL1 = weights; }
  arma::mat getWL2() const { return WL2; }
  void setWL2(arma::mat &weights) { WL2 = weights; }
  arma::mat getB() const { return B; }
  void setB(arma::mat &bias) { B = bias; }

  arma::mat integrate(arma::mat) override;
  bool save(string) override;
  bool load(string) override;
  void mutate() override;
  SMP *clone() override { return new SMP(*this); }

  static string getExtension() { return ".smp"; }

private:
  arma::mat WL1, WL2;
  arma::mat B;

  arma::mat f(arma::mat x) { return x; } // Activation function; TODO: make a lambda function in its place
};

#endif // SMP_H
