#include "utils.h"
#include <stdlib.h>

struct Particle
{
    struct Coord2D current_coord;
    struct Coord2D best_coord;

    Speed2D speed;

    int best_result;
};

int randMinMax(int a,int b)
{
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}

struct Coord2D genRandCoord2D(int min_coord, int max_coord)
{

}
