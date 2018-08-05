#ifndef TILESMAP_H
#define TILESMAP_H

#define MAX_TILE 4096

/** \brief Structure contenant les donnees des definitions de tuiles (valeurs libres)
 *
 *
 */
typedef struct
{
    int value1;     /**< Valeur1 de la tile */
    int value2;     /**< Valeur2 de la tile */
    int value3;     /**< Valeur2 de la tile */
} s_tiledef;

/** \brief Structure contenant les donnees des maps de tiles
 *
 *
 */
typedef struct
{
    int mapLargeur; /**< Nombre de tile de hauteur de la map */
    int mapHauteur; /**< Nombre de tile de largeur de la map */
    int tileLH;     /**< Valeur Hauteur/Largeur d'une tile = carre */
    int *tmap;      /**< Pointeur vers la map representant les decors */
    int *tmapData;  /**< Pointeur vers la map representant les obstacles */
} s_tilemap;

/** \brief Specifie la tileMap courante
 *
 * \param h : Hauteur de la tileMap
 * \param l : Largeur de la tileMap
 * \param thl : Taille d'une tile en pixel
 * \param *data : TileMap de decor
 * \param *data2 : TileMap de collision
 *
 */
void tm_setCurrentTilemap(int h,int l,int thl,int *data,int *data2);

/** \brief Retourne le numero de la tile decor depuis la tileMap decor courante
 *
 * \param x : Position x de la tile
 * \param y : Position y de la tile
 * \return Valeur de la tile de decor
 *
 */
int tm_getTileNumberFromCurrentMap(int x,int y);

/** \brief Retourne le numero de la tile decor depuis la tileMap collision courante
 *
 * \param x : Position x de la tile
 * \param y : Position y de la tile
 * \return Valeur de la tile de collision
 *
 */
int tm_getTileNumberFromCurrentMapDataLayer(int x,int y);

/** \brief Retourne la valeur1 de la tile decor depuis la tileMap decor courante
 *
 * \param x : Position x de la tile
 * \param y : Position y de la tile
 * \return Valeur1 de la tile dans la map de decor
 *
 */
int tm_getTileDefValue1FromCurrentMap(int x,int y);

/** \brief Retourne la valeur1 de la tile decor depuis la tileMap collision courante
 *
 * \param x : Position x de la tile
 * \param y : Position y de la tile
 * \return Valeur1 de la tile dans la map de collision
 *
 */
int tm_getTileDefValue1FromCurrentMapDataLayer(int x,int y);

/** \brief Met a jour les valeur d'une tile
 *
 * \param tileno : Numero de tile
 * \param v1 : Valeur 1 de la tile
 * \param v2 : Valeur 2 de la tile
 * \param v3 : Valeur 3 de la tile
 *
 */
void tm_setTileDef(int tileno,int v1,int v2,int v3);

/** \brief Recupere la valeur1 d'une tile
 *
 * \param tileno : Numero de tile
 * \return Valeur1 de la tile
 */
int tm_getTileDefv1(int tileno);

/** \brief Recupere la valeur2 d'une tile
 *
 * \param tileno : Numero de tile
 * \return Valeur2 de la tile
 */
int tm_getTileDefv2(int tileno);

/** \brief Recupere la valeur3 d'une tile
 *
 * \param tileno : Numero de tile
 * \return Valeur3 de la tile
 */
int tm_getTileDefv3(int tileno);

/** \brief NE PAS UTILISER !!! Garde pour le moment pour compatibilite Sydney Hunter
 *
 */
void tm_showCurrentTileMapImageBank(int scrPosX,int scrPosY,int decal);

/** \brief Affiche la tileMap a l'ecran
 *
 * \param scrPosX : Position x
 * \param scrPosY : Position y
 */
void tm_showCurrentTileMap(int scrPosX,int scrPosY);

/** \brief Change une tuile dans la map decor
 *
 * \param mapX : Position x de la tile
 * \param mapY : Position y de la tile
 * \param v : valeur de la tuile
 *
 */
