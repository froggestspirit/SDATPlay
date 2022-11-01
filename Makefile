C ?= gcc
CFLAGS := -Wall -fPIC
AR := ar

LDFLAGS := -lm -lportaudio -L./ -lsdatplay

LIB_SRCS := src/*.c

LIB_HEADERS := src/*.h

SRCS := main.cpp

HEADERS := sdatplay.h

.PHONY: all clean

all: libsdatplay.so sdatplay123 tidy
	@:

libsdatplay.a: $(LIB_SRCS) $(LIB_HEADERS)
	$(C) $(CFLAGS) $(LIB_SRCS) -c
	$(AR) -cvq libsdatplay.a *.o

libsdatplay.so: $(LIB_SRCS) $(LIB_HEADERS)
	$(C) $(CFLAGS) $(LIB_SRCS) -c
	$(C) $(CFLAGS) --shared -o libsdatplay.so *.o

sdatplay123: $(SRCS) $(HEADERS)
	g++ $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

tidy:
	$(RM) *.o

clean:
	$(RM) sdatplay123 sdatplay123.exe libsdatplay.a libsdatplay.so *.o
