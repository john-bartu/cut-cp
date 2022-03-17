# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy
all: program clone fork


program.o: program.c
	$(CCOMP) -c $(OPT) program.c

program: program.o
	$(LOADER) $(OPT) program.o -o program $(LIB)


clone.o: clone.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c

clone: clone.o pomiar_czasu.o
	$(LOADER) $(OPT) clone.o pomiar_czasu.o -o clone $(LIB)


fork.o: fork.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c

fork: fork.o pomiar_czasu.o
	$(LOADER) $(OPT) fork.o pomiar_czasu.o -o fork $(LIB)


pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o