void tm_changeTileInCurrentTilemap(int mapX,int mapY,int v);

/** \brief Change une tuile dans la map collision
 *
 * \param mapX : Position x de la tile
 * \param mapY : Position y de la tile
 * \param v : valeur de la tuile
 *
 */
void tm_changeTileInCurrentTilemapDataLayer(int mapX,int mapY,int v);

/** \brief Beta version : Cherche si dans le data layer entre x (pixel) et x+largeur (pixel) il y a une tile avec une valeur1 = tdefv1_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis x jusqu'a x + largeur
 * \param tdefv1_search : Type de tile recherchée
 * \return 1 si on est sur une tile de value1 recherchée
 */
int tm_checkCollHorizontalValue1DataLayer(int x,int y,int largeur,int tdefv1_search);

/** \brief Beta version : Cherche si dans le data layer entre y (pixel) et y+hauteur (pixel) il y a une tile avec une valeur1 = tdefv1_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis y jusqu'a y + hauteur
 * \param tdefv1_search : Type de tile recherchée
 * \return 1 si on est sur une tile de value1 recherchée
 */
int tm_checkCollVerticalValue1DataLayer(int x,int y,int hauteur,int tdefv1_search);

/** \brief Beta version : Cherche si dans la tilemap entre x (pixel) et x+largeur (pixel) il y a une tile avec une valeur1 = tdefv1_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis x jusqu'a x + largeur
 * \param tdefv1_search : Type de tile recherchée
 * \return 1 si on est sur une tile de value1 recherchée
 */
int tm_checkCollHorizontalValue1TileMap(int x,int y,int largeur,int tdefv1_search);

/** \brief Beta version : Cherche si dans la tilemap entre y (pixel) et y+hauteur (pixel) il y a une tile avec une valeur1 = tdefv1_search
 *
 * \param mapX : Position x pixel
 * \param mapY : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis y jusqu'a y + hauteur
 * \param tdefv1_search : Type de tile recherchée
 * \return 1 si on est sur une tile de value1 recherchée
 */
int tm_checkCollVerticalValue1TileMap(int x,int y,int hauteur,int tdefv1_search);

/** \brief Beta version : Cherche si dans le data layer entre x (pixel) et x+largeur (pixel) il y a une tile avec un index = tn_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis x jusqu'a x + largeur
 * \param tn_search : n° de tile recherchée
 * \return 1 si on est sur une tile d'index recherchée
 */
int tm_checkCollHorizontalTileNumberDataLayer(int x,int y,int largeur,int tn_search);

/** \brief Beta version : Cherche si dans le data layer entre y (pixel) et y+hauteur (pixel) il y a une tile avec un index = tn_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis y jusqu'a y + hauteur
 * \param tn_search : n° de tile recherchée
 * \return 1 si on est sur une tile d'index recherchée
 */
int tm_checkCollVerticalTileNumberDataLayer(int x,int y,int hauteur,int tn_search);

/** \brief Beta version : Cherche si dans la Tilemap entre x (pixel) et x+largeur (pixel) il y a une tile avec un index = tn_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis x jusqu'a x + largeur
 * \param tn_search : n° de tile recherchée
 * \return 1 si on est sur une tile d'index recherchée
 */
int tm_checkCollHorizontalTileNumberTileMap(int x,int y,int largeur,int tn_search);

/** \brief Beta version : Cherche si dans la Tilemap entre y (pixel) et y+hauteur (pixel) il y a une tile avec un index = tn_search
 *
 * \param x : Position x pixel
 * \param y : Position y pixel
 * \param largeur : Tester les valeur1 des tuiles depuis y jusqu'a y + hauteur
 * \param tn_search : n° de tile recherchée
 * \return 1 si on est sur une tile d'index recherchée
 */
int tm_checkCollVerticalTileNumberTileMap(int x,int y,int hauteur,int tn_search);


void tm_setTileNumberCurrentMap(int x,int y,int v);
void tm_setTileNumberCurrentMapDataLayer(int x,int y,int v);


#endif

