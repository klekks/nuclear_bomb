#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "include/utils.h"




int update_particle_score(struct Particle *particle, float radius, const Target *targets, int targetsNumber)
{
    int hitTargets = findTargetsInCircle(particle->current_coord, radius, targets, targetsNumber);
    if (hitTargets >= particle->best_result)
    {
        particle->best_result = hitTargets;
        particle->best_coord = particle->current_coord;
    }
}

int run_swarm(int cnt_particle, float inertia_rate, float attraction_rate, float memory_rate, int epochs, const Target *aims, int aims_number, float radius)
{
    struct Particle * particles = (struct Particle*) calloc(cnt_particle, sizeof(struct Particle));
    
    int global_best_result = 0;
    struct Coord2D global_best_coord;

    for (int i = 0; i < cnt_particle; i++)
    {
        particles[i].current_coord.x = particles[i].current_coord.x = rand() % 100;
        particles[i].current_coord.y = particles[i].current_coord.y = rand() % 100;
        particles[i].speed.x = (float)(rand() % 100) / (rand() % 10 + 1);
        particles[i].speed.y = (float)(rand() % 100) / (rand() % 10 + 1);

        update_particle_score(&particles[i], radius, aims, aims_number);

        if (particles[i].best_result > global_best_result)
        {
            global_best_result = particles[i].best_result;
            global_best_coord = particles[i].best_coord;
        }
    }

    while (epochs--)
    {
        for (int i = 0; i < cnt_particle; i++)
        {
            particles[i].current_coord.x += particles[i].speed.x;
            particles[i].current_coord.y += particles[i].speed.y;

            update_particle_score(&particles[i], radius, aims, aims_number);

            if (particles[i].best_result > global_best_result)
            {
                global_best_result = particles[i].best_result;
                global_best_coord = particles[i].best_coord;
            }
        }

        for (int i = 0; i < cnt_particle; i++)
        {
            particles[i].speed.x = particles[i].speed.x * inertia_rate + (particles[i].best_coord.x - particles[i].current_coord.x) * memory_rate + (global_best_coord.x - particles[i].current_coord.x) * attraction_rate;
            particles[i].speed.y = particles[i].speed.y * inertia_rate + (particles[i].best_coord.y - particles[i].current_coord.y) * memory_rate + (global_best_coord.y - particles[i].current_coord.y) * attraction_rate;
        }
    }

    return global_best_result;
}



#define N (100)
int main()
{
    srand(time(0));
   Target aims[N];
    for (int i = 0; i < N; i++)
    {
        aims[i].x = rand() % 100;
        aims[i].y = rand() % 100;
    }

    int res = run_swarm(200, 0.3, 0.4, 0.3, 200, aims, N, 10);

    printf("Result: %d\nTrue result: %d\n", res, true_ans(aims, N, 10));
}


