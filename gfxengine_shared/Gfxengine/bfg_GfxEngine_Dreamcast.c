#include <stdlib.h>
#include <kos.h>
#include <png/png.h>
#include "bfg_GfxEngine_Dreamcast.h"

simage imagesTra[MAX_IMAGE_TRA];
unsigned char *mask[MAX_IMAGE_TRA];
unsigned char *maskCompress[MAX_IMAGE_TRA];
sibank imageBankTra[MAX_IMAGEBANK_TRA];
stiles imageTile[MAX_IMGTILE];
salpha imageAlpha[MAX_ALPHA];

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

int resX = 640;
int resY = 480;

/*
 	PVR_FILTER_NONE   0
 	No filtering (point sample)
 	PVR_FILTER_NEAREST   0
 	No filtering (point sample)
 	PVR_FILTER_BILINEAR   2
 	Bilinear interpolation.
 	PVR_FILTER_TRILINEAR1   4
 	Trilinear interpolation pass 1.
 	PVR_FILTER_TRILINEAR2   6
 	Trilinear interpolation pass 2.
*/
int traitement = 2;


/*
int nx(int mx,int my,float c, float s,int i,int j){
  return ((int) ( (float) c * (i - mx) + s * (j - my) + mx ));
}

int ny(int mx,int my,float c, float s,int i,int j){
  return ((int) ( (float) -s * (i - mx) + c * (j - my) + my ));
}
*/

/* Tentative pour régler le soucis de décalage rotation PC/DC */
float nx(float mx,float my,float c, float s,float i,float j)
{
    return ( ( c * (i - mx) + s * (j - my) + mx ));
}

float ny(float mx,float my,float c, float s,float i,float j)
{
    return ( (  -s * (i - mx) + c * (j - my) + my ));
}

