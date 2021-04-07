# SRC_FILES specifies my cpp source files
SRC_FILES = main.cpp media_funcs.cpp window_logic.cpp key_presses.cpp L_Texture.cpp

# OBJS specifies the object files that were created
OBJS = main.o media_funcs.o window_logic.o key_presses.o L_Texture.o

# CXX specifies which C++ compiler we're using
CXX=g++

# DEPS specifies the set of header files the c++ files depend on.
DEPS=media_funcs.hpp window_logic.hpp key_presses.hpp L_Texture.hpp

# CXX_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXX_FLAGS=-w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# TARGET speciies the name of our exectuable
TARGET=test_game

# This is the target that compiles our executable
build: $(OBJS)
	$(CXX) $(OBJS) $(CXX_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

# This will be used to install the application to /usr/local/bin practice doing installs / assets and whatnot
install: 
	# Nothing yet

# This will uninstall the executable from /usr/local/bin as well as assets
uninstall:
	# Nothing yet

# I need to see what the .PHONY means again
.PHONY: clean

clean:
	rm -f *.o
