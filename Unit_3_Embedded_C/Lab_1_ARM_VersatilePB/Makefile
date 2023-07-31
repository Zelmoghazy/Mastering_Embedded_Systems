CC=arm-none-eabi-gcc-12.2.0.exe
AS=arm-none-eabi-as.exe
LD=arm-none-eabi-ld.exe
OBJCPY=arm-none-eabi-objcopy.exe
QEMU=qemu-system-arm.exe
MCPU=-mcpu=arm926ej-s

all:
	@$(CC) -c -I . -g $(MCPU) uart.c -o uart.o
	@$(CC) -c -I . -g $(MCPU) app.c -o app.o
	@$(AS) $(MCPU) -g startup.s -o startup.o
	@$(LD) -T linker_script.ld -Map="Map_file.map" startup.o app.o uart.o -o app.elf
	@$(OBJCPY) -O binary app.elf app.bin
	@$(QEMU) -M versatilepb -m 128M -nographic -kernel app.bin

clean:
	rm *.o
	rm *.map
	rm *.elf
	rm *.bin