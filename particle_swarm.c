#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

struct Particle
{
    float coord_x, coord_y;
    float best_coord_x, best_coord_y;
    int best_result;

    float speed_x, speed_y;
};

struct Aim
{
    float x, y;
};

float distance_square(const struct Particle *p, const struct Aim *a)
{
    return (p->coord_x - a->x) * (p->coord_x - a->x) + (p->coord_y - a->y) * (p->coord_y - a->y);
}

int update_particle_score(struct Particle *particle, const struct Aim *aims, int aims_number, float radius)
{
    int selected_aims = 0;
    for (int i = 0; i < aims_number; i++)
    {
        if (distance_square(particle, &aims[i]) <= radius * radius) selected_aims++;
    }
    if (selected_aims >= particle->best_result)
    {
        particle->best_result = selected_aims;
        particle->best_coord_x = particle->coord_x;
        particle->best_coord_y = particle->coord_y;
    }
}

int run_swarm(int cnt_particle, float inertia_rate, float attraction_rate, float memory_rate, int epochs, const struct Aim *aims, int aims_number, float radius)
{
    struct Particle * particles = (struct Particle*) calloc(cnt_particle, sizeof(struct Particle));
    
    int max_aims = 0;
    float max_aims_x = -1, max_aims_y = -1;

    for (int i = 0; i < cnt_particle; i++)
    {
        particles[i].coord_x = particles[i].best_coord_x = rand() % 100;
        particles[i].coord_y = particles[i].best_coord_y = rand() % 100;
        particles[i].speed_x = (float)(rand() % 100) / (rand() % 10 + 1);
        particles[i].speed_y = (float)(rand() % 100) / (rand() % 10 + 1);

        update_particle_score(&particles[i], aims, aims_number, radius);

        if (particles[i].best_result > max_aims)
        {
            max_aims = particles[i].best_result;
            max_aims_x = particles[i].best_coord_x;
            max_aims_y = particles[i].best_coord_y;
        }
    }

    while (epochs--)
    {
        for (int i = 0; i < cnt_particle; i++)
        {
            particles[i].coord_x += particles[i].speed_x;
            particles[i].coord_y += particles[i].speed_y;

            update_particle_score(&particles[i], aims, aims_number, radius);

            if (particles[i].best_result > max_aims)
            {
                max_aims = particles[i].best_result;
                max_aims_x = particles[i].best_coord_x;
                max_aims_y = particles[i].best_coord_y;
            }
        }

        for (int i = 0; i < cnt_particle; i++)
        {
            particles[i].speed_x = particles[i].speed_x * inertia_rate + (particles[i].best_coord_x - particles[i].coord_x) * memory_rate + (max_aims_x - particles[i].coord_x) * attraction_rate;
            particles[i].speed_y = particles[i].speed_y * inertia_rate + (particles[i].best_coord_y - particles[i].coord_y) * memory_rate + (max_aims_y - particles[i].coord_y) * attraction_rate;
        }
    }

    return max_aims;
}

int true_ans(struct Aim *aims, int aims_cnt, float radius)
{
    struct Particle p;
    p.best_result = 0;
    for (int i = 0; i < aims_cnt; i++)
    {
        for (int j = i + 1; j < aims_cnt; j++)
        {
            float x1 = aims[i].x, x2 = aims[j].x, y1 = aims[i].y, y2 = aims[j].y;
            float d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
            float h = sqrt(radius * radius - (d/2) * (d/2));

            float x01 = x1 + (x2 - x1)/2 + h * (y2 - y1) / d;
            float y01 = y1 + (y2 - y1)/2 - h * (x2 - x1) / d;

            float x02 = x1 + (x2 - x1)/2 - h * (y2 - y1) / d;
            float y02 = y1 + (y2 - y1)/2 + h * (x2 - x1) / d;

            p.coord_x = x01;
            p.coord_y = y01;
            update_particle_score(&p, aims, aims_cnt, radius);

            p.coord_x = x02;
            p.coord_y = y02;
            update_particle_score(&p, aims, aims_cnt, radius);
        }
    }

    return p.best_result;
}

#define N (100)
int main()
{
    srand(time(0));
    struct Aim aims[N];
    for (int i = 0; i < N; i++)
    {
        aims[i].x = rand() % 100;
        aims[i].y = rand() % 100;
    }

    int res = run_swarm(200, 0.3, 0.4, 0.3, 200, aims, N, 10);

    printf("Result: %d\nTrue result: %d\n", res, true_ans(aims, N, 10));
}


