#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "../gfxengine_shared/bfg_gfxEngine.h"

#ifndef PC_VERSION
    #include <png/png.h>
    #include <kos.h>
#endif

#include <stdlib.h>
#include <stdio.h>

extern int resX;
extern int resY;
extern sibank imageBankTra[];
extern unsigned char *mask[MAX_IMAGE_TRA];

ssprite sprite[MAX_SPRITE];
smsprite msprite[MS_MAXMSPRITE];

int spr_isSpriteCollidePerfect(int sprite1,int sprite2)

{
	int rect1_x, rect1_y;
	int rect2_x, rect2_y;
	int i, j, k, l;

	int coorx_1 = sprite[sprite1].posx;
	int coory_1 = sprite[sprite1].posy;
	int coorx_2 = sprite[sprite2].posx;
	int coory_2 = sprite[sprite2].posy;
	int sprite1w = imageBankTra[sprite[sprite1].ibno].sl;
	int sprite1h = imageBankTra[sprite[sprite1].ibno].sh;
	int sprite2w = imageBankTra[sprite[sprite2].ibno].sl;
	int sprite2h = imageBankTra[sprite[sprite2].ibno].sh;
    int imageTraNo1 = imageBankTra[sprite[sprite1].ibno].image_source;
    int imageTraNo2 = imageBankTra[sprite[sprite2].ibno].image_source;

	if (sprite[sprite1].utilise==0) return 0;
	if (sprite[sprite2].utilise==0) return 0;

	/*Détection par bounding box
	Retourne 0 et sort de la fonction
	si les sprites ne possédent pas de zones superposées*/

	if(coorx_1 > coorx_2+imageBankTra[sprite[sprite2].ibno].sl) return 0;
	if(coorx_1+imageBankTra[sprite[sprite1].ibno].sl < coorx_2) return 0;
	if(coory_1 > coory_2+imageBankTra[sprite[sprite2].ibno].sh) return 0;
	if(coory_1+imageBankTra[sprite[sprite1].ibno].sh < coory_2) return 0;



	/*Le but des lignes suivantes est de définir un
	rectangle qui englobe la zone d'affichage
	commune aux deux sprites
	On traite les coordonnées x du rectangle*/
	if (coorx_1 < coorx_2)
	{
		rect1_x = coorx_2;
		if (coorx_1 + sprite1w >= coorx_2 + sprite2w)
			rect2_x = coorx_2 + sprite2w;
		else
			rect2_x = coorx_1 + sprite1w;
	}
	else
	{
		rect1_x = coorx_1;
		if (coorx_2 + sprite2w >= coorx_1 + sprite1w)
			rect2_x = coorx_1 + sprite1w;
		else
			rect2_x = coorx_2 + sprite2w;
	}

	/*On traite les coordonnées y du rectangle*/
	if (coory_1 < coory_2)
	{
		rect1_y = coory_2;
		if (coory_1 + sprite1h >= coory_2 + sprite2h)
			rect2_y = coory_2 + sprite2h;
		else
			rect2_y = coory_1 + sprite1h;
	}
	else
	{
		rect1_y = coory_1;
		if (coory_2 + sprite2h > coory_1 + sprite1h)
            rect2_y = coory_1 + sprite1h;
		else
			rect2_y = coory_2 + sprite2h;
	}


	/*Il ne reste plus qu'à tester pour chaque
	pixel du rectangle précèdemment défini si ses pixels
	sont transparents
	Un pixel non transparent signifie qu'un bout de sprite
	est present dans le rectangle
	et donc que les sprites sont en collision*/

	for (i = rect1_x - coorx_1, j = rect1_x - coorx_2;i < rect2_x - coorx_1; i++, j++)
	{
		for (k = rect1_y - coory_1, l = rect1_y - coory_2;k < rect2_y - coory_1; k++, l++)
		{
			if((getPixelMask(imageTraNo1, i+imageBankTra[sprite[sprite1].ibno].sx, k+imageBankTra[sprite[sprite1].ibno].sy) != 0) && (getPixelMask(imageTraNo2, j+imageBankTra[sprite[sprite2].ibno].sx, l+imageBankTra[sprite[sprite2].ibno].sy) != 0))
			{
				return 1;
			}
		}
	}

	return 0;

}

int spr_isSpriteCollidePerfectCompress(int sprite1,int sprite2)

