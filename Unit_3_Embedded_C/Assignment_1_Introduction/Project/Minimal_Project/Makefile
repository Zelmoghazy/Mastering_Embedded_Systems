CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCPY=arm-none-eabi-objcopy

INCS=-I.
OPT=-Og
DBG=-gdwarf-2
CPU=-mcpu=cortex-m3

CFLAGS=$(CPU) $(DBG) $(INCS) $(OPT) -mcpu=cortex-m3 --specs=nano.specs -mfloat-abi=soft -mthumb
ASFLAGS=$(CPU) $(DBG) -mcpu=cortex-m3 -mfloat-abi=soft -mthumb

SRC=$(foreach DIR,$(CODEDIRS),$(wildcard $(DIR)/*.c))
ASM=$(foreach DIR,$(CODEDIRS),$(wildcard $(DIR)/*.s))
OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
OBJ+=$(addprefix $(BUILD_DIR)/,$(notdir $(ASM:.s=.o)))

LIB=

BUILD_DIR=build
CODEDIRS=.

PROJ=STM32

STARTUP=startup_stm32f103x6

LS=STM32F103C6Tx_FLASH.ld

LDFLAGS=-T $(LS) --specs=nosys.specs -Wl,-Map="./$(BUILD_DIR)/Map.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

HEX =-O ihex
BIN =-O binary

all: $(BUILD_DIR)/$(PROJ).bin $(BUILD_DIR)/$(PROJ).hex
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(PROJ).elf: $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(PROJ).bin: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) $(BIN) $^ $@

$(BUILD_DIR)/$(PROJ).hex: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) $(HEX) $^ $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)