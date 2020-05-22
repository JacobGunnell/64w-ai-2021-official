#include "Brain.h"

Brain::Brain(int numInputs, int numHidden)
{
    WL1 = mat(numInputs, numHidden, fill::zeros);
    WL2 = mat(numHidden, 1, fill::zeros);
    B = mat(1, numHidden, fill::zeros);
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
    catch(string)
    {
        throw "Bad matrix dimensions for a Brain object.";
    }
}

mat Brain::integrate(mat X)
{
    mat EB(X.n_rows, B.n_cols, fill::zeros);
    EB.each_row() += B;
    mat U = (f(X*WL1 + EB) * WL2);
    return U;
}