{
	int rect1_x, rect1_y;
	int rect2_x, rect2_y;
	int i, j, k, l;

	int coorx_1 = sprite[sprite1].posx;
	int coory_1 = sprite[sprite1].posy;
	int coorx_2 = sprite[sprite2].posx;
	int coory_2 = sprite[sprite2].posy;
	int sprite1w = imageBankTra[sprite[sprite1].ibno].sl;
	int sprite1h = imageBankTra[sprite[sprite1].ibno].sh;
	int sprite2w = imageBankTra[sprite[sprite2].ibno].sl;
	int sprite2h = imageBankTra[sprite[sprite2].ibno].sh;
    int imageTraNo1 = imageBankTra[sprite[sprite1].ibno].image_source;
    int imageTraNo2 = imageBankTra[sprite[sprite2].ibno].image_source;

	if (sprite[sprite1].utilise==0) return 0;
	if (sprite[sprite2].utilise==0) return 0;

	/*Détection par bounding box
	Retourne 0 et sort de la fonction
	si les sprites ne possédent pas de zones superposées*/

	if(coorx_1 > coorx_2+imageBankTra[sprite[sprite2].ibno].sl) return 0;
	if(coorx_1+imageBankTra[sprite[sprite1].ibno].sl < coorx_2) return 0;
	if(coory_1 > coory_2+imageBankTra[sprite[sprite2].ibno].sh) return 0;
	if(coory_1+imageBankTra[sprite[sprite1].ibno].sh < coory_2) return 0;



	/*Le but des lignes suivantes est de définir un
	rectangle qui englobe la zone d'affichage
	commune aux deux sprites
	On traite les coordonnées x du rectangle*/
	if (coorx_1 < coorx_2)
	{
		rect1_x = coorx_2;
		if (coorx_1 + sprite1w >= coorx_2 + sprite2w)
			rect2_x = coorx_2 + sprite2w;
		else
			rect2_x = coorx_1 + sprite1w;
	}
	else
	{
		rect1_x = coorx_1;
		if (coorx_2 + sprite2w >= coorx_1 + sprite1w)
			rect2_x = coorx_1 + sprite1w;
		else
			rect2_x = coorx_2 + sprite2w;
	}

	/*On traite les coordonnées y du rectangle*/
	if (coory_1 < coory_2)
	{
		rect1_y = coory_2;
		if (coory_1 + sprite1h >= coory_2 + sprite2h)
			rect2_y = coory_2 + sprite2h;
		else
			rect2_y = coory_1 + sprite1h;
	}
	else
	{
		rect1_y = coory_1;
		if (coory_2 + sprite2h > coory_1 + sprite1h)
            rect2_y = coory_1 + sprite1h;
		else
			rect2_y = coory_2 + sprite2h;
	}


	/*Il ne reste plus qu'à tester pour chaque
	pixel du rectangle précèdemment défini si ses pixels
	sont transparents
	Un pixel non transparent signifie qu'un bout de sprite
	est present dans le rectangle
	et donc que les sprites sont en collision*/

	for (i = rect1_x - coorx_1, j = rect1_x - coorx_2;i < rect2_x - coorx_1; i++, j++)
	{
		for (k = rect1_y - coory_1, l = rect1_y - coory_2;k < rect2_y - coory_1; k++, l++)
		{
			if((getPixelCompressMask(imageTraNo1, i+imageBankTra[sprite[sprite1].ibno].sx, k+imageBankTra[sprite[sprite1].ibno].sy) != 0) && (getPixelCompressMask(imageTraNo2, j+imageBankTra[sprite[sprite2].ibno].sx, l+imageBankTra[sprite[sprite2].ibno].sy) != 0))
			{
				return 1;
			}
		}
	}

	return 0;

}

int spr_isSpriteCollideWithIBPerfectCompress(int sprite1,int x,int y,int ibno)
{
	int rect1_x, rect1_y;
	int rect2_x, rect2_y;
	int i, j, k, l;

	int coorx_1 = sprite[sprite1].posx;
	int coory_1 = sprite[sprite1].posy;
	int coorx_2 = x;
	int coory_2 = y;
	int sprite1w = imageBankTra[sprite[sprite1].ibno].sl;
	int sprite1h = imageBankTra[sprite[sprite1].ibno].sh;
	int sprite2w = imageBankTra[ibno].sl;
	int sprite2h = imageBankTra[ibno].sh;
    int imageTraNo1 = imageBankTra[sprite[sprite1].ibno].image_source;
    int imageTraNo2 = imageBankTra[ibno].image_source;

	if (sprite[sprite1].utilise==0) return 0;

	/*Détection par bounding box
	Retourne 0 et sort de la fonction
	si les sprites ne possédent pas de zones superposées*/

	if(coorx_1 > coorx_2+imageBankTra[ibno].sl) return 0;
	if(coorx_1+imageBankTra[sprite[sprite1].ibno].sl < coorx_2) return 0;
	if(coory_1 > coory_2+imageBankTra[ibno].sh) return 0;
	if(coory_1+imageBankTra[sprite[sprite1].ibno].sh < coory_2) return 0;



	/*Le but des lignes suivantes est de définir un
	rectangle qui englobe la zone d'affichage
	commune aux deux sprites
	On traite les coordonnées x du rectangle*/
	if (coorx_1 < coorx_2)
	{
		rect1_x = coorx_2;
		if (coorx_1 + sprite1w >= coorx_2 + sprite2w)
			rect2_x = coorx_2 + sprite2w;
		else
			rect2_x = coorx_1 + sprite1w;
	}
	else
	{
		rect1_x = coorx_1;
		if (coorx_2 + sprite2w >= coorx_1 + sprite1w)
			rect2_x = coorx_1 + sprite1w;
		else
			rect2_x = coorx_2 + sprite2w;
	}

	/*On traite les coordonnées y du rectangle*/
	if (coory_1 < coory_2)
	{
		rect1_y = coory_2;
		if (coory_1 + sprite1h >= coory_2 + sprite2h)
			rect2_y = coory_2 + sprite2h;
		else
			rect2_y = coory_1 + sprite1h;
	}
	else
	{
		rect1_y = coory_1;
		if (coory_2 + sprite2h > coory_1 + sprite1h)
            rect2_y = coory_1 + sprite1h;
		else
			rect2_y = coory_2 + sprite2h;
	}


	/*Il ne reste plus qu'à tester pour chaque
	pixel du rectangle précèdemment défini si ses pixels
	sont transparents
	Un pixel non transparent signifie qu'un bout de sprite
	est present dans le rectangle
	et donc que les sprites sont en collision*/

	for (i = rect1_x - coorx_1, j = rect1_x - coorx_2;i < rect2_x - coorx_1; i++, j++)
	{
		for (k = rect1_y - coory_1, l = rect1_y - coory_2;k < rect2_y - coory_1; k++, l++)
		{
			if((getPixelCompressMask(imageTraNo1, i+imageBankTra[sprite[sprite1].ibno].sx, k+imageBankTra[sprite[sprite1].ibno].sy) != 0) && (getPixelCompressMask(imageTraNo2, j+imageBankTra[ibno].sx, l+imageBankTra[ibno].sy) != 0))
			{
				return 1;
			}
		}
	}

	return 0;

}

