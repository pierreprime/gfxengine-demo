#ifndef GFXENGINEGBL_H
#define GFXENGINEGBL_H

#ifdef PC_VERSION
	#include "./Gfxengine/bfg_GfxEngine_PC.h"
#else
	#include "./Gfxengine/bfg_GfxEngine_Dreamcast.h"
#endif

#endif

#include "bfg_fileEngine.h"
#include "bfg_rndEngine.h"
#include "bfg_tilesmaps.h"
#include "bfg_scrollMap.h"
#include "bfg_sfxEngine.h"
#include "bfg_SpriteEngine.h"
#include "bfg_WriteEngine.h"
