CFLAGS = -ansi -Wall -Werror -pedantic -std=c++11 -lpthread

all: ThreadPool Example

ThreadPool: ThreadPool.h ThreadPool.cpp
	g++ $(CFLAGS) -c ThreadPool.cpp -o ThreadPool

Example: example.cpp ThreadPool
	g++ $(CFLAGS) example.cpp ThreadPool -o Example

clean:
	rm -f *.o
	rm -f *.out
	rm -f ThreadPool
	rm -f Example
