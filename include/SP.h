#ifndef SP_H
#define SP_H


#include "Brain.h"

class SP : public Brain
{
public:
  SP() {}
  SP(int);
  SP(arma::colvec weights) : W(weights) {}
  ~SP() {}

  void setW(arma::colvec WNew) { W = WNew; }
  arma::colvec getW() const { return W; }

  arma::mat integrate(arma::mat) override;
  bool save(string) override;
  bool load(string) override;
  void mutate() override;
  SP *clone() override { return new SP(*this); }

  static string getExtension() { return ".sp"; }

private:
  arma::colvec W;
};

#endif // SP_H
