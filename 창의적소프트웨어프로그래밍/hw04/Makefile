.SUFFIXES : .cc .o

TARGETS = blackjack reply_admin minesweeper creative_stone

OBJECTS1 = blackjack.o
OBJECTS2 = reply_admin.o reply_admin_main.o
OBJECTS3 = minesweeper.o minesweeper_main.o
OBJECTS4 = creative_stone.o creative_stone_main.o

CC = g++
CPPFLAGS = -g -c -std=c++0x

all : $(TARGETS)

blackjack : $(OBJECTS1)
	$(CC) -o $@ $^

reply_admin : $(OBJECTS2)
	$(CC) -o $@ $^

minesweeper : $(OBJECTS3)
	$(CC) -o $@ $^

creative_stone : $(OBJECTS4)
	$(CC) -o $@ $^

clean : 
	rm -rf $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(TARGETS) 
