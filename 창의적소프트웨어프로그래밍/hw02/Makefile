.SUFFIXES : .cc .o

TARGETS = draw_points prime_factorization radix_notation

OBJECTS1 = draw_points.o
OBJECTS2 = prime_factorization.o
OBJECTS3 = radix_notation.o

CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

draw_points : $(OBJECTS1)
	$(CC) -o $@ $^

prime_factorization : $(OBJECTS2)
	$(CC) -o $@ $^

radix_notation : $(OBJECTS3)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(TARGETS) 