int spr_count_used_sprites(void)
{
    int i,cpt;
    cpt = 0;
    for (i=0;i<MAX_SPRITE;i++)
    {
        if (sprite[i].utilise==1) cpt++;
    }

    return cpt;
}

void spr_initSpriteEngine()
{
    int i;
    for (i=0; i<MAX_SPRITE; i++)
    {
        sprite[i].utilise=0;
        sprite[i].fin_animation=0;
        sprite[i].finRotation=0;
        sprite[i].finTX=0;
        sprite[i].finTY=0;
        sprite[i].nbFrameR=0;
        sprite[i].nbFrameTX=0;
        sprite[i].nbFrameTY=0;
        sprite[i].rot = 0.0f;
        sprite[i].zx = 1.0f;
        sprite[i].zy = 1.0f;
        sprite[i].layer=0;
        sprite[i].rotcenter=0;
    }
}

void spr_initSprite(int n,float x,float y,float rot,int i)
{
    sprite[n].posx = x;
    sprite[n].posy = y;
    sprite[n].ibno = i;
    sprite[n].utilise = 1;
    sprite[n].current_animation = -1;
    sprite[n].intern1 = 0;
    sprite[n].current_animation_frame = -1;
    sprite[n].fin_animation=0;
    sprite[n].finRotation=0;
    sprite[n].finTX=0;
    sprite[n].finTY=0;
    sprite[n].nbFrameR=0;
    sprite[n].nbFrameTX=0;
    sprite[n].nbFrameTY=0;
    sprite[n].rot = rot;
    sprite[n].zx = 1.0f;
    sprite[n].zy = 1.0f;
    sprite[n].rotcenter=0;
}

int spr_reserveFreeSprite(void)
{
    int i;


    for (i=1; i<MAX_SPRITE; i++)
    {
        if (sprite[i].utilise==0)
        {
            sprite[i].utilise = 1;
            sprite[i].current_animation = -1;
            sprite[i].fin_animation=0;
            sprite[i].finRotation=0;
            sprite[i].nbFrameR=0;
            sprite[i].nbFrameTX=0;
            sprite[i].nbFrameTY=0;
            sprite[i].finTX=0;
            sprite[i].finTY=0;
            sprite[i].rot = 0.0f;
            sprite[i].zx = 1.0f;
            sprite[i].zy = 1.0f;
            sprite[i].rotcenter=0;
            return i;
        }
    }

    return -1;
}

int spr_reserveFreeSpriteFrom(int borne)
{
    int i;

    for (i=borne; i<MAX_SPRITE; i++)
    {
        if (sprite[i].utilise==0)
        {
            sprite[i].utilise = 1;
            sprite[i].current_animation = -1;
            sprite[i].fin_animation=0;
            sprite[i].finRotation=0;
            sprite[i].finTX=0;
            sprite[i].finTY=0;
            sprite[i].nbFrameR=0;
            sprite[i].nbFrameTX=0;
            sprite[i].nbFrameTY=0;
            sprite[i].rot = 0.0f;
            sprite[i].zx = 1.0f;
            sprite[i].zy = 1.0f;
            sprite[i].rotcenter=0;
            return i;
        }
    }

    return -1;
}

int spr_initFreeSprite(float x,float y,float r,int i)
{
    int j;


    for (j=1; j<MAX_SPRITE; j++)
    {
        if (sprite[j].utilise==0)
        {
            sprite[j].posx = x;
            sprite[j].posy = y;
            sprite[j].rot = r;
            sprite[j].ibno = i;
            sprite[j].utilise = 1;
            sprite[j].current_animation = -1;
            sprite[j].intern1 = 0;
            sprite[j].current_animation_frame = -1;
            sprite[j].fin_animation = 0;
            sprite[j].finRotation=0;
            sprite[j].finTX=0;
            sprite[j].finTY=0;
            sprite[j].nbFrameR=0;
            sprite[j].nbFrameTX=0;
            sprite[j].nbFrameTY=0;
            sprite[j].zx = 1.0f;
            sprite[j].zy = 1.0f;
            sprite[j].rotcenter=0;

            return j;
        }
    }

    printf("\n Plus de sprites de libre !!");
    return -1;
}

