#include "include/two-point-circle.h"

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MAX(A, B, C) (MAX(A, MAX(B, C)))


int twoPointCircleSolution(const Target *targets, int targetsNumber, float radius)
{
    int global_best_result = 0;
    struct Coord2D global_best_coord;

    struct Coord2D center[2];
    int hitTargets = 0;
    for (int i = 0; i < targetsNumber; i++)
    {
        for (int j = i + 1; j < targetsNumber; j++)
        {
            if (!findCircleCenter2D(targets[i], targets[j], radius, &center[0], &center[1]))
            {
                hitTargets = findTargetsInCircle(center[i], radius, targets, targetsNumber);
            
                if (hitTargets > global_best_result)
                {
                    global_best_result = hitTargets;
                    global_best_coord = center[i];
                }
            }
        }
    }

    return global_best_result;
}