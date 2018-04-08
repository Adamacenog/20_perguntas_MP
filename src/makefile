IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR =../lib

LIBS=-lm

_DEPS = Arvore.h Funcs.h Vinte_Perguntas.h Jogo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Arvore.o Funcs.o Vinte_Perguntas.o Jogo.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Jogo_20_Perguntas: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
