CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCPY=arm-none-eabi-objcopy
CFLAGS=-mcpu=cortex-m3
INCS= I .
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIB=	
PROJ=STM32

all: $(PROJ).bin
	@echo "Success"

startup.o: startup.s
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@

$(PROJ).elf: $(OBJ) startup.o
	$(LD) -T linker_script.ld $(LIB) $(OBJ) startup.o -o $@

$(PROJ).bin: $(PROJ).elf
	$(OBJCPY) -O binary $< $@
