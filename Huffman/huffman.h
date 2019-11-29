#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitset>

typedef unsigned short byte_t;

class Huffman {
    protected:
        byte_t arr[256] = {0};
        Heap h;
        Tree r;
        std::string codeArr[256] = {""};
        
    public:
        void huffmanTree();
};

class Encoder : public Huffman {
    public:
        void frequencyHeap(FILE *);
        void encode(std::string);
        void code(FILE *, FILE *);
};

class Decoder : public Huffman {
    public:
        void decode(std::string);
        int makeHeap();
};

void huffmanCoding(Tree, std::string, std::string *);
void freeHuffmanTree(Tree);
bool bitCompare(std::bitset<1>, std::bitset<1>);

#endif //HUFFMAN_H
