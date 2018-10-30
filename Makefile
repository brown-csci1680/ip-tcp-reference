CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -D_REENTRANT -DCOLOR \
	-D__BSD_VISIBLE -DREADLINE

INCLUDES=-Isupport -I.
LDFLAGS = -Llib -lpthread -lipref -lreadline

HEADERS=$(wildcard *.h)
SRCS=$(wildcard *.c)

all: node

node: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

clean:
	rm -fv *.o node
