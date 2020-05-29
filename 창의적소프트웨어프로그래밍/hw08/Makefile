.SUFFIXES : .cc .o

TARGETS = sorted_array new_vector

OBJECTS1 = sorted_array_main.o
OBJECTS2 = new_vector.o new_vector_main.o


CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

sorted_array : $(OBJECTS1)
	$(CC) -o $@ $^

new_vector : $(OBJECTS2)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(TARGETS) 
