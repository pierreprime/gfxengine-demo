
#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_tilesmaps.h"

s_tiledef tiledef[MAX_TILE];
s_tilemap currentTilemap;


void tm_setCurrentTilemap(int h,int l,int thl,int *data,int *data2)
{
    currentTilemap.mapLargeur = l;
    currentTilemap.mapHauteur = h;
    currentTilemap.tileLH = thl;
    currentTilemap.tmap = data;
    currentTilemap.tmapData = data2;
}

int tm_getTileNumberFromCurrentMap(int x,int y)
{
    return currentTilemap.tmap[x+(y*currentTilemap.mapLargeur)];
}

int tm_getTileNumberFromCurrentMapDataLayer(int x,int y)
{
    return currentTilemap.tmapData[x+(y*currentTilemap.mapLargeur)];
}

int tm_getTileDefValue1FromCurrentMap(int x,int y)
{
    return tiledef[currentTilemap.tmap[x+(y*currentTilemap.mapLargeur)]].value1;
}

int tm_getTileDefValue1FromCurrentMapDataLayer(int x,int y)
{
    return tiledef[currentTilemap.tmapData[x+(y*currentTilemap.mapLargeur)]].value1;
}

void tm_setTileDef(int tileno,int v1,int v2,int v3)
{
    tiledef[tileno].value1 = v1;
    tiledef[tileno].value2 = v2;
    tiledef[tileno].value3 = v3;
}

int tm_getTileDefv1(int tileno)
{
    return tiledef[tileno].value1;
}

int tm_getTileDefv2(int tileno)
{
    return tiledef[tileno].value1;
}

int tm_getTileDefv3(int tileno)
{
    return tiledef[tileno].value1;
}


// Gère l'affichage de la tileMap sur l'écran
// Gère l'affichage de la tileMap sur l'écran
void tm_showCurrentTileMapImageBank(int scrPosX,int scrPosY,int decal)
{
    int x,y,t;

    for (x=0; x<currentTilemap.mapLargeur; x++)
    {
        for (y=0; y<currentTilemap.mapHauteur; y++)
        {
            t = tm_getTileNumberFromCurrentMap(x,y);
            if (t>0) blitImageBankTra(t+decal,scrPosX+(x*currentTilemap.tileLH),scrPosY+(y*currentTilemap.tileLH));
			//if (t>0) blitImageTile(t,scrPosX+(x*currentTilemap.tileLH),scrPosY+(y*currentTilemap.tileLH));

            // TODO : AFFICHE LA TILE t
        }
    }
}

/* Version corrigée !! Se base bien sur les ImagesTile et pas sur les ImagesBanks !! */
void tm_showCurrentTileMap(int scrPosX,int scrPosY)
{
    int x,y,t;

    for (x=0; x<currentTilemap.mapLargeur; x++)
    {
        for (y=0; y<currentTilemap.mapHauteur; y++)
        {
            t = tm_getTileNumberFromCurrentMap(x,y);
            //if (t>0) blitImageBankTra(t+decal,scrPosX+(x*currentTilemap.tileLH),scrPosY+(y*currentTilemap.tileLH));
			if (t>0) blitImageTile(t,scrPosX+(x*currentTilemap.tileLH),scrPosY+(y*currentTilemap.tileLH));

            // TODO : AFFICHE LA TILE t
        }
    }
}
void tm_changeTileInCurrentTilemap(int mapX,int mapY,int v)
{
    currentTilemap.tmap[mapX+(mapY*currentTilemap.mapLargeur)]=v;
}

