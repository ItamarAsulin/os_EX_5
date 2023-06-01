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

namespace os{
    void printTest(){
        std::cout << "HI FROM PRINT TEST" << std::endl;
    }

    // void busyLoop(ActiveObject *object){
    //     std::cout << "started busy loop" << std::endl;
    //     void *task;
    //     while(object->isActive){
    //         while((task = object->queue->dequeue()) != nullptr){
    //             object->func(std::ref(object->next->queue),task);
    //             // validate object thread is still active;
    //             break;
    //         }
    //     }
    // }
    // ActiveObject *CreateActiveObject(FunctionPtrType targetFunc){
    //     std::cout << "Creating Active Object" << std::endl;
    //     ActiveObject *toReturn = new ActiveObject(targetFunc);
    //     std::cout << "Created Active Object" << std::endl;

    //     toReturn->isActive = true;
    //     std::cout << "before thread" << std::endl;

    //     std::thread myThread (busyLoop, toReturn);
    //     myThread.join();
    //     std::cout << "after thread" << std::endl;
    //     return toReturn;
    // }

    // TSQueue * getQueue(ActiveObject *object){
    //     return object->queue;
    // }

    // void stop(ActiveObject *object){
    //     object->isActive = false;
    // }
}