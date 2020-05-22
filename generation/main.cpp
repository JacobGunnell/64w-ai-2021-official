#include <iostream>
#include "include/Brain.h"

using namespace std;
using namespace arma;

int main()
{
    mat WL1 = { {1, 1, 1},
                {1, 1, 1},
                {1, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 1, 1},
                {0, 0, 1},
                {0, 0, 1},
                {0, 0, 1} };

    colvec WL2 = {1, 1, 1};

    rowvec B = {0, 0, 0};

    Brain brain(WL1, WL2, B);

    mat X(10000000, 9, fill::randu);
    mat U = brain.integrate(X);

    return 0;
}
