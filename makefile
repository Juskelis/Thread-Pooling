CFLAGS = -ansi -Wall -Werror -pedantic -std=c++11

all: ThreadPool

ThreadPool: ThreadPool.h ThreadPool.cpp
	g++ $(CFLAGS) -c ThreadPool.cpp -o ThreadPool

clean:
	rm -f *.o
	rm -f *.out
	rm -f ThreadPool
