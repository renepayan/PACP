# Archivo Makefile para Tarea 4 - Ventaneo
PROYECTO=tarea4_Ventaneo_Procesos
DESTDIR=/usr/local/bin
CFLAGS=-Wall -lpthread
LDFLAGS=-lm -lpthread
CC=gcc
SRCS=$(wildcard *.c)
all: $(PROYECTO)
%.o:%.c
	$(CC) -c $< $(CFLAGS)
$(PROYECTO): $(SRCS:.c=.o)
	$(CC) $^ -o $@ $(LDFLAGS)
clean:
	rm -rf *.a
	rm -rf $(PROYECTO)
	rm -rf *.o
	rm -rf ventana.dat
	rm -rf producto.dat
.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir -p $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)
uninstall:
	sudo rm -rf $(DESTDIR)/$(PROYECTO)
zip:
	zip $(PROYECTO).zip *.c Makefile
