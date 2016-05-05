#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool
{
 public:
  ThreadPool(size_t thread_count);

  void enqueue(function<void(void*)> f, void *args);

  ~ThreadPool();

 private:
  vector<thread> workers;

  deque<function<void()>> tasks;

  static void* execute(void *);

  mutex deque_lock;

  mutex condition_lock;
  condition_variable condition;

  bool stop;
};

#endif
