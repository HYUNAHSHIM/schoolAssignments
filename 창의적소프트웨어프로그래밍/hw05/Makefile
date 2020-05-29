.SUFFIXES : .cc .o

TARGETS = simple_int_set message_book draw_shape sorted_array

OBJECTS1 = simple_int_set.o simple_int_set_main.o
OBJECTS2 = message_book.o message_book_main.o
OBJECTS3 = draw_shape.o draw_shape_main.o
OBJECTS4 = sorted_array.o sorted_array_main.o

CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

simple_int_set : $(OBJECTS1)
	$(CC) -o $@ $^

message_book : $(OBJECTS2)
	$(CC) -o $@ $^

draw_shape : $(OBJECTS3)
	$(CC) -o $@ $^

sorted_array : $(OBJECTS4)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(TARGETS) 
