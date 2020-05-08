#ifndef _64W_AI_H_
#define _64W_AI_H_

#include <cstring>
#include <cmath>

enum ActivationFunction {HEAVISIDE, SIGMOID, PASSTHROUGH};

class Perceptron
{
public:
  Perceptron(const int, double *, double, ActivationFunction);
  ~Perceptron();
  double Integrate(double *, const int);

private:
  double *w;
  double wlen;
  double b;
  ActivationFunction f;
  double dotproduct(double *, double *, const int);
};

#endif // _64W_AI_H_
