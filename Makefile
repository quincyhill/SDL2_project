SRC_FILES = src/main.cpp src/media_funcs.cpp src/window_logic.cpp src/key_presses.cpp src/L_Texture.cpp src/L_Button.cpp

OBJ_FILES = obj/main.o obj/media_funcs.o obj/window_logic.o obj/key_presses.o obj/L_Texture.o obj/L_Button.o

DEP_FILES = include/L_Texture.hpp include/L_Button.hpp include/key_presses.hpp include/media_funcs.hpp include/window_logic.hpp

CXX=g++

# Figure out how to use this for folders
IDIR=include

SRCDIR=src

ODIR=obj

# CXX_FLAGS specifies the additional compilation options we're using
# This time im allowing warnings to be shown
# -w , for eg, suppresses all warnings
CXX_FLAGS=""

# LDFLAGS specifies the libraries we're linking against
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

TARGET=build/game

build: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET) 
	# $(CXX) $(OBJ_FILES) $(CXX_FLAGS) $(LDFLAGS) -o $(TARGET) 

# This create final build for main only test
build-main-only: obj/main.o
	$(CXX) $^ -o $(TARGET)

# This builds the main.o object file
obj/main.o: src/main.cpp include/window_logic.hpp include/media_funcs.hpp
	g++ -g -c $< -o $@

obj/media_funcs.o: src/media_funcs.cpp include/media_funcs.hpp include/window_logic.hpp include/key_presses.hpp include/L_Texture.hpp
	g++ -g -c $< -o $@

obj/window_logic.o: src/window_logic.cpp include/window_logic.hpp include/key_presses.hpp include/media_funcs.hpp include/L_Texture.hpp include/L_Button.hpp
	g++ -g -c $< -o $@

obj/key_presses.o: src/key_presses.cpp include/key_presses.hpp include/window_logic.hpp include/media_funcs.hpp
	g++ -g -c $< -o $@

obj/L_Texture.o: src/L_Texture.cpp include/L_Texture.hpp include/media_funcs.hpp include/window_logic.hpp
	g++ -g -c $< -o $@

obj/L_Button.o: src/L_Button.cpp include/L_Button.hpp include/L_Texture.hpp
	g++ -g -c $< -o $@

install: 
	echo "Nothing yet"

uninstall:
	echo "Nothing yet either"

# I need to see what the .PHONY means again
.PHONY: clean

clean:
	rm -f obj/*.o $(TARGET)
