CC=avr-gcc
OBJCPY=avr-objcopy

OPT=-Og
DBG=-gdwarf-2
CPU=-mmcu=atmega32
F_CPU=-DF_CPU=8000000UL
BAUD=-DBAUD=9600

INCS=$(foreach DIR,$(INC_DIRS),-I$(DIR))

WARNINGS=-Wall -pedantic -Wextra

CFLAGS=$(CPU) $(DBG) $(INCS) $(OPT) $(F_CPU) $(BAUD) $(WARNINGS)
LDFLAGS=-Wl,--gc-sections -Wl,--relax

BUILD_DIR=build
INC_DIRS=.
LIB_DIRS=
CODE_DIRS=.
VPATH=$(CODE_DIRS)

SRC=$(foreach DIR,$(CODE_DIRS),$(wildcard $(DIR)/*.c))
OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))

PROJ=atmega32

HEX =ihex

all: $(BUILD_DIR)/$(PROJ).hex
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="


$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(PROJ).elf: $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(PROJ).hex: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) -O $(HEX) $^ $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)

simulate:
	start .\Proteus\atmega32.pdsprj

.PHONY: all clean debug simulate