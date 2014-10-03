CC = g++
CFLAGS = -std=c++11 -Wall -Werror
LFLAGS = -lGL -lGLEW -lSDL2 -lSDL2_image

SRCDIR = src

EXE = dim3


SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.hpp)

all: $(EXE)

clean:
	rm -f $(EXE)

dim3: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(LFLAGS) -o $(EXE)
