#ifndef ENEMY_H

#define INACTIVE_ENEMY 0
#define YELLOW_ENEMY 1
#define BLUE_ENEMY 2

#define MAX_ENEMY 10

typedef struct
{
    int type;
    int sprno;
    int pv;
    int direction;
} s_enemy;

#endif // ENEMY_H
