CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCPY=arm-none-eabi-objcopy

INCS=-I.
OPT=-Og
DBG=-gdwarf-2
CPU=-mcpu=cortex-m3 -mthumb -mfloat-abi=soft

WARNINGS=-Wall -Wextra -Wsign-conversion -Wconversion

CFLAGS=$(CPU) $(DBG) $(OPT) $(INCS) $(WARNINGS)
ASFLAGS=$(CPU) $(DBG)

SRC=$(foreach DIR,$(CODEDIRS),$(wildcard $(DIR)/*.c))
ASM=$(foreach DIR,$(CODEDIRS),$(wildcard $(DIR)/*.s))

OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
OBJ+=$(addprefix $(BUILD_DIR)/,$(notdir $(ASM:.s=.o)))

LIB=

BUILD_DIR=build
CODEDIRS=.

PROJ=STM32

LS=linker_script.ld

LDFLAGS=$(CPU) -nostartfiles --specs=nano.specs -T $(LS)  -Wl,-Map=$(BUILD_DIR)/Map_file.map 

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
	$(CC) $(LDFLAGS) $^ -o $@ 

$(BUILD_DIR)/$(PROJ).bin: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) $(BIN) $^ $@

$(BUILD_DIR)/$(PROJ).hex: $(BUILD_DIR)/$(PROJ).elf
	$(OBJCPY) $(HEX) $^ $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)