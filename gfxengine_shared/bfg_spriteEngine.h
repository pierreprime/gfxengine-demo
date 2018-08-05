#ifndef SPRITEENGINE_H
#define SPRITEENGINE_H

#ifndef PC_VERSION
    #include <stdlib.h>
    #include <kos.h>
#else
    #include <stdlib.h>
#endif

#define MAX_SPRITE 500 /**< Nombre de sprite disponible */
#define MAX_ANIMATION 30 /**< Nombre d'animations disponibles pour un sprite */
#define MAX_ANIMATION_FRAME 20 /**< Nombre d'imageBank pour une animation */
#define ANIM_LOOP	1 /**< L'animation boucle automatiquement */
#define ANIM_NOLOOP 0 /**< L'animation ne boucle pas */

#define ANIMATION_CLASSIQUE 0 /**< Type d'animation classique pour les mega-sprite */
#define ANIMATION_COMPLEXE  1 /**< Type d'animation complexe pour les mega-sprite */

#define MAXHITBOX   10  /**< Nombre de hitbox pour un mega-sprite */

#define MS_MAXMSPRITE  100  /**< Nombre de mega-sprite */
#define MS_MAXPART 8   /**< Nombre de parties composant le mega-sprite */
#define MS_MAXANIM  10  /**< Nombre d'animations possibles pour un mega-sprite */

/** \brief Structure contenant les donnees des sprites
 *
 *
 */
typedef struct
{
    int utilise;	/**< Sprite utilise ? */
    float posx;		/**< Position x a l'ecran*/
    float posy;		/**< Position y a l'ecran */
    int ibno;		/**< Numero d'imagebank representant le sprite */
    int animation[MAX_ANIMATION][MAX_ANIMATION_FRAME]; /**< n animation de z frame */


    float stepR; /**< Rotation souple */
    int nbFrameR; /**< Rotation souple */
    int finRotation; /**< Rotation souple */


    float stepTX; /**< Translation X souple */
    int nbFrameTX; /**< Translation X souple */
    int finTX; /**< Translation X souple */


    float stepTY; /**< Translation Y souple */
    int nbFrameTY; /**< Translation Y souple */
    int finTY; /**< Translation Y souple */


    int animation_loop[MAX_ANIMATION]; /**< Flag de boucle pour animation */
    int animation_speed[MAX_ANIMATION];   /**< Vitesse d'une animation */
    int current_animation; /**< Animation courante (-1 = non anime) */
    int current_animation_frame; /**< numéro de frame courante courante */
    int intern1;	/**< Interne */
    int fin_animation; /**< 1 = fin d'animation ou une loop jouee */
    int rotcenter; /**< 0 = rotation par rapport au coin superieur gauche 1 = rotation au centre */
    int hitbox_x; /**< Position x du coin superieur gauche de la hitbox du sprite */
    int hitbox_y; /**< Position y du coin superieur gauche de la hitbox du sprite */
    int hitbox_h; /**< Hauteur de la hitbox */
    int hitbox_l; /**< Largeur de la hitbox */

    float rot; /**< Indice de rotation */
    float zx; /**< Facteur de zoom x */
    float zy; /**< Facteur de zoom y */
    int layer; /**< Inutilise */
} ssprite;

/** \brief Structure contenant les donnees des morceaux de mega-sprite
 *
 *
 */
typedef struct
{
    float x;        /**< Position x */
    float step_x;   /**< Pas de translation x */
    float y;        /**< Position y */
    float step_y;   /**< Pas de translation y */
    float rot;      /**< Rotation */
    float step_rot; /**< Pas de rotation */
    float zx;       /**< Facteur de zoom x */
    float zy;       /**< Facteur de zoom y */
    int ibno;       /**< numero d'imageBank pour cette partie */

    int *anim;      /**< Pointeur vers un tableau contenant les frames d'animation */
    int anim_loop;  /**< L'animation boucle t'elle ? */
    int animate;    /**< Flag qui indique si l'animation est demarree ou non */
    int anim_offset; /**< Position dans la chaine d'animation */
    int anim_cpt;    /**< Compteur pour passer a la frame suivante */
} spart;

/** \brief Structure contenant les donnees des mega-sprite
 *
 *
 */