void spr_releaseSprite(int n)
{
    if ((n<0) || (n>=MAX_SPRITE)) return;
    sprite[n].utilise = 0;
    sprite[n].fin_animation=0;
    sprite[n].finRotation=0;
    sprite[n].finTX=0;
    sprite[n].finTY=0;
    sprite[n].nbFrameR=0;
    sprite[n].nbFrameTX=0;
    sprite[n].nbFrameTY=0;
    sprite[n].current_animation = -1;
}


void spr_releaseAllSprite()
{
    int i;
    for (i=0; i<MAX_SPRITE; i++)
    {
        sprite[i].utilise=0;
        sprite[i].fin_animation=0;
        sprite[i].finRotation=0;
        sprite[i].finTX=0;
        sprite[i].finTY=0;
        sprite[i].nbFrameR=0;
        sprite[i].nbFrameTX=0;
        sprite[i].nbFrameTY=0;
        sprite[i].current_animation = -1;
    }
}

/* Animation Classique */
void spr_animateSprite(int s,int a)
{
    if (s==-1) return;
    if (a==sprite[s].current_animation)
    {
        if ((sprite[s].animation_loop[a])==ANIM_LOOP) return;
        else if (sprite[s].fin_animation==0) return;
    }

    sprite[s].ibno=sprite[s].animation[a][0];
    sprite[s].current_animation = a;
    sprite[s].current_animation_frame = 0; // On se positionne … la frame0
    sprite[s].intern1 = 0;
    sprite[s].fin_animation=0;
}



void spr_changeSmoothSpriteRotAbsolute(int s,float nouvelAngle,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finRotation = 0;

    sprite[s].stepR = (nouvelAngle - sprite[s].rot)
                      / nbFrame;
    sprite[s].nbFrameR = nbFrame;
}

void spr_changeSmoothSpriteRotRelative(int s,float AngleStep,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finRotation = 0;

    sprite[s].stepR = AngleStep;
    sprite[s].nbFrameR = nbFrame;
}


void spr_changeSmoothSpriteTXAbsolute(int s,float nouvelPosX,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finTX = 0;

    sprite[s].stepTX = (nouvelPosX - sprite[s].posx)
                       / nbFrame;
    sprite[s].nbFrameTX = nbFrame;
}

void spr_changeSmoothSpriteTXRelative(int s,float StepX,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finTX = 0;

    sprite[s].stepTX = StepX;
    sprite[s].nbFrameTX = nbFrame;
}

void spr_changeSmoothSpriteTYAbsolute(int s,float nouvelPosY,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finTY = 0;

    sprite[s].stepTY = (nouvelPosY - sprite[s].posy)
                       / nbFrame;
    sprite[s].nbFrameTY = nbFrame;
}

void spr_changeSmoothSpriteTYRelative(int s,float StepY,int nbFrame)
{
    if (s==-1) return;

    sprite[s].finTY = 0;

    sprite[s].stepTY = StepY;
    sprite[s].nbFrameTY = nbFrame;
}

void spr_setSpriteAnimation2(int s,int a,int speed,int *v,int loop)
{
    int i;

    if (s==-1) return;
    sprite[s].animation_speed[a] = speed;
    sprite[s].animation_loop[a] = loop;

    for (i=0; i<MAX_ANIMATION_FRAME; i++)
    {
        sprite[s].animation[a][i] = v[i];
        if (v[i]<0) break;
    }
}

void spr_setSpriteAnimation(int s,int a,int speed,int f0,int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9,int f10,int f11,int f12,int f13,int f14,int f15,int f16,int f17,int f18,int f19,int loop)
{
    if (s==-1) return;
    sprite[s].animation_speed[a] = speed;
    sprite[s].animation_loop[a] = loop;
    sprite[s].animation[a][0] = f0;
    sprite[s].animation[a][1] = f1;
    sprite[s].animation[a][2] = f2;
    sprite[s].animation[a][3] = f3;
    sprite[s].animation[a][4] = f4;
    sprite[s].animation[a][5] = f5;
    sprite[s].animation[a][6] = f6;
    sprite[s].animation[a][7] = f7;
    sprite[s].animation[a][8] = f8;
    sprite[s].animation[a][9] = f9;
    sprite[s].animation[a][10] = f10;
    sprite[s].animation[a][11] = f11;
    sprite[s].animation[a][12] = f12;
    sprite[s].animation[a][13] = f13;
    sprite[s].animation[a][14] = f14;
    sprite[s].animation[a][15] = f15;
    sprite[s].animation[a][16] = f16;
    sprite[s].animation[a][17] = f17;
    sprite[s].animation[a][18] = f18;
    sprite[s].animation[a][19] = f19;
}


void spr_moveSprite(int n,float x,float y)
{
    if (n==-1) return;
    sprite[n].posx=x;
    sprite[n].posy=y;
}

