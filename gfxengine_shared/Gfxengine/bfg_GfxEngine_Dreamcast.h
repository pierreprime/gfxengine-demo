#ifndef GFXENGINE_H
#define GFXENGINE_H

#include <stdlib.h>
#include <kos.h>

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

/** \brief Structure contenant les donnees des images
 *
 *
 */
typedef struct {
	int chargee;	/**< Flag qui indique si l'image est chargee */
	int hauteur;	/**< Hauteur en pixel de l'image */
	int largeur;    /**< Largeur en pixel de l'image */
	pvr_ptr_t surface;  /**< Technique */
} simage;

/** \brief Structure contenant les donnees des morceaux d'images appeles ImageBank
 *
 *
 */
typedef struct
{
	int image_source; /**< Numero de l'image source */
	int chargee; /**< Flag qui indique si l'imageBank est chargee */
	int sx; /**< Position x du point haut-gauche dans l'image source */
	int sy; /**< Position y du point haut-gauche dans l'image source */
	int sh; /**< Hauteur de l'imageBank */
	int sl; /**< Largeur de l'imageBank */
	float p1_x;/**< Technique */
	float p1_y;/**< Technique */
	float p2_x;/**< Technique */
	float p2_y;/**< Technique */
	float p3_x;/**< Technique */
	float p3_y;/**< Technique */
	float p4_x;/**< Technique */
	float p4_y;/**< Technique */
} sibank;

/** \brief Structure contenant les donnees des tuiles (tiles)
 *
 *
 */
typedef struct
{
	int image_source;/**< Numero de l'image source */
	int chargee;/**< Flag qui indique si la tile est chargee */
	int sx;/**< Position x du point haut-gauche dans l'image source */
	int sy;/**< Position y du point haut-gauche dans l'image source */
	int sh;/**< Hauteur de l'imageBank */
	int sl;/**< Largeur de l'imageBank */
	float p1_x;/**< Technique */
	float p1_y;/**< Technique */
	float p2_x;/**< Technique */
	float p2_y;/**< Technique */
	float p3_x;/**< Technique */
	float p3_y;/**< Technique */
	float p4_x;/**< Technique */
	float p4_y;/**< Technique */
} stiles;

/** \brief Structure contenant les donnees des caracteres alphabetiques (alpha)
 *
 *
 */
typedef struct
{
	int image_source;/**< Numero de l'image source */
	int chargee;/**< Flag qui indique si le caractere est charge */
	int sx;/**< Position x du point haut-gauche dans l'image source */
	int sy;/**< Position y du point haut-gauche dans l'image source */
	int sh;/**< Hauteur de l'imageBank */
	int sl;/**< Largeur de l'imageBank */
	float p1_x;/**< Technique */
	float p1_y;/**< Technique */
	float p2_x;/**< Technique */
	float p2_y;/**< Technique */
	float p3_x;/**< Technique */
	float p3_y;/**< Technique */
	float p4_x;/**< Technique */
	float p4_y;/**< Technique */
} salpha;

/** \brief Initialise le gfxEngine en 640*480
 *
 * \param
 * \param
 * \return
 *
 */
void initGfxEngine();

/** \brief Initialise le gfxEngine en 320*240
 *
 * \param
 * \param
 * \return
 *
 */
void initGfxEngine320();

/** \brief Nouvelle methode d'initialisation de la GfxEngine
 *
 * \param   Resolution : RES_320x240 ou RES_640x480
 * \param   hz : HZ_AUTO ou HZ_FORCE_60
 * \return
 *
 */
void gfxe_init(int resolution,int hz);

/** \brief Change le rafraichissement d'ecran (Dreamcast uniquement, ne fait rien sur PC)
 *
 * \param   hz : HZ_AUTO ou HZ_FORCE_60
 * \return
 *
 */
void gfxe_changeHz(int hz);

/** \brief Renvoie la valeur du rafraichissement d'ecran
 *
 * \return 0 - VGA / 50 - PAL / 60 - NTSC / -1 - ERREUR
 *
 */
int gfxe_returnHz(void);


/** \brief Retourne la valeur de la resolution x en pixel
 *
 * \param
 * \param
 * \return valeur de la resolution x en pixel
 *
 */
int getResX(void);

/** \brief Retourne la valeur de la resolution y en pixel
 *
 * \param
 * \param
 * \return valeur de la resolution y en pixel
 *
 */
int getResY(void);

