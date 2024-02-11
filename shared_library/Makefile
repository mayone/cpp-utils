CC = gcc
CFLAGS  += -I./hello
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS += -L./hello -lhello -Wl,-rpath,'$$ORIGIN'/lib
	LIB_EXT=so
else ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L./hello -lhello
	LIB_EXT=dylib
endif
# DEF += -D
# PROJDIRS = ./
# SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.c"))
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBS = lib/libhello.$(LIB_EXT)
EXEC = main

all: $(LIBS) $(EXEC)

lib/lib%.$(LIB_EXT): %
	$(MAKE) -C $^
	cp $^/lib$^.$(LIB_EXT) lib
	# Changing Dynamic Library IDs
	# install_name_tool -id @rpath/lib$^.$(LIB_EXT) lib/lib$^.$(LIB_EXT)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
ifeq ($(UNAME_S),Darwin)
	# Changing Loader Paths
	install_name_tool -change libhello.$(LIB_EXT) @loader_path/lib/libhello.$(LIB_EXT) $@
endif
%.o: %.c
# .c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(EXEC)
clean:
	rm -f $(EXEC) $(OBJS) $(LIBS)
	$(MAKE) -C ./hello clean
