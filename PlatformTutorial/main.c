#include <stdio.h>
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "myDefines.h"

const int map1[300] = {
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 3, 4, 5, 2, 2, 2, 1, 2, 2, 2, 2, 3, 4, 5, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

const int map1_collision[300] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
};



int main(int argc, char *argv[])
{
    // this part does not change with gfxengine
    int i, x, y, tile_value;
    int image_nb;
    int sprnb_pointer;
    int xSprite, ySprite, xTile, yTile;
    int tile_attribute;

    int ram_map[300];
int ram_map_collision[300];

    printf("\nTUTO PLATEFORME");

    initGfxEngine320();
    spr_initSpriteEngine();

    for(i=0; i<300; i++)
        ram_map[i] = map1[i];
    for(i=0; i<300; i++)
        ram_map_collision[i] = map1_collision[i];

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
            tm_setTileDef(image_nb, TILEATTR_NULL, TILEATTR_NULL, TILEATTR_NULL);
            image_nb++;
        }
    }

    tm_setTileDef(1, TILEATTR_PLATFORM, TILEATTR_NULL, TILEATTR_NULL);
    tm_setTileDef(6, TILEATTR_PLATFORM, TILEATTR_NULL, TILEATTR_NULL);

    // 0 mapNb, 20 width in tiles, 15 width in tiles, 16 tile size px, ram_map
    sm_setScrollData(0, 20, 15, 16, ram_map);
    sm_setScrollView(0, 0.0f, 0.0f);

    sm_setScrollData(SCROLL1, 20, 15, 16, ram_map_collision);
    sm_setScrollView(SCROLL1, 0.0f, 0.0f);

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

        // make cursor move
        if(getKeyUp())
            spr_moveSpriteRelative(sprnb_pointer, 0.0f, -1.0f);
        if(getKeyDown())
           spr_moveSpriteRelative(sprnb_pointer, 0.0f, 1.0f);
        if(getKeyLeft())
            spr_moveSpriteRelative(sprnb_pointer, -1.0f, 0.0f);
        if(getKeyRight())
            spr_moveSpriteRelative(sprnb_pointer, 1.0f, 0.0f);

        xSprite = (int)spr_getSpriteX(sprnb_pointer);
        ySprite = (int)spr_getSpriteY(sprnb_pointer);

        // coordinates of tile where we are
        xTile = xSprite / 16;
        yTile = ySprite / 16;

        // tile map array value formula
        //tile_value = ram_map[xTile + (yTile * 20)];
        // tile value gfx version
        // determines what is displayed tile
        tile_value = sm_getTileFromScrollMap(SCROLL1, xTile, yTile);
        tile_attribute = tm_getTileDefv1(tile_value);

        printf("\n Sprite x : %d, y : %d", xSprite, ySprite);
        printf("\n Tile x : %d, y : %d", xTile, yTile);
        printf("\n Tile value : %d", tile_value);
        printf("\n Tile attribute : %d", tile_attribute);
    }

    return 0;
}
