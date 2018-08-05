#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "bfg_GfxEngine_PC.h"

simage imagesTra[MAX_IMAGE_TRA];
unsigned char *mask[MAX_IMAGE_TRA];
unsigned char *maskCompress[MAX_IMAGE_TRA];
sibank imageBankTra[MAX_IMAGEBANK_TRA];
stiles imageTile[MAX_IMGTILE];
salpha imageAlpha[MAX_ALPHA];


int fullscreen=0;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gBackBuffer = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Rect nativeSize;
SDL_Rect newWindowSize;
char resize;
float scaleRatioW=1.0f;
float scaleRatioH=1.0f;



int keyRight = 0;
int keyLeft = 0;
int keyUp = 0;
int keyDown = 0;
int keyQuit = 0;
int keyActionA = 0;
int keyActionB = 0;
int keyActionX = 0;
int keyActionY = 0;
int keyActionStart =0;
int ZPos = 0;																																		// Duranik

int resX;
int resY;

/* Taille de la fenêtre à afficher et resize ! */
int show_resX;
int show_resY;

int nx(int mx,int my,float c, float s,int i,int j)
{
    return ((int) ( (float) c * (i - mx) + s * (j - my) + mx ));
}

int ny(int mx,int my,float c, float s,int i,int j)
{
    return ((int) ( (float) -s * (i - mx) + c * (j - my) + my ));
}

// Uniquement sur PC
void destroyGfxEngine()
{
    SDL_DestroyWindow(gWindow);
}


void gfxe_init(int resolution,int hz)
{
    int i;

    for (i=0;i<MAX_IMAGE_TRA;i++) imagesTra[i].chargee=0;
    for (i=0;i<MAX_IMAGEBANK_TRA;i++) imageBankTra[i].chargee=0;
	for (i=0;i<MAX_IMGTILE;i++) imageTile[i].chargee=0;
	for (i=0;i<MAX_ALPHA;i++) imageAlpha[i].chargee=0;

    if (resolution==RES_640x480)
    {
        resX = 640;
        resY = 480;
        show_resX = 640;
        show_resY = 480;

    }
    else
    {
        resX = 320;
        resY = 240;
        show_resX = 320;
        show_resY = 240;
    }

    nativeSize.x = 0;
    nativeSize.y = 0;
    nativeSize.w = resX;
    nativeSize.h = resY;

    newWindowSize.x = 0;
    newWindowSize.y = 0;
    newWindowSize.w = show_resX;
    newWindowSize.h = show_resY;

    resize = 0;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {

        if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") < 0)
        {
            printf("\nFailed to set Render Scale Quality");
        }

        if (fullscreen==1) gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        else gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_FULLSCREEN*/);

        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED |  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE  );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 200, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }

            gBackBuffer = SDL_CreateTexture(gRenderer,
                                            SDL_GetWindowPixelFormat(gWindow),
                                            SDL_TEXTUREACCESS_TARGET,
                                            resX,
                                            resY);

            SDL_SetRenderTarget(gRenderer, gBackBuffer);
        }
    }
}

void gfxe_changeHz(int hz)
{

}

int gfxe_returnHz(void)
{
    return 0;
}

void initGfxEngine()
{
    int i;

    for (i=0;i<MAX_IMAGE_TRA;i++) imagesTra[i].chargee=0;
    for (i=0;i<MAX_IMAGEBANK_TRA;i++) imageBankTra[i].chargee=0;
	for (i=0;i<MAX_IMGTILE;i++) imageTile[i].chargee=0;
	for (i=0;i<MAX_ALPHA;i++) imageAlpha[i].chargee=0;

    resX = 640;
    resY = 480;

    show_resX=640;
    show_resY=480;

    nativeSize.x = 0;
    nativeSize.y = 0;
    nativeSize.w = resX;
    nativeSize.h = resY;

    newWindowSize.x = 0;
    newWindowSize.y = 0;
    newWindowSize.w = show_resX;
    newWindowSize.h = show_resY;

    resize = 0;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {

        if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") < 0)
        {
            printf("\nFailed to set Render Scale Quality");
        }

        if (fullscreen==1) gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        else gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_FULLSCREEN*/);

        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED |  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE  );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 200, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }

            gBackBuffer = SDL_CreateTexture(gRenderer,
                                            SDL_GetWindowPixelFormat(gWindow),
                                            SDL_TEXTUREACCESS_TARGET,
                                            resX,
                                            resY);

            SDL_SetRenderTarget(gRenderer, gBackBuffer);
        }
    }
}

