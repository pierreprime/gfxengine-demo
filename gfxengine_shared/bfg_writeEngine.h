#ifndef WRITEENGINE_H
#define WRITEENGINE_H

/** \brief Affiche une chaine de caracteres de maniere graphique
 *
 *  IMPORTANT : Les alpha doivent-etre charge avec getImageAlpha (voir gfxEngine)
 *  \n Le numero de l'alpha doit correspondre a son code ascii
 *
 * \param x : Position de depart X de la chaine
 * \param y : Position de depart Y de la chaine
 * \param *chaine : Chaine a afficher
 * \return
 *
 */
void we_printString(int x,int y,char *chaine);

void we_printChar(int x,int y,unsigned char c);

/** \brief Affiche une valeur numerique de maniere graphique
 *
 *  IMPORTANT : Les alpha doivent-etre charge avec getImageAlpha (voir gfxEngine)
 *  \n Le numero de l'alpha doit correspondre a son code ascii
 *
 * \param x : Position de depart X de la chaine
 * \param y : Position de depart Y de la chaine
 * \param valeur : Valeur entiere a afficher
 * \return
 *
 */
void we_printInt(int x,int y,int valeur);

#endif
