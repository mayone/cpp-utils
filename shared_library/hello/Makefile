CC = gcc
CFLAGS  += -I. -fPIC
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS += -L. -shared
	LIB_EXT=so
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L. -dynamiclib
	LIB_EXT=dylib
endif

# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = libhello.$(LIB_EXT)

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
