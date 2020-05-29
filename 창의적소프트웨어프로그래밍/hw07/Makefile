.SUFFIXES : .cc .o

TARGETS = matrix draw_shape

OBJECTS1 = matrix.o matrix_main.o
OBJECTS2 = draw_shape.o draw_shape_main.o


CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

matrix : $(OBJECTS1)
	$(CC) -o $@ $^

draw_shape : $(OBJECTS2)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(TARGETS) 
