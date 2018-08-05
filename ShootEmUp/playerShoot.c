#include "playerShoot.h"
#include "myDefines.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"

s_playerShoot ps[PS_MAX];

void ps_init(){
    int i;

    for(i=0; i<PS_MAX; i++){
        ps[i].type = PS_INACTIF;
        ps[i].sprno = -1;
    }
}

int ps_create(int x, int y){
    int i;

    for(i=0; i<PS_MAX; i++){
        if(ps[i].type == PS_INACTIF){
            ps[i].sprno = spr_reserveFreeSprite();
            if(ps[i].sprno != -1){
                ps[i].type = PS_ACTIF;
                spr_changeSpriteImage(ps[i].sprno, IB_SHOOT_PLAYER_F0);
                spr_moveSprite(ps[i].sprno, x, y);
                spr_setSpriteHitbox(ps[i].sprno, 0, 0, 54, 9);
                return i;
            }
        }
    }

    return -1;
}

void ps_moveAll(){
    int i;

    for(i=0; i<PS_MAX; i++){
        if(ps[i].type != PS_INACTIF){
            spr_moveSpriteRelative(ps[i].sprno, 0, -3);
            if(spr_getSpriteY(ps[i].sprno) < 0){
                ps_destroy(i);
            }
        }
    }
}

void ps_destroy(int psno){
    if(ps[psno].type != PS_INACTIF){
        ps[psno].type = PS_INACTIF;
        if(ps[psno].sprno != -1){
            spr_releaseSprite(ps[psno].sprno);
        }
    }
}

void ps_destroyAll(void){
    int i;

    for(i=0; i<PS_MAX; i++){
        ps_destroy(i);
    }
}

int ps_getType(int psno){
    return ps[psno].type;
}

int ps_getSprno(int psno){
    return ps[psno].sprno;
}
