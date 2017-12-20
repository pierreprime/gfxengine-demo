#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Window* gWindow = NULL;

	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,480, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);

	if( gWindow == NULL )
	{
        	    printf( "\nWindow could not be created! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		printf("\n ça marche !! \n");
	}

	while(1) /* = while (1) */
	{
	}

   return 0;
}
