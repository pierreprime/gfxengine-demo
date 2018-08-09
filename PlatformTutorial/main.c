#include <stdio.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "myDefines.h"

const int map1[300] = {
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 3, 4, 5, 2, 2, 3, 4, 5, 2, 2, 3, 4, 5, 2,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int ram_map[300];

int main(int argc, char *argv[])
{
    // this part does not change with gfxengine
    int i, x, y, tile_value;
    int image_nb;
    int sprnb_pointer;

    printf("\nTUTO PLATEFORME");

    initGfxEngine320();
    spr_initSpriteEngine();

    for(i=0; i<300; i++)
        ram_map[i] = map1[i];

    loadImageTra("cd/gfx/tileset1.png", IMAGE_TILES, 64, 64);
    loadImageTra("cd/gfx/spritesheet.png", IMAGE_SPRITE, 128, 128);
    //loadImageTra("cd/gfx/stone_background.png", 3, 512, 512);

    getImageBankTra(IB_POINTER, IMAGE_SPRITE, 0, 0, 16, 16);
    sprnb_pointer = spr_initFreeSprite(0,0,0,IB_POINTER);
    //

    image_nb = 1;
    // Commence à l'ImageBank 30 pour la tile 0 (non dessiné)
    for(y=0; y<64; y+=16)
    {
        for(x=0; x<64; x+=16)
        {
            getImageTile(image_nb, IMAGE_TILES, x, y, 16, 16);
            image_nb++;
        }
    }

    // 0 mapNb, 20 width in tiles, 15 width in tiles, 16 tile size px, ram_map
    sm_setScrollData(0, 20, 15, 16, ram_map);
    sm_setScrollView(0, 0.0f, 0.0f);

    while(1)
    {
        prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        // upside down and left to right tiles display
        //blitImageTra(3,0,0);
        sm_scrollDraw(0,0,0);
        spr_showAllSprites();

        termineEcritureVideoTra();
        termineEcritureVideoGlobale();

        checkController();
    }

    return 0;
}
