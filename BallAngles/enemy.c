#include "myDefines.h"
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "enemy.h"
#include "enemyShoot.h"

s_enemy enemy[MAX_ENEMY];

int yellow_enemy_animation[] = {IB_ALIEN_F0, IB_ALIEN_F1, -1};

void en_init(){
    int i;
    for(i=0; i<MAX_ENEMY; i++){
        enemy[i].type = INACTIVE_ENEMY;
        enemy[i].sprno = -1;
        enemy[i].pv = 0;
        enemy[i].direction = 0;
        enemy[i].warmup = 10;
    }
}

int en_create(int type, int x, int y, int pv, int direction){
    int i;

    for(i=0; i<MAX_ENEMY; i++)
    {
        if(enemy[i].type == INACTIVE_ENEMY)
        {
            enemy[i].sprno = spr_reserveFreeSprite();
            if(enemy[i].sprno != -1)
            {
                if(type == YELLOW_ENEMY)
                {
                    enemy[i].type = type;
                    enemy[i].direction = direction;
                    enemy[i].pv = pv;
                    enemy[i].warmup = rnd_random2(50, 150);
                    spr_setSpriteAnimation2(enemy[i].sprno, 0, 12, yellow_enemy_animation, ANIM_LOOP);
                    spr_animateSprite(enemy[i].sprno, 0);
                    spr_moveSprite(enemy[i].sprno, x, y);
                    spr_setSpriteHitbox(enemy[i].sprno, 26, 0, 68, 68);
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

void en_intern_move_yellow(int eno)
{
    spr_moveSpriteRelative(enemy[eno].sprno, enemy[eno].direction, 0);
    if(spr_getSpriteX(enemy[eno].sprno) < 0)
    {
        spr_moveSprite(enemy[eno].sprno, 0, spr_getSpriteY(enemy[eno].sprno));
        enemy[eno].direction *= -1;
    }
    else if(spr_getSpriteX(enemy[eno].sprno) > (640 - 124)){
        spr_moveSprite(enemy[eno].sprno, (640 - 124), spr_getSpriteY(enemy[eno].sprno));
        enemy[eno].direction *= -1;
    }

    if(enemy[eno].warmup > 0)
    {
        enemy[eno].warmup--;
    }
    else
    {
        es_create(spr_getSpriteX(enemy[eno].sprno)+62, spr_getSpriteY(enemy[eno].sprno)+50);
        enemy[eno].warmup = rnd_random2(50, 150);
    }
}

void en_intern_move_blue(int eno)
{

}

void en_moveAll(void){
    int i;
    for(i=0; i < MAX_ENEMY; i++)
    {
        if(enemy[i].type == YELLOW_ENEMY)
            en_intern_move_yellow(i);
        else if(enemy[i].type == BLUE_ENEMY)
            en_intern_move_blue(i);
    }

}

int en_getType(int ano){
    return enemy[ano].type;
}

int en_getSprno(int ano){
    return enemy[ano].sprno;
}

int en_getPv(int ano)
{
    return enemy[ano].pv;
}

void en_setPv(int ano, int pv)
{
    enemy[ano].pv = pv;
}

void en_destroy(int ano)
{
    spr_releaseSprite(enemy[ano].sprno);
    enemy[ano].type = INACTIVE_ENEMY;
}

int en_count()
{
    int i, cpt;
    cpt = 0;
    for(i=0; i<MAX_ENEMY; i++)
    {
        if(enemy[i].type != INACTIVE_ENEMY)
            cpt++;
    }

    return cpt;
}
