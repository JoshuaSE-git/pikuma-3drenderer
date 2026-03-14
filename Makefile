build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lm -o renderer

run:
	./renderer

clean:
	rm renderer*

debug:
	gcc -g -O0 -std=c99 ./src/*.c -lSDL2 -lm -o renderer-debug

memcheck:
	gcc -g -O0 -std=c99 ./src/*.c -lSDL2 -lm -o renderer-debug
	valgrind --leak-check=full ./renderer-debug
	rm renderer-debug
