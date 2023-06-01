#include <iostream>
#include "ActiveObject.hpp"
#include <cmath>
#include <time.h>
#include <unistd.h>
#include "ActiveObject.hpp"

int isPrime(unsigned int num){
    if (num % 2 == 0){
        return 0;
    }
    int round_sqrt = (int) sqrt(num);
    for (int i = 3; i < round_sqrt + 1; i++){
        if (num % i == 0){
            return 0;
        }
    }
    return 1;
}

void generateNumberAndPass(TSQueue *targetQueue, void *voidN){
    int *n = static_cast<int*> (voidN);
    int numToGenerate = *n;
    int **generatedNumbers = new int*[numToGenerate];
    for (int i = 0; i < numToGenerate; i++){
        std::string firstHalf = std::to_string(rand() % 900 + 100);
        std::string secondtHalf = std::to_string(rand() % 900 + 100);
        std::string generatedNumberStr = firstHalf + secondtHalf;
        int generatedNumber = std::stoi(generatedNumberStr);
        generatedNumbers[i] = new int(generatedNumber);
    }
    for (int i = 0; i < numToGenerate; i++){
        targetQueue->push(generatedNumbers[i]);
        usleep(1);
    }
}

void addEleven(TSQueue *targetQueue, void* voidNum){
    int* numPtr = static_cast<int*>(voidNum);
    int num = *numPtr;
    std::cout << num << std::endl;
    int isPrimeNum = isPrime(uint(num));
    if (isPrimeNum){
        std::cout << "True" << std::endl;
    }else{
        std::cout << "False" << std::endl;
    }
    *numPtr = *numPtr + 11;
    targetQueue->push(numPtr);
}

void subThirteen(TSQueue *targetQueue, void* voidNum){
    int* numPtr = static_cast<int*>(voidNum);
    int num = *numPtr;
    std::cout << num << std::endl;
    int isPrimeNum = isPrime(uint(num));
    if (isPrimeNum){
        std::cout << "True" << std::endl;
    }else{
        std::cout << "False" << std::endl;
    }
    *numPtr = *numPtr - 13;
    targetQueue->push(numPtr);
}

void addTwo(TSQueue *targetQueue, void* voidNum){
    int* numPtr = static_cast<int*>(voidNum);
    std::cout << *numPtr << std::endl;
    *numPtr = *numPtr + 2;
    int num = *numPtr;
    std::cout << num << std::endl;
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

int main(int argc, char* argv[]){
    ActiveObject* pipeline[4];
    int n;
    unsigned int seed;
    n = atoi(argv[1]);
    if (argc == 3){
        seed = (unsigned int) atoi(argv[2]);
    }else{
        seed = time(NULL);
    }
    srand(seed);
    pipeline[0] = CreateActiveObject(generateNumberAndPass);
    pipeline[1] = CreateActiveObject(addEleven);
    pipeline[2] = CreateActiveObject(subThirteen);
    pipeline[3] = CreateActiveObject(addTwo);
    pipeline[0]->next = pipeline[1];
    pipeline[1]->next = pipeline[2];
    pipeline[2]->next = pipeline[3];
    

    pipeline[0]->queue->push(new int(n));
    sleep(3);
}