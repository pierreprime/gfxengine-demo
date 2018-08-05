#include "collision.h"
#include "enemy.h"
#include "playerShoot.h"
#include "animatedObject.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"

void col_checkCollisionShootAlien(void)
{
    int psno, ano;

    for(psno=0; psno<PS_MAX; psno++)
    {
        if(ps_getType(psno) != PS_INACTIF)
        {
            for(ano=0; ano<MAX_ENEMY; ano++)
            {
                if(en_getType(ano) != INACTIVE_ENEMY)
                {
                    if(spr_isSpriteCollide(ps_getSprno(psno), en_getSprno(ano)) == 1)
                    {
                        if(en_getPv(ano) > 0)
                        {
                            en_setPv(ano, en_getPv(ano)-1);
                            ao_create(ANIMATED_SMALL_EXPLOSION, spr_getSpriteX(ps_getSprno(psno)), spr_getSpriteY(ps_getSprno(psno)));
                            ps_destroy(psno);
                        }
                        else
                        {
                            ao_create(ANIMATED_BIG_EXPLOSION, spr_getSpriteX(en_getSprno(ano)), spr_getSpriteY(en_getSprno(ano)));
                            ps_destroy(psno);
                            en_destroy(ano);
                            playSound(1, 0);
                        }
                        break;
                    }
                }
            }
        }
    }
}
