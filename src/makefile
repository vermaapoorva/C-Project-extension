CC = gcc
CFLAGS = -g -Wall -Werror -pedantic -std=c99
LFLAGS = `sdl2-config --cflags --libs`


# Build rule for final executable
all: main.o game_states.o init.o destroy.o move.o render.o utils.o
	$(CC) $(CFLAGS) main.o core_gameplay/game_states.o objects/init.o objects/destroy.o core_gameplay/move.o objects/render.o misc/utils.o $(LFLAGS) -lSDL2_ttf -lSDL2_image -lSDL2_mixer -o pong

# Build rules for .o files
main.o: main.c misc/defs.h
	$(CC) $(CFLAGS) main.c -c -o main.o

game_states.o: core_gameplay/game_states.c misc/defs.h
	$(CC) $(CFLAGS) core_gameplay/game_states.c -c -o core_gameplay/game_states.o

init.o: objects/init.c misc/defs.h
	$(CC) $(CFLAGS) objects/init.c -c -o objects/init.o

destroy.o: objects/destroy.c misc/defs.h
	$(CC) $(CFLAGS) objects/destroy.c -c -o objects/destroy.o

move.o: core_gameplay/move.c misc/defs.h
	$(CC) $(CFLAGS) core_gameplay/move.c -c -o core_gameplay/move.o

render.o: objects/render.c misc/defs.h
	$(CC) $(CFLAGS) objects/render.c -c -o objects/render.o

utils.o: misc/utils.c misc/defs.h
	$(CC) $(CFLAGS) misc/utils.c -c -o misc/utils.o

# Rule to install dependencies
dependencies:
	echo "Installing libsdl2-dev"
	sudo apt-get install libsdl2-dev
	echo "Installing libsdl2-image-dev"
	sudo apt-get install libsdl2-image-dev
	echo "Installing libsdl2-ttf-dev"
	sudo apt-get install libsdl2-ttf-dev
	echo "Installing libsdl2-mixer-dev"
	sudo apt-get install libsdl2-mixer-dev

# Rule to clean generated files
clean:
	rm -f misc/*.o
	rm -f core_gameplay/*.o
	rm -f objects/*.o
	rm -f *.o
	rm -f pong

.PHONY: clean
