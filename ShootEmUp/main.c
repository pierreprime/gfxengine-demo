#include <stdio.h>
#include <time.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "myDefines.h"
#include "player.h"
#include "playerShoot.h"
#include "enemyShoot.h"
#include "enemy.h"
#include "collision.h"
#include "animatedObject.h"
#include "workflow.h"
#include "score.h"

int main(int argc, char *argv[])
{
    int x,y,c;

    w_set(WORKFLOW_INIT);

    while(1)
    {
        if(w_get() == WORKFLOW_INIT)
        {
            initGfxEngine();
            spr_initSpriteEngine();
            initSfxEngine();

            rnd_srand2(time(NULL));

            loadImageTra("cd/spritesheet.png", IMAGE_SPRITE, 512, 512);
            loadImageTra("cd/fond_etoile.png", IMAGE_DECOR, 512, 512);
            loadImageTra("cd/font16x16.png", IMAGE_FONT, 256, 256);

            // ASCII Table Image loop, c represent character number in table
            c = 0;
            for(y=0; y<256; y+=16)
            {
                for(x=0; x<256; x+=16)
                {
                    getImageAlpha(c, IMAGE_FONT, x, y, 16, 16);
                    c++;
                }
            }

            //getImageBankTra(IB_AW_INGAMELIEN_F0, IMAGE_SPRITE, 1, 1, 108, 124);
            getImageBankTra(IB_ALIEN_F0, IMAGE_SPRITE,1,1,108,124);
            getImageBankTra(IB_ALIEN_F1, IMAGE_SPRITE,126,1,108,124);
            getImageBankTra(IB_PLAYER_F0, IMAGE_SPRITE,251,1,70,91);
            getImageBankTra(IB_SHOOT_ALIEN_F0, IMAGE_SPRITE,1,110,57,13);
            getImageBankTra(IB_SHOOT_PLAYER_F0, IMAGE_SPRITE,15,110,54,9);
            getImageBankTra(IB_EXPLODE_F0, IMAGE_SPRITE,2,187,64,64);
            getImageBankTra(IB_EXPLODE_F1, IMAGE_SPRITE,70,187,64,64);
            getImageBankTra(IB_EXPLODE_F2, IMAGE_SPRITE,138,187,64,64);
            getImageBankTra(IB_EXPLODE_F3, IMAGE_SPRITE,206,187,64,64);
            getImageBankTra(IB_EXPLODE_F4, IMAGE_SPRITE,274,187,64,64);
            getImageBankTra(IB_EXPLODE_F5, IMAGE_SPRITE,342,187,64,64);

            loadSound("cd/piou.wav", 0);
            loadSound("cd/boom.wav", 1);

            w_set(WORKFLOW_TITLE_SCREEN);
        }
        else if(w_get() == WORKFLOW_TITLE_SCREEN)
        {
            title_screen();
            playerInit();
            ps_init();
            en_init();
            ao_init();
            es_init();

            en_create(YELLOW_ENEMY, 300, 100, 2, 3);
            en_create(YELLOW_ENEMY, 300, 50, 2, 4);
            en_create(YELLOW_ENEMY, 300, 150, 2, 5);

            playMusic("cd/music1.ogg", 0);
        }
        else if (w_get() == WORKFLOW_INGAME)
        {
            while(w_get() == WORKFLOW_INGAME)
            {
                playerControl();
                ps_moveAll();
                en_moveAll();
                ao_updateAll();
                es_moveAll();
                col_checkCollisionShootAlien();

                prepareEcritureVideoGlobale();
                prepareEcritureVideoTra();

                blitImageTra(IMAGE_DECOR, 0, 0);
                blitImageTra(IMAGE_DECOR, 512, 0);

                we_printString(0, 0, "SCORE :");
                we_printInt(0, 16, score_get());

                spr_updateAllSprites();
                spr_showAllSprites();

                termineEcritureVideoTra();
                termineEcritureVideoGlobale();

                // check if aliens left
                if(en_count() == 0)
                {
                    w_set(WORKFLOW_NEXTLEVEL);
                }
            }
        }
        else if(w_get() == WORKFLOW_NEXTLEVEL)
        {
            ao_destroyAll();
            es_destroyAll();
            ps_destroyAll();
            next_level();

            en_create(YELLOW_ENEMY, 300, 100, 2, 3);
            en_create(YELLOW_ENEMY, 300, 50, 2, 4);
            en_create(YELLOW_ENEMY, 300, 150, 2, 5);
        }


    }

   return 0;
}
