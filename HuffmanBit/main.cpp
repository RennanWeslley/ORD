#include "huffman.h"

void test(Heap *);

int main(int argc, char *argv[]) {
    FILE *f = fopen("files/laptop.txt", "r");              /* ORIGINAL FILE */
    FILE *newF = fopen("files/laptopCoded.txt", "w+b");     /* COMPRESSED FILE */
    FILE *test = fopen("files/laptopCodedTest.txt", "w+b"); /* CODING TEST FILE */
    
    /* HUFFMAN */
    huffman(f, newF, test);
    
    fclose(test);
    fclose(newF);
    fclose(f);
    
    return 0;
}

void test(Heap *h) {
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
    
    h->build_min_heap();
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
}
