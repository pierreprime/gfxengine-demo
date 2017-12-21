#include <stdio.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"

#define IMAGE_DECOR 0
#define IMAGE_SPRITE 1

#define IB_ALIEN_F0 0
#define IB_ALIEN_F1 1
#define IB_PLAYER_F0 2
#define IB_SHOOT_ALIEN_F0 3
#define IB_SHOOT_PLAYER_F0 4
#define IB_EXPLODE_F0 5
#define IB_EXPLODE_F1 6
#define IB_EXPLODE_F2 7
#define IB_EXPLODE_F3 8
#define IB_EXPLODE_F4 9
#define IB_EXPLODE_F5 10


int main(int argc, char *argv[])
{
    int player_sprite;

    initGfxEngine();
    spr_initSpriteEngine();

	loadImageTra("cd/spritesheet.png", IMAGE_SPRITE, 512, 512);
	loadImageTra("cd/fond_etoile.png", IMAGE_DECOR, 512, 512);

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

	// reserve sprite in memory
	player_sprite = spr_reserveFreeSprite();
	spr_initSprite(player_sprite, 100, 100, 0, IB_PLAYER_F0);

    while(1){
        checkController();

        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR, 0, 0);
        blitImageTra(IMAGE_DECOR, 512, 0);

        if(getKeyLeft() == 1)
            x--;
        if(getKeyRight() == 1)
            x++;
        if(getKeyUp() == 1)
            y--;
        if(getKeyDown() == 1)
            y++;



        termineEcritureVideoTra();
        termineEcritureVideoGlobale();
    }

   return 0;
}
