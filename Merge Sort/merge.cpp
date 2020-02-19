#include <iostream>
#include <sstream>

void ctoi(int *, int, char **);
void printArr(int *, int);
void inter(int *, int, int, int);
void merge_sort(int *, int, int);

int main(int argc, char *argv[]) {
    /* CHAR TO INT */
    int size = --argc;
    int arr[size];
    
    ctoi(arr, size, argv);
    /* END OF CHAR TO INT */
    
    std::cout << std::endl;
    
    printArr(arr, size);

    std::cout << "\nApplying Merge Sort...\n" << std::endl;

    merge_sort(arr, 0, size-1);

    std::cout << "Done\n" << std::endl;

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
    std::cout << "Array: {";

    for(int i = 0 ; i < size; i++)
        if((i+1) != size)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
}

void inter(int *arr, int i, int mid, int end) {
    int size = end-i+1;
    int begin = i;
    int sArr[size];
    int j = mid+1;
    int k = 0;
    
    while(i <= mid && j <= end)
        if(arr[i] > arr[j])
            sArr[k++] = arr[j++];
        else
            sArr[k++] = arr[i++];
    
    while(i <= mid) 
        sArr[k++] = arr[i++];
    
    while(j <= end) 
        sArr[k++] = arr[j++];
    
    for(k = begin; k <= end; arr[k] = sArr[k-begin], k++);
}

void merge_sort(int *arr, int i, int j) {
    int mid = (i+j)/2;
    
    if(i >= j)
        return;
        
    merge_sort(arr, i, mid);
    merge_sort(arr, (mid+1), j);
    
    inter(arr, i, mid, j);
}
