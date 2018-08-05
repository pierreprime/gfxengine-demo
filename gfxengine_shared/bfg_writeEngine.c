#include <stdio.h>

#include "../gfxengine_shared/bfg_gfxEngine.h"

extern salpha imageAlpha[MAX_ALPHA];


void we_printString(int x,int y,char *chaine)
{
    int decal;
    unsigned char c;
    int offset;

    decal = 0;
    offset = 0;
    c = *(chaine+offset);

    while (c!='\0')
    {
        blitImageAlpha(c,x+decal,y);
        decal = decal + imageAlpha[c].sl;
        offset++;
        c = *(chaine+offset);
    }
}

void we_printChar(int x,int y,unsigned char c)
{
      blitImageAlpha(c,x,y);
}

void we_printInt(int x,int y,int valeur)
{
    int decal;
    unsigned char c;
    int offset;
    char chaine[20];

	sprintf(chaine, "%d", valeur);
    chaine[19]='\0';

    decal = 0;
    offset = 0;
    c = *(chaine+offset);

    while (c!='\0')
    {
        blitImageAlpha(c,x+decal,y);
        decal = decal + imageAlpha[c].sl;
        offset++;
        c = *(chaine+offset);
    }
}