void initGfxEngine320()
{
    int i;

    for (i=0;i<MAX_IMAGE_TRA;i++) imagesTra[i].chargee=0;
    for (i=0;i<MAX_IMAGEBANK_TRA;i++) imageBankTra[i].chargee=0;
	for (i=0;i<MAX_IMGTILE;i++) imageTile[i].chargee=0;
	for (i=0;i<MAX_ALPHA;i++) imageAlpha[i].chargee=0;

    resX = 320;
    resY = 240;

    show_resX=320;
    show_resY=240;

    nativeSize.x = 0;
    nativeSize.y = 0;
    nativeSize.w = resX;
    nativeSize.h = resY;

    newWindowSize.x = 0;
    newWindowSize.y = 0;
    newWindowSize.w = show_resX;
    newWindowSize.h = show_resY;

    resize = 0;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {

        if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") < 0)
        {
            printf("\nFailed to set Render Scale Quality");
        }

        if (fullscreen==1) gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        else gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, show_resX, show_resY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_FULLSCREEN*/);

        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED |  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE  );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 200, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }

            gBackBuffer = SDL_CreateTexture(gRenderer,
                                            SDL_GetWindowPixelFormat(gWindow),
                                            SDL_TEXTUREACCESS_TARGET,
                                            resX,
                                            resY);

            SDL_SetRenderTarget(gRenderer, gBackBuffer);
        }
    }
}

int getResX(void)
{
    return resX;
}

int getResY(void)
{
    return resY;
}

void prepareEcritureVideoGlobale()
{
}

void prepareEcritureVideoTra()
{
}

void termineEcritureVideoTra()
{
}

void Resize()
{
    int w, h;

    SDL_GetWindowSize(gWindow, &w, &h);

    scaleRatioW = w / nativeSize.w;
    scaleRatioH = h / nativeSize.h;

    newWindowSize.w = w;
    newWindowSize.h = h;

    //In order to do a resize, you must destroy the back buffer. Try without it, it doesn't work
    SDL_DestroyTexture(gBackBuffer);
    gBackBuffer = SDL_CreateTexture(gRenderer,
                                   SDL_GetWindowPixelFormat(gWindow),
                                   SDL_TEXTUREACCESS_TARGET, //Again, must be created using this
                                   nativeSize.w,
                                   nativeSize.h);

    SDL_Rect viewPort;
    SDL_RenderGetViewport(gRenderer, &viewPort);

    if(viewPort.w != newWindowSize.w || viewPort.h != newWindowSize.h)
    {
        //VERY IMPORTANT - Change the viewport over to the new size. It doesn't do this for you.
        SDL_RenderSetViewport(gRenderer, &newWindowSize);
    }
}

void termineEcritureVideoGlobale()
{
    //SDL_RenderCopy(gRenderer, gBackBuffer, &nativeSize, &newWindowSize); //Render the backBuffer onto the



    SDL_SetRenderTarget(gRenderer, NULL); //Set the target back to the window

   	if(resize==1) //If a resize is neccessary, do so.
    {
        printf("\n Debut resize ");
        Resize();
        resize = 0;
        printf("\n Fin resize ");
    }


    SDL_RenderCopy(gRenderer, gBackBuffer, &nativeSize, &newWindowSize);

    SDL_RenderPresent( gRenderer );
    SDL_RenderClear(gRenderer);

    SDL_SetRenderTarget(gRenderer, gBackBuffer); //Set the target back to the back buffer
    SDL_RenderClear(gRenderer); //Clear the back buffer

}

SDL_Surface* loadSurface( char *filename )
{
    //The final optimized image
    //  SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( filename );

    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
    }

    return loadedSurface;
}


SDL_Texture* loadTexture( char *filename )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = loadSurface(filename);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

int loadImageTra(char *filename,int noImage,int hauteur,int largeur)
{
	printf("\n Chargement image %d : %s - %dx%d",noImage,filename,hauteur,largeur);
    imagesTra[noImage].surface = loadTexture( filename );
    imagesTra[noImage].hauteur = hauteur;
    imagesTra[noImage].largeur = largeur;
    imagesTra[noImage].chargee = 1;

    //SDL_SetColorKey(imagesTra[noImage].surface, (SDL_RLEACCEL), SDL_MapRGB(imagesTra[noImage].surface->format,255,255,255));

    return 0;
}

/* Charge le masque d'une image (sert pour la collision précise des sprites) */
int loadMask(char *filename,int noImage)
{
    int size,hauteur,largeur;
    FILE *fichier;
    fichier = fopen(filename, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier mask");
        return -1;
    }

    hauteur = imagesTra[noImage].hauteur;
    largeur = imagesTra[noImage].largeur;

    size = (hauteur * largeur) + 1;
    mask[noImage] = malloc(size*sizeof(char));


    fread(mask[noImage],size,1,fichier);

    fclose(fichier);
    fichier = NULL;

    return 0;
}

void freeMask(int noImage)
{
    free(mask[noImage]);
}

