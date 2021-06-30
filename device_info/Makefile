CC = gcc
CFLAGS  += -I.
LDFLAGS += -L.
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o: %.c
# .c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(EXEC)
clean:
	rm -f $(EXEC) $(OBJS)
