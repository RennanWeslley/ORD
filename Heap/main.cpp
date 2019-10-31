#include "heap.h"

int main(int argc, char *argv[]) {
    int arr[argc-1];
    std::stringstream *d;
    
    for(int i = 1; i < argc; i++) {
        d = new std::stringstream(argv[i]);
        *d >> arr[i-1];
    }
    
    std::cout << "\nArray...: {";
    for(int i = 0 ; i < (argc-1); i++)
        if((i+1) != (argc-1))
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
        
    std::cout << "\nHeaping...\n\nMax Heap: ";
        
    heapSort(arr, (argc-1));
    
    std::cout << "\nHeapSorting...\n\nSorted..: {";
    for(int i = 0 ; i < (argc-1); i++)
        if((i+1) != (argc-1))
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;

    
    std::cout << std::endl;
        
    return 0;
}
