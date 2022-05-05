CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=correcteur_1.o ATR.o Listes.o Levenshtein.o

correcteur_1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

correcteur_1.o: correcteur_1.c ATR.h Listes.h Levenshtein.h

ATR.o: ATR.c ATR.h

Listes.o: Listes.c Listes.h

Levenshtein.o: Levenshtein.c Levenshtein.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)
