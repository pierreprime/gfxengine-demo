#ifndef PLAYERSHOOT_H
#define PLAYERSHOOT_H

#define PS_MAX 10

#define PS_INACTIF 0
#define PS_ACTIF 1

typedef struct{
    int type;
    int sprno;
} s_playerShoot;

void ps_init();
int ps_create(int x, int y);
void ps_destroy(int psno);
void ps_destroyAll(void);
void ps_moveAll();

#endif // PLAYERSHOOT_H
