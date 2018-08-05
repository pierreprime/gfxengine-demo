#ifndef SFXENGINE_H
#define SFXENGINE_H

#define MAX_SAMPLES 15

/** \brief Charge un bruitage
 *
 * \param *filename : Chemin + nom du fichier
 * \param soundNumber : Numero du bruitage
 *
 */
void loadSound(char *filename,int soundNumber);

/** \brief Joue bruitage
 *
 * \param soundNumber : Numero du bruitage
 * \param numberLoop : Nombre de fois
 *
 */
void playSound(int soundNumber,int numberLoop);

/** \brief Libere un bruitage de la memoire
 *
 * \param soundNumber : Numero du bruitage
 *
 */
void clearSound(int soundNumber);

/** \brief Libere tout les bruitages de la memoire
 *
 */
void clearAllSound (void);

/** \brief Initialise le moteur musique/sons
 *
 *
 */
void initSfxEngine(void);

/** \brief Joue un fichier ogg-vorbis
 *
 * \param *filename : Chemin + nom du fichier
 *
 */
void playMusic(char *filename,int loop);

/** \brief Stoppe la musique
 *
 *
 */
void stopMusic(void);

int isMusicPlay(void);

/** \brief Libere la memoire du sfxEngine
 *
 */
void quitSfxEngine(void);


#endif
