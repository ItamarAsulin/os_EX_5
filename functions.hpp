#include <iostream>
#include <cmath>
// #include <time.h>
#include <unistd.h>
#include "ThreadSafeQueue.hpp"

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
    int num = *numPtr;
    std::cout << num << std::endl;
    int isPrimeNum = isPrime(uint(num));
    if (isPrimeNum){
        std::cout << "True" << std::endl;
    }else{
        std::cout << "False" << std::endl;
    }
    *numPtr = *numPtr + 2;
    std::cout << *numPtr << std::endl;
}