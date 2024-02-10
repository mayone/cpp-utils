CC = gcc
CFLAGS  += -I./cjson
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS += -L./cjson -lcjson -Wl,-rpath,'$$ORIGIN'/lib
	LIB_EXT=so
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L./cjson -lcjson
	LIB_EXT=dylib
endif
CJSON_VER=1.7.17
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBS = lib/libcjson.$(LIB_EXT)
EXEC = main

all: cjson $(LIBS) $(EXEC)

cjson:
	wget "https://github.com/DaveGamble/cJSON/archive/refs/tags/v$(CJSON_VER).tar.gz"
	tar zxvf "v$(CJSON_VER).tar.gz" -s "/cJSON-$(CJSON_VER)/cjson/"
	rm "v$(CJSON_VER).tar.gz"
	# $(MAKE) -C cjson

lib/lib%.$(LIB_EXT): %
	$(MAKE) -C $^
	cp $^/lib$^.$(LIB_EXT) lib
	# Changing Dynamic Library IDs
	# install_name_tool -id @rpath/lib$^.$(LIB_EXT) lib/lib$^.$(LIB_EXT)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	# Changing Loader Paths
	install_name_tool -change libcjson.$(LIB_EXT).$(CJSON_VER) @loader_path/lib/libcjson.$(LIB_EXT) $@
%.o: %.c
# .c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(EXEC)
clean:
	rm -rf $(EXEC) $(OBJS) $(LIBS) cjson
