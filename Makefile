CFLAGS=-Wall -Werror -lm -std=c11

DEPS=3dsfiles.h

msbt2txt: main.c msbt_*.c msbt_*.h 3dsfiles.c $(DEPS)
	gcc $^ -o $@ $(CFLAGS)