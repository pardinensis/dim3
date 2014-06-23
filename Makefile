CC = g++
CFLAGS = -std=c++11
LFLAGS = -lSDL2 -lGL

SRCDIR = src

EXE = dim3


SOURCES = $(wildcard $(SRCDIR)/*.cpp)

all: $(EXE)

clean:
	rm -f $(EXE)

dim3: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LFLAGS) -o $(EXE)