void tm_changeTileInCurrentTilemapDataLayer(int mapX,int mapY,int v)
{
    currentTilemap.tmapData[mapX+(mapY*currentTilemap.mapLargeur)]=v;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	largeur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollHorizontalValue1DataLayer(int x,int y,int largeur,int tdefv1_search)
{
	int x_parcours;
	int x_max;
	int tile_v1;

	x_parcours = x;
	x_max = x + largeur;

	while (x_parcours<x_max)
	{
		tile_v1 = tm_getTileDefValue1FromCurrentMapDataLayer((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
		if (tile_v1==tdefv1_search) return 1;
		x_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	x_parcours = x + largeur;
	tile_v1 = tm_getTileDefValue1FromCurrentMapDataLayer((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
	if (tile_v1==tdefv1_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	hauteur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollVerticalValue1DataLayer(int x,int y,int hauteur,int tdefv1_search)
{
	int y_parcours;
	int y_max;
	int tile_v1;

	y_parcours = y;
	y_max = y + hauteur;

	while (y_parcours<y_max)
	{
		tile_v1 = tm_getTileDefValue1FromCurrentMapDataLayer((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
		if (tile_v1==tdefv1_search) return 1;
		y_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	y_parcours = y + hauteur;
	tile_v1 = tm_getTileDefValue1FromCurrentMapDataLayer((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
	if (tile_v1==tdefv1_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	largeur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollHorizontalValue1TileMap(int x,int y,int largeur,int tdefv1_search)
{
	int x_parcours;
	int x_max;
	int tile_v1;

	x_parcours = x;
	x_max = x + largeur;

	while (x_parcours<x_max)
	{
		tile_v1 = tm_getTileDefValue1FromCurrentMap((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
		if (tile_v1==tdefv1_search) return 1;
		x_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	x_parcours = x + largeur;
	tile_v1 = tm_getTileDefValue1FromCurrentMap((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
	if (tile_v1==tdefv1_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	hauteur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollVerticalValue1TileMap(int x,int y,int hauteur,int tdefv1_search)
{
	int y_parcours;
	int y_max;
	int tile_v1;

	y_parcours = y;
	y_max = y + hauteur;

	while (y_parcours<y_max)
	{
		tile_v1 = tm_getTileDefValue1FromCurrentMap((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
		if (tile_v1==tdefv1_search) return 1;
		y_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	y_parcours = y + hauteur;
	tile_v1 = tm_getTileDefValue1FromCurrentMap((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
	if (tile_v1==tdefv1_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	largeur : nombre de pixel de la bande a tester
	tn_search : true si on trouve sur la ligne horizontale un tile qui possède le même index.
*/
int tm_checkCollHorizontalTileNumberDataLayer(int x,int y,int largeur,int tn_search)
{
	int x_parcours;
	int x_max;
	int tile_number;

	x_parcours = x;
	x_max = x + largeur;

	while (x_parcours<x_max)
	{
		tile_number = tm_getTileNumberFromCurrentMapDataLayer((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
		if (tile_number==tn_search) return 1;
		x_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	x_parcours = x + largeur;
	tile_number = tm_getTileNumberFromCurrentMapDataLayer((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
	if (tile_number==tn_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	hauteur : nombre de pixel de la bande a tester
	tn_search : true si on trouve sur la ligne verticale un tile qui possède le même index.
*/
int tm_checkCollVerticalTileNumberDataLayer(int x,int y,int hauteur,int tn_search)
{
	int y_parcours;
	int y_max;
	int tile_number;

	y_parcours = y;
	y_max = y + hauteur;

	while (y_parcours<y_max)
	{
		tile_number = tm_getTileNumberFromCurrentMapDataLayer((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
		if (tile_number==tn_search) return 1;
		y_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	y_parcours = y + hauteur;
	tile_number = tm_getTileNumberFromCurrentMapDataLayer((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
	if (tile_number==tn_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	largeur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollHorizontalTileNumberTileMap(int x,int y,int largeur,int tn_search)
{
	int x_parcours;
	int x_max;
	int tile_number;

	x_parcours = x;
	x_max = x + largeur;

	while (x_parcours<x_max)
	{
		tile_number = tm_getTileNumberFromCurrentMap((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
		if (tile_number==tn_search) return 1;
		x_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	x_parcours = x + largeur;
	tile_number = tm_getTileNumberFromCurrentMap((x_parcours/currentTilemap.tileLH),(y/currentTilemap.tileLH));
	if (tile_number==tn_search) return 1;

	return 0;
}

/*
	ALPHA VERSION

	x : x pixel
	y : y pixel
	hauteur : nombre de pixel de la bande a tester
	tdefv1_search : true si on trouve sur la ligne horizontale un tile qui possède cette valeur dans value1.
*/
int tm_checkCollVerticalTileNumberTileMap(int x,int y,int hauteur,int tn_search)
{
	int y_parcours;
	int y_max;
	int tile_number;

	y_parcours = y;
	y_max = y + hauteur;

	while (y_parcours<y_max)
	{
		tile_number = tm_getTileNumberFromCurrentMap((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
		if (tile_number==tn_search) return 1;
		y_parcours+=currentTilemap.tileLH;
	}

	/* Test Final du dernier point */
	y_parcours = y + hauteur;
	tile_number = tm_getTileNumberFromCurrentMap((x/currentTilemap.tileLH),(y_parcours/currentTilemap.tileLH));
	if (tile_number==tn_search) return 1;

	return 0;
}

void tm_setTileNumberCurrentMap(int x,int y,int v)
{
    currentTilemap.tmap[x+(y*currentTilemap.mapLargeur)] = v;
}

void tm_setTileNumberCurrentMapDataLayer(int x,int y,int v)
{
    currentTilemap.tmapData[x+(y*currentTilemap.mapLargeur)] = v;
}
