#include <stdio.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "myDefines.h"
#include "player.h"
#include "playerShoot.h"

int main(int argc, char *argv[])
{
    int alien_sprite;

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

	// reserve sprite for alien
	alien_sprite = spr_reserveFreeSprite();
    spr_initSprite(alien_sprite, 200, 200, 0, IB_ALIEN_F0);

    playerInit();
    ps_init();

    while(1){
        playerControl();
        ps_moveAll();

        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(IMAGE_DECOR, 0, 0);
        blitImageTra(IMAGE_DECOR, 512, 0);

        spr_showAllSprites();

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();
    }

   return 0;
}
