CC=g++
CFLAGS=-c -g -O0 -std=c++11 -Wall
LDFLAGS= -lSDL2 -lSDL2_image
SOURCES=src/chess.cpp src/piece.cpp src/pawn.cpp src/knight.cpp src/rook.cpp src/bishop.cpp src/queen.cpp src/king.cpp src/SDL_Manager.cpp src/ai.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f core $(EXECUTABLE) $(OBJECTS)
