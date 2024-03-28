# Variables which should be modified for each project
PKGS = glfw3
LIBS = glad=deps/glad.sh glm=deps/glm.sh stb=deps/stb.sh

# Useful directories variable
SRC_DIR := src
INC_DIR := include
OUT_DIR := build
EXT_DIR := external

# # Static files which will not be changed throughout development (usually libraries).
# # Note that all files must be in the output format and not the source format.
# STATIC_DIR := $(OUT_DIR)/$(EXT_DIR)
# STATIC_BUILD_FILES := $(wildcard $(STATIC_DIR)/*)
# # STATIC_BUILD_FILES := $(OUT_DIR)/glad.o $(OUT_DIR)/stb/stb_image.o

# The output file that the program will create after compiling everything
OUT_FILE := $(OUT_DIR)/$(notdir $(CURDIR))

# The source files to be compiled
C_SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
CPP_SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp" -not -name "main.cpp")
INC_FILES := $(shell find $(INC_DIR) -name "*.hpp" -o -name "*.h")

# The object files that the source files will be compiled into
C_OBJ_FILES := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(C_SRC_FILES))
CPP_OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.o, $(CPP_SRC_FILES))
OBJ_FILES := $(C_OBJ_FILES) $(CPP_OBJ_FILES)

MAIN_SRC := $(shell find $(SRC_DIR) -name "main.cpp")
MAIN_OBJ := $(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.o, $(MAIN_SRC))

# The C++ compiler
# The '@' symbol just silences the line, meaning that the command will not be echoed to the console
CXX := @g++

# The flags to be passed to the C compiler (the $CC)
CXXFLAGS = -I$(INC_DIR) -I$(EXT_DIR) -g $(DEBUG) $(args) $(shell pkg-config --cflags $(PKGS))

# The libraries that our executable is being linked against
# LIBRARIES := -L$(LIB_DIR) -lglfw3
LIBRARIES := $(shell pkg-config --libs $(PKGS))

# Pass this variable onto the scripts to ensure it is running from make
MAKING := true

export

# The default target to develop the program
dev: compile run

# Fetch the dependencies for the program
fetch: check_packages install_deps

# Compile the entire program
all: fetch compile run

# Sets the debug flag passed as a #define in all files (redundant?)
set_debug:
DEBUG := -DDEBUG

# Checks if all packages specified in LIBS exist
check_packages:
	@$(foreach PKG, $(PKGS), \
		pkg-config --exists $(PKG) || \
		(echo "Missing package: $(PKG)." && false);)

install_deps:
	@echo -e "Checking external dependencies..."
	@mkdir -p $(EXT_DIR)
	@$(foreach LIB, $(LIBS), \
			$(eval LIB_NAME := $(word 1,$(subst =, ,$(LIB)))) \
			$(eval LIB_SH := $(word 2,$(subst =, ,$(LIB)))) \
			if [ ! -d $(EXT_DIR)/$(LIB_NAME) ]; then \
				echo -e "Downloading $(EXT_DIR)/$(LIB_NAME)..."; \
				$(LIB_SH); \
				echo -e "Downloaded $(EXT_DIR)/$(LIB_NAME)"; \
			else \
				echo -e "$(LIB_NAME) already exists"; \
			fi;)

debug: set_debug all

prepare:
	@echo "Compiling project..."

compile : prepare $(OBJ_FILES) main
	$(CXX) $(filter-out $(OBJ_FILES) $(MAIN_OBJ), $(shell find $(OUT_DIR) -name *.o)) $(OBJ_FILES) $(MAIN_OBJ) $(CXXFLAGS) $(LIBRARIES) -o $(OUT_FILE)
	@echo "Compilation done."

$(C_OBJ_FILES) : $(OUT_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "Building $(basename $^)"
	$(CXX) $^ $(CXXFLAGS) $(LIBRARIES) -c -o $@

$(CPP_OBJ_FILES) : $(OUT_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "Building $(basename $^)"
	$(CXX) $^ $(CXXFLAGS) $(LIBRARIES) -c -o $@

main:
	@mkdir -p $(dir $(MAIN_OBJ))
	@echo "Building $(basename $(MAIN_SRC))"
	$(CXX) $(MAIN_SRC) $(CXXFLAGS) $(LIBRARIES) -c -o $(MAIN_OBJ)

run:
	@echo "Running project..."
	@./$(OUT_FILE)

# Only cleans files which are not marked static
clean:
	@rm -rf -- $(filter-out $(STATIC_BUILD_FILES), $(OBJ_FILES))
	@rm -rf -- $(OUT_FILE)

# Cleans all the files in the build directory (you should very rarely need to run this)
clean_all:
	@rm -rf -- $(OUT_DIR)
	@rm -rf -- $(EXT_DIR)
