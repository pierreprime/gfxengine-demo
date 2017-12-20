#include <stdio.h>
#include "headers.h"



unsigned int tableau[10];

void init_tableau(void){
    int idx;
    for(idx=0; idx<10; idx++){
        tableau[idx] = 0;
    }
}

void affiche_tableau(void){
    int idx;
    for(idx=0; idx<10; idx++){
        printf("\n Tableau[%d] = %d", idx, tableau[idx]);
    }
}

unsigned int puissance_carre(unsigned char valeur){

    return valeur * valeur;
}

unsigned int puissance(unsigned int valeur, unsigned int puissance){
    unsigned int resultat, p;

    resultat = 1;
    printf("\n Start : %d", resultat);

    for(p=0; p<puissance; p++){
        resultat = resultat * valeur;
        printf("\n Iteration %d --> %d", p, resultat);
    }

    return resultat;
}

int main(void){

    unsigned int carre;
    unsigned int retour;
    printf("\n\n");

    carre = puissance_carre(2);
    printf("\n Le carre de 2 est %d", carre);
    printf("\n\n");
    retour = puissance(3, 4);
    printf("\n Retour : %d", retour);

    POUET

    #ifdef DEBUG
        printf("\nDEBUG");
    #else
        printf("\nPas de DEBUG");
    #endif // DEBUG

    return 0;
}
