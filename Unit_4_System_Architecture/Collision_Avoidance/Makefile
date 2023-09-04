CC=gcc

INCS=-I.
OPT=-O0
DBG=-g

WARNINGS=-Wall -Wextra -Wsign-conversion -Wconversion

CFLAGS=$(DBG) $(OPT) $(INCS) $(WARNINGS)

SRC=$(foreach DIR,$(CODEDIRS),$(wildcard $(DIR)/*.c))

OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))

LIB=

BUILD_DIR=build
CODEDIRS=.

EXEC=Main.exe

all: $(BUILD_DIR)/$(EXEC)
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="
	@# @cd ./$(BUILD_DIR) && ./$(EXEC) && cd ..

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ 

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)