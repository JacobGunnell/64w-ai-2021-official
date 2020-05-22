#ifndef BRAIN_H
#define BRAIN_H


#include <string>
#include <fstream>
using namespace std;

#include <armadillo> // optimized (fast) matrix library
using namespace arma;

class Brain
{
public:
    Brain(int, int);
    Brain(mat, mat, mat);

    mat getWL1() const { return WL1; }
    void setWL1(mat weights) { WL1 = weights; }
    mat getWL2() const { return WL2; }
    void setWL2(mat weights) { WL2 = weights; }
    mat getB() const { return B; }
    void setB(mat bias) { B = bias; }

    mat integrate(mat);
    bool save(string);
    bool load(string);

private:
    mat WL1, WL2;
    mat B;

    mat f(mat x) { return x; } // Activation function
};

#endif // BRAIN_H
