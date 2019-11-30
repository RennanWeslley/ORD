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
        Heap hCopy;
        Tree r;
        std::string codeArr[256] = {""};
        
        void freeHuffmanTree(Tree);
        
    public:
        void huffmanTree();
        std::string codeString();
        void freeTree();
        
        Heap getHeap();
        Tree getTree();
};

class Encoder : public Huffman {
    public:
        void makeHeap(FILE *);
        void encode(std::string);
        void code(FILE *, FILE *);
};

class Decoder : public Huffman {
    public:
        int makeHeap();
        void decode(std::string);
        void dcode(FILE *, FILE *);
};

void huffmanCoding(Tree, std::string, std::string *);
bool bitCompare(std::bitset<1>, std::bitset<1>);

#endif //HUFFMAN_H
