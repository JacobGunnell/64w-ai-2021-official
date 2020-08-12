#ifndef BRAIN_H
#define BRAIN_H

#include <string>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;

#include "armadillo"

class Brain;
Brain *_brain_dynamic_load(string);
Brain *_brain_random(int);

class Brain
{
public:
  virtual ~Brain() {}

  virtual arma::mat integrate(arma::mat) = 0;
  virtual bool save(string) = 0;
  virtual bool load(string) = 0;
  virtual void mutate() = 0;
  virtual Brain *clone() = 0;

  static Brain *breed(Brain *, Brain *);
  static Brain *dynamic_load(string file) { return _brain_dynamic_load(file); }
  static Brain *random(int inputSize) { return _brain_random(inputSize); }
};

#endif // BRAIN_H
