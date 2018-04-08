IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR =../lib

LIBS=-lm

_DEPS = Arvore.h Funcs.h Vinte_Perguntas.h Jogo.h catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Arvore.o Funcs.o Vinte_Perguntas.o Jogo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: Jogo_20_Perguntas Testa_Arvore

Jogo_20_Perguntas: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

Testa_Arvore: Testa_Arvore.cpp Arvore.c Funcs.c Vinte_Perguntas.c
	g++ -std=c++11 -o Testa_Arvore --coverage Testa_Arvore.cpp Arvore.c Funcs.c Vinte_Perguntas.c -I../include

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
