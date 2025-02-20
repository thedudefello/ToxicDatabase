##############################################################################

TARGET = MOUSEMVD.EXE
CFLAGS = -D_UNICODE -DUNICODE -O2 -s
LDFLAGS = -mwindows -municode -s
CC = gcc
WINDRES = windres
OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) resource.o

##############################################################################

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

resource.o: resource.rc
	$(WINDRES) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

##############################################################################