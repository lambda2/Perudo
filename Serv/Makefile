#
#	Makefile de la partie serveur du projet Perudo.
#
CC=g++
CFLAGS=-lpthread
LDFLAGS=-lpthread
EXEC=serv

all: $(EXEC)
	rm *.o

serv: Gestionnaire.o Linker.o LServeur.o LDebug.o main.o
	$(CC) -o serv Gestionnaire.o Linker.o LServeur.o LDebug.o main.o $(LDFLAGS)

Gestionnaire.o: Gestionnaire.cpp Gestionnaire.hpp ../header.h
	$(CC) -o Gestionnaire.o -c Gestionnaire.cpp $(CFLAGS)

Linker.o: Linker.cpp Linker.h ../header.h ../LDebug.h
	$(CC) -o Linker.o -c Linker.cpp $(CFLAGS)
	
LServeur.o: LServeur.cpp LServeur.h ../header.h ../LDebug.h
	$(CC) -o LServeur.o -c LServeur.cpp $(CFLAGS)
	
LDebug.o: ../LDebug.cpp ../header.h ../LDebug.h
	$(CC) -o LDebug.o -c ../LDebug.cpp $(CFLAGS)
	
main.o: main.cpp ../header.h ../LDebug.h
	$(CC) -o main.o -c main.cpp $(CFLAGS)

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