/** \brief Signale au PVR qu'il va recevoir des donnees (Dreamcast only)
 *
 * La version PC est presente pour compatibilite mais ne fait rien
 *
 * \param
 * \param
 * \return
 *
 */
void prepareEcritureVideoGlobale();

/** \brief Signale au PVR qu'il va recevoir des polygones avec transparence (Dreamcast only)
 *
 * La version PC est presente pour compatibilite mais ne fait rien
 * \n Snippet :
 * \n prepareEcritureVideoGlobale();
 * \n prepareEcritureVideoTra();
 * \n AFFICHER DECOR, SPRITES, ETC ...
 * \n termineEcritureVideoTra();
 * \n termineEcritureVideoGlobale();
 *
 * \param
 * \param
 * \return
 *
 */
void prepareEcritureVideoTra();

/** \brief Signale au PVR qu'on a termine l'envoie des polygones transparent (Dreamcast only)
 *
 * La version PC est presente pour compatibilite mais ne fait rien
 *
 * \param
 * \param
 * \return
 *
 */
void termineEcritureVideoTra();

/** \brief Signale au PVR qu'on a termine d'ecrire des donnees et affiche a l'ecran.(Dreamcast) Ou affiche le buffer video PC a l'ecran. (PC)
 *
 * \param
 * \param
 * \return
 *
 */
void termineEcritureVideoGlobale();

/** \brief Charge une image PNG 32bits.
 *
 * Attention : Pour garder la compatibilite Dreamcast l'image doit être un carre multiple de 2. (Ex: 128x128,512x512, ...).
 *
 * \param *filename : Chemin + nom du fichier image
 * \param noImage : Numero de l'image a charger
 * \param hauteur : Hauteur du fichier .PNG en pixel
 * \param largeur : Largeur du fichier .PNG en pixel

 * \return
 *
 */
int loadImageTra(char *filename,int noImage,int hauteur,int largeur);

/** \brief Affiche une image.
 *
 * \param ino : Numero de l'image a afficher
 * \param dx : Position x en pixel
 * \param dy : Position y en pixel
 * \return
 *
 */
void blitImageTra(int ino,int dx,int dy);

/** \brief Cree en memoire une portion d'image (= ImageBank) a partir d'une image complete.
 *
 * \param ibno : Numero de l'imageBank que l'on veut cree
 * \param is : Numero de l'image source
 * \param sx : Position x de depart dans l'image source
 * \param sy : Position y de depart dans l'image source
 * \param sh : Hauteur de l'imageBank
 * \param sl : Largeur de l'imageBank
 * \return
 *
 */
void getImageBankTra(int ibno,int is,int sx,int sy,int sh,int sl);

/** \brief Cree en memoire une tuile (= Tile) a partir d'une image complete. (Servira pour tileMapEngine ou scrollMapEngine)
 *
 * \param ibno : Numero de la tuile que l'on veut cree
 * \param is : Numero de l'image source
 * \param sx : Position x de depart dans l'image source
 * \param sy : Position y de depart dans l'image source
 * \param sh : Hauteur de la tuile
 * \param sl : Largeur de la tuile
 * \return
 *
 */
void getImageTile(int ibno,int is,int sx,int sy,int sh,int sl);

/** \brief Cree en memoire un caractere graphique (= Alpha) a partir d'une image complete. (Servira pour writeEngine)
 *
 * \param ibno : Numero de l'alpha que l'on veut cree
 * \param is : Numero de l'image source
 * \param sx : Position x de depart dans l'image source
 * \param sy : Position y de depart dans l'image source
 * \param sh : Hauteur de l'alpha
 * \param sl : Largeur de l'alpha
 * \return
 *
 */
void getImageAlpha(int ibno,int is,int sx,int sy,int sh,int sl);

/** \brief Charge un masque de collision de sprite en memoire
 *
 * Pour creer un masque de collision utiliser les outils livre avec la librairie
 *
 * \param *filename : Chemin + nom du fichier masque
 * \param noImage : Numero de l'image que reference le masque
 * \return
 *
 */
int loadMask(char *filename,int noImage);

int getPixelMask(int noImage,int x,int y);

/** \brief Libere la memoire utilisee par le masque lie a une image
 *
 * \param noImage : Numero de l'image que reference le masque
 * \return
 *
 */
void freeMask(int noImage);

