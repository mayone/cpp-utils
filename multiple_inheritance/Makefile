CC = g++
CFLAGS  += -I. -std=c++20
LDFLAGS += -L.
#DEF += -D
#PROJDIRS = ./
#SRCS = $(sort $(shell find $(PROJDIRS) -type f -name "*.cpp"))
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o: %.cpp
#.c.o:
	$(CC) $(CFLAGS) $(DEF) -c $? -o $@

.PHONY: run clean

run:
	./$(EXEC)
clean:
	rm -f $(EXEC) $(OBJS)
