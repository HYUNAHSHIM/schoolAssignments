all : readerwriter philosopher

readerwriter : readerwriter.c
	gcc -o readerwriter readerwriter.c -pthread

philosopher : philosopher.c
	gcc -o philosopher philosopher.c -pthread

clean :
	rm readerwriter philosopher
