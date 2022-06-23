OBJ_FILES = obj/main.o

# This is still valid
CXX=g++

CXXFLAGS=-g -Wall

# Figure out how to use this for folders
IDIR=include

SRC=src

OBJ=obj

# LDFLAGS specifies the libraries we're linking against
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

TARGET=bin/game

build-debug: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET) 

# Might need to use macros so to not require the other object files
build-main-only: obj/main.o
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

# This builds the main.o object file, maybe update it eventually
obj/main.o: src/main.cpp
	$(CXX) -c $< -o $@

install: 
# would also have to copy over assets and make sure the path that are referenced in the code are valid so yea it would be a release build
	echo "Nothing yet"

uninstall:
	echo "Nothing yet either"

# I need to see what the .PHONY means again
.PHONY: clean

clean:
	rm -f $(OBJ)/*.o $(TARGET)