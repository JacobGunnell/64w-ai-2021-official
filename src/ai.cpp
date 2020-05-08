#include "ai.h"

Perceptron::Perceptron(const int numInputs, double *weights, double bias, ActivationFunction function)
{
  w = new double[numInputs];
  memcpy(w, weights, numInputs);
  wlen = numInputs;
  b = bias;
  f = function;
}

Perceptron::~Perceptron()
{
  delete w;
  w = nullptr;
}

double Perceptron::Integrate(double *inputs, const int numInputs)
{
  if(numInputs != wlen)
    throw -1;
  double raw = dotproduct(inputs, w, wlen) + b;
  switch(f)
  {
  case HEAVISIDE:
    if(raw < 0)
      return 0;
    else
      return 1;
    break;
  case SIGMOID:
    return 1.0 / (1.0 + exp(-raw));
    break;
  case PASSTHROUGH:
    return raw;
    break;
  }
}

double Perceptron::dotproduct(double *a, double *b, const int len)
{
  double total = 0;
  for(int i = 0; i < len; i++)
    total += a[i]*b[i];
  return total;
}
