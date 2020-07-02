all : peterson_algorithm ex child

peterson_algorithm : peterson_algorithm.cpp
	g++ -o peterson_algorithm peterson_algorithm.cpp -pthread

ex : parent.c
	gcc -o ex parent.c

child : child.c
	gcc -o child child.c

clean :
	rm peterson_algorithm ex child