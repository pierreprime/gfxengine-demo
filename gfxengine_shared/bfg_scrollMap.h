#ifndef SCROLLMAP_H
#define SCROLLMAP_H

#define MAX_TILESCROLL  10

/** \brief Structure contenant les donnees des scrollMaps
 *
 *
 */
typedef struct
{
    float currentWorldMapX;      /**< viewPort X du scrollMap */
    float currentWorldMapY;     /**< viewPort Y du scrollMap */

    int mapLargeur; /**< largeur du scrollMap */
    int mapHauteur; /**< hauteur du scrollMap */
    int tileLH;     /**< taille des tiles du scrollMap */
    int *tmap;       /**< donnees de la scrollMap */
} s_scrollMap;

/** \brief Specifie une scrollMap
 *
 * \param s : Numero du scrollmap
 * \param mapL : Largeur de la scrolleMap
 * \param mapH : Hauteur de la scrollMap
 * \param tileLH : Taille d'une tile en pixel
 * \param *map : data du scrollMap
 *
 */
void sm_setScrollData(int s,int mapL,int mapH,int tileLH,int *map);

/** \brief Change le viewport d'une scrollMap
 *
 * \param s : Numero du scrollmap
 * \param x : Position x du viewport (pixel)
 * \param y : Position y du viewport (pixel)
 *
 */
void sm_setScrollView(int s,float x,float y);

/** \brief Affiche la scrollMap a l'ecran
 *
 * \param s : Numero du scrollmap
 * \param decalX : Position x a l'ecran (pixel)
 * \param decalY : Position y a l'ecran (pixel)
 *
 */
void sm_scrollDraw(int s,int decalX,int decalY);

/** \brief Recupere la position x du viewport
 *
 * \param s : Numero du scrollmap
 * \return Position x du viewport (pixel)
 *
 */
float sm_getScrollViewX(int s);

/** \brief Recupere la position y du viewport
 *
 * \param s : Numero du scrollmap
 * \return Position y du viewport (pixel)
 *
 */
float sm_getScrollViewY(int s);

/** \brief Retourne le numero de la tile de la scrollMap
 *
 * \param s : Numero du scrollMap
 * \param x : Position x de la tile (tile)
 * \param y : Position y de la tile (tile)
 * \return Valeur de la tile
 *
 */
int sm_getTileFromScrollMap(int s,int x,int y);

/** \brief Retourne le numero de la tile de la scrollMap
 *
 * \param s : Numero du scrollMap
 * \param x : Position x de la tile (pixel)
 * \param y : Position y de la tile (pixel)
 * \return Valeur de la tile
 *
 */
int sm_getTileFromScrollWorld(int s,int x,int y);

/** \brief Converti une coordonnee x (pixel) dans le scrollmap en coordonne x ecran (pixel)
 *
 * \param s : Numero du scrollMap
 * \param xSourceValue : Valeur d'une position x pixel du monde
 * \return Valeur x ecran
 *
 */
int sm_convertXWorldInXScreen(int s,int xSourceValue);

/** \brief Converti une coordonnee y (pixel) dans le scrollmap en coordonne y ecran (pixel)
 *
 * \param s : Numero du scrollMap
 * \param xSourceValue : Valeur d'une position y pixel du monde
 * \return Valeur y ecran
 *
 */
int sm_convertYWorldInYScreen(int s,int ySourceValue);

/** \brief Retourne la valeur 1 de la tile de la scrollMap
 *
 * \param s : Numero du scrollMap
 * \param x : Position x de la tile (tile)
 * \param y : Position y de la tile (tile)
 * \return Valeur de la tile
 *
 */
int sm_getTileDefv1FromScrollMap(int s,int x,int y);

/** \brief Retourne la valeur 1 de la tile de la scrollMap
 *
 * \param s : Numero du scrollMap
 * \param x : Position x de la tile (pixel)
 * \param y : Position y de la tile (pixel)
 * \return Valeur de la tile
 *
 */
int sm_getTileDefv1FromScrollWorld(int s,int x,int y);

int sm_checkHorizontalTileDefv1FromScrollWorld(int s,int x,int y,int largeur,int v1_search);
int sm_checkVerticalTileDefv1FromScrollWorld(int s,int x,int y,int hauteur,int v1_search);

#endif
