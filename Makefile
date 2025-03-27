CC=clang
LIBS=-lraylib -lm

emulator: emulator.c
	$(CC) emulator.c -o emulator $(LIBS) -L./lib/ -I./lib/

clean:
	rm -f emulator
