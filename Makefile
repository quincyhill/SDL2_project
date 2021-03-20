# SRC_FILES specifies my cpp source files
SRC_FILES = main.cpp image_funcs.cpp window_logic.cpp key_presses.cpp

# OBJS specifies which files to compile as part of the project
OBJS=main.o image_funcs.o window_logic.o key_presses.o

# CXX specifies which C++ compiler we're using
CXX=g++

# DEPS specifies the set of header files the c++ files depend on.
DEPS=image_funcs.hpp window_logic.hpp key_presses.hpp

# CXX_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXX_FLAGS=-w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS=-lSDL2 -lSDL2_image

# TARGET speciies the name of our exectuable
TARGET=game

# This is the target that compiles our executable
build: $(OBJS)
	$(CXX) $(OBJS) $(CXX_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

# I need to see what the .PHONY means again
.PHONY: clean

clean:
	rm -f *.o
