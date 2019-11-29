#include "huffman.h"

int main(int argc, char *argv[]) {
    /* HUFFMAN */
    Encoder c;
    Decoder d;
    
    c.encode(std::string(argv[1]));
    d.decode(std::string(argv[1]));
    
    return 0;
}
