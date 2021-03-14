# SRC_FILES specifies my cpp source files
SRC_FILES = main.cpp my_image_funcs.cpp window_logic.cpp

# OBJS specifies which files to compile as part of the project
OBJS=main.o my_image_funcs.o window_logic.o

# CXX specifies which C++ compiler we're using
CXX=g++

# DEPS specifies the set of header files the c++ files depend on.
DEPS=my_image_funcs.hpp window_logic.hpp

# CXX_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXX_FLAGS=-w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS=-lSDL2 -lSDL2_image

# TARGET speciies the name of our exectuable
TARGET=game

# This is the target that compiles our executable
all: $(OBJS)
	$(CXX) $(OBJS) $(CXX_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

.PHONY: clean

clean:
	rm -f *.o
