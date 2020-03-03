#include <iostream>
#include <sstream>

void ctoi(int *, int, char **);
void printArr(int *, int);
void printArrN(int *, int, int);
void median(int *, int, int);
int  part(int *, int, int);
void quick_sort(int *, int, int);

int main(int argc, char *argv[]) {
    /* CHAR TO INT */
    int size = --argc;
    int arr[size];
    
    ctoi(arr, size, argv);
    /* END OF CHAR TO INT */

    printArr(arr, size);

    std::cout << "\nApplying Quick Sort...\n" << std::endl;

    quick_sort(arr, 0, size-1);

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

void printArrN(int *arr, int begin, int end) {
    if(begin > end)
        return;
    
    std::cout << "\nArray: {";

    for(int i = begin ; i <= end; i++)
        if(i != end)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
}

void median(int *arr, int a, int c) {
    int b = (a+c)/2;
    int m;
    
    if(a < b) {
        if(b < c)
            m = b;
        else {
            if(a < c)
                m = c;
            else
                m = a;
        }
    }
    else {
        if(c > b) {
            if(a > c)
                m = c;
            else
                m = a;
        }
        else
            m = b;
    }
    
    std::swap(arr[m], arr[c]);
}

int part(int *arr, int begin, int end) {
    int v = begin;
    
    median(arr, begin, end);
    
    int pivot = end;
    
    for(int i = begin; i < end; i++)
        if(arr[i] < arr[pivot])
            std::swap(arr[i], arr[v++]);
    
    std::swap(arr[v], arr[end]);
    
    return v;
}

void quick_sort(int *arr, int i, int j) {
    if(i >= j)
        return;
    
    int m = part(arr, i, j);
    
    quick_sort(arr, i, m-1);
    quick_sort(arr, m+1, j);
}
