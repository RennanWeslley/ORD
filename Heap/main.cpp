#include "heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define HEAPCOMP 256000

void doSort(int *, int);

int main(int argc, char *argv[]) {
    std::stringstream *d;
    
    if(argc > 2) {
        int arr[argc-1];
        
        for(int i = 1; i < argc; i++) {
            d = new std::stringstream(argv[i]);
            *d >> arr[i-1];
        }
        
        doSort(arr, (argc-1));
        
        return 1;
    }
    
    char arq[] = "files/";
    strcat(arq, argv[1]);
    
    FILE *f = fopen(arq, "r");
    
    if(!f) {
        std::cerr << "Arquivo não pôde ser aberto" << std::endl;
        return 0;
    }
    
    char s[1024];
    int arr[HEAPCOMP];
    int size = 0;
    
    while(true) {
        fgets(s, 1024, f);
    
        if(!s) {
            std::cerr << "Linha não pôde ser lida" << std::endl;
            return 0;
        }
    
        d = new std::stringstream(s);
        *d >> arr[size++];
        
        if(feof(f))
            break;
    }
    
    fclose(f);
    
    doSort(arr, size);
    
    char sorted[] = "files/sorted-";
    strcat(sorted, argv[1]);
    
    f = fopen(sorted, "w");
    
    if(!f) {
        std::cerr << "Arquivo não pôde ser criado" << std::endl;
        return 0;
    }
    
    char aux[50];
    
    for(int i = 0; i < size; i++) {
        sprintf(aux, "%d\n" , arr[i]);
        
        fputs(aux, f);
    }
    
    fclose(f);
    
    std::cout << "Arquivo ordenado gerado." << std::endl;   
    
    return 0;
}

void doSort(int *arr, int size) {
    std::cout << "\nArray...: ";
    print(arr, size);
        
    std::cout << "\nHeaping...\n\nMax Heap: ";
        
    heapSort(arr, size);
    
    std::cout << "\nHeapSorting...\n\nSorted..: ";
    print(arr, size);

    std::cout << std::endl;
}