void gfxe_init(int resolution,int hz)
{
    int i;

    for (i=0; i<MAX_IMAGE_TRA; i++) imagesTra[i].chargee=0;

    for (i=0; i<MAX_IMAGEBANK_TRA; i++) imageBankTra[i].chargee=0;

    for (i=0; i<MAX_IMGTILE; i++) imageTile[i].chargee=0;
    for (i=0; i<MAX_ALPHA; i++) imageAlpha[i].chargee=0;

    if (resolution==RES_320x240)
    {
        if(vid_check_cable()==CT_VGA)
        {
            vid_set_mode(DM_320x240_VGA, PM_RGB565);
        }
        else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
        {
            vid_set_mode(DM_320x240_PAL,PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        else
        {
            vid_set_mode(DM_320x240_NTSC, PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        resX=320;
        resY=240;
    }
    else
    {
        if(vid_check_cable()==CT_VGA)
        {
            vid_set_mode(DM_320x240_VGA, PM_RGB565);
        }
        else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
        {
            vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        else
        {
            vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        resX=320;
        resY=240;
    }
}

void gfxe_changeHz(int hz)
{
    if (resX==320)  // 320x240
    {
        if(vid_check_cable()==CT_VGA)   // VGA
        {
            vid_set_mode(DM_320x240_VGA, PM_RGB565);
        }
        else if(flashrom_get_region()==FLASHROM_REGION_EUROPE) // EUROPE
        {
            if (hz==HZ_AUTO)
            {
                vid_set_mode(DM_320x240_PAL,PM_RGB565);
                vid_border_color(0,0,0);
                pvr_init_defaults();
                PVR_SET(PVR_SCALER_CFG, 0x400);
            }
            else
            {
                vid_set_mode(DM_320x240_NTSC, PM_RGB565);
                vid_border_color(0,0,0);
                pvr_init_defaults();
                PVR_SET(PVR_SCALER_CFG, 0x400);
            }
        }
        else // US
        {
            vid_set_mode(DM_320x240_NTSC, PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        resX=320;
        resY=240;
    }
    else    // 640x480
    {
        // VGA
        if(vid_check_cable()==CT_VGA)
        {
            vid_set_mode(DM_320x240_VGA, PM_RGB565);
        } // EUROPE
        else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
        {
            if (hz==HZ_AUTO)
            {
                vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
                vid_border_color(0,0,0);
                pvr_init_defaults();
                PVR_SET(PVR_SCALER_CFG, 0x400);
            }
            else
            {
                vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
                vid_border_color(0,0,0);
                pvr_init_defaults();
                PVR_SET(PVR_SCALER_CFG, 0x400);
            }
        }
        else // US
        {
            vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
            vid_border_color(0,0,0);
            pvr_init_defaults();
            PVR_SET(PVR_SCALER_CFG, 0x400);
        }
        resX=320;
        resY=240;
    }
}

int gfxe_returnHz(void)
{
        if(vid_check_cable()==CT_VGA)
        {
            return 0;
        }
        else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
        {
            return 50;
        }
        else
        {
            return 60;
        }

        return -1;
}

void initGfxEngine320()
{
    int i;

    for (i=0; i<MAX_IMAGE_TRA; i++) imagesTra[i].chargee=0;

    for (i=0; i<MAX_IMAGEBANK_TRA; i++) imageBankTra[i].chargee=0;

    for (i=0; i<MAX_IMGTILE; i++) imageTile[i].chargee=0;
    for (i=0; i<MAX_ALPHA; i++) imageAlpha[i].chargee=0;

//	vid_set_mode(DM_320x240,PM_RGB565);


    if(vid_check_cable()==CT_VGA)
    {
        vid_set_mode(DM_320x240_VGA, PM_RGB565);
    }
    else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
    {
        vid_set_mode(DM_320x240_PAL,PM_RGB565);
        vid_border_color(0,0,0);
        pvr_init_defaults();
        PVR_SET(PVR_SCALER_CFG, 0x400);
    }
    else
    {
        vid_set_mode(DM_320x240_NTSC, PM_RGB565);
        vid_border_color(0,0,0);
        pvr_init_defaults();
        PVR_SET(PVR_SCALER_CFG, 0x400);
    }


    resX=320;
    resY=240;
}

void initGfxEngine()
{
    int i;

    for (i=0; i<MAX_IMAGE_TRA; i++) imagesTra[i].chargee=0;

    for (i=0; i<MAX_IMAGEBANK_TRA; i++) imageBankTra[i].chargee=0;

    for (i=0; i<MAX_IMGTILE; i++) imageTile[i].chargee=0;
    for (i=0; i<MAX_ALPHA; i++) imageAlpha[i].chargee=0;

    vid_set_mode(DM_640x480,PM_RGB565);
    vid_border_color(0,0,0);
    pvr_init_defaults();
    resX=640;
    resY=480;

    /*
    DM_INVALID
    Invalid display mode.

    DM_320x240_VGA
    320x240 VGA 60Hz

    DM_320x240_NTSC
    320x240 NTSC 60Hz

    DM_640x480_VGA
    640x480 VGA 60Hz

    DM_640x480_NTSC_IL
    640x480 NTSC Interlaced 60Hz

    DM_800x608_VGA
    800x608 VGA 60Hz

    DM_640x480_PAL_IL
    640x480 PAL Interlaced 50Hz

    DM_256x256_PAL_IL
    256x256 PAL Interlaced 50Hz

    DM_768x480_NTSC_IL
    768x480 NTSC Interlaced 60Hz

    DM_768x576_PAL_IL
    768x576 PAL Interlaced 50Hz

    DM_768x480_PAL_IL
    768x480 PAL Interlaced 50Hz

    DM_320x240_PAL
    320x240 PAL 50Hz
    // */

}

int getResX(void)
{
    return resX;
}

int getResY(void)
{
    return resY;
}

int loadImageTra(char *filename,int noImage,int hauteur,int largeur)
{
    imagesTra[noImage].surface = pvr_mem_malloc(hauteur*largeur*2);
    png_to_texture(filename, imagesTra[noImage].surface, PNG_FULL_ALPHA);
    imagesTra[noImage].hauteur = hauteur;
    imagesTra[noImage].largeur = largeur;
    imagesTra[noImage].chargee = 1;

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

int getPixelMask(int noImage,int x,int y)
{
    if (x<0) return 0;
    if (x>imagesTra[noImage].largeur) return 0;

    if (y<0) return 0;
    if (y>imagesTra[noImage].hauteur) return 0;

    return *(mask[noImage]+((y*imagesTra[noImage].largeur)+x));
}

void freeMask(int noImage)
{
    free(maskCompress[noImage]);
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


void getImageBankTra(int ibno,int is,int sx,int sy,int sh,int sl)
{
    float img_sx;
    float img_sy;
    float img_sh;
    float img_sl;
    float img_h;
    float img_l;
    imageBankTra[ibno].chargee = 1;
    imageBankTra[ibno].image_source = is;
    imageBankTra[ibno].sx = sx;
    imageBankTra[ibno].sy = sy;
    imageBankTra[ibno].sh = sh;
    imageBankTra[ibno].sl = sl;

    img_sx = imageBankTra[ibno].sx;
    img_sy = imageBankTra[ibno].sy;
    img_sh = imageBankTra[ibno].sh;
    img_sl = imageBankTra[ibno].sl;
    img_h = imagesTra[imageBankTra[ibno].image_source].hauteur;
    img_l = imagesTra[imageBankTra[ibno].image_source].largeur;

    // point1 ........... point2
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    // point 3            point4

    imageBankTra[ibno].p1_x = (1.0f/img_l)*img_sx;
    imageBankTra[ibno].p1_y = (1.0f/img_h)*img_sy;

    imageBankTra[ibno].p2_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageBankTra[ibno].p2_y = (1.0f/img_h)*img_sy;

    imageBankTra[ibno].p3_x = (1.0f/img_l)*img_sx;
    imageBankTra[ibno].p3_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);

    imageBankTra[ibno].p4_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageBankTra[ibno].p4_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);
}

void getImageTile(int ibno,int is,int sx,int sy,int sh,int sl)
{
    float img_sx;
    float img_sy;
    float img_sh;
    float img_sl;
    float img_h;
    float img_l;
    imageTile[ibno].chargee = 1;
    imageTile[ibno].image_source = is;
    imageTile[ibno].sx = sx;
    imageTile[ibno].sy = sy;
    imageTile[ibno].sh = sh;
    imageTile[ibno].sl = sl;

    img_sx = imageTile[ibno].sx;
    img_sy = imageTile[ibno].sy;
    img_sh = imageTile[ibno].sh;
    img_sl = imageTile[ibno].sl;
    img_h = imagesTra[imageTile[ibno].image_source].hauteur;
    img_l = imagesTra[imageTile[ibno].image_source].largeur;

    // point1 ........... point2
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    // point 3            point4

    imageTile[ibno].p1_x = (1.0f/img_l)*img_sx;
    imageTile[ibno].p1_y = (1.0f/img_h)*img_sy;

    imageTile[ibno].p2_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageTile[ibno].p2_y = (1.0f/img_h)*img_sy;

    imageTile[ibno].p3_x = (1.0f/img_l)*img_sx;
    imageTile[ibno].p3_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);

    imageTile[ibno].p4_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageTile[ibno].p4_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);
}

void getImageAlpha(int ibno,int is,int sx,int sy,int sh,int sl)
{
    float img_sx;
    float img_sy;
    float img_sh;
    float img_sl;
    float img_h;
    float img_l;
    imageAlpha[ibno].chargee = 1;
    imageAlpha[ibno].image_source = is;
    imageAlpha[ibno].sx = sx;
    imageAlpha[ibno].sy = sy;
    imageAlpha[ibno].sh = sh;
    imageAlpha[ibno].sl = sl;

    img_sx = imageAlpha[ibno].sx;
    img_sy = imageAlpha[ibno].sy;
    img_sh = imageAlpha[ibno].sh;
    img_sl = imageAlpha[ibno].sl;
    img_h = imagesTra[imageAlpha[ibno].image_source].hauteur;
    img_l = imagesTra[imageAlpha[ibno].image_source].largeur;

    // point1 ........... point2
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    //    .                  .
    // point 3            point4

    imageAlpha[ibno].p1_x = (1.0f/img_l)*img_sx;
    imageAlpha[ibno].p1_y = (1.0f/img_h)*img_sy;

    imageAlpha[ibno].p2_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageAlpha[ibno].p2_y = (1.0f/img_h)*img_sy;

    imageAlpha[ibno].p3_x = (1.0f/img_l)*img_sx;
    imageAlpha[ibno].p3_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);

    imageAlpha[ibno].p4_x = ((1.0f/img_l)*img_sx) + ((1.0f/img_l)*img_sl);
    imageAlpha[ibno].p4_y = ((1.0f/img_h)*img_sy) + ((1.0f/img_h)*img_sh);
}

void prepareEcritureVideoGlobale()
{
    ZPos = 0;
    pvr_wait_ready();	// = Wait VBL
    pvr_scene_begin();
}

void prepareEcritureVideoTra()
{
    pvr_list_begin(PVR_LIST_TR_POLY);
}

void termineEcritureVideoTra()
{
    pvr_list_finish();
}

void termineEcritureVideoGlobale()
{
    pvr_scene_finish();
}

void blitImageTra(int ino,int dx,int dy)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if (imagesTra[ino].chargee==0) return;

    ZPos++;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, imagesTra[ino].largeur, imagesTra[ino].hauteur, imagesTra[ino].surface, traitement);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = dx;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = 0;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+imagesTra[ino].largeur;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = 1;
    vert.v = 0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx;
    vert.y = dy+imagesTra[ino].hauteur;
    vert.z = ZPos;
    vert.u = 0;
    vert.v = 1;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+imagesTra[ino].largeur;
    vert.y = dy+imagesTra[ino].hauteur;
    vert.z = ZPos;
    vert.u = 1;
    vert.v = 1;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));


    //imagesTra[noImage].hauteur = hauteur;
    //imagesTra[noImage].largeur = largeur;
    //imagesTra[noImage].chargee = 1;
}

int getFreeImageBankTra()
{
    int i;

    for (i=0; i<MAX_IMAGEBANK_TRA; i++)
    {
        if (imageBankTra[i].chargee==0) return i;
    }

    return -1;
}

void blitImageBankTra(int ibno,int dx,int dy)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if ((ibno<0) || (ibno>(MAX_IMAGEBANK_TRA-1)))
    {
        printf("\n !!!! Dépassement ImageBankTra !!!!: %d",ibno);
        return;
    }
    if (imageBankTra[ibno].chargee==0)
    {
        printf("\n !!!! ImageBankTra non chargee !!!!: %d",ibno);
        return;
    }

    // Récupération des infos image et imageBank
    float img_sh = imageBankTra[ibno].sh;
    float img_sl = imageBankTra[ibno].sl;

    //if ((imagesTra[imageBankTra[ibno].image_source].largeur!=512) || (imagesTra[imageBankTra[ibno].image_source].hauteur!=512)) printf("\n ibno : %d l : %d, h: %d",ibno,imagesTra[imageBankTra[ibno].image_source].largeur,imagesTra[imageBankTra[ibno].image_source].hauteur);


    ZPos++;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, imagesTra[imageBankTra[ibno].image_source].largeur, imagesTra[imageBankTra[ibno].image_source].hauteur, imagesTra[imageBankTra[ibno].image_source].surface, traitement);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = dx;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p1_x;
    vert.v = imageBankTra[ibno].p1_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p2_x;
    vert.v = imageBankTra[ibno].p2_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p3_x;
    vert.v = imageBankTra[ibno].p3_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p4_x;
    vert.v = imageBankTra[ibno].p4_y;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void blitImageTile(int ibno,int dx,int dy)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if (imageTile[ibno].chargee==0) return;

    // Récupération des infos image et imageBank
    float img_sh = imageTile[ibno].sh;
    float img_sl = imageTile[ibno].sl;

    ZPos++;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, imagesTra[imageTile[ibno].image_source].largeur, imagesTra[imageTile[ibno].image_source].hauteur, imagesTra[imageTile[ibno].image_source].surface, traitement);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = dx;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageTile[ibno].p1_x;
    vert.v = imageTile[ibno].p1_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageTile[ibno].p2_x;
    vert.v = imageTile[ibno].p2_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageTile[ibno].p3_x;
    vert.v = imageTile[ibno].p3_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageTile[ibno].p4_x;
    vert.v = imageTile[ibno].p4_y;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void blitImageAlpha(int ibno,int dx,int dy)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    if (imageAlpha[ibno].chargee==0) return;

    // Récupération des infos image et imageBank
    float img_sh = imageAlpha[ibno].sh;
    float img_sl = imageAlpha[ibno].sl;

    ZPos++;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, imagesTra[imageAlpha[ibno].image_source].largeur, imagesTra[imageAlpha[ibno].image_source].hauteur, imagesTra[imageAlpha[ibno].image_source].surface, traitement);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = dx;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageAlpha[ibno].p1_x;
    vert.v = imageAlpha[ibno].p1_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy;
    vert.z = ZPos;
    vert.u = imageAlpha[ibno].p2_x;
    vert.v = imageAlpha[ibno].p2_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageAlpha[ibno].p3_x;
    vert.v = imageAlpha[ibno].p3_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = dx+img_sl;
    vert.y = dy+img_sh;
    vert.z = ZPos;
    vert.u = imageAlpha[ibno].p4_x;
    vert.v = imageAlpha[ibno].p4_y;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void blitImageBankTraRot(int ibno,int dx,int dy,float myrot,float zx,float zy,int center)
{
    pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;
    int ddx,ddy;

    // Récupération des infos image et imageBank
    float img_sh = imageBankTra[ibno].sh*zy;
    float img_sl = imageBankTra[ibno].sl*zx;
    float rot;
    float s,c;

    ZPos++;

    if (center==1)
    {
        ddx = dx + (img_sl/2);
        ddy = dy + (img_sh/2);
    }
    else
    {
        ddx = dx;
        ddy = dy;
    }

    rot = myrot * F_PI / 180.f;
    c = fcos (rot);
    s = fsin (rot);

    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, imagesTra[imageBankTra[ibno].image_source].largeur, imagesTra[imageBankTra[ibno].image_source].hauteur, imagesTra[imageBankTra[ibno].image_source].surface, traitement);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = nx(ddx,ddy,c,s,dx,dy);//dx;
    vert.y = ny(ddx,ddy,c,s,dx,dy);//dy;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p1_x;
    vert.v = imageBankTra[ibno].p1_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = nx(ddx,ddy,c,s,dx+img_sl,dy);//dx+img_sl;
    vert.y = ny(ddx,ddy,c,s,dx+img_sl,dy);//dy;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p2_x;
    vert.v = imageBankTra[ibno].p2_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = nx(ddx,ddy,c,s,dx,dy+img_sh);//dx;
    vert.y = ny(ddx,ddy,c,s,dx,dy+img_sh);//dy+img_sh;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p3_x;
    vert.v = imageBankTra[ibno].p3_y;
    pvr_prim(&vert, sizeof(vert));

    vert.x = nx(ddx,ddy,c,s,dx+img_sl,dy+img_sh);//dx+img_sl;
    vert.y = ny(ddx,ddy,c,s,dx+img_sl,dy+img_sh);//dy+img_sh;
    vert.z = ZPos;
    vert.u = imageBankTra[ibno].p4_x;
    vert.v = imageBankTra[ibno].p4_y;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void freeImageTra(int noImage)
{
    if (imagesTra[noImage].chargee==1)
    {
        pvr_mem_free(imagesTra[noImage].surface);
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

int checkController()
{
    keyUp=0;
    keyLeft=0;
    keyRight=0;
    keyDown=0;
    keyActionA=0;
    keyActionB=0;
    keyActionX=0;
    keyActionY=0;
    keyActionStart=0;

    MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)

    if(st->buttons & CONT_A )
        keyActionA = 1;
    if(st->buttons & CONT_B )
        keyActionB = 1;
    if(st->buttons & CONT_X )
        keyActionX = 1;
    if(st->buttons & CONT_Y )
        keyActionY = 1;
    if(st->buttons & CONT_DPAD_UP )
        keyUp = 1;
    if(st->buttons & CONT_DPAD_DOWN )
        keyDown = 1;
    if(st->buttons & CONT_DPAD_LEFT )
        keyLeft = 1;
    if(st->buttons & CONT_DPAD_RIGHT )
        keyRight = 1;
    if(st->buttons & CONT_START )																					// Duranik
        keyActionStart = 1; 																									// Duranik

    MAPLE_FOREACH_END()

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
    if (
        (keyActionA==1)
        || (keyActionB==1)
        || (keyActionX==1)
        || (keyActionY==1)
    ) return 1;

    return 0;
}

