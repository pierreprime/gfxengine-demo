#ifndef PC_VERSION
#include <kos.h>
#include <oggvorbis/sndoggvorbis.h>
#else
#include "SDL_mixer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#endif

#include "../gfxengine_shared/bfg_sfxEngine.h"

#ifndef PC_VERSION
sfxhnd_t sound[MAX_SAMPLES];
int initSfx = 0;
#else
Mix_Music *music = NULL;
int flags=MIX_INIT_OGG;
int initted;

Mix_Chunk *sample[MAX_SAMPLES];

#endif

void initSfxEngine(void)
{
#ifndef PC_VERSION
    sndoggvorbis_init();
#else
    int i;
    music = NULL;
    initted=Mix_Init(flags);
    if((initted&flags) != flags)
    {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        // start SDL with audio support
    }
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    }

    for (i=0;i<MAX_SAMPLES;i++) sample[i] = NULL;
    Mix_AllocateChannels(16);
#endif
}

void loadSound(char *filename,int soundNumber)
{
#ifndef PC_VERSION
    sound[soundNumber] = snd_sfx_load (filename);
#else
    sample[soundNumber]=Mix_LoadWAV(filename);
    if(!sample[soundNumber])
    {
        printf("Mix_LoadWAV: %s %s\n", filename,Mix_GetError());
        // handle error
    }
#endif
}


void playSound(int soundNumber,int numberLoop)
{
#ifndef PC_VERSION
    int res;
    res = snd_sfx_play(sound[soundNumber],255,128);
#else
    if(Mix_PlayChannel(-1, sample[soundNumber],0)==-1)
    {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }

#endif
}

/*
  0 - pas clearé
  1 - clearé
*/
void clearSound(int soundNumber)
{
#ifndef PC_VERSION
    snd_sfx_unload(sound[soundNumber]);
#else
    if (sample[soundNumber] != NULL)
    {
        Mix_FreeChunk(sample[soundNumber]);
        sample[soundNumber]=NULL;
    }
#endif
}

void clearAllSound (void)
{
#ifndef PC_VERSION
    snd_sfx_unload_all();
#else
    int i;
    for (i=0; i<MAX_SAMPLES; i++)
    {
        clearSound(i);
    }
#endif
}

/*
	Dreamcast : Pour boucler ? : sndoggvorbis_isplaying() == 0
*/
void playMusic(char *filename,int loop)
{
#ifndef PC_VERSION
    sndoggvorbis_start(filename,0);
#else
    int l;

    if (loop==1) l=-1; else l=1;
    music=Mix_LoadMUS(filename);
    if(!music)
    {
        printf("Mix_LoadMUS(\"%s\"): %s\n", filename,Mix_GetError());
    }
    if(Mix_PlayMusic(music, l)==-1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
#endif
}



void stopMusic(void)
{
#ifndef PC_VERSION
    sndoggvorbis_stop();
#else
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music=NULL;
#endif
}

int isMusicPlay(void)
{
    #ifndef PC_VERSION
    return sndoggvorbis_isplaying();
#else
    return Mix_PlayingMusic();
#endif
}

void quitSfxEngine(void)
{
#ifndef PC_VERSION
    sndoggvorbis_shutdown();
#else
    stopMusic();
    clearAllSound();
#endif
}