void spr_moveSpriteRelative(int n,float x,float y)
{
    if (n==-1) return;
    sprite[n].posx+=x;
    sprite[n].posy+=y;
}

void spr_changeSpriteRotation(int n,float r,int center)
{
    if (n==-1) return;
    sprite[n].rot = r;
    sprite[n].rotcenter = center;
}

void spr_changeSpriteZoom(int n,float zx,float zy)
{
    if (n<0) return;
    sprite[n].zx = zx;
    sprite[n].zy = zy;
}

void spr_changeSpriteImage(int n,int i)
{
    if (i<0) return;
    sprite[n].ibno=i;
}

void spr_changeSpriteLayer(int n,int lno)
{
    if (n<0) return;
    sprite[n].layer=lno;
}

void intern_spr_animationClassique(int n)
{
    // Doit on avancer d'une frame ?
    if (sprite[n].intern1<=0)
    {
        // On est à la fin de l'animation
        if (sprite[n].animation[sprite[n].current_animation][sprite[n].current_animation_frame] == -1)
        {
            // Est-ce qu'on boucle ?
            // OUI
            if (sprite[n].animation_loop[sprite[n].current_animation]==ANIM_LOOP)
            {
                // On se repositionne à la 1ere frame
                sprite[n].current_animation_frame=0;
                sprite[n].fin_animation=1;
            }
            else // NON
            {
                // On se repositionne sur la dernière image
                sprite[n].current_animation_frame--;
                sprite[n].fin_animation=1;
            }
        }

        // Affecte la nouvelle image
        sprite[n].ibno = sprite[n].animation[sprite[n].current_animation][sprite[n].current_animation_frame];
        // Remet à zéro le timer d'animation
        sprite[n].intern1 = sprite[n].animation_speed[sprite[n].current_animation];
        // Avance dans l'image suivante pour le prochain tour quand le timer sera à 0
        sprite[n].current_animation_frame ++;
        // Est-ce que pour le prochain tour on à dépassé la 20 image ?
        if (sprite[n].current_animation_frame>19)
        {
            // On boucle ?
            if (sprite[n].animation_loop[sprite[n].current_animation]==ANIM_LOOP)
            {
                // On boucle
                sprite[n].current_animation_frame=0;
                sprite[n].fin_animation=1;
            }
            else
            {
                // On boucle pas, donc on reste sur la dernière image max
                sprite[n].current_animation_frame=19;
                sprite[n].fin_animation=1;
            }
        }
    }
    sprite[n].intern1--;

}


void spr_updateSprites(int n)
{
    if (n==-1) return;

    if (sprite[n].nbFrameR>0)
    {
        sprite[n].nbFrameR--;
        sprite[n].rot += sprite[n].stepR;
    }
    else sprite[n].finRotation = 1;

    if (sprite[n].nbFrameTX>0)
    {
        sprite[n].nbFrameTX--;
        sprite[n].posx += sprite[n].stepTX;
    }
    else sprite[n].finTX = 1;

    if (sprite[n].nbFrameTY>0)
    {
        sprite[n].nbFrameTY--;
        sprite[n].posy += sprite[n].stepTY;
    }
    else sprite[n].finTY = 1;

    // Le sprite est il utilisé ?
    if (sprite[n].utilise== 1)
    {
        // Est on sur un sprite animé ?
        if (sprite[n].current_animation!=-1)
        {
            intern_spr_animationClassique(n);
        }
        else
        {
            sprite[n].intern1 = 0;
        }
    }
}

void spr_showSprite(int n)
{
    if (n==-1) return;

    if (sprite[n].utilise== 1)
    {
        if (sprite[n].posy > resY) return;
        if (sprite[n].posx > resX) return;
        if ((sprite[n].posy + imageBankTra[sprite[n].ibno].sh)<0) return;
        if ((sprite[n].posx + imageBankTra[sprite[n].ibno].sl)<0) return;

        if ((sprite[n].rot==0.0f) && (sprite[n].zx==1.0f) && (sprite[n].zy==1.0f))
        {
            blitImageBankTra(sprite[n].ibno,sprite[n].posx, sprite[n].posy);
            //printf("\n%d %d %d",sprite[n].ibno,sprite[n].posx, sprite[n].posy);
        }
        else
        {
            blitImageBankTraRot(sprite[n].ibno,sprite[n].posx,sprite[n].posy,sprite[n].rot,sprite[n].zx,sprite[n].zy,sprite[n].rotcenter);
        }
    }
}


void spr_updateAllSprites()
{
    int i;
    for (i=0; i<MAX_SPRITE; i++)
        spr_updateSprites(i);
}



void spr_stopAnimateSprite(int s)
{
    sprite[s].current_animation = -1;
    sprite[s].current_animation_frame = -1;
    sprite[s].intern1 = sprite[s].animation_speed[sprite[s].current_animation];
}

void spr_showAllSprites()
{
    int i;
    for (i=0; i<MAX_SPRITE; i++)
    {
        if (sprite[i].utilise==1)
        {
            spr_showSprite(i);
        }
    }
}

