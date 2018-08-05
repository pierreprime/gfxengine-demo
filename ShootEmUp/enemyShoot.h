#ifndef ENEMY_SHOOT_H
#define ENEMY_SHOOT_H

#define MAX_ENEMY_SHOOT 20
#define INACTIVE_ENEMY_SHOOT 0
#define ACTIVE_ENEMY_SHOOT 1

typedef struct {
    int type;
    int spriteNumber;

} s_enemyShoot;

void es_init(void);
int es_create(int x, int y);
void es_moveAll();

int es_getType(int esNumber);
void es_destroy(int esNumber);
int es_getSpriteNumber(int esNumber);

#endif // ENEMY_SHOOT_H
