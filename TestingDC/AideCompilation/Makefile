all: rm-elf main.elf

include $(KOS_BASE)/Makefile.rules

OBJS =	main.o ../gfxengine_shared/bfg_gfxEngine.o ../gfxengine_shared/bfg_spriteEngine.o ../gfxengine_shared/bfg_tilemaps.o ../gfxengine_shared/bfg_sfxEngine.o ../gfxengine_shared/bfg_scrollMap.o ../gfxengine_shared/bfg_rndEngine.o

KOS_LOCAL_CFLAGS = -I$(KOS_BASE)/addons/zlib
	
clean:
	-rm -f main.elf $(OBJS)


dist:
	-rm -f $(OBJS)
	$(KOS_STRIP) main.elf
	
rm-elf:
	-rm -f main.elf


main.elf: $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $@ $(KOS_START) $^ -lpng -lz -lm -ltremor $(KOS_LIBS)
romdisk.img:
	$(KOS_GENROMFS) -f $@ -d romdisk -v
	

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk $@
	
run: main.elf
	$(KOS_LOADER) $<