void spr_showAllSpritesLayer(int layerno)
{
    int i;
    for (i=0; i<MAX_SPRITE; i++)
    {
        if ((sprite[i].utilise==1) && (sprite[i].layer==layerno))
        {
            spr_showSprite(i);
        }
    }
}

int intern_isSpriteCollide(int sprite1,int sprite2)
{
    int coorx_1 = sprite[sprite1].posx+sprite[sprite1].hitbox_x;
    int coory_1 = sprite[sprite1].posy+sprite[sprite1].hitbox_y;
    int coorx_2 = sprite[sprite2].posx+sprite[sprite2].hitbox_x;
    int coory_2 = sprite[sprite2].posy+sprite[sprite2].hitbox_y;

    int sprite1w = sprite[sprite1].hitbox_l;
    int sprite1h = sprite[sprite1].hitbox_h;
    int sprite2w = sprite[sprite2].hitbox_l;
    int sprite2h = sprite[sprite2].hitbox_h;

    /*Détection par bounding box
    Retourne 0 et sort de la fonction
    si les sprites ne possédent pas de zones superposées*/
    if(coorx_1 > coorx_2+sprite2w) return 0;
    if(coorx_1+sprite1w < coorx_2) return 0;
    if(coory_1 > coory_2+sprite2h) return 0;
    if(coory_1+sprite1h < coory_2) return 0;

    return 1;
}

int spr_isSpriteCollide(int sprite1,int sprite2)
{
    if (sprite[sprite1].utilise==0) return 0;
    if (sprite[sprite2].utilise==0) return 0;

    return intern_isSpriteCollide(sprite1,sprite2);
}

void spr_setSpriteHitbox(int sprno,int hbx,int hby,int hbh,int hbl)
{
    sprite[sprno].hitbox_x = hbx;
    sprite[sprno].hitbox_y = hby;
    sprite[sprno].hitbox_h = hbh;
    sprite[sprno].hitbox_l = hbl;

}

float spr_getSpriteZoomX(int n)
{
    if (n<0)
    {
        printf("\n Erreur code sprite !!");
        return 0;
    }
    return sprite[n].zx;
}

float spr_getSpriteZoomY(int n)
{
    if (n<0)
    {
        printf("\n Erreur code sprite !!");
        return 0;
    }
    return sprite[n].zy;
}

float spr_getSpriteRot(int n)
{
    return sprite[n].rot;
}

float spr_getSpriteX(int n)
{
    return sprite[n].posx;
}

float spr_getSpriteY(int n)
{
   return sprite[n].posy;
}

int spr_getFinAnimation(int sprno)
{
    return sprite[sprno].fin_animation;
}

int spr_getFinRotation(int sprno)
{
    return sprite[sprno].finRotation;
}

int spr_getFinTX(int sprno)
{
    return sprite[sprno].finTX;
}

int spr_getFinTY(int sprno)
{
    return sprite[sprno].finTY;
}

int spr_getCurrentAnimation(int sprno)
{
    return sprite[sprno].current_animation;
}

int spr_getCurrentAnimationFrame(int sprno)
{
    return sprite[sprno].current_animation_frame;
}

int spr_getHitBoxX(int sprno)
{
    return sprite[sprno].hitbox_x;
}
int spr_getHitBoxY(int sprno)
{
    return sprite[sprno].hitbox_y;
}
int spr_getHitBoxH(int sprno)
{
    return sprite[sprno].hitbox_h;
}
int spr_getHitBoxL(int sprno)
{
    return sprite[sprno].hitbox_l;
}

/**************************/
/* GESTION DE MEGA-SPRITE */
/**************************/

void ms_initMegaSpriteEngine(void)
{
    int i;

    for (i=0; i<MS_MAXPART; i++)
    {
        msprite[i].utilise=0;
    }
}

int ms_reserveFreeMegaSprite(int nbPart)
{
    int i,j;

    for (i=0; i<MS_MAXPART; i++)
    {
        if (msprite[i].utilise==0)
        {
            msprite[i].utilise = 1;
            msprite[i].nbpart = nbPart;
            msprite[i].offset = 0;
            msprite[i].cpt = 0;
            msprite[i].anim_onoff = 0;
            msprite[i].current_phase = 0;
            for (j=0; j<MS_MAXPART; j++) msprite[i].part[j].animate = 0;
            return i;
        }
    }


    return -1;
}

void ms_destroyMegaSprite(int msno)
{
    msprite[msno].utilise = 0;
}

void ms_setDataMoveAnimation(int msno,float *data,int loop)
{
    msprite[msno].dataMove_animation = data;
    msprite[msno].loop = loop;
}

void ms_setImagePart(int msno,int ipart,int ibno)
{
    if (msno<0) return;
    msprite[msno].part[ipart].ibno = ibno;
}
/* Format des datamoves : !! IMPORTANT DOIT RESPECTER LE NOMBRE DE PART !! */
/* Timer A */
/* PositionX,PositionY,Rotation Part 1 pour Timer A */
/* PositionX,PositionY,Rotation Part 2 pour Timer A */
/* [...] */
/* Timer B */
/* PositionX,PositionY,Rotation Part 1 pour Timer B */
/* PositionX,PositionY,Rotation Part 2 pour Timer B */
/* -1 */

