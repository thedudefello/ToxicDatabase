##############################################################################

TARGET = RECYCLE
SRC = recycle.c resource.rc
CFLAGS = -D_UNICODE -DUNICODE -O2 -s
LDFLAGS = -lComctl32 -s -mwindows
CC = gcc # https://www.msys2.org/
WINDRES = windres
OBJS = recycle.o resource.o

##############################################################################

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

recycle.o: recycle.c
	$(CC) $(CFLAGS) -c $< -o $@

resource.o: resource.rc
	$(WINDRES) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

##############################################################################