int getPixelMask(int noImage,int x,int y)
{
    if (x<0) return 0;
    if (x>imagesTra[noImage].largeur) return 0;

    if (y<0) return 0;
    if (y>imagesTra[noImage].hauteur) return 0;

    return *(mask[noImage]+((y*imagesTra[noImage].largeur)+x));
}

/* Charge le masque compressé d'une image (sert pour la collision précise des sprites) */
int loadCompressMask(char *filename,int noImage)
{
    int size,hauteur,largeur;
    FILE *fichier;
    fichier = fopen(filename, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier mask");
        return -1;
    }

    hauteur = imagesTra[noImage].hauteur;
    largeur = imagesTra[noImage].largeur;

    size = (hauteur * (largeur/8)) + 1;
    maskCompress[noImage] = malloc(size*sizeof(char));


    fread(maskCompress[noImage],size,1,fichier);

    fclose(fichier);
    fichier = NULL;

    return 0;
}

int getPixelCompressMask(int noImage,int x,int y)
{
    int nocar;
    int octet;
    unsigned char bit;

    if (x<0) return 0;
    if (x>imagesTra[noImage].largeur) return 0;

    if (y<0) return 0;
    if (y>imagesTra[noImage].hauteur) return 0;


    nocar = (y*imagesTra[noImage].largeur)+x;
    octet = nocar>>3;
    bit =  nocar - (octet <<3);

    if (((*(maskCompress[noImage]+octet)) & (128>>bit))!=0) return 1;
    else return 0;
}

void freeCompressMask(int noImage)
{
    free(maskCompress[noImage]);
}

void blitImageTra(int ino,int dx,int dy)
{
    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = imagesTra[ino].largeur;
    dest.h = imagesTra[ino].hauteur;

    SDL_RenderCopy( gRenderer, imagesTra[ino].surface, NULL, &dest );

    //SDL_BlitSurface( imagesTra[ino].surface, NULL, gScreenSurface, &dest );
}

int getFreeImageBankTra()
{
    int i;

    for (i=0;i<MAX_IMAGEBANK_TRA;i++)
    {
        if (imageBankTra[i].chargee==0) return i;
    }

    return -1;
}

void getImageBankTra(int ibno,int is,int sx,int sy,int sh,int sl)
{
    imageBankTra[ibno].chargee = 1;
    imageBankTra[ibno].image_source = is;
    imageBankTra[ibno].sx = sx;
    imageBankTra[ibno].sy = sy;
    imageBankTra[ibno].sh = sh;
    imageBankTra[ibno].sl = sl;
}

void blitImageBankTra(int ibno,int dx,int dy)
{
    if ( (ibno<0) || (ibno>MAX_IMAGEBANK_TRA) )
    {
        printf("\n Depassement d'imageBank : %d",ibno);
        return;
    }

    SDL_Rect src;
    src.x = imageBankTra[ibno].sx;
    src.y = imageBankTra[ibno].sy;
    src.w = imageBankTra[ibno].sl;
    src.h = imageBankTra[ibno].sh;

    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = imageBankTra[ibno].sl;
    dest.h = imageBankTra[ibno].sh;



    SDL_RenderCopy( gRenderer,imagesTra[imageBankTra[ibno].image_source].surface, &src, &dest );
    //SDL_BlitSurface( imagesTra[imageBankTra[ibno].image_source].surface, &src, gScreenSurface, &dest );
}

void blitImageBankTraRot(int ibno,int dx,int dy,float myrot,float zx,float zy,int center)
{
    float dmyrot;
    SDL_Point p;

    SDL_Rect src;
    src.x = imageBankTra[ibno].sx;
    src.y = imageBankTra[ibno].sy;
    src.w = imageBankTra[ibno].sl;
    src.h = imageBankTra[ibno].sh;

    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = (imageBankTra[ibno].sl)*zx;
    dest.h = (imageBankTra[ibno].sh)*zy;

    dmyrot = myrot*-1;/* * 3.141592f / 180.0f;*/

    if (center==1)
    {
        //p.x=imageBankTra[ibno].sl/2;
        //p.y=imageBankTra[ibno].sh/2;

        SDL_RenderCopyEx( gRenderer, imagesTra[imageBankTra[ibno].image_source].surface, &src, &dest,dmyrot, NULL, SDL_FLIP_NONE );

    }
    else
    {
        p.x = 0;
        p.y = 0;

        SDL_RenderCopyEx( gRenderer, imagesTra[imageBankTra[ibno].image_source].surface, &src, &dest,dmyrot, &p, SDL_FLIP_NONE );

    }


}


void getImageTile(int ibno,int is,int sx,int sy,int sh,int sl)
{
    imageTile[ibno].chargee = 1;
    imageTile[ibno].image_source = is;
    imageTile[ibno].sx = sx;
    imageTile[ibno].sy = sy;
    imageTile[ibno].sh = sh;
    imageTile[ibno].sl = sl;
}

