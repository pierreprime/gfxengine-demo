#ifndef FILEENGINE_H
#define FILEENGINE_H

/** \brief Lit une chaine de caractere dans un fichier texte balise
 *
 * Exemple de format fichier balise:
 * \n {NOM_BALISE1}
 * \n [VALEUR_TEXTE1]
 * \n {NOM_BALISE2}
 * \n [VALEUR_TEXTE2]
 *
 * \param *fileName : Chemin d'acces + nom du fichier
 * \param *search_balise : Balise recherchee
 * \return chaine de caractere
 *
 */
char* fe_readStringFromDataFile(char *fileName,char *search_balise);

/** \brief Lit un numerique dans un fichier texte balise
 *
 * Exemple de format fichier balise:
 * \n {NOM_BALISE1}
 * \n [VALEUR_NUMERIQUE_ENTIERE1]
 * \n {NOM_BALISE2}
 * \n [VALEUR_NUMERIQUE_ENTIERE2]
 *
 * \param *fileName : Chemin d'acces + nom du fichier
 * \param *search_balise : Balise recherchee
 * \return numerique lu
 *
 */
int fe_readIntFromDataFile(char *fileName,char *search_balise);

/** \brief Lit un tableau de numerique dans un fichier texte balise
 *
 * Exemple de format fichier balise:
 * \n {NOM_BALISE1}
 * \n [1,2,3,4,5]
 * \n {NOM_BALISE2}
 * \n [6,7,8,9,10,11,12]
 *
 * \param *fileName : Chemin d'acces + nom du fichier
 * \param *search_balise : Balise recherchee
 * \param endValue : Valeur a ecrire en derniere position du tableau. (ex : -1)
 * \return tableau de numerique
 *
 */
int* fe_readIntArrayFromDataFile(char *fileName,char *search_balise,int endValue);

int* fe_readTiledMapFromTxtFile(char *fileName,char *search_balise,int endValue);
int fe_readTiledMapFromTxtFileNoMalloc(char *fileName,char *search_balise,int *t);

#endif