void ms_updateMegaSprite(int msno)
{
    int i;
    float x,y,rot;
    if (msprite[msno].anim_onoff==0) return;
    if (msno<0) return;
    if ((msprite[msno].dataMove_animation[msprite[msno].offset]<0) && (msprite[msno].cpt==0))
    {
        if (msprite[msno].loop==ANIM_NOLOOP)
        {
            msprite[msno].fin_animation=1;
            return;
        }
        else
        {
            msprite[msno].offset=0;
        }
    }
    // Début du lecture du tableau !
    if (msprite[msno].offset==0)
    {
        msprite[msno].current_phase = 0;
        msprite[msno].fin_animation = 0;
        /* Affectation des images */
        for (i=0; i<msprite[msno].nbpart; i++)
        {
            /* On initialise les premières coordonnées relatives */
            msprite[msno].part[i].ibno = msprite[msno].dataMove_animation[msprite[msno].offset];
            msprite[msno].offset+=1;
        }

        msprite[msno].timer_precedent = msprite[msno].dataMove_animation[msprite[msno].offset];
        msprite[msno].timer_courant = msprite[msno].dataMove_animation[msprite[msno].offset];
        msprite[msno].offset++;
        /* On se positionne sur les data de placement */
        for (i=0; i<msprite[msno].nbpart; i++)
        {
            /* On initialise les premières coordonnées relatives */
            msprite[msno].part[i].x = msprite[msno].dataMove_animation[msprite[msno].offset];
            msprite[msno].part[i].y = msprite[msno].dataMove_animation[msprite[msno].offset+1];
            msprite[msno].part[i].rot = msprite[msno].dataMove_animation[msprite[msno].offset+2];
            msprite[msno].offset+=3;
        }
        msprite[msno].cpt=0; /* On considère ce 1er mouvement comme terminé car c'est une init */
    }

    /* On à terminé le précédent mouvement */
    if (msprite[msno].cpt==0)
    {
        msprite[msno].timer_precedent = msprite[msno].timer_courant;
        msprite[msno].timer_courant = msprite[msno].dataMove_animation[msprite[msno].offset];
        msprite[msno].cpt =  msprite[msno].timer_courant - msprite[msno].timer_precedent;
        msprite[msno].offset++;
        for (i=0; i<msprite[msno].nbpart; i++)
        {
            /* On récupère les coordonnées relatives qu'on doit atteindre */
            x = msprite[msno].dataMove_animation[msprite[msno].offset];
            y = msprite[msno].dataMove_animation[msprite[msno].offset+1];
            rot = msprite[msno].dataMove_animation[msprite[msno].offset+2];

            /* Calcul du step et du compteur suivant*/
            msprite[msno].cpt = msprite[msno].timer_courant - msprite[msno].timer_precedent;
            msprite[msno].part[i].step_x = (x - msprite[msno].part[i].x) / msprite[msno].cpt;
            msprite[msno].part[i].step_y = (y - msprite[msno].part[i].y) / msprite[msno].cpt;
            msprite[msno].part[i].step_rot = (rot - msprite[msno].part[i].rot) / msprite[msno].cpt;

            msprite[msno].offset+=3;
        }
        msprite[msno].current_phase++;
    }

    /* On effectur les mouvements */
    for (i=0; i<msprite[msno].nbpart; i++)
    {
        msprite[msno].part[i].x += msprite[msno].part[i].step_x;
        msprite[msno].part[i].y += msprite[msno].part[i].step_y;
        msprite[msno].part[i].rot += msprite[msno].part[i].step_rot;

        /* Gestion des animations classique de parties */
        if (msprite[msno].part[i].animate==1)
        {
            // Première frame
            if (msprite[msno].part[i].anim_offset==0)
            {
                msprite[msno].part[i].anim_cpt = msprite[msno].part[i].anim[msprite[msno].part[i].anim_offset];
                msprite[msno].part[i].ibno =  msprite[msno].part[i].anim[msprite[msno].part[i].anim_offset+1];
                msprite[msno].part[i].anim_offset+=2;
            }

            if (msprite[msno].part[i].anim_cpt>0) msprite[msno].part[i].anim_cpt--;

            if (msprite[msno].part[i].anim_cpt==0)
            {
                /* On passe à l'image suivante !*/
                msprite[msno].part[i].anim_cpt = msprite[msno].part[i].anim[msprite[msno].part[i].anim_offset];
                /* Dernière frame ? */
                if (msprite[msno].part[i].anim_cpt<0)
                {
                    if (msprite[msno].part[i].anim_loop==1)
                    {
                        msprite[msno].part[i].anim_offset=0;
                    }
                    else msprite[msno].part[i].anim_cpt=0;
                }
                else
                {
                    msprite[msno].part[i].anim_cpt = msprite[msno].part[i].anim[msprite[msno].part[i].anim_offset];
                    msprite[msno].part[i].ibno =  msprite[msno].part[i].anim[msprite[msno].part[i].anim_offset+1];
                    msprite[msno].part[i].anim_offset+=2;
                }
            }
        }
    }
    if (msprite[msno].cpt>0) msprite[msno].cpt--;
}

