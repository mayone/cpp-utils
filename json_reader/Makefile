CC = gcc
CFLAGS  += -I. -I./cjson
LDFLAGS += -L./cjson -lcjson -Wl,-rpath,'$$ORIGIN'/cjson
CJSON_VER=1.7.15
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
EXEC = main

all: cjson $(EXEC)

cjson:
	wget "https://github.com/DaveGamble/cJSON/archive/refs/tags/v$(CJSON_VER).tar.gz"
	tar zxvf "v$(CJSON_VER).tar.gz" --transform "s/cJSON-$(CJSON_VER)/cjson/"
	rm "v$(CJSON_VER).tar.gz"
	$(MAKE) -C cjson

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o: %.c
# .c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(EXEC)
clean:
	rm -rf $(EXEC) $(OBJS) cjson
