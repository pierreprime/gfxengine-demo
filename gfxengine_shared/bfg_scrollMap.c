#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_scrollMap.h"

s_scrollMap scrollMap[MAX_TILESCROLL];

void sm_setScrollData(int s,int mapL,int mapH,int tileLH,int *map)
{
    scrollMap[s].mapLargeur=mapL; // Nombre de tile en hauteur de la map
    scrollMap[s].mapHauteur=mapH; // Nombre de tile en largeur de la map
    scrollMap[s].tileLH = tileLH;     // Tile = carré --> Nb pixels
    scrollMap[s].tmap = map;       // Pointeur vers les données de la map
}

/* Affiche la map à l'écran à partir de la position x,y DE LA MAP */
/* Exemple : */
/* sm_setScrollView(0,100,100) --> Affichera la map à partir des tiles se trouvant en 100,100 pixels dans la map */
/* sm_scrollDraw(0,16,16); --> Affiche le scroll 0 à l'écran à partir du point haut/gauche 16,16 de l'écran */
/*                         --> Donne une bande noire en haut et à gauche */
void sm_setScrollView(int s,float x,float y)
{
    scrollMap[s].currentWorldMapX = x;
    scrollMap[s].currentWorldMapY = y;
}

float sm_getScrollViewX(int s)
{
    return scrollMap[s].currentWorldMapX;
}

float sm_getScrollViewY(int s)
{
    return scrollMap[s].currentWorldMapY;
}

// *mapTiles : Tableau en "rom" ou en ram... des tiles
/* Affiche le scroll à l'écran à partir de la position X,Y de l'écran */
void sm_scrollDraw(int s,int decalX,int decalY)
{
    int map_drawx = scrollMap[s].currentWorldMapX;
    int map_drawy = scrollMap[s].currentWorldMapY;
    int tileLH = scrollMap[s].tileLH;
    int maxH = scrollMap[s].mapHauteur;
    int maxL = scrollMap[s].mapLargeur;
    int i, j;
    int mapx, mapy;
    int map_xoff, map_yoff;
    int current_tile;

    int maxx = (getResX()/tileLH)+1;
    int maxy = (getResY()/tileLH)+1;

    mapx = map_drawx / tileLH;
    mapy = map_drawy / tileLH;

    map_xoff = map_drawx & (tileLH-1);
    map_yoff = map_drawy & (tileLH-1);

    for(i = 0; i < maxy; i++)
    {
        for(j = 0; j < maxx; j++)
        {
            if ( (j+mapx<maxL) && (i+mapy<maxH) && (j+mapx>=0) && (i+mapy>=0) )
            {
                current_tile = scrollMap[s].tmap[(j+mapx)+((i+mapy)*maxL)];
                //printf("\n %d %d : %d --> %d",(j+mapx),(i+mapy),(j+mapx)+((i+mapy)*maxL),current_tile) ;
                if (current_tile>0) blitImageTile(current_tile,decalX + (j * tileLH - map_xoff),decalY + (i * tileLH - map_yoff));
            }
        }
    }
}

int sm_getTileFromScrollMap(int s,int x,int y)
{
    int maxL = scrollMap[s].mapLargeur;
    int maxH = scrollMap[s].mapHauteur;

    if ((x>=maxL) || (y>=maxH)) return -1;

    return scrollMap[s].tmap[x+(y*maxL)];
}

int sm_getTileFromScrollWorld(int s,int x,int y)
{
    int newx,newy;
    int maxL = scrollMap[s].mapLargeur;
    int maxH = scrollMap[s].mapHauteur;

    newx = x/scrollMap[s].tileLH;
    newy = y/scrollMap[s].tileLH;

    if ((newx>=maxL) || (newy>=maxH)) return -1;

    return scrollMap[s].tmap[newx+(newy*maxL)];
}

int sm_convertXWorldInXScreen(int s,int xSourceValue)
{
    return xSourceValue - scrollMap[s].currentWorldMapX;
};

int sm_convertYWorldInYScreen(int s,int ySourceValue)
{
    return ySourceValue - scrollMap[s].currentWorldMapY;
}

int sm_getTileDefv1FromScrollMap(int s,int x,int y)
{
    int maxL = scrollMap[s].mapLargeur;
    int maxH = scrollMap[s].mapHauteur;

    if ((x>=maxL) || (y>=maxH)) return -1;

    return tm_getTileDefv1(scrollMap[s].tmap[x+(y*maxL)]);
}

int sm_getTileDefv1FromScrollWorld(int s,int x,int y)
{
    int newx,newy;
    int maxL = scrollMap[s].mapLargeur;
    int maxH = scrollMap[s].mapHauteur;

    newx = x/scrollMap[s].tileLH;
    newy = y/scrollMap[s].tileLH;

    if ((newx>=maxL) || (newy>=maxH)) return -1;

    return tm_getTileDefv1(scrollMap[s].tmap[newx+(newy*maxL)]);
}

int sm_checkHorizontalTileDefv1FromScrollWorld(int s,int x,int y,int largeur,int v1_search)
{
	int x_parcours;
	int x_max;
	int valeur;

    x_parcours = x;
	x_max = x + largeur;

    while (x_parcours<x_max)
	{
	    valeur = sm_getTileDefv1FromScrollWorld(s,x_parcours,y);
	    if (valeur==v1_search) return 1;
	    x_parcours += scrollMap[s].tileLH;
	}

    valeur = sm_getTileDefv1FromScrollWorld(s,x_max,y);
    if (valeur==v1_search) return 1;

	return 0;
}

int sm_checkVerticalTileDefv1FromScrollWorld(int s,int x,int y,int hauteur,int v1_search)
{
	int y_parcours;
	int y_max;
	int valeur;

    y_parcours = y;
	y_max = y + hauteur;

    while (y_parcours<y_max)
	{
	    valeur = sm_getTileDefv1FromScrollWorld(s,x,y_parcours);
	    if (valeur==v1_search) return 1;
	    y_parcours += scrollMap[s].tileLH;
	}

    valeur = sm_getTileDefv1FromScrollWorld(s,x,y_parcours);
    if (valeur==v1_search) return 1;

	return 0;
}
