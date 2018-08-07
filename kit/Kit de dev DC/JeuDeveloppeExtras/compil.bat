rm *.bin
make
sh-elf-objcopy -O binary -R .stack main.elf dcpang.bin
dcscram.exe dcpang.bin dcpangs.bin