#include <iostream>
#include <sstream>
#include <limits.h>

void ctoi(int *, int, char **);
void printArr(int *, int);
void selection_sort(int *, int);

int main(int argc, char *argv[]) {
    /* CHAR TO INT */
    int size = --argc;
    int arr[size];
    
    ctoi(arr, size, argv);
    /* END OF CHAR TO INT */

    printArr(arr, size);

    std::cout << "\nApplying Selection Sort...\n" << std::endl;

    selection_sort(arr, size);

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

void selection_sort(int *arr, int size) {
    int lower = INT_MAX;
    int lPos  = 0;

    for(int i = 0; i < size; lower = INT_MAX, i++) {
        for(int j = i; j < size; j++)
            if(arr[j] < lower) {
                lower = arr[j];
                lPos  = j; 
            }
        
        std::swap(arr[i], arr[lPos]);
    }
}

