#ifndef GFXENGINEGBL_H
#define GFXENGINEGBL_H

int test;

#ifdef PC_VERSION
	#include "./Gfxengine/bfg_GfxEngine_PC.h"
#else
	#include "./Gfxengine/bfg_GfxEngine_Dreamcast.h"	
#endif

#endif
