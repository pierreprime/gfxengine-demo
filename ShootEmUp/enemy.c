#include "enemy.h"

s_enemy enemy[MAX_ENEMY];

int yellow_enemy_animation[] = {IB_ALIEN_F0, IB_ALIEN_F1, -1};

void en_init(){
    int i;
    for(i=0; i<MAX_ENEMY; i++){
        enemy[i].type = INACTIVE_ENEMY;
        enemy[i].sprno = -1;
        enemy[i].pv = 0;
        enemy[i].direction = 0;
    }
}

void en_create(int type, int x, int y, int pv, int direction){
    int i;

    for(i=0; i<MAX_ENEMY; i++)
    {
        if(enemy[i].type == INACTIVE_ENEMY)
        {
            enemy[i].sprno = spr_reserveFreeSprite();
            if(enemy[i].sprno != -1)
            {
                if(enemy[i].type == YELLOW_ENEMY)
                {
                    enemy[i].type = type;
                    enemy[i].direction = direction;
                    enemy[i].pv = 10;
                    spr_setSpriteAnimation2(enemy[i].sprno, 0, 12, yellow_enemy_animation, ANIM_LOOP);
                    spr_animateSprite(enemy[i].sprno, 0);
                    spr_moveSprite(enemy[i].sprno, x, y);
                }
                else if(enemy[i].type == BLUE_ENEMY)
                {

                }
                return i;
            }
        }
    }

    return -1;
}
