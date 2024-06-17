struct Coord2D
{
    float x, y;
};

typedef struct Coord2D Speed2D;
typedef struct Coord2D Target;


float distance2D(const struct Coord2D a, const struct Coord2D b);
int findCircleCenter2D(const struct Coord2D a, const struct Coord2D b, float radius, struct Coord2D *center1, struct Coord2D *center2);
int findAimsInCircle(const struct Coord2D center, float radius, const Target *aims, int targetsNumber);

