SRC_DIR = src

SRC_ENTRIES = $(shell find $(SRC_DIR) -type d)
SRC_SUBDIRS = $(filter-out $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.h),$(SRC_ENTRIES))
# SRC_SUBDIRS := $(sort $(dir $(shell find $(SRC_DIR) -type d)))

BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
CC = g++
# SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/core/*.cpp) $(wildcard $(SRC_DIR)/graphics/*.cpp)
# SRC_FILES = $(shell find $(SRC_DIR) -name "*.cpp")
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name '*.h' -o -name '*.cpp' \))
OBJ_NAME = play
INCLUDE_PATHS = $(addprefix -I,$(SRC_SUBDIRS)) -Iinclude -Iinclude/SDL2/ -Iinclude/SDL2_image/ -Iinclude/SDL2_ttf/
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.3/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -lsdl2 -lsdl2_image -lsdl2_ttf

build-dev:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(DEBUG_DIR)/$(OBJ_NAME)

run-dev:
	./$(DEBUG_DIR)/$(OBJ_NAME)

clean:
	rm -rf $(DEBUG_DIR) ; mkdir $(DEBUG_DIR)