#include "ActiveObject.hpp"

ActiveObject::ActiveObject(FunctionPtrType func){
    this->queue = new TSQueue();
    this->isActive = false;
    this->next = nullptr;
    this->func = func;
}

ActiveObject::~ActiveObject(){
    delete(this->queue);
    this->next = nullptr;
    this->func = nullptr;
}
void busyLoop(ActiveObject *object){
    void *task;
    while(object->isActive){
        
        while((task = object->queue->dequeue()) != nullptr){
            if(object->next != nullptr){
                object->func(object->next->queue,task);
            }else{
                object->func(nullptr,task);
            }
            // validate object thread is still active;
            break;
        }
    }
}
ActiveObject *CreateActiveObject(FunctionPtrType targetFunc){
    FunctionPtrType* ptr = new FunctionPtrType(targetFunc);
    ActiveObject *toReturn = new ActiveObject(*ptr);
    toReturn->isActive = true;
    std::thread myThread (busyLoop, toReturn);
    myThread.detach();
    return toReturn;
}
TSQueue * getQueue(ActiveObject *object){
    return object->queue;
}
void stop(ActiveObject *object){
    object->isActive = false;
}