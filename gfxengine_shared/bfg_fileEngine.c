#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../gfxengine_shared/bfg_fileEngine.h"

#define VRAI    1
#define FAUX    0

int compare(char* chaine1,char* chaine2)
{
    unsigned int i=0;
    if( strlen(chaine1) != strlen(chaine2) )
        return FAUX;
    for(i=0; i<strlen(chaine1); i++)
        if( chaine1[i] != chaine2[i])
            return FAUX;
    return VRAI;

}

char* fe_readStringFromDataFile(char *fileName,char *search_balise)
{


    char c;
    char balise[50];
    int offset=0;

    char *chaine;

    FILE *fichier;
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    chaine = malloc(500*sizeof(char));
    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='{')
        {
            offset = 0;
            c=fgetc(fichier);
            while (c!='}')
            {
                balise[offset]=c;
                offset++;
                c=fgetc(fichier);
            }
            balise[offset]='\0'; /* On marque la fin de chaine */
            if (compare(search_balise,balise)==1)
            {
                while(c!='[') c=fgetc(fichier); /* On se positionne sur la valeur */
                offset=0;
                c=fgetc(fichier);
                while (c!=']')
                {
                    chaine[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                chaine[offset]='\0';
                fclose(fichier);
                fichier=NULL;
                return chaine;
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;


    return 0;
}

int fe_readIntFromDataFile(char *fileName,char *search_balise)
{
    char c;
    char balise[50];
    int offset=0;
    char entier[10];
    FILE *fichier;
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='{')
        {
            offset = 0;
            c=fgetc(fichier);
            while (c!='}')
            {
                balise[offset]=c;
                offset++;
                c=fgetc(fichier);
            }
            balise[offset]='\0'; /* On marque la fin de chaine */
            if (compare(search_balise,balise)==1)
            {
                while(c!='[') c=fgetc(fichier); /* On se positionne sur la valeur */
                offset=0;
                c=fgetc(fichier);
                while (c!=']')
                {
                    entier[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                entier[offset]='\0';
                fclose(fichier);
                fichier=NULL;
                return atoi(entier);
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;


    return 0;
}

int* fe_readIntArrayFromDataFile(char *fileName,char *search_balise,int endValue)
{
    char c;
    char balise[50];
    int nbcar,nbvalue,offset;

    int *rdata;
    char *data_file;
    char *token;


    FILE *fichier;



    /* 1er passage, récupérer le nombre de caractère du tableau ! */
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='{')
        {
            offset = 0;
            c=fgetc(fichier);
            while (c!='}')
            {
                balise[offset]=c;
                offset++;
                c=fgetc(fichier);
            }
            balise[offset]='\0'; /* On marque la fin de chaine */

            /* On est sur la bonne balise ? */
            if (compare(search_balise,balise)==1)
            {
                while(c!='[') c=fgetc(fichier); /* On se positionne sur la valeur */
                offset=0;
                c=fgetc(fichier);
                while (c!=']')
                {
                    nbcar++;
                    if (c==',') nbvalue++;
                    offset++;
                    c=fgetc(fichier);
                }
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;

    //printf("\n nbcar : %d",nbcar);

    data_file = malloc((nbcar+2)*sizeof(int));
    rdata = malloc((nbvalue+2)*sizeof(int));

    /* 2eme passage */
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='{')
        {

            offset = 0;
            c=fgetc(fichier);
            while (c!='}')
            {
                balise[offset]=c;
                offset++;
                c=fgetc(fichier);
            }
            balise[offset]='\0'; /* On marque la fin de chaine */

            /* On est sur la bonne balise ? */
            if (compare(search_balise,balise)==1)
            {

                while(c!='[') c=fgetc(fichier); /* On se positionne sur la valeur */
                offset=0;
                c=fgetc(fichier);
                while (c!=']')
                {
                    data_file[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                break;
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;
    data_file[offset]='\0';


    //printf("\n datafile : %s",data_file);

    /* Remplissage du tableau */



    token = strtok(data_file, ",");


    offset = 0;
    while( token != NULL )
    {
        *(rdata+offset) = atoi(((token)));
        offset++;
        token = strtok(NULL,",");
    }
    free(data_file);
    //free(token);
    data_file=NULL;
    token=NULL;

    *(rdata+offset) = endValue;

    return rdata;

}

int* fe_readTiledMapFromTxtFile(char *fileName,char *search_balise,int endValue)
{
    char c;
    char balise[50];
    int nbcar,nbvalue,offset;

    int *rdata;
    char *data_file;
    char *token;


    FILE *fichier;


    /* 1er passage, récupérer le nombre de caractère du tableau ! */
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='t')
        {

            c=fgetc(fichier);
            if (c=='y')
            {
                while (c!='=')
                {
                    c=fgetc(fichier);
                }
                c=fgetc(fichier);


                offset = 0;
                while (c!='\n')
                {
                    balise[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                balise[offset]='\0'; /* On marque la fin de chaine */

                /* On est sur la bonne balise ? */
                if (compare(search_balise,balise)==1)
                {
                    while(c!='=') c=fgetc(fichier); /* On se positionne sur la valeur */
                    offset=0;
                    c=fgetc(fichier);
                    while ((c!='[') && (c!=EOF)) /* Tant qu'on est pas sur le prochaine [layer] */
                    {
                        nbcar++;
                        if (c==',') nbvalue++;
                        offset++;
                        c=fgetc(fichier);
                    }
                }

            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;

    //printf("\n nbcar : %d",nbcar);

    data_file = malloc((nbcar+2)*sizeof(int));
    rdata = malloc((nbvalue+2)*sizeof(int));

    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
        return 0;
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='t')
        {

            c=fgetc(fichier);
            if (c=='y')
            {
                while (c!='=')
                {
                    c=fgetc(fichier);
                }
                c=fgetc(fichier);


                offset = 0;
                while (c!='\n')
                {
                    balise[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                balise[offset]='\0';


                if (compare(search_balise,balise)==1)
                {

                    while(c!='=') c=fgetc(fichier);
                    offset=0;
                    c=fgetc(fichier);
                    while ((c!='[') && (c!=EOF))
                    {
                        data_file[offset]=c;
                        offset++;
                        c=fgetc(fichier);
                    }
                    break;
                }
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;
    data_file[offset]='\0';








    token = strtok(data_file, ",");


    offset = 0;
    while( token != NULL )
    {
        *(rdata+offset) = atoi(((token)));
        offset++;
        token = strtok(NULL,",");
    }
    free(data_file);
    //free(token);
    data_file=NULL;
    token=NULL;

    *(rdata+offset) = endValue;

    return rdata;

}


int fe_readTiledMapFromTxtFileNoMalloc(char *fileName,char *search_balise,int *t)
{
    char c;
    char balise[50];
    int nbcar,nbvalue,offset;
    int trouve;

    //int *rdata;
    char *data_file;
    char *token;


    FILE *fichier;

    trouve = 0;


    /* 1er passage, récupérer le nombre de caractère du tableau ! */
    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='t')
        {

            c=fgetc(fichier);
            if (c=='y')
            {
                while (c!='=')
                {
                    c=fgetc(fichier);
                }
                c=fgetc(fichier);


                offset = 0;
                while (c!='\n')
                {
                    balise[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                balise[offset]='\0'; /* On marque la fin de chaine */

                /* On est sur la bonne balise ? */
                if (compare(search_balise,balise)==1)
                {
                    trouve = 1;
                    while(c!='=') c=fgetc(fichier); /* On se positionne sur la valeur */
                    offset=0;
                    c=fgetc(fichier);
                    while ((c!='[') && (c!=EOF)) /* Tant qu'on est pas sur le prochaine [layer] */
                    {
                        nbcar++;
                        if (c==',') nbvalue++;
                        offset++;
                        c=fgetc(fichier);
                    }
                }

            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;

    if (trouve==0)
    {
        printf("\n balise %s non trouvee",search_balise);
        return 0;
    }

    //printf("\n nbcar : %d",nbcar);

    data_file = malloc((nbcar+2)*sizeof(int));
    //rdata = malloc((nbvalue+2)*sizeof(int));

    fichier = fopen(fileName, "r");
    if (fichier==NULL)
    {
        printf("\n Erreur ouverture fichier");
    }

    nbcar = 0;
    nbvalue = 0;

    c = fgetc(fichier);
    while (c!=EOF)
    {
        if (c=='t')
        {

            c=fgetc(fichier);
            if (c=='y')
            {
                while (c!='=')
                {
                    c=fgetc(fichier);
                }
                c=fgetc(fichier);


                offset = 0;
                while (c!='\n')
                {
                    balise[offset]=c;
                    offset++;
                    c=fgetc(fichier);
                }
                balise[offset]='\0';


                if (compare(search_balise,balise)==1)
                {

                    while(c!='=') c=fgetc(fichier);
                    offset=0;
                    c=fgetc(fichier);
                    while ((c!='[') && (c!=EOF))
                    {
                        data_file[offset]=c;
                        offset++;
                        c=fgetc(fichier);
                    }
                    break;
                }
            }
        }

        c=fgetc(fichier);
    }
    fclose(fichier);
    fichier = NULL;
    data_file[offset]='\0';








    token = strtok(data_file, ",");


    offset = 0;
    while( token != NULL )
    {
        //*(rdata+offset) = atoi(((token)));
        t[offset] = atoi(((token)));
        offset++;
        token = strtok(NULL,",");
    }
    free(data_file);
    //free(token);
    data_file=NULL;
    token=NULL;

    //*(rdata+offset) = endValue;

    //return rdata;
    return 0;
}
