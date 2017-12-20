#ifndef PC_VERSION
    #include <kos.h>
    #include <oggvorbis/sndoggvorbis.h>
#else
#endif

#ifndef PC_VERSION
sfxhnd_t sound[15];
int initSfx = 0;
#else
#endif

void loadSound(char *filename,int soundNumber)
{
#ifndef PC_VERSION
    sound[soundNumber] = snd_sfx_load (filename);
#else
#endif
}


void playSound(int soundNumber,int numberLoop)
{
#ifndef PC_VERSION
    int res;
    res = snd_sfx_play(sound[soundNumber],255,128);
#else
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
#endif
}

void clearAllSound (void)
{
#ifndef PC_VERSION
    snd_sfx_unload_all();
#else
#endif
}

void quitSoundEngine()
{
#ifndef PC_VERSION
#else
#endif
}

void initSfxEngine(void)
{
#ifndef PC_VERSION
    sndoggvorbis_init();
#else
#endif
}

void playMusic(char *filename)
{
#ifndef PC_VERSION
    sndoggvorbis_start(filename,0);
#else
#endif
}

void stopMusic(void)
{
#ifndef PC_VERSION
    sndoggvorbis_stop();
#else
#endif
}

void quitSfxEngine(void)
{
#ifndef PC_VERSION
    sndoggvorbis_shutdown();
#else
#endif
}
