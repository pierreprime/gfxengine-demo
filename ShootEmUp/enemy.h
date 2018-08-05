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

void en_init();
int en_create(int type, int x, int y, int pv, int direction);
void en_moveAll(void);
int en_getType(int ano);
int en_getSprno(int ano);
int en_getPv(int ano);
void en_setPv(int ano, int pv);
void en_destroy(int ano);

#endif // ENEMY_H
