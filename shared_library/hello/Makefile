CC = gcc
CFLAGS  += -I. -fPIC
LDFLAGS += -L. -shared
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = libhello.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o: %.c
# .c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(TARGET)
clean:
	rm -f $(TARGET) $(OBJS)
