#ifndef BRAIN_H
#define BRAIN_H

#include <string>
#include <fstream>
using namespace std;

#include "armadillo"

class Brain;
Brain *_dynamic_load(string);

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
  static Brain *dynamic_load(string file) { return _dynamic_load(file); }
};

#endif // BRAIN_H
