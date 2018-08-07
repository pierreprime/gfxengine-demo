#include <stdio.h>
#include "../gfxEngine_shared/bfg_GfxEngine.h"

int main(int argc, char *argv[])
{
	initGfxEngine();
	
	loadImageTra("cd/DATA/hello.png",0,512,512);
	
	while (1)
	{
		prepareEcritureVideoGlobale();
        prepareEcritureVideoTra();

        blitImageTra(0,0,0);
		
		termineEcritureVideoTra();
        termineEcritureVideoGlobale();
	}
}