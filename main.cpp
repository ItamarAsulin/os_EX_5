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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::string lastOutput = getCurrentOutput();
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string currentOutput = getCurrentOutput();
        if (currentOutput == lastOutput) {
            // Output remains the same, so exit the loop
            break;
        } else {
            // Output has changed, update the lastOutput and continue the loop
            lastOutput = currentOutput;
        }
        // Wait for a short duration before checking again
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}