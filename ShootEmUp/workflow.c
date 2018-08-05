#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "workflow.h"
#include "myDefines.h"
#include "enemyShoot.h"

int w_state = 0;

void w_set(int value)
{
    w_state = value;
}

int w_get()
{
    return w_state;
}

void title_screen()
{
    int cpt;
    cpt = 0;

    while(w_get() == WORKFLOW_TITLE_SCREEN)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR, 0, 0);
        blitImageTra(IMAGE_DECOR, 512, 0);

        we_printString(64, 128, "SHOOTEM UP GAME");

        if(cpt<11)
            we_printString(64, 196, "Press Start to Play");

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();
        if(getKeyStart() == 1)
            w_set(WORKFLOW_INGAME);

        cpt++;
        if(cpt == 20)
            cpt = 0;
    }
}

void next_level()
{
    int cpt = 0;

    while(w_get() == WORKFLOW_NEXTLEVEL)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR, 0, 0);
        blitImageTra(IMAGE_DECOR, 512, 0);

        if(cpt<11)
            we_printString(64, 196, "PRESS START for Next Level");

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();
        if(getKeyStart() == 1)
            w_set(WORKFLOW_INGAME);

        cpt++;
        if(cpt == 20)
            cpt = 0;
    }
}
