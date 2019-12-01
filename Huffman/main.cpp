#include "huffman.h"

int main(int argc, char *argv[]) {
    /* HUFFMAN */
    Encoder c;
    Decoder d;
    
    c.code(std::string(argv[1]));
    d.code(std::string(argv[1]));
    
    c.freeTree();
    d.freeTree();
    
    return 0;
}
