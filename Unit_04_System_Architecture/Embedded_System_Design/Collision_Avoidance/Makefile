CC=gcc

OPT=-O0
DBG=-g
WARNINGS=-Wall -Wextra -Wsign-conversion -Wconversion
DEPFLAGS=-MP -MD

INCS=$(foreach DIR,$(INC_DIRS),-I$(DIR))
LIBS=$(foreach DIR,$(LIB_DIRS),-L$(DIR))
LIBS+=

CFLAGS=$(DBG) $(OPT) $(INCS) $(LIBS) $(WARNINGS) $(DEPFLAGS)

INC_DIRS=. ./include/
CODE_DIRS=. src
LIB_DIRS=
BUILD_DIR=build
VPATH=$(CODE_DIRS)

SRC=$(foreach DIR,$(CODE_DIRS),$(wildcard $(DIR)/*.c))

OBJ=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
DEP=$(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.d)))


EXEC=Main.exe

all: $(BUILD_DIR)/$(EXEC)
	@echo "========================================="
	@echo "              BUILD SUCCESS              "
	@echo "========================================="
	@# @cd ./$(BUILD_DIR) && ./$(EXEC) && cd ..

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c  $< -o $@ $(CFLAGS)
	
$(BUILD_DIR)/$(EXEC): $(OBJ)
	$(CC)  $^ -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir $@

clean:
	rm -fR $(BUILD_DIR)

-include $(DEP)

.PHONY: all clean
