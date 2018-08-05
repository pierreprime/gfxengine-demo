#include "enemyShoot.h"
#include "myDefines.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"

s_enemyShoot enemyShoot[MAX_ENEMY_SHOOT];

void es_init(){
    int i;

    for(i=0; i<MAX_ENEMY_SHOOT; i++){
        enemyShoot[i].type = INACTIVE_ENEMY_SHOOT;
        enemyShoot[i].spriteNumber = -1;
    }
}

int es_create(int x, int y){
    int i;

    for(i=0; i<MAX_ENEMY_SHOOT; i++){
        if(enemyShoot[i].type == INACTIVE_ENEMY_SHOOT){
            enemyShoot[i].spriteNumber = spr_reserveFreeSprite();
            if(enemyShoot[i].spriteNumber != -1){
                enemyShoot[i].type = ACTIVE_ENEMY_SHOOT;
                spr_changeSpriteImage(enemyShoot[i].spriteNumber, IB_SHOOT_ALIEN_F0);
                spr_moveSprite(enemyShoot[i].spriteNumber, x, y);
                spr_setSpriteHitbox(enemyShoot[i].spriteNumber, 0, 0, 54, 9);
                return i;
            }
        }
    }

    return -1;
}

void es_moveAll(){
    int i;

    for(i=0; i<MAX_ENEMY_SHOOT; i++){
        if(enemyShoot[i].type != INACTIVE_ENEMY_SHOOT){
            spr_moveSpriteRelative(enemyShoot[i].spriteNumber, 0, 6);
            if(spr_getSpriteY(enemyShoot[i].spriteNumber) > 480)
            {
                enemyShoot[i].type = INACTIVE_ENEMY_SHOOT;
                spr_releaseSprite(enemyShoot[i].spriteNumber);
            }
        }
    }
}

void es_destroy(int esno){
    if(enemyShoot[esno].type != INACTIVE_ENEMY_SHOOT)
    {
        enemyShoot[esno].type = INACTIVE_ENEMY_SHOOT;
        if(enemyShoot[esno].spriteNumber != -1){
            spr_releaseSprite(enemyShoot[esno].spriteNumber);
        }
    }
}

void es_destroyAll(void){
    int i;

    for(i=0; i<MAX_ENEMY_SHOOT; i++){
        es_destroy(i);
    }
}

int es_getType(int esno){
    return enemyShoot[esno].type;
}

int es_getSprno(int esno){
    return enemyShoot[esno].spriteNumber;
}

