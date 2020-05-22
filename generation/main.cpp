#include <iostream>
#include "include/Brain.h"
#include <chrono>

using namespace std;
using namespace std::chrono;
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

    rowvec B = {0, 0};

    Brain brain(WL1, WL2, B);

    mat X(10000000, 9, fill::randu);
    cout << "Integration start" << endl;
    auto start = high_resolution_clock::now();
    mat U = brain.integrate(X);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Integration complete in " << duration.count() / 1000.0 << " seconds." << endl;

    return 0;
}
