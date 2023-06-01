#ifndef ACTIVEOCJECT_HPP
#define ACTIVEOCJECT_HPP

#include "ThreadSafeQueue.hpp"
# include <thread>

class ActiveObject;

typedef void (*FunctionPtrType)(TSQueue *,void *);
class ActiveObject{
    public:
        TSQueue *queue;
        ActiveObject *next;
        FunctionPtrType func;
        bool isActive;
        ActiveObject(){};
        ActiveObject(FunctionPtrType func);
        ~ActiveObject();
        // static void printTest();
        // static void run();
};

// namespace os{
//     ActiveObject *CreateActiveObject(FunctionPtrType targetFunc);
//     TSQueue * getQueue(ActiveObject *object);
//     void stop(ActiveObject *object);
// }
#endif