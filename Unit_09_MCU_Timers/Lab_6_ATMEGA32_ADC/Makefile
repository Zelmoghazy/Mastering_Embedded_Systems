CC=avr-gcc
OBJCPY=avr-objcopy

OPT=-O0
DBG=-g -gdwarf-2
CPU=-mmcu=atmega328p
F_CPU=-DF_CPU=8000000UL
BAUD=-DBAUD=9600

INCS=$(foreach DIR,$(INC_DIRS),-I$(DIR))

WARNINGS=-Wall -pedantic -Wextra

CFLAGS=$(CPU) $(DBG) $(INCS) $(OPT) $(F_CPU) $(BAUD) $(WARNINGS) -save-temps
LDFLAGS=-Wl,--gc-sections -Wl,--relax

BUILD_DIR=build
INC_DIRS=. ./include/ ./HAL/
LIB_DIRS=
CODE_DIRS=. src HAL
VPATH=$(CODE_DIRS)

SRC=$(foreach DIR,$(CODE_DIRS),$(wildcard $(DIR)/*.c))
OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))

PROJ=atmega32

HEX=ihex

all: $(BUILD_DIR)/$(PROJ).hex
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="


$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(PROJ).elf: $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(PROJ).hex: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) -O $(HEX) -R .eeprom  $^ $@

$(BUILD_DIR):
	mkdir $@

clean: 
	rm -fR $(BUILD_DIR)

flash: all
	avrdude -v -V -patmega328p -cusbasp -Pusb "-Uflash:w:$(BUILD_DIR)/$(PROJ).hex"

simulate: all
	start .\Proteus\atmega32.pdsprj

.PHONY: all clean debug simulate