typedef struct
{

    int utilise; /**< Le mega-sprite est il utilise ? */


    float posx; /**< Position x globale du mega-sprite. Point de reference pour ses parts*/
    float posy; /**< Position y globale du mega-sprite. Point de reference pour ses parts*/
    int nbpart; /**< Nombre de parties composant le mega-sprite */

    int offset; /**< Offset dans le tableau d'animation */
    int timer_precedent;
    int timer_courant;
    int cpt;

    float *dataMove_animation;  /**< Mouvements des parties du mega-sprite */
    int anim_onoff; /**< Animation active ou non */
    int loop;   /**< Animation boucle ou non */

    int current_phase;  /**< numero de la phase courante de l'animation */
    int fin_animation;  /**< L'animation est terminee */

    spart part[MS_MAXPART]; /**< Les parties du mega-sprite */

    int nbHitBox;   /**< Le nombre de hitbox du megasprite */
    int hb_x[MAXHITBOX];    /**< Position x du coin superieur gauche des hitbox du mega-sprite */
    int hb_y[MAXHITBOX];    /**< Position y du coin superieur gauche des hitbox du mega-sprite */
    int hb_h[MAXHITBOX];    /**< hauteur des hitbox du mega-sprite */
    int hb_l[MAXHITBOX];    /**< largeur des hitbox du mega-sprite */

} smsprite;


/** \brief Teste la collision parfaite entre deux sprites (Necessite un mask charge en memoire)
 *
 * \param sprite1 : numero du 1er sprite
 * \param sprite2 : Numero du second sprite
 * \return 0 - Pas de collision / 1 - Collision
 *
 */
int spr_isSpriteCollidePerfect(int sprite1,int sprite2);

/** \brief Teste la collision parfaite entre deux sprites (Necessite un mask compresse charge en memoire)
 *
 * \param sprite1 : numero du 1er sprite
 * \param sprite2 : Numero du second sprite
 * \return 0 - Pas de collision / 1 - Collision
 *
 */
int spr_isSpriteCollidePerfectCompress(int sprite1,int sprite2);

/** \brief BETA : Teste la collision parfaite entre un sprites et une imageBank(Necessite un mask compresse charge en memoire)
 *
 * \param sprite1 : numero du 1er sprite
 * \param x : position x de l'imageBank dans l'écran de jeu
 * \param y : position y de l'imageBank dans l'écran de jeu
 * \param ibno : numéro d'imageBank
 * \return 0 - Pas de collision / 1 - Collision
 *
 */
int spr_isSpriteCollideWithIBPerfectCompress(int sprite1,int x,int y,int ibno);

/** \brief Compte le nombre de sprite actif
 *
 * \return Nombre de sprite utilise
 *
 */
int spr_count_used_sprites(void);


/** \brief Initialise le moteur de sprite classique
 *
 *
 */
void spr_initSpriteEngine();

/** \brief Reserve un sprite specifique a une position x,y avec une rotation et indique son centre de rotation
 *
 * \param n : numero du sprite a reserver
 * \param x : position x
 * \param y : position y
 * \param rot : angle de rotation
 * \param i : numero d'ImageBank
 *
 */
void spr_initSprite(int n,float x,float y,float rot,int i);

/** \brief Reserve et initialise un sprite
*
* \return Numero du sprite reserve (-1 si reservation impossible)
*/
int spr_reserveFreeSprite(void);

/** \brief Reserve un sprite libre a partir d'un numero de sprite
*
* \param borne : numero de borne de recherche de sprite libre
* \return Numero du sprite reserve (-1 si reservation impossible)
*/
int spr_reserveFreeSpriteFrom(int borne);

/** \brief Reserve un sprite specifique a une position x,y avec une rotation et indique son centre de rotation
 *
 * \param x : position x
 * \param y : position y
 * \param r : angle de rotation
 * \param i : Numero d'imageBank
 * \return Numero du sprite reserve (-1 si reservation impossible)
 */
int spr_initFreeSprite(float x,float y,float r,int i);

/** \brief Libere le sprite
 *
 * \param n : Numero du sprite a liberer
 */
void spr_releaseSprite(int n);

/** \brief Libere tout les sprites
 *
 */
void spr_releaseAllSprite();

/** \brief Declenche l'animation d'un sprite
 *
 * \param s : Numero du sprite
 * \param a : Numero de l'animation
 */
void spr_animateSprite(int s,int a);

/** \brief Change de maniere fluide la rotation d'un sprite en absolue
 *
 * \param s : Numero du sprite
 * \param nouvelAngle : Angle
 * \param nbFrame : Donne le nombre d'etape pour atteindre le nouvel angle
 */
void spr_changeSmoothSpriteRotAbsolute(int s,float nouvelAngle,int nbFrame);


 /** \brief Change de maniere fluide la rotation d'un sprite en relatif
 *
 * \param s : Numero du sprite

 * \param AngleStep : Ajoute/Soustrait la valeur de ce parametre a l'angle courant
 * \param nbFrame : Donne le nombre d'etape pour atteindre le nouvel angle
 */
