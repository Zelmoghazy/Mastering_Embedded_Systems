CC=arm-none-eabi-gcc.exe
AS=arm-none-eabi-as.exe
LD=arm-none-eabi-ld.exe
MCPU=-mcpu=arm926ej-s
OBJCPY=arm-none-eabi-objcopy.exe
QEMU=qemu-system-arm.exe
Q_FLAGS=-s -S -M versatilepb -m 128M -nographic -kernel
DBG=-g

all:
	@$(CC) -c -I . $(DBG) $(MCPU) uart.c -o uart.o
	@$(CC) -c -I . $(DBG) $(MCPU) app.c -o app.o
	@$(AS) $(MCPU) $(DBG) startup.s -o startup.o
	@$(LD) -T linker_script.ld -Map="Map_file.map" startup.o app.o uart.o -o app.elf
	@$(OBJCPY) -O binary app.elf app.bin
	@$(QEMU) $(Q_FLAGS) app.elf

debug:
	gdb-multiarch -ex "target remote localhost:1234" app.elf

clean:
	rm *.o
	rm *.map
	rm *.elf
	rm *.bin