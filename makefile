proj5: process.o stack.o
	g++ -o proj5 process.o stack.o

process.o: process.cpp proj5.h
	g++ -c process.cpp

stack.o: stack.cpp proj5.h
	g++ -c stack.cpp


