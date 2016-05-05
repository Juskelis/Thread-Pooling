#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t thread_count)
{
  this -> stop = false;

  for(size_t i = 0; i < thread_count; i++) {
	this -> workers.push_back(thread(&ThreadPool::execute, (void*)this)); 
  }
}

ThreadPool::~ThreadPool()
{
  
  this -> stop = true;

  //get condition lock
  this -> condition_lock.lock();

  condition.notify_all();

  this -> condition_lock.unlock();
  //release condition lock

  for(size_t i = 0; i < this -> workers.size(); i++) {
	this -> workers[i].join();
  }
  
}

void ThreadPool::enqueue(function<void(void *)> to_call, void *arguments)
{
  
  //get deque lock
  this -> deque_lock.lock();

  this -> tasks.push_back([to_call, arguments]{
	  to_call(arguments);
	});
  
  this -> deque_lock.unlock();
  //release deque lock

  //get condition lock
  {
	unique_lock<mutex> condition_ulock(this -> condition_lock);
	
	condition.notify_one();
  }
  //release condition lock
  
}

void* ThreadPool::execute(void *args)
{

  ThreadPool* us = (ThreadPool*)args;

  function<void()> task;
  while(true) {

	//get condition lock
	{
	  unique_lock<mutex> condition_ulock(us -> condition_lock);
	  while(!us -> stop && us -> tasks.empty()) {
		us -> condition.wait(condition_ulock);
	  }
	  
	}
	//release condition lock

	if(us -> stop) return NULL;

	//get deque lock
	us -> deque_lock.lock();

	task = us -> tasks.front();
	us -> tasks.pop_front();

	us -> deque_lock.unlock();
	//release deque lock

	task();
  }

}