void spr_changeSmoothSpriteRotRelative(int s,float AngleStep,int nbFrame);

/** \brief Change de maniere fluide la position x d'un sprite en absolue
 *
 * \param s : Numero du sprite
 * \param nouvelPosX : Position X a atteindre
 * \param nbFrame : Donne le nombre d'etape pour atteindre la nouvelle position
 */
void spr_changeSmoothSpriteTXAbsolute(int s,float nouvelPosX,int nbFrame);

/** \brief Change de maniere fluide la position x d'un sprite en relatif
 *
 * \param s : Numero du sprite
 * \param nouvelPosX :  Ajoute/Soustrait la valeur de ce parametre a la position x
 * \param nbFrame : Donne le nombre d'etape pour atteindre la nouvelle position
 */
void spr_changeSmoothSpriteTXRelative(int s,float StepX,int nbFrame);

/** \brief Change de maniere fluide la position y d'un sprite en absolue
 *
 * \param s : Numero du sprite
 * \param nouvelPosY : Position y a atteindre
 * \param nbFrame : Donne le nombre d'etape pour atteindre la nouvelle position
 */
void spr_changeSmoothSpriteTYAbsolute(int s,float nouvelPosY,int nbFrame);

/** \brief Change de maniere fluide la position y d'un sprite en relatif
 *
 * \param s : Numero du sprite
 * \param nouvelPosY :  Ajoute/Soustrait la valeur de ce parametre a la position x
 * \param nbFrame : Donne le nombre d'etape pour atteindre la nouvelle position
 */
void spr_changeSmoothSpriteTYRelative(int s,float StepY,int nbFrame);

/** \brief Fonction toute pourrie pour definir une animation de sprite
 *
 * \param s : Numero du sprite
 * \param a : Numero de l'animation a definir
 * \param speed : Vitesse de l'animation
 * \param f1..f19 : Numero d'imageBank pour une frame. -1 = Fin d'animation
 * \param loop : ANIM_LOOP = Animation qui boucle / ANIM_NOLOOP = Ne boucle pas
 */
void spr_setSpriteAnimation(int s,int a,int speed,int f0,int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9,int f10,int f11,int f12,int f13,int f14,int f15,int f16,int f17,int f18,int f19,int loop);

/** \brief Fonction un peu moins pourri pour definir une animation de sprite
 *
 * \param s : Numero du sprite
 * \param a : Numero de l'animation a definir
 * \param speed : Vitesse de l'animation
 * \param v : Tableau contenant les numeros d'ImageBank composant l'animation. Doit se terminer par -1 et ne pas contenir plus de 20 valeurs.
 * \param loop : ANIM_LOOP = Animation qui boucle / ANIM_NOLOOP = Ne boucle pas
 */
void spr_setSpriteAnimation2(int s,int a,int speed,int *v,int loop);

/** \brief Definit la hitbox d'un sprite
 *
 * \param s : Numero du sprite
 * \param hbx : Position x du coin superieur gauche de la hitbox
 * \param hby : Position y du coin superieur gauche de la hitbox
 * \param hbh : Hauteur de la hitbox
 * \param hbl : Largeur de la hitbox
 */
void spr_setSpriteHitbox(int sprno,int hbx,int hby,int hbh,int hbl);

/** \brief Positionne le sprite
 *
 * \param n : Numero du sprite
 * \param x : Position x du coin superieur gauche du sprite
 * \param y : Position y du coin superieur gauche du sprite
 */
void spr_moveSprite(int n,float x,float y);

/** \brief Positionne le sprite de manière relatif
 *
 * \param n : Numero du sprite
 * \param x : Valeur x à ajouter ou soustraire de la position x courante
 * \param y : Valeur y à ajouter ou soustraire de la position x courante
 */
void spr_moveSpriteRelative(int n,float x,float y);

/** \brief Change l'angle du sprite.
 *
 * \param n : Numero du sprite
 * \param r : Angle
 * \param center : 0 - Rotation par rapport au coin superieur gauche / 1 - Par rapport au centre
 */
void spr_changeSpriteRotation(int n,float r,int center);

/** \brief Change le zoom du sprite
 *
 * \param n : Numero du sprite
 * \param zx : Facteur grossissant x
 * \param zy : Facteur grossissant y
 */
void spr_changeSpriteZoom(int n,float zx,float zy);

/** \brief Change l'image du sprite
 *
 * \param n : Numero du sprite
 * \param i : ImageBank
 */
