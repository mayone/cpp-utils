CC = gcc
CFLAGS  += -I./hello
LDFLAGS += -L./hello -lhello -Wl,-rpath,'$$ORIGIN'/lib
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBS = lib/libhello.so
EXEC = main

all: $(LIBS) $(EXEC)

lib/lib%.so: %
	$(MAKE) -C $^
	cp $^/lib$^.so lib

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
