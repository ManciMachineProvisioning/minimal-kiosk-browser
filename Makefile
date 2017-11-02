PROGRAM=provisioning-browser
OBJECTS=provisioning-browser.o

CC=gcc
CFLAGS=$(shell pkg-config --cflags webkit2gtk-4.0)
CFLAGS+= -Wall -g

LDFLAGS=$(shell pkg-config --libs webkit2gtk-4.0)

all: $(PROGRAM)

provisioning-browser: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(PROGRAM)

clean:
	rm -rf $(OBJECTS) $(PROGRAM)

%.o : %.c
	$(CC) $(CFLAGS) -c $<
