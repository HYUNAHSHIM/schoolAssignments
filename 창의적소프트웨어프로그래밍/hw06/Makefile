.SUFFIXES : .cc .o

TARGETS = omok point2d parse_radix torrent

OBJECTS1 = omok.o omok_main.o
OBJECTS2 = point2d.o point2d_main.o
OBJECTS3 = parse_radix.o parse_radix_main.o
OBJECTS4 = torrent.o torrent_main.o

CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

omok : $(OBJECTS1)
	$(CC) -o $@ $^

point2d : $(OBJECTS2)
	$(CC) -o $@ $^

parse_radix : $(OBJECTS3)
	$(CC) -o $@ $^

torrent : $(OBJECTS4)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(TARGETS) 
