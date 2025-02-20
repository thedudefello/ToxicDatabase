##############################################################################

TARGET = ALERTA
SRC = alerta.c resource.rc
CFLAGS = -D_UNICODE -DUNICODE -O2 -s
LDFLAGS = -s -mwindows
CC = gcc
WINDRES = windres
OBJS = alerta.o resource.o

##############################################################################

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

alerta.o: alerta.c
	$(CC) $(CFLAGS) -c $< -o $@

resource.o: resource.rc
	$(WINDRES) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

##############################################################################