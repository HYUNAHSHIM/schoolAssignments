.SUFFIXES : .cc .o

TARGETS = calendar world_clock

OBJECTS1 = calendar.o calendar_main.o
OBJECTS2 = world_clock.o world_clock_main.o


CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

calendar : $(OBJECTS1)
	$(CC) -o $@ $^

world_clock : $(OBJECTS2)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(TARGETS) 
