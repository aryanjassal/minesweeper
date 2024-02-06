# Useful directories variable
SRC_DIR := src
INC_DIR := include
OUT_DIR := build
LIB_DIR := lib

# The source files to be compiled
C_SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
CPP_SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
INC_FILES := $(shell find $(INC_DIR) -name "*.hpp" -o -name "*.h")

# The object files that the source files will be compiled into
C_OBJ_FILES := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(C_SRC_FILES))
CPP_OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.o, $(CPP_SRC_FILES))
OBJ_FILES := $(C_OBJ_FILES) $(CPP_OBJ_FILES)

# The output file that the program will create after compiling everything
OUT_FILE := $(OUT_DIR)/minesweeper

# The C++ compiler
# The '@' symbol just silences the line, meaning that the command will not be echoed to the console
CC := @g++

MKDIR := @mkdir -p

# The flags to be passed to the C compiler (the $CC)
COMPILER_FLAGS = -I$(INC_DIR) -g $(DEBUG)

# The libraries that our executable is being linked against
LIBRARIES := -L$(LIB_DIR) -lglfw3

# Some miscallenous commands which will prove useful later (if ever)
CP := @cp
ECHO := @echo
RM := @rm -rf -- 

# The default target that compiles the entire project
all: compile run

set_debug:
DEBUG := -DDEBUG

debug: set_debug all

prepare:
	$(ECHO) "Compiling project..."

compile : prepare $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(COMPILER_FLAGS) $(LIBRARIES) -o $(OUT_FILE)
	$(ECHO) "Compilation done."

$(C_OBJ_FILES) : $(OUT_DIR)%.o : $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $^ $(COMPILER_FLAGS) $(LIBRARIES) -c -o $@

$(CPP_OBJ_FILES) : $(OUT_DIR)%.o : $(SRC_DIR)%.cpp
	$(MKDIR) $(dir $@)
	$(CC) $^ $(COMPILER_FLAGS) $(LIBRARIES) -c -o $@

run:
	$(ECHO) "Running project..."
	@./$(OUT_FILE)

clean:
	$(RM) $(OUT_DIR)
	$(RM) $(OUT_FILE)
