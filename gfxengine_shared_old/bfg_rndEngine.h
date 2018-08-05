#ifndef BFG_RNDENGINE_H
#define BFG_RNDENGINE_H

/* Génére un nombre aléatoire d'une valeur entre START et END */
int rnd_random(int start,int end);

int rnd_random2(int start,int end);
void rnd_srand2(unsigned int seed);

#endif // BFG_RNDENGINE_H
