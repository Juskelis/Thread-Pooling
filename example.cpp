#include "ThreadPool.h"
#include <iostream>
#include <thread>

using namespace std;

struct myArgs
{
	string myMessage;
	int myNumber;
};

void threadPooledMethod(void* arguments);

int main()
{
	int NUMBER_OF_THREADS = 5;
	int NUMBER_OF_REQUESTS = NUMBER_OF_THREADS * 5;
	ThreadPool myPool(NUMBER_OF_THREADS);
	
	for(int i = 0; i < NUMBER_OF_REQUESTS; i++)
	{
		myArgs* args = new myArgs;
		args -> myMessage = "Hello";
		args -> myNumber = i;
		myPool.enqueue(threadPooledMethod, (void*)args);
	}

	cin.ignore();

	return 0;
}

void threadPooledMethod(void* arguments)
{
	myArgs* args = (myArgs*)arguments;
	cout << "Message: " << args->myMessage << ":" << args->myNumber << endl;
}
