.SUFFIXES : .cc .o

TARGETS = reply_admin minimal_fighter 

OBJECTS1 = reply_admin.o
OBJECTS2 = minimal_fighter.o

CC = g++
CPPFLAGS = -g -c

all : $(TARGETS)

reply_admin : $(OBJECTS1)
	$(CC) -o $@ $^

minimal_fighter : $(OBJECTS2)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(TARGETS) 
