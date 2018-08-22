#include <stdio.h>
#include <stdlib.h>

#include "../gfxengine_shared/bfg_gfxEngine.h"

#define SPRITESHEET0 0

int main(int argc, char *argv[])
{
    int ball_sprno;
    float ball_x, ball_y;
    int angle = 80;

    ball_x = 320.0f;
    ball_y = 440.0f;

    initGfxEngine();
    printf("\nDebug window");

    loadImageTra("cd/ball.png", SPRITESHEET0, 32, 32);
    getImageBankTra(0, SPRITESHEET0, 0, 0, 32, 32);
    ball_sprno = spr_reserveFreeSprite();
    spr_changeSpriteImage(ball_sprno, 0);
    spr_moveSprite(ball_sprno, ball_x, ball_y);

    while(1){
        checkController();

        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        ball_x = ball_x + cos(angle * 3.14 / 180);
        ball_y = ball_y + (sin(angle * 3.14 / 180) * -1);
        spr_moveSprite(ball_sprno, ball_x, ball_y);

        spr_showAllSprites();
        termineEcritureVideoTra();
        termineEcritureVideoGlobale();
    }

    return 0;
}
