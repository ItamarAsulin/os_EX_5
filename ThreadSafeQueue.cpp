#include "ThreadSafeQueue.hpp"

TSQueue::TSQueue(){}

void TSQueue::push (void *num){
    std::unique_lock<std::mutex> lock(this->mut);
    this->q.push(num);
    this->cond.notify_one();
}
void* TSQueue::dequeue() {
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [this]() {
        return !q.empty();
    });

    void* num = q.front();
    q.pop();

    return num;
}


int TSQueue::size(){
    return this->q.size();
}

