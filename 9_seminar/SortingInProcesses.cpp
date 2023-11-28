#include <unistd.h>
#include <fstream>
#include <__random/random_device.h>
#include <random>
#include "sorting.hpp"

#define N 1000

void writeToFile(int* array, char* fileName){
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; ++i) {
        outputFile << array[i] << std::endl;
    }
    outputFile.close();
}

int main(){
    int* array = new int[N];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, N - 1);

    for (int i = 0; i < N; ++i) {
        array[i] = dis(gen);
    }

    if(!fork()){
        if(!fork()){
            if(!fork()){
                bubbleSort(array, N);
                writeToFile(array, "bubbleSort.txt");
            }
            shellSort(array, N);
            writeToFile(array, "shellSort.txt");
        }
        quickSort(array, 0, N-1);
        writeToFile(array, "qSort.txt");
    } else{
        //papasha
        writeToFile(array, "initial.txt");
    }

    return 0;
}