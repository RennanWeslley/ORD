#include <iostream>
#include <sstream>

#define MAX 100

void ctoi(int *, int, char **);
void printArr(int *, int);
void counting_sort(int *, int);

int main(int argc, char *argv[]) {
    /* CHAR TO INT */
    int size = --argc;
    int arr[size];
    
    ctoi(arr, size, argv);
    /* END OF CHAR TO INT */

    printArr(arr, size);

    std::cout << "\nApplying Counting Sort...\n" << std::endl;

    counting_sort(arr, size);

    std::cout << "Done" << std::endl;

    printArr(arr, size);	

    return 0;
}

void ctoi(int *arr, int size, char *argv[]) {
    std::stringstream *d;
    size++;
    
    for(int i = 1; i < size; i++) {
        d = new std::stringstream(argv[i]);
        *d >> arr[i-1];
    }
}

void printArr(int *arr, int size) {
    std::cout << "\nArray: {";

    for(int i = 0 ; i < size; i++)
        if((i+1) != size)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
}

void counting_sort(int *arr, int size) {
    int c[MAX]    = {0};
    int aux[size] = {0};
    
    for(int i = 0; i < size; c[arr[i++]]++);
    for(int i = 1; i < MAX; c[i] += c[i-1], i++);
    for(int i = 0; i < size; aux[c[arr[i]]-- -1] = arr[i], i++);
    
    std::copy(aux, aux+size, arr);
}
