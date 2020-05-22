#ifndef MAT_H
#define MAT_H


#include <string>
#include <cstdint>
using namespace std;

class mat64
{
public:
    mat64(uint8_t, uint8_t);
    ~mat64();

    bool save(string);
    bool load(string);

    mat64 operator*(const mat64&);

private:
    uint8_t rows;
    uint8_t cols;
    double content[64][64]; // max 64x64 matrix
};

#endif // MAT_H
