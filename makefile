CFLAGS = -ansi -Wall -Werror -pedantic -std=c++11

all: ThreadPool Example

ThreadPool: ThreadPool.h ThreadPool.cpp
	g++ $(CFLAGS) -c ThreadPool.cpp -o ThreadPool

Example: main.cpp ThreadPool
	g++ $(CFLAGS) main.cpp ThreadPool -o Example

clean:
	rm -f *.o
	rm -f *.out
	rm -f ThreadPool
	rm -f Example
