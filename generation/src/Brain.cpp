#include "Brain.h"

Brain::Brain(int numInputs, int numHidden)
{
#ifdef BRAIN_USE_ARMA
    WL1 = mat(numInputs, numHidden, fill::zeros);
    WL2 = mat(numHidden, 1, fill::zeros);
    B = mat(1, numHidden, fill::zeros);
#else
    WL1 = mat(numInputs, numHidden);
    WL2 = mat(numHidden, 1);
    B = mat(1, numHidden);
#endif // BRAIN_USE_ARMA
}

Brain::Brain(mat wl1, mat wl2, mat b)
{
    WL1 = wl1;
    WL2 = wl2;
    B = b;

    try
    {
        mat temp = wl1 * wl2; // if this either of these multiplications fail (user has inputted bad data) it will throw
        temp = b * wl2;
    }
    catch(int)
    {
        throw "Bad matrix dimensions for a Brain object.";
    }
}

double Brain::integrate(mat X)
{
    mat U = (f(X*WL1 + B) * WL2);
    return U(0,0);
}
