CC=gcc
CFLAGS=-I$(IDIR) -g

IDIR=includes
ODIR=obj
SRCDIR=src

LIBS=-lgmp -lcurl -lpthread

_DEPS = database.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cprime.o database.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cprime: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

install:
	@mv cprime /usr/bin

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(INCDIR)/*~
