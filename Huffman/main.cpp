#include "huffman.h"

void test(Heap *);

int main(int argc, char *argv[]) {
    /* HUFFMAN */
    Encoder c;
    Decoder d;
    
    c.encode(std::string(argv[1]));
    d.decode(std::string(argv[1]));
    
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
