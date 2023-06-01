#include "ActiveObject.hpp"
#include "functions.hpp"

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