void getImageAlpha(int ibno,int is,int sx,int sy,int sh,int sl)
{
    imageAlpha[ibno].chargee = 1;
    imageAlpha[ibno].image_source = is;
    imageAlpha[ibno].sx = sx;
    imageAlpha[ibno].sy = sy;
    imageAlpha[ibno].sh = sh;
    imageAlpha[ibno].sl = sl;
}

void blitImageTile(int ibno,int dx,int dy)
{
    if ( (ibno<0) || (ibno>MAX_IMGTILE) )
    {
        printf("\n Depassement d'imageTile : %d",ibno);
        return;
    }

    SDL_Rect src;
    src.x = imageTile[ibno].sx;
    src.y = imageTile[ibno].sy;
    src.w = imageTile[ibno].sl;
    src.h = imageTile[ibno].sh;

    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = imageTile[ibno].sl;
    dest.h = imageTile[ibno].sh;
    //SDL_BlitScaled( imagesTra[ino].surface, NULL, screenSurface, &dest );

    SDL_RenderCopy( gRenderer,imagesTra[imageTile[ibno].image_source].surface, &src, &dest );
    //SDL_BlitSurface( imagesTra[imageTile[ibno].image_source].surface, &src, gScreenSurface, &dest );
}

void blitImageAlpha(int ibno,int dx,int dy)
{
    if ( (ibno<0) || (ibno>MAX_ALPHA) )
    {
        printf("\n Depassement d'imageTile : %d",ibno);
        return;
    }

    SDL_Rect src;
    src.x = imageAlpha[ibno].sx;
    src.y = imageAlpha[ibno].sy;
    src.w = imageAlpha[ibno].sl;
    src.h = imageAlpha[ibno].sh;

    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = imageAlpha[ibno].sl;
    dest.h = imageAlpha[ibno].sh;

    SDL_RenderCopy( gRenderer,imagesTra[imageAlpha[ibno].image_source].surface, &src, &dest );
}

void freeImageTra(int noImage)
{
    if (imagesTra[noImage].chargee==1)
    {
        SDL_DestroyTexture(imagesTra[noImage].surface);
        imagesTra[noImage].chargee=0;
    }
}

void freeAllImageTra(void)
{
    int i;
    for (i=0; i<MAX_IMAGE_TRA; i++)
    {
        freeImageTra(i);
    }
}

void freeAllImage(void)
{
    freeAllImageTra();
}

/*
int keyRight = 0;
int keyLeft = 0;
int keyUp = 0;
int keyDown = 0;
int keyQuit = 0;
int keyActionA = 0;
int keyActionB = 0;
int keyActionX = 0;
int keyActionY = 0;
int keyActionStart =0;
*/

int checkController()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                resize = 1;
            }
        }

        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            keyLeft = 1;
            break;
        case SDLK_RIGHT:
            keyRight = 1;
            break;
        case SDLK_UP:
            keyUp = 1;
            break;
        case SDLK_DOWN:
            keyDown = 1;
            break;
        case SDLK_c:
            keyActionA = 1;
            break;
        case SDLK_v:
            keyActionB = 1;
            break;
        case SDLK_b:
            keyActionX = 1;
            break;
        case SDLK_n:
            keyActionY = 1;
            break;
        case SDLK_p:
            keyActionStart = 1;
            break;
        }

        switch (event.type)
        {
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                keyLeft = 0;
                break;
            case SDLK_RIGHT:
                keyRight = 0;
                break;
            case SDLK_UP:
                keyUp = 0;
                break;
            case SDLK_DOWN:
                keyDown = 0;
                break;
            case SDLK_c:
                keyActionA = 0;
                break;
            case SDLK_v:
                keyActionB = 0;
                break;
            case SDLK_b:
                keyActionX = 0;
                break;
            case SDLK_n:
                keyActionY = 0;
                break;
            case SDLK_p:
                keyActionStart = 0;
                break;
            }
            break;

        }
    }

    return 0;
}

int getKeyA(void)
{
    return keyActionA;
}

int getKeyB(void)
{
    return keyActionB;
}

int getKeyX(void)
{
    return keyActionX;
}

int getKeyY(void)
{
    return keyActionY;
}

int getKeyUp(void)
{
    return keyUp;
}

int getKeyDown(void)
{
    return keyDown;
}

int getKeyLeft(void)
{
    return keyLeft;
}

int getKeyRight(void)
{
    return keyRight;
}

int getKeyStart(void)
{
    return keyActionStart;
}

int getNoDirection(void)
{
    if ((keyRight==0) && (keyUp==0) && (keyDown==0) && (keyLeft==0)) return 1;
    return 0;
}

int anyActionKeyPress(void)
{
    checkController();
    if (
        (keyActionA==1)
        || (keyActionB==1)
        || (keyActionX==1)
        || (keyActionY==1)
    ) return 1;

    return 0;
}

