#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitset>

typedef unsigned char byte_t;

void frequencyHeap(FILE *, Heap *, int *);
Node *huffmanTree(Heap *, int);
void huffmanCoding(Tree, std::string, std::string *);
bool bitCompare(std::bitset<1>, std::bitset<1>);
Tree code(Heap *, std::string *, int *, FILE *, FILE *, FILE *);
void testing(FILE *, FILE *);
void huffman(FILE *, FILE *, FILE *);
void freeHuffmanTree(Tree);

#endif //HUFFMAN_H
