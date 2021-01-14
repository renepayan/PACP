# Archivo Makefile para Tarea 8 - Filtro Sobel
PROYECTO=tarea8_Filtro_Sobel
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
