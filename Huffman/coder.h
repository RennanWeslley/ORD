#ifndef coder_H
#define coder_H

#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitset>

typedef unsigned short byte_t;

class Coder {
    protected:
        byte_t arr[256] = {0};
        Heap h;
        Tree r;
        
        void freeHuffmanTree(Tree);
        virtual void doCode(FILE *, FILE *) = 0;
        
    public:
        virtual void frequency(FILE *) = 0;
        virtual void makeHeap(FILE *)  = 0;
        void huffmanTree();
        void freeTree();
        virtual void code(std::string) = 0;
        
        Tree getTree();
};

bool bitCompare(std::bitset<1>, std::bitset<1>);

#endif //coder_H
