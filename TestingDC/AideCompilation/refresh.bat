rm *.o
rm *.bin
rm *.img
make
sh-elf-objcopy -O binary -R .stack main.elf lwp.bin
dcscram.exe lwp.bin 1ST_READ.bin