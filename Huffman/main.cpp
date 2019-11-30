#include "huffman.h"

int main(int argc, char *argv[]) {
    /* HUFFMAN */
    Encoder c;
    Decoder d;
    
    c.encode(std::string(argv[1]));
    d.decode(std::string(argv[1]));
    
    /*
    isEqualH(c.getHeap(), d.getHeap())? std::cout << "Heaps iguais" : std::cout << "Heaps diferentes";
    std::cout << std::endl;
    isEqual(c.getTree(), d.getTree())? std::cout << "Arvores iguais" : std::cout << "Arvores diferentes";
    std::cout << std::endl;
    */
    
    c.freeTree();
    d.freeTree();
    
    return 0;
}
