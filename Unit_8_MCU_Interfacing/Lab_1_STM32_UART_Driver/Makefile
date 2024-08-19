CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCPY=arm-none-eabi-objcopy
SZ=arm-none-eabi-size

OPT=-O0
DBG=-gdwarf-2 -g
CPU=-mcpu=cortex-m3
STDLIB=--specs=nano.specs
FP=-mfloat-abi=soft
ISA=-mthumb

INCS=$(foreach DIR,$(INC_DIRS),-I$(DIR))

CFLAGS=$(CPU) $(DBG) $(INCS) $(OPT) $(STDLIB) $(FP) $(ISA)
ASFLAGS=$(CPU) $(DBG) $(FP) $(ISA)


BUILD_DIR=build
INC_DIRS=. ./inc/
LIB_DIRS=
CODE_DIRS=. src HAL/Keypad_Driver HAL/LCD_Driver
VPATH=$(CODE_DIRS)

SRC=$(foreach DIR,$(CODE_DIRS),$(wildcard $(DIR)/*.c))
ASM=$(foreach DIR,$(CODE_DIRS),$(wildcard $(DIR)/*.s))
OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
OBJ+=$(addprefix $(BUILD_DIR)/,$(notdir $(ASM:.s=.o)))


PROJ=STM32

STARTUP=startup_stm32f103x6

LS=STM32F103C6Tx_FLASH.ld

LDFLAGS=-T $(LS) --specs=nosys.specs -Wl,-Map="./$(BUILD_DIR)/Map.map" $(STDLIB) $(FP) $(ISA) -Wl,--start-group -lc -lm -Wl,--end-group

HEX =ihex
BIN =binary

all: $(BUILD_DIR)/$(PROJ).bin $(BUILD_DIR)/$(PROJ).hex $(BUILD_DIR)/$(PROJ).axf
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="
	@$(SZ) $(BUILD_DIR)/$(PROJ).elf
	

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(PROJ).elf: $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(PROJ).bin: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) -O $(BIN) $^ $@

$(BUILD_DIR)/$(PROJ).hex: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) -O $(HEX) $^ $@

$(BUILD_DIR)/$(PROJ).axf: $(BUILD_DIR)/$(PROJ).elf
	cp $^ $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)

debug: all
	uv4 -d .\Keil\STM32.uvprojx

gdb: all
	gdb-multiarch -ex "target remote localhost:50000" $(BUILD_DIR)/$(PROJ).elf

openocd: all
	openocd -c "gdb_port 50000" -f "C:\msys64\mingw64\share\openocd\scripts\interface\stlink-v2.cfg" -f "C:\msys64\mingw64\share\openocd\scripts\target\stm32f1x.cfg"

simulate: all
	start .\Proteus\stm32.pdsprj

flash: all
	st-flash --reset write $(BUILD_DIR)/$(PROJ).bin 0x08000000

.PHONY: all clean debug simulate flash