void spr_changeSpriteImage(int n,int i);

/** \brief Change le layer du sprite (Non utilise)
 *
 * \param n : Numero du sprite
 * \param lno : Layer d'affichage
 */
void spr_changeSpriteLayer(int n,int lno);

/** \brief Affiche le sprite
 *
 * \param n : Numero du sprite
 */
void spr_showSprite(int n);

/** \brief Met a jour les animations du sprite
 *
 * \param n : Numero du sprite
 */
void spr_updateSprites(int n);

/** \brief Affiche tout les sprites actifs
 *
 */
void spr_showAllSprites();

/** \brief Affiche tout les sprites d'un certain layer (Non utilise)
 *
 * \param layerno : Numero du layer
 */
void spr_showAllSpritesLayer(int layerno);

/** \brief Met a jour les animations de tout les sprites
 *
 * \param n : Numero du sprite
 */
void spr_updateAllSprites();

/** \brief Arrete l'animation d'un sprite
 *
 * \param s : Numero du sprite
 */
void spr_stopAnimateSprite(int s);

/** \brief Teste la collision hitbox entre deux sprites.
 *
 * \param sprite1 : numero du 1er sprite
 * \param sprite2 : Numero du second sprite
 * \return 0 - Pas de collision / 1 - Collision
 *
 */
int spr_isSpriteCollide(int sprite1,int sprite2);

/** \brief Informe si le sprite est reserve - utilise
 *
 * \param sprno : numero du 1er sprite
 * \return 0 - libre / 1 - paslibre
 *
 */
int spr_getUtilise(int sprno);

int spr_getCurrentImageBank(int sprno);

float spr_getSpriteZoomX(int n);
float spr_getSpriteZoomY(int n);
float spr_getSpriteRot(int n);
float spr_getSpriteX(int n);
float spr_getSpriteY(int n);
int spr_getFinAnimation(int sprno);
int spr_getFinRotation(int sprno);
int spr_getFinTX(int sprno);
int spr_getFinTY(int sprno);
int spr_getCurrentAnimation(int sprno);
int spr_getCurrentAnimationFrame(int sprno);
int spr_getHitBoxX(int sprno);
int spr_getHitBoxY(int sprno);
int spr_getHitBoxH(int sprno);
int spr_getHitBoxL(int sprno);

/**************************/
/* GESTION DE MEGA-SPRITE */
/**************************/

void ms_initMegaSpriteEngine(void);
int ms_reserveFreeMegaSprite(int nbPart);
void ms_destroyMegaSprite(int msno);



/** \brief Definit les mouvements des differentes parties du megasprite
 *
* Format des datamoves : !! IMPORTANT DOIT RESPECTER LE NOMBRE DE PART !!
* \n Timer A
* \n PositionX,PositionY,Rotation Part 1 pour Timer A
* \n PositionX,PositionY,Rotation Part 2 pour Timer A
* \n [...]
* \n Timer B
* \n PositionX,PositionY,Rotation Part 1 pour Timer B
* \n PositionX,PositionY,Rotation Part 2 pour Timer B
* \n -1
 *
 * \param msno : numero du megasprite
 * \param *data : tableau de datamoves
 * \param loop : doit-on boucler ?
 * \return 0 - Pas de collision / 1 - Collision
 *
 */
void ms_setDataMoveAnimation(int msno,float *data,int loop);


void ms_setImagePart(int msno,int ipart,int ibno);
void ms_updateMegaSprite(int msno);
void ms_updateAllMegaSprite(void);
void ms_showMegaSprite(int msno);
void ms_showAllMegaSprite(void);
void ms_startAnimate(int msno);
void ms_stopAnimate(int msno);
void ms_setPosXPart(int msno,int pno,float x);
void ms_setPosYPart(int msno,int pno,float y);
void ms_setPosPart(int msno,int pno,float x,float y);
void ms_setRotPart(int msno,int pno,float r);
void ms_setPosX(int msno,float x);
void ms_setPosY(int msno,float y);
int ms_getCurrentPhase(int msno);
float ms_getPosX(int msno);
float ms_getPosY(int msno);
int ms_getFinAnimation(int msno);
int ms_isSpriteMegaSpriteCollide(int sprno,int msprno);
void ms_setNbHitBox(int msno,int nb);
void ms_setHitBox(int msprono,int hno,int vx,int vy,int vh,int vl);
void ms_setAnimationPart(int msno,int pno,int *data,int loop);
void ms_startAnimatePart(int msno,int pno);
void ms_stopAnimatePart(int msno,int pno);
#endif
