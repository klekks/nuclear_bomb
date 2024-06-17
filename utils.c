#include "include/utils.h"
#include <math.h>
#include <stdlib.h>

float distance2D(const struct Coord2D a, const struct Coord2D b)
{
    return sqrtf(powf(a.x  - b.x, 2) + powf(a.y - b.y, 2));
}

int findCircleCenter2D(const struct Coord2D a, const struct Coord2D b, float radius, struct Coord2D *center1, struct Coord2D *center2)
{
    float 
        d = distance2D(a, b),                             // the hord length 
        h = sqrt(radius * radius - (d/2) * (d/2));        // a half of distance between center of circles

    if (d > 0 && center1 && center2)
    {
        center1->x = a.x + (b.x - a.x) / 2 + h * (b.y - a.y) / d;
        center1->y = a.y + (b.y - a.y) / 2 - h * (b.x - a.x) / d;

        center2->x = a.x + (b.x - a.x) / 2 - h * (b.y - a.y) / d;
        center2->y = a.y + (b.y - a.y) / 2 + h * (b.x - a.x) / d;
    }

    return d <= 0;
}

int findAimsInCircle(const struct Coord2D center, float radius, const Target *targets, int targetsNumber)
{
    int hitTargets = 0;
    for (int i = 0; i < targetsNumber; i++)
    {
        if (distance2D(center, targets[i]) <= radius)
            hitTargets++;
    }
    return hitTargets;
}
