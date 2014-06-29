CC = g++
CFLAGS = -std=c++11 -Wall -Werror
LFLAGS = -lGL -lGLEW -lSDL2 -lSDL2_image

SRCDIR = src

EXE = dim3


SOURCES = $(wildcard $(SRCDIR)/*.cpp)

all: $(EXE)

clean:
	rm -f $(EXE)

dim3: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LFLAGS) -o $(EXE)
