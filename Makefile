all: test5 ListLinked
	g++ -o test5 test5.o ListLinked.o

test5: test5.cpp
	g++ -c test5.cpp

ListLinked: ListLinked.cpp ListLinked.h
	g++ -c ListLinked.cpp