void ms_updateAllMegaSprite(void)
{
    int i;

    for (i=0; i<MS_MAXMSPRITE; i++)
    {
        if (msprite[i].utilise==1) ms_updateMegaSprite(i);
    }
}

void ms_showMegaSprite(int msno)
{
    int i;

    if (msno<0) return;

    for (i=0; i<msprite[msno].nbpart; i++)
    {

        blitImageBankTraRot(msprite[msno].part[i].ibno,
                            msprite[msno].posx + msprite[msno].part[i].x,
                            msprite[msno].posy + msprite[msno].part[i].y,
                            msprite[msno].part[i].rot,
                            1.0f,
                            1.0f,
                            0);
    }
}

void ms_showAllMegaSprite(void)
{
    int i;

    for (i=0; i<MS_MAXMSPRITE; i++)
    {
        if (msprite[i].utilise==1) ms_showMegaSprite(i);
    }
}

void ms_startAnimate(int msno)
{
    msprite[msno].anim_onoff = 1;
    msprite[msno].offset=0;
}


void ms_stopAnimate(int msno)
{
    msprite[msno].anim_onoff = 0;
}

void ms_setPosXPart(int msno,int pno,float x)
{
    msprite[msno].part[pno].x = x;
}

void ms_setPosYPart(int msno,int pno,float y)
{
    msprite[msno].part[pno].y = y;
}

void ms_setPosPart(int msno,int pno,float x,float y)
{
    msprite[msno].part[pno].x = x;
    msprite[msno].part[pno].y = y;
}

void ms_setRotPart(int msno,int pno,float r)
{
    msprite[msno].part[pno].rot = r;
}

void ms_setPosX(int msno,float x)
{
    msprite[msno].posx = x;
}

void ms_setPosY(int msno,float y)
{
    msprite[msno].posy = y;
}

float ms_getPosX(int msno)
{
    return  msprite[msno].posx;
}

float ms_getPosY(int msno)
{
    return  msprite[msno].posy;
}

int ms_getCurrentPhase(int msno)
{
    return msprite[msno].current_phase;
}

int ms_getFinAnimation(int msno)
{
    return msprite[msno].fin_animation;
}

void ms_setNbHitBox(int msno,int nb)
{
    msprite[msno].nbHitBox = nb;
}

void ms_setHitBox(int msprono,int hno,int vx,int vy,int vh,int vl)
{
    msprite[msprono].hb_x[hno]=vx;
    msprite[msprono].hb_y[hno]=vy;
    msprite[msprono].hb_h[hno]=vh;
    msprite[msprono].hb_l[hno]=vl;
}

int intern_ms_isCollision(int x1,int y1,int h1,int l1,int x2,int y2,int h2,int l2)
{
    int coorx_1 = x1;
    int coory_1 = y1;
    int coorx_2 = x2;
    int coory_2 = y2;

    int sprite1w = l1;
    int sprite1h = h1;
    int sprite2w = l2;
    int sprite2h = h2;

    /*Détection par bounding box
    Retourne 0 et sort de la fonction
    si les sprites ne possédent pas de zones superposées*/
    if(coorx_1 > coorx_2+sprite2w) return 0;
    if(coorx_1+sprite1w < coorx_2) return 0;
    if(coory_1 > coory_2+sprite2h) return 0;
    if(coory_1+sprite1h < coory_2) return 0;

    return 1;
}

int ms_isSpriteMegaSpriteCollide(int sprno,int msprno)
{
    int i;
    for (i=0; i<msprite[msprno].nbHitBox; i++)
    {
        if (
            intern_ms_isCollision(
                (int)spr_getSpriteX(sprno)+(int)spr_getHitBoxX(sprno),
                (int)spr_getSpriteY(sprno)+(int)spr_getHitBoxY(sprno),
                (int)spr_getHitBoxH(sprno),
                (int)spr_getHitBoxL(sprno),
                (int)msprite[msprno].posx + (int)msprite[msprno].hb_x[i],
                (int)msprite[msprno].posy + (int)msprite[msprno].hb_y[i],
                (int)msprite[msprno].hb_h[i],
                (int)msprite[msprno].hb_l[i])==1
        ) return 1;
    }
    return 0;
}

/* Data de l'animation : */
/* Image à afficher, combien de cycle */
/* Image suivante, nb de cycle */
/* -1 pour la fin */
void ms_setAnimationPart(int msno,int pno,int *data,int loop)
{
    msprite[msno].part[pno].anim = data;
    msprite[msno].part[pno].anim_loop = loop;
    msprite[msno].part[pno].anim_offset=0;
}

void ms_startAnimatePart(int msno,int pno)
{
    msprite[msno].part[pno].animate = 1;
    msprite[msno].part[pno].anim_offset=0;
}

void ms_stopAnimatePart(int msno,int pno)
{
    msprite[msno].part[pno].animate = 0;
    msprite[msno].part[pno].anim_offset=0;
}

int spr_getUtilise(int sprno)
{
   return sprite[sprno].utilise;
}

int spr_getCurrentImageBank(int sprno)
{
    return sprite[sprno].ibno;
}
