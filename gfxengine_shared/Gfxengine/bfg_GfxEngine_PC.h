#ifndef GFXENGINE_PC_H_INCLUDED
#define GFXENGINE_PC_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdlib.h>
#define MAX_IMAGE_TRA 16
#define MAX_IMAGEBANK_TRA 5000
#define MAX_IMGTILE 4096
#define MAX_ALPHA	255

#define	IMAGE_TRA0	0
#define	IMAGE_TRA1	1
#define	IMAGE_TRA2	2
#define	IMAGE_TRA3	3
#define	IMAGE_TRA4	4
#define	IMAGE_TRA5	5
#define	IMAGE_TRA6	6
#define	IMAGE_TRA7	7
#define	IMAGE_TRA8	8
#define	IMAGE_TRA9	9
#define	IMAGE_TRA10	10
#define	IMAGE_TRA11	11
#define	IMAGE_TRA12	12
#define	IMAGE_TRA13	13
#define	IMAGE_TRA14	14
#define	IMAGE_TRA15	15

#define RES_320x240 0
#define RES_640x480 1

#define HZ_AUTO     0
#define HZ_FORCE_60 1

typedef struct si
{
    int chargee;	// L'image est elle chargée ?
    int hauteur;	// Hauteur
    int largeur; // Largeur
    SDL_Texture* surface;
} simage;

typedef struct ib
{
    int image_source;
    int chargee;
    int sx;
    int sy;
    int sh;
    int sl;
    float p1_x;
    float p1_y;
    float p2_x;
    float p2_y;
    float p3_x;
    float p3_y;
    float p4_x;
    float p4_y;
} sibank;

typedef struct it
{
    int image_source;
    int chargee;
    int sx;
    int sy;
    int sh;
    int sl;
    float p1_x;
    float p1_y;
    float p2_x;
    float p2_y;
    float p3_x;
    float p3_y;
    float p4_x;
    float p4_y;
} stiles;

typedef struct al
{
	int image_source;
	int chargee;
	int sx;
	int sy;
	int sh;
	int sl;
} salpha;

void destroyGfxEngine();
void initGfxEngine();
void initGfxEngine320();

void gfxe_init(int resolution,int hz);
void gfxe_changeHz(int hz);
int gfxe_returnHz(void);

int getResX(void);
int getResY(void);
void waitInMs(int ms);
void synchroStart();
void synchroEnd(int ms);
void prepareEcritureVideoGlobale();
void prepareEcritureVideoTra();
void termineEcritureVideoTra();
void termineEcritureVideoGlobale();
int loadImageTra(char *filename,int noImage,int hauteur,int largeur);

int loadMask(char *filename,int noImage);
int getPixelMask(int noImage,int x,int y);
void freeMask(int noImage);

int loadCompressMask(char *filename,int noImage);
void freeCompressMask(int noImage);
int getPixelCompressMask(int noImage,int x,int y);

void blitImageTra(int ino,int dx,int dy);
int getFreeImageBankTra();
void getImageBankTra(int ibno,int is,int sx,int sy,int sh,int sl);
void blitImageBankTra(int ibno,int dx,int dy);
void blitImageBankTraRot(int ibno,int dx,int dy,float myrot,float zx,float zy,int center);

void getImageTile(int ibno,int is,int sx,int sy,int sh,int sl);
void blitImageTile(int ibno,int dx,int dy);

void getImageAlpha(int ibno,int is,int sx,int sy,int sh,int sl);
void blitImageAlpha(int ibno,int dx,int dy);

void freeImageTra(int noImage);
void freeAllImageTra(void);
void freeAllImage(void);

int checkController();
int getKeyA(void);
int getKeyB(void);
int getKeyX(void);
int getKeyY(void);
int getKeyUp(void);
int getKeyDown(void);
int getKeyLeft(void);
int getKeyRight(void);
int getKeyStart(void);
int anyActionKeyPress(void);
int getNoDirection(void);

#endif // GFXENGINE_PC_H_INCLUDED