/** \brief Charge un masque de collision compresse de sprite en memoire
 *
 * \param *filename : Chemin + nom du fichier masque
 * \param noImage : Numero de l'image que reference le masque
 * \return
 *
 */
int loadCompressMask(char *filename,int noImage);

/** \brief Libere la memoire utilisee par le masque compresse lie a une image
 *
 * Pour creer un masque de collision utiliser les outils livre avec la librairie
 *
 * \param noImage : Numero de l'image que reference le masque
 * \return
 *
 */

int getPixelCompressMask(int noImage,int x,int y);
void freeCompressMask(int noImage);

/** \brief Retourne le premier numero d'imageBank non utilise.
 *
 * \return numero d'imageBank libre
 *
 */
int getFreeImageBankTra();

/** \brief Affiche une imageBank.
 *
 * \param ibno : Numero de l'imageBank a afficher
 * \param dx : Position x en pixel
 * \param dy : Position y en pixel
 * \return
 *
 */
void blitImageBankTra(int ibno,int dx,int dy);

/** \brief Affiche une imageBank avec zoom et rotation.
 *
 * \param ibno : Numero de l'imageBank a afficher
 * \param dx : Position x en pixel
 * \param dy : Position y en pixel
 * \param myrot : Angle de rotation
 * \param zx : Facteur de zoom x
 * \param zy : Facteur de zoom y
 * \param dy : La rotation se fait-elle du centre ou du coin superieur gauche ? (0 - coin / 1 - centre)
 * \return
 *
 */
void blitImageBankTraRot(int ibno,int dx,int dy,float myrot,float zx,float zy,int center);


/** \brief Affiche une tuile.
 *
 * \param ibno : Numero de la tile a afficher
 * \param dx : Position x en pixel
 * \param dy : Position y en pixel
 * \return
 *
 */
void blitImageTile(int ibno,int dx,int dy);

/** \brief Affiche un Alpha.
 *
 * \param ibno : Numero de l'alpha a afficher
 * \param dx : Position x en pixel
 * \param dy : Position y en pixel
 * \return
 *
 */
void blitImageAlpha(int ibno,int dx,int dy);


/** \brief Detruit l'image et libere la memoire
 *
 * \param noImage : Numero de l'image
 * \return
 *
 */
void freeImageTra(int noImage);

/** \brief Detruit toutes les images et libere la memoire
 *
 * \param noImage : Numero de l'image
 * \return
 *
 */
void freeAllImageTra(void);

/** \brief Detruit toutes les images et libere la memoire (Doublon freeAllImageTra)
 *
 * \param noImage : Numero de l'image
 * \return
 *
 */
void freeAllImage(void);

/** \brief Lit la manette (Dreamcast) ou le clavier (PC), et charge en memoire les donnees recueillis
 *
 * \return 0
 *
 */
int checkController();

/** \brief Retourne 1 si le bouton A de la manette a ete presse (Dreamcast), ou touche "C" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyA(void);

/** \brief Retourne 1 si le bouton B de la manette a ete presse (Dreamcast), ou touche "V" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyB(void);

/** \brief Retourne 1 si le bouton X de la manette a ete presse (Dreamcast), ou touche "B" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyX(void);

/** \brief Retourne 1 si le bouton Y de la manette a ete presse (Dreamcast), ou touche "N" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyY(void);

/** \brief Retourne 1 si le bouton HAUT de la manette a ete presse (Dreamcast), ou touche "haut" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyUp(void);

/** \brief Retourne 1 si le bouton BAS de la manette a ete presse (Dreamcast), ou touche "bas" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyDown(void);

/** \brief Retourne 1 si le bouton GAUCHE de la manette a ete presse (Dreamcast), ou touche "gauche" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyLeft(void);

/** \brief Retourne 1 si le bouton DROITE de la manette a ete presse (Dreamcast), ou touche "droite" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyRight(void);

/** \brief Retourne 1 si le bouton START de la manette a ete presse (Dreamcast), ou touche "P" (PC)
 *
 * \return 0 ou 1
 *
 */
int getKeyStart(void);

/** \brief Retourne 1 si une touche "action" (A,B,X,Y sur DC) (C,V,B,N sur PC) a ete enfonce
 *
 * \return 0 ou 1
 *
 */
int anyActionKeyPress(void);

/** \brief Retourne 1 si il n'y a aucune direction de selectionne
 *
 * \return 0 ou 1
 *
 */
int getNoDirection(void);


#endif
