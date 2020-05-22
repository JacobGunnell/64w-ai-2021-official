#ifndef BRAIN_H
#define BRAIN_H


#include "Brain-conf.h"

#include <string>
#include <fstream>
using namespace std;

#include "mat.h" // simplified (slow) matrix library that doesn't require fancy optimized kernels and 64-bit support, only allows matrices upto 64x64 (type: mat64)

#ifdef BRAIN_USE_ARMA

#include <armadillo> // optimized (fast) matrix library that requires all that stuff that doesn't run on v5
using namespace arma;

#else

typedef mat64 mat; // use mat64 exclusively on v5; for the generational program on pc use mat64 only for writing to file

#endif // BRAIN_USE_ARMA

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

    double integrate(mat);
    bool save(string);
    bool load(string);

private:
    mat WL1, WL2;
    mat B;

    mat f(mat x) { return x; } // Activation function
};

#endif // BRAIN_H
