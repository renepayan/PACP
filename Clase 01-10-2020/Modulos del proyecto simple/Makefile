# Archivo Makefile simple
PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc
all: $(PROYECTO)
%.o:%.c
	$(CC) -c $< $(CFLAGS)
$(PROYECTO): muestreo.o procesamiento.o archivos.o
	$(CC) $^ -o $@ $(LDFLAGS)
#$(PROYECTO): muestreo.o procesamiento.o archivos.o
#	$(CC) muestreo.o procesamiento.o archivos.o -o $(PROYECTO) $(LDFLAGS)
#muestreo.o: muestreo.c
#	$(CC) -c muestreo.c $(CFLAGS)
#procesamiento.o: procesamiento.c
#	$(CC) -c procesamiento.c $(CFLAGS)
#archivos.o: archivos.c
#	$(CC) -c archivos.c $(CFLAGS)
#muestreo: muestreo.o archivos.o procesamiento.o
#	$(CC) muestreo.o archivos.o procesamiento.o -o $(PROYECTO) $(LDFLAGS)
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
