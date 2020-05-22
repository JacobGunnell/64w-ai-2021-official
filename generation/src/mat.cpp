#include "mat.h"

mat64::mat64(uint8_t r, uint8_t c)
{
    if(r > 64 || c > 64 || r < 1 || c < 1)
        throw;
    rows = r;
    cols = c;
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 64; j++)
            content[i][j] = 0.0;
}
