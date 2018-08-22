#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "myDefines.h"
#include "animatedObject.h"

s_animated_object animated[MAX_ANIMATED];

int ao_explosion[] = {IB_EXPLODE_F0, IB_EXPLODE_F1, IB_EXPLODE_F2, IB_EXPLODE_F3, IB_EXPLODE_F4, IB_EXPLODE_F5, -1};

void ao_init(){
    int i;

    for(i=0; i<MAX_ANIMATED; i++)
    {
        animated[i].type = ANIMATED_INACTIVE;
        animated[i].sprno = -1;
    }
}

void ao_create(int type, int x, int y)
{
    int i;

    // parcours des AO
    for(i=0; i<MAX_ANIMATED; i++)
    {
        if(animated[i].type == ANIMATED_INACTIVE)
        {
            animated[i].type = type;

            // following animated object type
            if(type == ANIMATED_SMALL_EXPLOSION)
            {
                animated[i].sprno = spr_reserveFreeSprite();
                spr_moveSprite(animated[i].sprno, (float)x, (float)y);

                // set animation 0 of sprite
                spr_setSpriteAnimation2(animated[i].sprno, 0, 5, ao_explosion, ANIM_NOLOOP);
                // reduce zoom instead of calling other images
                spr_changeSpriteZoom(animated[i].sprno, 0.5f, 0.5f);
                spr_animateSprite(animated[i].sprno, 0);
            }
            else if (type == ANIMATED_BIG_EXPLOSION)
            {
                animated[i].sprno = spr_reserveFreeSprite();
                spr_moveSprite(animated[i].sprno, (float)x, (float)y);

                // set animation 0 of sprite
                spr_setSpriteAnimation2(animated[i].sprno, 0, 5, ao_explosion, ANIM_NOLOOP);
                // reduce zoom instead of calling other images
                spr_changeSpriteZoom(animated[i].sprno, 2.0f, 2.0f);
                spr_animateSprite(animated[i].sprno, 0);
            }

            break;
        }
    }
}

void ao_destroy(int aoNumber)
{
    animated[aoNumber].type = ANIMATED_INACTIVE;
    spr_releaseSprite(animated[aoNumber].sprno);
    animated[aoNumber].sprno = -1;
}

void ao_destroyAll()
{
    int i;

    for(i=0; i<MAX_ANIMATED; i++){
        ao_destroy(i);
    }
}

void ao_updateAll()
{
    int i;

    for(i=0; i<MAX_ANIMATED; i++)
    {
        // if ACTIVE found
        if(animated[i].type != ANIMATED_INACTIVE)
        {
            if(spr_getFinAnimation(animated[i].sprno))
            {
                ao_destroy(i);
            }
        }
    }
}
