#ifndef ThreadSafeQueue_HPP
#define ThreadSafeQueue_HPP

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>


class TSQueue{
    private:
      std::queue<void *> q;
      std::mutex mut;
      std::condition_variable cond;

    public:
        TSQueue();
        void push (void* num);
        void* dequeue();
        int size();
};


#endif 